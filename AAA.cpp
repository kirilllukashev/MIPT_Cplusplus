#include <iostream>

using namespace std;

int32_t StringToInt(const char* string) {
  int32_t res = 0;
  int32_t pos = 0;
  while (string[pos] != '\0') {
    res = res * 10 + static_cast<int32_t>(string[pos] - '0');
    pos++;
  }
  return res;
}

int64_t SumOfProducts(int32_t pos, int64_t multiple, const int32_t cnt_of_args, const int32_t* const * array,
                      const int32_t* array_sizes, bool* used) {
  if (pos == cnt_of_args) {
    return multiple;
  }
  int64_t res = 0;
  for (int32_t i = 0; i < array_sizes[pos]; ++i) {
    if (used[i] == false) {
      used[i] = true;
      int now_multiple =  multiple * static_cast<int64_t>(array[pos][i]);
      res += SumOfProducts(pos + 1, now_multiple,
                           cnt_of_args, array, array_sizes, used);
      used[i] = false;
    }
  }
  return res;
}

int main(int argc, char *argv[]) {
  int32_t cnt_of_args = static_cast<int32_t>(argc);

  if (cnt_of_args == 1) {
    std::cout << 0;
    return 0;
  }

  int32_t *array_sizes = new int32_t[cnt_of_args - 1];
  int32_t **array = new int32_t*[cnt_of_args - 1];

  int32_t max_size = 0;

  for (int32_t i = 1; i < cnt_of_args; ++i) {
    int32_t size = StringToInt(argv[i]);
    array_sizes[i - 1] = size;

    if (size > max_size) {
      max_size = size;
    }

    array[i - 1] = new int32_t[size];

    for (int32_t j = 0; j < size; ++j) {
      std::cin >> array[i - 1][j];
    }
  }

  bool *used = new bool[max_size];

  for (int32_t i = 0; i < max_size; ++i){
    used[i] = false;
  }
  std::cout << SumOfProducts(0, 1, cnt_of_args - 1, array, array_sizes, used);

  for (int32_t i = 0; i < cnt_of_args - 1; ++i) {
    delete[] array[i];
  }
  delete[] array;
  delete[] array_sizes;
  delete[] used;
}