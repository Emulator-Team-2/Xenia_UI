/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "xenia/base/disc_device.h"

#include <Windows.h>
#include <winioctl.h>
#include <ntddcdrm.h>

#include <memory>
#include <mutex>
#include <vector>

#include "xenia/base/logging.h"
#include "xenia/base/math.h"

namespace xe {

class Win32DiscDevice : public DiscDevice {
  public:
    Win32DiscDevice(const std::wstring& path) : DiscDevice(path) {}
    ~Win32DiscDevice() override {
      if (hDevice_ != INVALID_HANDLE_VALUE) {
        CloseHandle(hDevice_);
      }
    }

    // Lock the DVD in the drive
    virtual void Lock(bool locked);

    // Get sector size in bytes
    virtual uint32_t GetSectorSize();

    // Get size of disc in bytes
    virtual size_t GetSize();

    // Seek to address
    virtual void Seek(uint64_t addr);

    // Read to buffer
    virtual bool Read(uint8_t *buffer, size_t size);

  private:
    friend class DiscDevice;

    std::wstring path;
    HANDLE hDevice_;
};

std::unique_ptr<DiscDevice> DiscDevice::Open(const std::wstring& path) {
  HANDLE hDevice = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hDevice == INVALID_HANDLE_VALUE) {
    return nullptr;
  }

  auto dev = std::make_unique<Win32DiscDevice>();
  dev->hDevice_ = hDevice;

  return std::move(dev);
}

void Win32DiscDevice::Lock(bool locked) {
  DWORD dwUnused;

  PREVENT_MEDIA_REMOVAL pmrLock;
  pmrLock.PreventMediaRemoval = locked;
  DeviceIoControl(hDevice_, IOCTL_CDROM_MEDIA_REMOVAL, &pmrLock,
                  sizeof(pmrLock), NULL, 0, &dwUnused, NULL);
}

uint32_t Win32DiscDevice::GetSectorSize() {
  DWORD dwUnused;

  DISK_GEOMETRY dg;
  if (DeviceIoControl(hDevice_, IOCTL_CDROM_GET_DRIVE_GEOMETRY, NULL, 0,
                      &dg, sizeof(dg), &dwUnused, NULL)) {
    return dg.BytesPerSector;
  }
}

size_t Win32DiscDevice::GetSize() {
  return GetFileSize(hDevice_, NULL);
}

void Win32DiscDevice::Seek(uint64_t addr) {
  SetFilePointer(hDevice_, addr, NULL, FILE_BEGIN);
}

bool Win32DiscDevice::Read(uint8_t *buffer, size_t size) {
  DWORD dwUnused;
  return ReadFile(hDevice_, buffer, size, &dwUnused, NULL);
}

}; // namespace xe