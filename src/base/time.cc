#include "base/time.h"

#include <chrono>

namespace base {
   tick_t get_current_tick() {
      using namespace std::chrono;

      return time_point_cast<milliseconds>(steady_clock::now()).time_since_epoch().count();
   }
} // namespace base