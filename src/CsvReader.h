#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class CsvReader {
public:
  CsvReader(std::string file_name) : _file{file_name} { _next_line(); };

  // https://stackoverflow.com/a/69773072/14835397
  struct iterator {
  public:
    using T = std::vector<std::string>;
    using self_type = iterator;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using reference = T &;

    iterator() noexcept : _reader(nullptr){};
    iterator(CsvReader *r) noexcept : _reader(r){};

    reference operator*() noexcept {
      std::string curr;
      size_t i = 0;
      for (char c : _reader->_current_line) {
        if (c == ',') {
          if (i >= _parsed.size())
            _parsed.push_back(curr);
          else
            _parsed[i] = curr;
          curr = "";
          ++i;
        } else if (c != '"')
          curr += c;
      }
      if (!curr.empty()) {
        if (i >= _parsed.size())
          _parsed.push_back(curr);
        else
          _parsed[i] = curr;
      }
      return _parsed;
    };

    self_type operator++() noexcept {
      if (_reader && !_reader->_eof)
        _reader->_next_line();
      return *this;
    };

    bool operator==(const self_type &other) const noexcept {
      return !operator!=(other);
    }
    bool operator!=(const self_type &other) const noexcept {
      if (_reader && _reader->_eof)
        return false;
      return _reader != other._reader;
    };

  private:
    CsvReader *_reader;
    T _parsed;
  };

  iterator begin() { return iterator(this); }
  iterator end() { return iterator(); }

private:
  void _next_line() {
    if (!_eof && _file.is_open()) {
      std::getline(_file, _current_line);
      _eof = _file.eof();
    }
  };
  std::ifstream _file;
  std::string _current_line;
  bool _eof = false;
};
