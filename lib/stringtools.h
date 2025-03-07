#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H
#include <string>

namespace stringtools
{
    std::string trimEnds(std::string str);
    std::string trimR(std::string str);
    std::string trimL(std::string str);
    unsigned long checksum(std::string str);
    std::string toLower(std::string str);
    std::string toUpper(std::string str);
};

#endif // STRINGTOOLS_H