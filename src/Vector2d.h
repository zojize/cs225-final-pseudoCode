#pragma once

#include <cmath>
#include <iostream>
#include <utility>

// https://codereview.stackexchange.com/a/27112/245101
template <typename T>
struct Vector2d {
  T x, y;

  Vector2d() : Vector2d(T(0), T(0)){};
  Vector2d(T x, T y) : x(x), y(y){};
  Vector2d(std::pair<T, T> p) : x(p.first), y(p.second){};

  double magnitude() const { return hypot(x, y); };
  T dist_sq(Vector2d const& v) const {
    return pow(x - v.x, 2) + pow(y - v.y, 2);
  };
  double dist(Vector2d const& v) const { return hypot(x - v.x, y - v.y); };
  T dot(Vector2d const& v) const { return x * v.x + y * v.y; };
  T cross(Vector2d const& v) const { return x * v.y - y * v.x; };
  Vector2d& set(T x_, T y_) const {
    x = x_;
    y = y_;
    return *this;
  };
  Vector2d& rotate(T const angle) {
    T x_ = x;
    x = std::cos(angle) * x - std::sin(angle) * y;
    y = std::sin(angle) * x_ + std::cos(angle) * y;
    return *this;
  };
  Vector2d& normalize() {
    T mag = magnitude();
    return operator/=(mag == T(0) ? T(1) : mag);
  };
  // clang-format off
  // 2x2 matrix
  Vector2d& apply_matrix(double m11, double m12, 
                         double m21, double m22) {
    return set(x * m11 + y * m21, x * m12 + y * m22);
  };
  // 3x3 homogenous matrix (last column ignored)
  Vector2d& apply_matrix(double m11, double m12, /* m13 */
                         double m21, double m22, /* m23 */
                         double m31, double m32  /* m33 */) {
    return set(x * m11 + y + m21 + m31, x * m12 + y * m22 + m32);
  };
  // clang-format on
  Vector2d clone() const { return *this; };

  Vector2d& operator+=(Vector2d const& v) {
    x += v.x;
    y += v.y;
    return *this;
  };
  Vector2d& operator+=(T const& s) { return operator+=(Vector2d(s, s)); };
  Vector2d& operator-=(Vector2d const& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  };
  Vector2d& operator-=(T const& s) { return operator-=(Vector2d(s, s)); };
  Vector2d& operator*=(Vector2d const& v) {
    x *= v.x;
    y *= v.y;
    return *this;
  };
  Vector2d& operator*=(T const& s) { return operator*=(Vector2d(s, s)); };
  Vector2d& operator/=(Vector2d const& v) {
    x /= v.x;
    y /= v.y;
    return *this;
  };
  Vector2d& operator/=(T const& s) { return operator/=(Vector2d(s, s)); };

  friend Vector2d operator+(Vector2d const& L, Vector2d const& R) {
    return Vector2d(L) += R;
  }
  friend Vector2d operator+(T const& L, Vector2d const& R) {
    return Vector2d(R) += L;
  }
  friend Vector2d operator+(Vector2d const& L, T const& R) {
    return Vector2d(L) += R;
  }
  friend Vector2d operator-(Vector2d const& v) { return Vector2d(-v.x, -v.y); }
  friend Vector2d operator-(Vector2d const& L, Vector2d const& R) {
    return Vector2d(L) -= R;
  }
  friend Vector2d operator-(Vector2d const& L, T const& R) {
    return Vector2d(L) -= R;
  }
  friend Vector2d operator*(Vector2d const& L, Vector2d const& R) {
    return Vector2d(L) *= R;
  }
  friend Vector2d operator*(T const& L, Vector2d const& R) {
    return Vector2d(R) *= L;
  }
  friend Vector2d operator*(Vector2d const& L, T const& R) {
    return Vector2d(L) *= R;
  }
  friend Vector2d operator/(Vector2d const& L, Vector2d const& R) {
    return Vector2d(L) /= R;
  }
  friend Vector2d operator/(Vector2d const& L, T const& R) {
    return Vector2d(L) /= R;
  }

  friend bool operator==(Vector2d const& L, Vector2d const& R) {
    return std::pair(L.x, L.y) == std::pair(R.x, R.y);
  }
  friend bool operator!=(Vector2d const& L, Vector2d const& R) {
    return !(L == R);
  };

  friend bool operator<(Vector2d const& L, Vector2d const& R) {
    return std::pair(L.x, L.y) < std::pair(R.x, R.y);
  }
  friend bool operator>=(Vector2d const& L, Vector2d const& R) {
    return !(L < R);
  }
  friend bool operator>(Vector2d const& L, Vector2d const& R) { return R < L; }
  friend bool operator<=(Vector2d const& L, Vector2d const& R) {
    return !(R < L);
  }

  friend std::ostream& operator<<(std::ostream& os, Vector2d const& v) {
    return os << "(" << v.x << ", " << v.y << ")";
  }
};
