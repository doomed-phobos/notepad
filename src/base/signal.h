#pragma once
#include <functional>
#include <vector>

namespace base {
   template<typename Callable>
   class Signal {};

   template<typename... Args>
   class Signal<void(Args...)> {
   public:
      typedef std::function<void(Args...)> slot_t;

      ~Signal() {
         for(auto& slot : m_slots)
            delete slot;
         m_slots.clear();
      }

      template<typename Fn,
         std::enable_if_t<std::is_convertible_v<Fn, slot_t>, int> = 0> 
      slot_t* const connect(Fn&& fn) {
         auto slot = new slot_t(std::forward<Fn>(fn));
         m_slots.push_back(slot);
         return slot;
      }

      template<class Class>
      slot_t* const connect(void(Class::*m)(Args&&... args), Class* t) {
         auto slot = new slot_t([t, m] (Args&&... args) {(t->*m)(std::forward<Args>(args)...);});
         m_slots.push_back(slot);
         return slot;
      }

      void disconnect(slot_t* slot) {
         for(auto it = m_slots.begin(); it != m_slots.end(); ++it) {
            if(*it == slot) {
               m_slots.erase(it);
               delete *it;
               return;
            }
         }
      }

      void operator()(Args&&... args) {
         for(auto& slot : m_slots)
            (*slot)(std::forward<Args>(args)...);
      }
   private: 
      std::vector<slot_t*> m_slots;
   };
} // namespace base