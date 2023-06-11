#include "os/priv/x11.h"

namespace os::priv {
   X11::X11() {
      m_display = XOpenDisplay(nullptr);
   }

   X11::~X11() {
      if(m_display)
         XCloseDisplay(m_display);
      m_display = nullptr;
   }

   X11* X11::GetInstance() {
      static X11 s_instance;
      
      return &s_instance;
   }

   ::Display* const X11::display() const {return m_display;}
} // namespace os::priv 