#pragma once

#include <string>

template <typename T>
T checked_stoi(std::string const& s) {
  if (s != "\\N")
    return std::stoi(s);
  throw std::domain_error("wait... this is not a number!");
}

// https://stackoverflow.com/a/8319960/14835397
template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
