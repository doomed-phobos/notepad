#include "os/priv/x11/x11.h"

#include "os/event.h"

#include <cstring>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

namespace os {
   class Window::X11Window {
   public:
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

      void run(const Window& parent) {
         XEvent ev;
         bool run = true;
         while(run) {
            XNextEvent(m_xdisplay, &ev);

            switch(ev.type) {
               case ClientMessage:
                  if(ev.xclient.message_type == WM_PROTOCOLS &&
                     Atom(ev.xclient.data.l[0]) == WM_DELETE_WINDOW) {
                     parent.onExit();
                     run = false;
                  }
               break;
               case ButtonPress:
               case ButtonRelease: {
                  MouseEvent mev;
                  mev.pos = {ev.xbutton.x, ev.xbutton.y};
                  mev.modifiers = get_key_modifiers(ev.xbutton.state);

                  if(is_mouse_wheel_button(ev.xbutton.button)) {
                     if(ev.type == ButtonPress) {
                        mev.delta = get_mouse_wheel_delta(ev.xbutton.button);
                        parent.onMouseWheel(mev);
                     }
                  } else {
                     mev.button = get_mouse_button(ev.xbutton.button);

                     if(ev.type == ButtonPress)
                        parent.onMouseDown(mev);
                     else if(mev.button)
                        parent.onMouseUp(mev);
                  }
               }
               break;
               case MotionNotify: {
                  MouseEvent mev;
                  mev.modifiers = get_key_modifiers(ev.xmotion.state);
                  mev.pos = {ev.xmotion.x, ev.xmotion.y};
                  parent.onMouseOver(mev);
               }
               break;
            }
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
         XSelectInput(xdisplay, xwin, ExposureMask | PointerMotionMask | ButtonPressMask |
                                      ButtonReleaseMask | KeyPressMask | KeyReleaseMask);

         X11Window* win = new X11Window(xdisplay, xwin);
         win->focus();
         
         return win;
      }

   private:
      static inline bool is_mouse_wheel_button(const int button) {
         return (button == Button4 || button == Button5 ||
                 button == 6 || button == 7);
      }

      static inline char get_mouse_wheel_delta(const int button) {
         switch(button) {
            case Button4: return -1;
            case Button5: return +1;
            default:      return 0;
         }
      }

      static inline MouseEvent::Button get_mouse_button(const int button) {
         switch(button) {
            case Button1: return MouseEvent::kLeft_Button;
            case Button2: return MouseEvent::kMiddle_Button;
            case Button3: return MouseEvent::kRight_Button;
            default:      return MouseEvent::kUnknown_Button;
         }
      }

      static inline KeyModifiers get_key_modifiers(const int state) {
         int modifiers = kNone_KeyModifiers;
         if(state & ShiftMask)                          modifiers |= kShift_KeyModifiers;
         if(state & ControlMask)                      modifiers |= kCtrl_KeyModifiers;
         if(state & (Mod1Mask | Mod5Mask))  modifiers |= kAlt_KeyModifiers;
         if(state & Mod4Mask)                            modifiers |= kWin_KeyModifiers;

         return (KeyModifiers)modifiers;
      }

      static inline Atom WM_DELETE_WINDOW = 0;
      static inline Atom WM_PROTOCOLS = 0;
      ::Window m_xwin;
      ::Display* const m_xdisplay;
   };

} // namespace os