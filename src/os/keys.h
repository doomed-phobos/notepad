#pragma once

namespace os {
   enum KeyModifiers {
      kNone_KeyModifiers    = 0,
      kShift_KeyModifiers   = 1 << 0,
      kCtrl_KeyModifiers    = 1 << 1,
      kAlt_KeyModifiers     = 1 << 2,
      kCmd_KeyModifiers     = 1 << 3,
      kSpace_KeyModifiers   = 1 << 4,
      kWin_KeyModifiers     = 1 << 5,
   };
} // namespace os