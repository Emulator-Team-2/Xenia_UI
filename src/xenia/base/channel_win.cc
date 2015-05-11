/**
******************************************************************************
* Xenia : Xbox 360 Emulator Research Project                                 *
******************************************************************************
* Copyright 2015 Ben Vanik. All rights reserved.                             *
* Released under the BSD license - see LICENSE in the root for more details. *
******************************************************************************
*/

#include "xenia/base/channel.h"

#include <Windows.h>

#include <memory>
#include <mutex>
#include <vector>

#include "xenia/base/logging.h"
#include "xenia/base/math.h"

namespace xe {
namespace base {

// Communications channel
// Win32 file pipe
class Win32ChannelPipe : public Channel {
  public:
    Win32ChannelPipe(const std::wstring &name);
    virtual ~Win32ChannelPipe() = default;

    virtual void SetBlocking(bool blocking);

    virtual int Read(uint8_t *buffer, uint32_t bufSize);
    virtual int Write(uint8_t *buffer, uint32_t numBytes);

  protected:
    HANDLE hPipe_;
    std::wstring name_;
};

// Open function
std::unique_ptr<Channel> Channel::OpenPipe(const std::wstring& name) {
  auto pipe = std::make_unique<Win32ChannelPipe>(name);

  return std::move(pipe);
}

Win32ChannelPipe::Win32ChannelPipe(const std::wstring& name)
        : Channel(kChannelPipe), name_(name) {
  hPipe_ = CreateNamedPipeW(name.c_str(), PIPE_ACCESS_DUPLEX,
                    PIPE_TYPE_MESSAGE, PIPE_UNLIMITED_INSTANCES,
                    2048, 2048, 0, NULL);
}

Win32ChannelPipe::~Win32ChannelPipe() {
  if (hPipe_ != INVALID_HANDLE_VALUE) {
    CloseHandle(hPipe_);
  }
}

void Win32ChannelPipe::SetBlocking(bool blocking) {
  DWORD dwMode = PIPE_READMODE_MESSAGE | (blocking ? PIPE_NOWAIT : 0);
  SetNamedPipeHandleState(hPipe_, &dwMode, NULL, NULL);

  blocking_ = blocking;
}

int Win32ChannelPipe::Read(uint8_t* buffer, uint32_t bufSize) {
  DWORD dwNumBytesRead;
  int ret = ReadFile(hPipe_, buffer, bufSize, &dwNumBytesRead, NULL);
  // Send an error back to the caller as a negative number
  if (ret) {
    return ret > 0 ? -ret : ret;
  }

  return dwNumBytesRead;
}

int Win32ChannelPipe::Write(uint8_t* buffer, uint32_t numBytes) {
  DWORD dwNumBytesWritten;
  int ret = WriteFile(hPipe_, buffer, numBytes, &dwNumBytesWritten, NULL);
  // Send an error back to the caller as a negative number
  if (ret) {
    return ret > 0 ? -ret : ret;
  }

  return dwNumBytesWritten;
}

}  // namespace base
}  // namespace xe