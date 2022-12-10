/**
 * @file RGBAPixel.h
 *
 * @author CS 225: Data Structures
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
class RGBAPixel {
public:
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;

  RGBAPixel();
  RGBAPixel(unsigned char r, unsigned char g, unsigned char b);
  RGBAPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

  bool operator==(RGBAPixel const& other) const;
  bool operator!=(RGBAPixel const& other) const;
};

/**
 * Stream operator that allows pixels to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param pixel Pixel to write to the stream.
 */
std::ostream& operator<<(std::ostream& out, RGBAPixel const& pixel);
std::stringstream& operator<<(std::stringstream& out, RGBAPixel const& pixel);
} // namespace cs225
