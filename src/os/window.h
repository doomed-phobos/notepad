#pragma once
#include "base/signal.h"
#include "os/point.h"

#include <memory>

class SkCanvas;

namespace os {
   struct MouseEvent;

   class Window {
   public:
      ~Window();

      void focus();
      void setTitle(const char* title);
      void invalidate();
      void run();

      base::Signal<void()> onExit;
      base::Signal<void(const MouseEvent&)> onMouseOver;
      base::Signal<void(const MouseEvent&)> onMouseDown;
      base::Signal<void(const MouseEvent&)> onMouseUp;
      base::Signal<void(const MouseEvent&)> onMouseWheel;
      base::Signal<void(const Point& /*size*/)> onResize;
      base::Signal<void(SkCanvas* const)> onPaint;

      static std::shared_ptr<Window> Make(int w, int h);
   private:
      #ifdef NOTEPAD_UNIX
      class X11Window;
      typedef X11Window WindowBase;
      #elif defined(NOTEPAD_WIN)
      class WinWindow;
      typedef WinWindow WindowBase;
      #else
      #  error "No existe una compatibilidad con su sistema"
      #endif

      WindowBase* m_base;
      // SkCanvas* m_canvas;
   };
} // namespace os