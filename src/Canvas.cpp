#include "Canvas.h"
#include "cs225/RGB_HSL.h"

#include <cmath>

using std::abs;

Canvas::Canvas(PNG img) : _img(img) {}

Canvas::Canvas(unsigned int width, unsigned int height) : _img(width, height) {}

unsigned int Canvas::width() const { return _img.width(); };
unsigned int Canvas::height() const { return _img.height(); };

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// Naive bresenham's algorithm
// TODO: support line width
// http://members.chello.at/~easyfilter/bresenham.html
Canvas& Canvas::line(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx - dy, e2, x2; /* error value e_xy */
  int ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);

  for (;;) { /* pixel loop */
    // setPixelAA(x0, y0, 255 * abs(err - dx + dy) / ed);
    _plot(x0, y0, stroke_style);
    e2 = err;
    x2 = x0;
    if (2 * e2 >= -dx) { /* x step */
      if (x0 == x1)
        break;
      if (e2 + dy < ed)
        // setPixelAA(x0, y0 + sy, 255 * (e2 + dy) / ed);
        _plot(x0, y0 + sy, stroke_style);
      err -= dy;
      x0 += sx;
    }
    if (2 * e2 <= dy) { /* y step */
      if (y0 == y1)
        break;
      if (dx - e2 < ed)
        // setPixelAA(x2 + sx, y0, 255 * (dx - e2) / ed);
        _plot(x2 + sx, y0, stroke_style);
      err += dx;
      y0 += sy;
    }
  }

  return *this;
}

Canvas& Canvas::fill_rect(int x, int y, int width, int height) {
  int init_edge_x = x + width - 1;
  int init_edge_y = y + height - 1;
  int init_x = x, init_y = y;
  int edge_x = std::min(init_edge_x, (int)_img.width() - 1);
  int edge_y = std::min(init_edge_y, (int)_img.height() - 1);
  for (; x <= edge_x; x++) {
    for (y = init_y; y <= edge_y; y++) {
      if (x == init_x || y == init_y || x == init_edge_x || y == init_edge_y)
        _plot(x, y, stroke_style);
      else
        _plot(x, y, fill_style);
    }
  }
  return *this;
}

void Canvas::writeToFile(std::string const& fname) { _img.writeToFile(fname); }

void Canvas::_plot(int x, int y, RGBAPixel const& c) {
  auto& pixel = _img.getPixel(x, y);
  // pixel = c;
  pixel = _mix(c, pixel);
}

// https://stackoverflow.com/a/68936281/14835397
RGBAPixel Canvas::_mix(RGBAPixel const& f, RGBAPixel const& b) const {
  double f_a = (double)f.a / 255.;
  double b_a = (double)b.a / 255.;
  double f_a_ = 1 - f_a;

  RGBAPixel c;
  c.r = f_a * f.r + f_a_ * b_a * b.r;
  c.g = f_a * f.g + f_a_ * b_a * b.g;
  c.b = f_a * f.b + f_a_ * b_a * b.b;
  c.a = round((f_a + f_a_ * b_a) * 255);

  return c;
}
