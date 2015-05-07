/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2014 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_BASE_DISC_DEVICE_H_
#define XENIA_BASE_DISC_DEVICE_H_

#include <memory>
#include <string>

namespace xe {

// Helper class for accessing hardware DVD-ROM/CD-ROM
class DiscDevice {
  public:
    virtual ~DiscDevice() = default;

    static std::unique_ptr<DiscDevice> Open(const std::wstring& path);

    // Lock the DVD in the drive
    virtual void Lock(bool locked) = 0;

    // Get sector size in bytes
    virtual uint32_t GetSectorSize() = 0;

    // Get size of disc in bytes
    virtual size_t GetSize() = 0;

    // Seek to address
    virtual void Seek(uint64_t addr) = 0;

    // Read to buffer
    virtual bool Read(uint8_t *buffer, size_t size) = 0;

  protected:
    DiscDevice(const std::wstring& path) : path_(path) {}

    std::wstring path_;
};

}; // namespace xe

#endif // XENIA_BASE_DISC_DEVICE_H_