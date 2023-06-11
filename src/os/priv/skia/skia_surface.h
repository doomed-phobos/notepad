#pragma once
#include <include/core/SkCanvas.h>
#include <include/core/SkBitmap.h>
#include <include/core/SkImageInfo.h>

#include <stdexcept>

namespace os::priv {
   class SkiaSurface {
   public:
      SkiaSurface() :
         m_canvas{nullptr} {}
      ~SkiaSurface() {
         dispose();
      }

      // FIXME: Añadir SkColorSpace?
      void create(int w, int h) {
         if(w <= 0 || h <= 0)
            return;

         dispose();

         SkBitmap bmp;
         if(!bmp.tryAllocPixels(
            SkImageInfo::MakeN32Premul(w, h)))
            throw std::runtime_error("Error to creating Skia surface");

         bmp.eraseColor(SK_ColorTRANSPARENT);
         swapBitmap(bmp);
      }

      void dispose() {
         delete m_canvas;
         m_canvas = nullptr;
      }

      SkCanvas* const skCanvas() const {return m_canvas;}
      const SkBitmap& bitmap() const {return m_bmp;}
   private:
      void swapBitmap(SkBitmap& other) {
         m_bmp.swap(other);
         delete m_canvas;
         m_canvas = new SkCanvas(m_bmp);
      }

      SkBitmap m_bmp;
      SkCanvas* m_canvas;
   };
} // namespace os::priv