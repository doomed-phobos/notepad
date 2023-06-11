#pragma once
#include "base/signal.h"

#include <memory>

namespace os {
   class Window {
   public:
      ~Window();

      void focus();
      void setTitle(const char* title);
      void run();

      base::Signal<void()> onExit;

      static std::shared_ptr<Window> Make(int w, int h);
   private:
      #ifdef NOTEPAD_UNIX
      struct X11Window;
      typedef X11Window WindowBase;
      #elif defined(NOTEPAD_WIN)
      struct WinWindow;
      typedef WinWindow WindowBase;
      #else
      #  error "No existe una compatibilidad con su sistema"
      #endif

      Window(WindowBase* base) :
         m_base{base} {}

      WindowBase* m_base;
   };
} // namespace os