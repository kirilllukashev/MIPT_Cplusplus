#include <cstring>
#include <iostream>

struct Node {
  Node* prev;
  char* str;

  Node(Node* now_prev, char* now_str) : prev(now_prev), str(now_str) {}

  ~Node() { delete[] str; }
};

class Stack {
 public:
  Stack() {
    size_ = 0;
    data_ = nullptr;
  }

  void Push(char* str) {
    this->data_ = new Node(data_, str);
    this->size_ += 1;
  }

  void Pop() {
    Node* node = data_;
    data_ = data_->prev;
    size_ -= 1;
    delete node;
  }

  void Clear() {
    while (size_ != 0) {
      Node* node = data_;
      data_ = data_->prev;
      size_ -= 1;
      delete node;
    }
    size_ = 0;
  }

  char* Top() { return data_->str; }

  int32_t Size() { return size_; }

  ~Stack() { delete data_; }

 private:
  int32_t size_;
  Node* data_;
};

char* ResizeString(char* str, int32_t size) {
  char* buffer = new char[size * 2];
  memcpy(buffer, str, sizeof(char) * size);
  delete[] str;
  return buffer;
}

char* ReadString() {
  int32_t length = 0;
  int32_t size = 5;
  char* buffer = new char[size];
  char chr = getchar();
  while (chr != ' ' && chr != '\n') {
    buffer[length] = chr;
    length++;
    if (length == size) {
      buffer = ResizeString(buffer, size);
      size *= 2;
    }
    chr = getchar();
  }
  buffer[length] = '\0';
  return buffer;
}

void PrintString(char* str) {
  int32_t i = 0;
  while (str[i] != '\0') {
    std::cout << str[i];
    i++;
  }
  std::cout << '\n';
}

bool CompareString(char* s_1, char* s_2) {
  int32_t i = 0;
  while (s_2[i] != '\0') {
    if (s_2[i] != s_1[i]) {
      return false;
    }
    i++;
  }
  return true;
}

int main() {
  Stack stack = Stack();

  char* str = ReadString();
  char str_push[] = "push";
  char str_pop[] = "pop";
  char str_back[] = "back";
  char str_size[] = "size";
  char str_clear[] = "clear";
  while (true) {
    if (CompareString(str, str_push)) {
      delete[] str;
      str = ReadString();
      stack.Push(str);
      std::cout << "ok\n";

    } else if (CompareString(str, str_pop)) {
      delete[] str;
      if (stack.Size() == 0) {
        std::cout << "error\n";
      } else {
        PrintString(stack.Top());
        stack.Pop();
      }

    } else if (CompareString(str, str_back)) {
      delete[] str;
      if (stack.Size() == 0) {
        std::cout << "error\n";
      } else {
        PrintString(stack.Top());
      }

    } else if (CompareString(str, str_size)) {
      delete[] str;
      std::cout << stack.Size() << '\n';

    } else if (CompareString(str, str_clear)) {
      delete[] str;
      stack.Clear();
      std::cout << "ok\n";

    } else {
      stack.Clear();
      std::cout << "bye\n";
      delete[] str;
      break;
    }
    str = ReadString();
  }
  return 0;
}