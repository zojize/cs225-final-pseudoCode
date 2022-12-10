/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 */

#include "RGBAPixel.h"
#include <cmath>
#include <iostream>

namespace cs225 {
RGBAPixel::RGBAPixel() : RGBAPixel(0, 0, 0, 255) {}

RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b)
    : RGBAPixel(r, g, b, 255) {}

RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b,
                     unsigned char a)
    : r(r), g(g), b(b), a(a) {}

bool RGBAPixel::operator==(RGBAPixel const& other) const {
  if (a == 0 && other.a == 0)
    return true;

  return a == other.a && r == other.r && g == other.g && b == other.b;
}

bool RGBAPixel::operator!=(RGBAPixel const& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, RGBAPixel const& pixel) {
  out << "(" << pixel.r << ", " << pixel.g << ", " << pixel.b
      << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

  return out;
}

} // namespace cs225
