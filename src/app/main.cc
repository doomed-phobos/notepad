#include "os/window.h"
#include "os/event.h"

#include <include/core/SkCanvas.h>

void dump_mouse_event(const os::MouseEvent& ev) {
   printf("Modifiers: %d   Button: %d   Position: (%d, %d)   Delta: %d\n", ev.modifiers, ev.button, ev.pos.x, ev.pos.y, ev.delta);
}

void draw(SkCanvas* const c) {
   c->drawColor(SK_ColorRED);
}

int main() {
   auto win = os::Window::Make(800, 400);
   if(!win) {
      printf("Error al crear ventana");
      return 1;
   }
   win->setTitle("Challenge: Notepad");
   win->onMouseDown.connect(dump_mouse_event);
   win->onMouseUp.connect(dump_mouse_event);
   win->onMouseWheel.connect(dump_mouse_event);
   win->onPaint.connect(draw);
   win->run();

   return 0;
}