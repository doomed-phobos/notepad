#pragma once
#include <X11/Xlib.h>

namespace os::priv {
   class X11 {
   public:
      ~X11();

      ::Display* const display() const;

      static X11* GetInstance();
   private:
      X11();

      ::Display* m_display;
   };
} // namespace os::priv