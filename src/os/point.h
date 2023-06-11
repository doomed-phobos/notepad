#pragma once
#include <type_traits>

namespace os {
   template<typename T,
      std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
   struct PointT {
      PointT() :
         x{}, y{} {}
      PointT(const T& x, const T& y) :
         x{x}, y{y} {}
      template<typename U,
         std::enable_if_t<std::is_convertible_v<U, T>, int> = 0>
      PointT(const PointT<U>& pt) :
         x{pt.x}, y{pt.y} {}

      PointT& operator+=(const PointT& pt) {
         x += pt.x;
         y += pt.y;
         return *this;
      }

      PointT operator+(const PointT& pt) const {
         return {x + pt.x, y + pt.y};
      }

      PointT& operator=(const PointT& pt) {
         x = pt.x;
         y = pt.y;
         return *this;
      }

      T x, y;
   };

   typedef PointT<int> Point;
} // namespace os