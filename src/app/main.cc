#include "os/window.h"

int main() {
   auto win = os::Window::Make(400, 400);
   if(!win)
      return 1;
   win->setTitle("Challenge: Notepad");
   win->run();

   return 0;
}