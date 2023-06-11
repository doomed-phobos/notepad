#pragma once

namespace os::priv {
   struct Event {
      enum Type {
         None_Type,
         CloseWindow_Type
      };

      Type type = None_Type;
   };
} // namespace os::priv