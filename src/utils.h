#include <string>

template <typename T>
T checked_stoi(std::string const& s) {
  if (s != "\\N")
    return std::stoi(s);
  throw std::domain_error("wait... this is not a number!");
}
