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
      struct X11Window;

      Window(X11Window* base) :
         m_base{base} {}

      X11Window* m_base;
   };
} // namespace os