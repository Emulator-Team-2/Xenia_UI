/**
******************************************************************************
* Xenia : Xbox 360 Emulator Research Project                                 *
******************************************************************************
* Copyright 2015 Ben Vanik. All rights reserved.                             *
* Released under the BSD license - see LICENSE in the root for more details. *
******************************************************************************
*/

#ifndef XENIA_BASE_CHANNEL_H_
#define XENIA_BASE_CHANNEL_H_

#include <memory>
#include <string>

namespace xe {
namespace base {

// Communications channel
class Channel {
  public:
    virtual ~Channel() = default;

    static std::unique_ptr<Channel> OpenPipe(const std::wstring& name);

    virtual void SetBlocking(bool blocking) = 0;
    virtual bool IsBlocking() { return blocking_; }

    virtual int Read(uint8_t *buffer, uint32_t bufSize) = 0;
    virtual int Write(uint8_t *buffer, uint32_t numBytes) = 0;

    enum tChannelType {
      kChannelPipe = 0,
      kChannelSocket = 1,
    };

  protected:
    Channel(tChannelType type) { type_ = type; }

    tChannelType type_;
    bool blocking_;
};

}  // namespace base
}  // namespace xe

#endif  // XENIA_BASE_CHANNEL_H_
