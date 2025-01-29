#include "usarchive.h"
#include <iostream>
#include <string>

int main() {
  //std::cout << static_cast<uint_fast32_t>(static_cast<unsigned char>(145)) << std::endl;
  usarchive archive;
  archive.addFile("test.sno");
  archive.addFile("testf.sno");
  std::cout << "added" << std::endl;
  archive.writeTo("test.usa");
  usarchive archive2("test.usa");
  std::cout << archive2.error() << std::endl;
  usa::file test1 = archive2.popFile();
  std::cout << "Name: " << test1.name << std::endl;
  std::cout << "Data: " << test1.data << std::endl;
  usa::file test2 = archive2.popFile();
  std::cout << "Name: " << test2.name << std::endl;
  std::cout << "Data: " << test2.data << std::endl;
}