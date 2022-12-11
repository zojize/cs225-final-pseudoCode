#pragma once

// legacy png-based canvas
// i'm keeping it because i dont want to admit
// that my time all went to waste :(

#include "Vector2d.h"
#include "cs225/PNG.h"
#include "cs225/RGBAPixel.h"

using cs225::PNG;
using cs225::RGBAPixel;

class Canvas {
public:
  Canvas() = default;
  Canvas(PNG img);
  Canvas(unsigned int width, unsigned int height);

  RGBAPixel stroke_style;
  RGBAPixel fill_style;
  // size_t line_width = 1;

  unsigned int width() const;
  unsigned int height() const;

  Canvas& line(int x0, int y0, int x1, int y1);
  Canvas& fill_rect(int x, int y, int width, int height);

  void writeToFile(std::string const& fname);

private:
  PNG _img;
  void _plot(int x, int y, RGBAPixel const& c);
  RGBAPixel _mix(RGBAPixel const& a_, RGBAPixel const& b_) const;
};
