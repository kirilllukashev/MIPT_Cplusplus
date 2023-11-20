#include <iostream>
#include <cstring>
#include <algorithm>

class String {
public:
  String();
  String(const char* string);
  String(int n, char c);
  String(const String& string);

  ~String();

  static void swap(String& string_1, String& string_2);

  String& operator=(String string);
  String& operator+=(char chr);
  String& operator+=(const String& string);
  char& operator[](size_t index);
  const char& operator[](size_t index) const;

  size_t size() const;
  size_t capacity() const;
  size_t length() const;
  char* data();
  const char* data() const;
  char& front();
  const char& front() const;
  char& back();
  const char& back() const;
  size_t find(const String& string) const;
  size_t rfind(const String& string) const;
  bool empty() const;
  String substr(size_t start, size_t count) const;

  void clear();
  void push_back(char c);
  void pop_back();
  void shrink_to_fit();

  void print() const;

private:
  size_t size_;
  size_t capacity_;
  char* data_;
  void reserve(size_t size);
};

bool operator==(const String& string_1, const String& string_2);
bool operator!=(const String& string_1, const String& string_2);
bool operator>(const String& string_1, const String& string_2);
bool operator<(const String& string_1, const String& string_2);
bool operator>=(const String& string_1, const String& string_2);
bool operator<=(const String& string_1, const String& string_2);

String operator+(const String& string_1, const String& string_2);
String operator+(char string_1, const String& string_2);
String operator+(const String& string_1, char string_2);

std::ostream& operator<<(std::ostream& out, const String& string);
std::istream& operator>>(std::istream& in, String& string);

String::String() : size_(0), capacity_(0), data_(new char[1]){
  data_[0] = '\0';
}

String::String(const char* string) :
    size_(strlen(string)),
    capacity_(strlen(string)),
    data_(new char[strlen(string) + 1]) {
  std::copy(string, string + size_ + 1, data_);
}

String::String(int n, char c) : size_(n), capacity_(n), data_(new char[size_ + 1]) {
  std::fill(data_, data_ + size_, c);
  data_[size_] = '\0';
}

String::String(const String& string) :
    size_(string.size_),
    capacity_(string.capacity_),
    data_(new char[string.capacity_ + 1]) {
  std::copy(string.data_, string.data_ + size_ + 1, data_);
}

String::~String() {
  delete[] data_;
}

void String::reserve(size_t size) {
  capacity_ = size;
  char* arr = new char[capacity_ + 1];
  std::copy(data_, data_ + size_ + 1, arr);
  delete[] data_;
  data_ = arr;
}

void String::shrink_to_fit() {
  reserve(size_);
}

void String::swap(String& string_1, String& string_2) {
  std::swap(string_1.size_, string_2.size_);
  std::swap(string_1.capacity_, string_2.capacity_);
  std::swap(string_1.data_, string_2.data_);
}

String& String::operator=(String string) {
  swap(string, *this);
  return *this;
}

String& String::operator+=(char chr) {
  push_back(chr);
  return *this;
}

String& String::operator+=(const String& string) {
  if (size_ + string.size_ < capacity_) {
    std::copy(string.data_, string.data_ + string.size_ + 1, data_ + size_);
    size_ = size_ + string.size_;
  } else {
    reserve(2 * (size_ + string.size_));
    std::copy(string.data_, string.data_ + string.size_ + 1, data_ + size_);
    size_ = size_ + string.size_;
    capacity_ = 2 * size_;
  }
  return *this;
}

char& String::operator[](size_t index) {
  return data_[index];
}

const char& String::operator[](size_t index) const {
  return data_[index];
}

size_t String::size() const {
  return size_;
}

size_t String::capacity() const {
  return capacity_;
}

size_t String::length() const {
  return size_;
}

char* String::data() {
  return data_;
}

const char* String::data() const {
  return data_;
}

char& String::front() {
  return data_[0];
}

const char& String::front() const {
  return data_[0];
}

char& String::back() {
  return data_[size_ - 1];
}

const char& String::back() const {
  return data_[size_ - 1];
}

bool String::empty() const {
  return (size_ == 0);
}

size_t String::find(const String& string) const {
  for (size_t i = 0; i < size_ - string.size_ + 1; ++i) {
    bool flag = true;
    for (size_t j = 0; j < string.size_; ++j) {
      if (data_[i + j] != string[j]) {
        flag = false;
        break;
      }
    }
    if (flag) return i;
  }
  return length();
}

size_t String::rfind(const String& string) const {
  size_t result = length();
  for (size_t i = 0; i < size_ - string.size_ + 1; ++i) {
    bool flag = true;
    for (size_t j = 0; j < string.size_; ++j) {
      if (data_[i + j] != string[j]) {
        flag = false;
        break;
      }
    }
    if (flag) result = i;
  }
  return result;
}

String String::substr(size_t start, size_t count) const {
  String result(count, '0');
  if (start + count < size_) {
    std::copy(data_ + start, data_ + start + count, result.data_);
  }
  return result;
}

void String::clear() {
  data_[0] = '\0';
  size_ = 0;
}

void String::push_back(char c) {
  if (capacity_ == 0) {
    capacity_ = 1;
    size_ = 1;
    reserve(1);
    data_[0] = c;
    data_[1] = '\0';
  } else if (size_ == capacity_) {
    capacity_ *= 2;
    reserve(capacity_);
    data_[size_] = c;
    data_[++size_] = '\0';
  } else {
    data_[size_] = c;
    data_[++size_] = '\0';
  }
}

void String::pop_back() {
  data_[--size_] = '\0';
}

bool operator==(const String& string_1, const String& string_2) {
  return strcmp(string_1.data(), string_2.data()) == 0;
}

bool operator!=(const String& string_1, const String& string_2) {
  return strcmp(string_1.data(), string_2.data()) != 0;
}

bool operator>(const String& string_1, const String& string_2) {
  return strcmp(string_1.data(), string_2.data()) > 0;
}

bool operator<(const String& string_1, const String& string_2) {
  return strcmp(string_1.data(), string_2.data()) < 0;
}

bool operator>=(const String& string_1, const String& string_2) {
  return !(string_1 < string_2);
}

bool operator<=(const String& string_1, const String& string_2) {
  return !(string_1 > string_2);
}

String operator+(const String& string_1, const String& string_2) {
  String result = string_1;
  result += string_2;
  return result;
}

String operator+(char string_1, const String& string_2) {
  String result;
  result += string_1;
  result += string_2;
  return result;
}

String operator+(const String& string_1, char string_2) {
  String result = string_1;
  result += string_2;
  return result;
}

std::ostream& operator<<(std::ostream& out, const String& string) {
  for (size_t i = 0; i < string.size(); ++i) {
    out << string[i];
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& string) {
  String result;
  char chr;
  while (in.get(chr)) {
    if (chr == '\n' || chr == '0' || chr == '\t') {
      break;
    }
    result.push_back(chr);
  }
  string = result;
  return in;
}

void String::print() const {
  std::cout << "size:" << size_ << '\n';
  std::cout << "capacity: " << capacity_ << "\n";
  std::cout << "strlen: " << strlen(data_) << "\n";
  char* now = data_;
  for (int i = 0; i < size_; ++i) {
    std::cout << *(data_ + i);
  }
  std::cout << '\n';
}