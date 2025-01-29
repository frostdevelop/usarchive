#include "usarchive.h"
#include <iostream>
#include <string>

int main() {
  usarchive archive2("test.usa");
  std::cout << archive2.error() << std::endl;
  archive2.unArchive("./");
}