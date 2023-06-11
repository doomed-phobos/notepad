#include "os/window.h"

#ifdef NOTEPAD_UNIX
#  include "os/priv/x11/window.h"
#else
#  include "os/priv/win/window.h"
#endif

namespace os {
   Window::~Window() {
      delete m_base;
   }

   void Window::focus() {
      m_base->focus();
   }

   void Window::setTitle(const char* title) {
      m_base->setTitle(title);
   }

   void Window::run() {
      m_base->run(*this);
   }

   std::shared_ptr<Window> Window::Make(int w, int h) {
      #ifdef NOTEPAD_UNIX
      auto base = X11Window::Make(w, h);
      #else
      // auto base = WinWindow::Make(w, h);
      #endif
      if(!base)
         return nullptr;
      
      return std::shared_ptr<Window>(new Window(base));
   }
} // namespace os