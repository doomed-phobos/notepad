#pragma once
#include "os/point.h"
#include "os/keys.h"

namespace os {
   struct MouseEvent {
      enum Button {
         kNone_Button = 0,
         kLeft_Button,
         kMiddle_Button,
         kRight_Button,
         kUnknown_Button,
      };

      MouseEvent() :
         button{kNone_Button},
         delta{0},
         modifiers{kNone_KeyModifiers} {}

      Button button;
      Point pos;
      char delta : 2;
      int modifiers;
   };
} // namespace os