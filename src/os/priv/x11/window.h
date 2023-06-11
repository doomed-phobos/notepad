#include "os/priv/event.h"
#include "os/priv/x11/x11.h"

#include <cstring>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

namespace os {
   struct Window::X11Window {
      X11Window(::Display* const xdisplay, ::Window xwin) :
         m_xdisplay{xdisplay},
         m_xwin{xwin} {}
      ~X11Window() {
         XDestroyWindow(m_xdisplay, m_xwin);
      }

      void focus() {
         XMapRaised(m_xdisplay, m_xwin);
      }

      void setTitle(const char* title) {
         if(!title)
            return;
         XTextProperty prop;
         prop.value = (unsigned char*)title;
         prop.encoding = XA_STRING;
         prop.format = 8;
         prop.nitems = std::strlen(title);
         XSetWMName(m_xdisplay, m_xwin, &prop);
      }

      void nextEvent(XEvent& ev) {
         XNextEvent(m_xdisplay, &ev);
      }

      void processEvent(XEvent& xev, priv::Event& ev) {
         switch(xev.type) {
            case ClientMessage:
               if(xev.xclient.message_type == WM_PROTOCOLS &&
                  Atom(xev.xclient.data.l[0]) == WM_DELETE_WINDOW)
                  ev.type = priv::Event::CloseWindow_Type;
            break;
         }
      }

      static X11Window* Make(int w, int h) {
         const auto xdisplay = priv::X11::GetInstance()->display();
         auto xwin = XCreateSimpleWindow(
                           xdisplay,
                           XDefaultRootWindow(xdisplay),
                           0, 0,
                           w, h,
                           0,
                           0,
                           0);

         if(!xwin)
            return nullptr;
         if(!WM_DELETE_WINDOW)
            WM_DELETE_WINDOW = XInternAtom(xdisplay, "WM_DELETE_WINDOW", False);
         if(!WM_PROTOCOLS)
            WM_PROTOCOLS = XInternAtom(xdisplay, "WM_PROTOCOLS", False);
         XSetWMProtocols(xdisplay, xwin, &WM_DELETE_WINDOW, 1);
         XSelectInput(xdisplay, xwin, ExposureMask);

         X11Window* win = new X11Window(xdisplay, xwin);
         win->focus();
         
         return win;
      }

      static inline Atom WM_DELETE_WINDOW = 0;
      static inline Atom WM_PROTOCOLS = 0;
      ::Window m_xwin;
      ::Display* const m_xdisplay;
   };
} // namespace os