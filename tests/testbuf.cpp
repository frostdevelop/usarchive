#include "usarchive.h"
#include <iostream>
#include <string>
#include <fstream>

int main() {
  usarchive archive("test.usa");
  std::cout << archive.error() << std::endl;
  usa::databuf testbuf = archive.writeBuf();
  std::cout << std::string(reinterpret_cast<char*>(testbuf.data),testbuf.size) << std::endl;
  std::cout << archive.error() << std::endl;
  std::ofstream teststream("archive.usa");
  teststream.write(reinterpret_cast<char*>(testbuf.data),testbuf.size);
  teststream.close();
}