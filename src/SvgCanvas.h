#pragma once

#define ATTR(k) " " #k "=\"" << k << "\" "

#include <fstream>
#include <sstream>
#include <unordered_map>

using std::to_string;

class SvgCanvas {
public:
  SvgCanvas() = default;
  SvgCanvas(int width, int height) : width(width), height(height){};

  int width;
  int height;

  std::unordered_map<std::string, std::string> attrs;

  SvgCanvas& image(std::string href) {
    _svg << "\t<image " << ATTR(href) << "/>\n";
    return *this;
  };
  SvgCanvas& line(int x1, int y1, int x2, int y2) {
    _svg << "\t<line " << ATTR(x1) << ATTR(y1) << ATTR(x2) << ATTR(y2)
         << _attrs() << "/>\n";
    return *this;
  };
  SvgCanvas& rect(int x, int y, int width, int height) {
    _svg << "\t<rect " << ATTR(x) << ATTR(y) << ATTR(width) << ATTR(height)
         << _attrs() << "/>\n";
    return *this;
  };
  SvgCanvas& circle(int cx, int cy, int r) {
    _svg << "\t<circle " << ATTR(cx) << ATTR(cy) << ATTR(r) << _attrs()
         << "/>\n";
    return *this;
  };
  SvgCanvas& ellipse(int cx, int cy, int rw, int ry) {
    _svg << "\t<ellipse " << ATTR(cx) << ATTR(cy) << ATTR(rw) << ATTR(ry)
         << _attrs() << "/>\n";
    return *this;
  };
  SvgCanvas& text(int x, int y, std::string const& content) {
    _svg << "\t<text " << ATTR(x) << ATTR(y) << _attrs() << ">" << content
         << "</text>\n";
    return *this;
  };
  SvgCanvas& cubic_bezier(int x0, int y0, int x1, int y1, int x2, int y2,
                          int x3, int y3) {
    // can we use std::format plz ;(
    return path("M " + to_string(x0) + " " + to_string(y0) + " C " +
                to_string(x1) + " " + to_string(y1) + " " + to_string(x2) +
                " " + to_string(y2) + " " + to_string(x3) + " " +
                to_string(y3));
  }
  SvgCanvas& quadratic_bezier(int x0, int y0, int x1, int y1, int x2, int y2) {
    return path("M " + to_string(x0) + " " + to_string(y0) + " Q " +
                to_string(x1) + " " + to_string(y1) + " " + to_string(x2) +
                " " + to_string(y2));
  }
  SvgCanvas& path(std::string const& d) {
    _svg << "\t<path " << ATTR(d) << _attrs() << "/>\n";

    return *this;
  }

  void writeToFile(std::string const& fname) {
    std::ofstream f(fname);
    f << "<svg width=\"" << width << "\" height=\"" << height
      << "\" xmlns=\"http://www.w3.org/2000/svg\">\n"
      << _svg.str() << "</svg>";
    f.close();
  };

private:
  std::stringstream _svg;

  inline std::string _attribute(std::string const& k, std::string const& v) {
    return k + "=\"" + v + "\"";
  }

  inline std::string _attrs() {
    std::string ret = " ";
    for (auto p : attrs)
      ret += p.first + "=\"" + p.second + "\" ";
    ret += " ";
    return ret;
  }
};

#undef ATTR
