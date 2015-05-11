/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2015 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_DEBUG_DEBUG_SERVER_H_
#define XENIA_DEBUG_DEBUG_SERVER_H_

#include <string>

#include "xenia/base/channel.h"
#include "xenia/emulator.h"

namespace xe {
namespace debug {

class DebugServer {
  public:
    DebugServer(Emulator* emulator);
    ~DebugServer();

    // Called by the emulator when we're about to be destroyed
    void Shutdown();

  private:
    Emulator* emulator_;
};

}  // namespace debug
}  // namespace xe

#endif  // XENIA_DEBUG_DEBUG_SERVER_H_
