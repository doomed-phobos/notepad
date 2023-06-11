#pragma once
#include <cstdint>

namespace base {
   typedef int64_t tick_t;

   /// @brief Obtener el tick actual del sistema en microsegundos
   tick_t get_current_tick();
} // namespace base