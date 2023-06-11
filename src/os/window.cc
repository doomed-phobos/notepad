#include "os/window.h"

#ifdef NOTEPAD_UNIX
#  include "os/priv/x11/window.h"
#else
#  include "os/priv/win/window.h"
#endif

namespace os {
   Window::Window() :
      m_base{nullptr} {}

   Window::~Window() {
      delete m_base;
   }

   void Window::focus() {
      m_base->focus();
   }

   void Window::invalidate() {
      m_base->invalidate();
   }

   void Window::setTitle(const char* title) {
      m_base->setTitle(title);
   }

   void Window::run() {
      m_base->run();
   }

   std::shared_ptr<Window> Window::Make(int w, int h) {
      std::shared_ptr<Window> win(new Window());

      #ifdef NOTEPAD_UNIX
      auto base = X11Window::Make(*win, w, h);
      if(base) {
         win->m_base = base;
         return win;
      }
      #else
      // auto base = WinWindow::Make(w, h);
      #endif
      
      return nullptr;
   }
} // namespace os