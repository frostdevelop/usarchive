#include <stdint.h>
#include <array>
#ifndef DATATOOL_H
#define DATATOOL_H
namespace dtt{
union ufast16bytes {
    uint_fast16_t value;
    uint8_t bytes[2];
};
union ufast32bytes {
    uint_fast32_t value;
    uint8_t bytes[4];
};
union ufast64bytes {
    uint_fast64_t value;
    uint8_t bytes[8];
};
uint_fast16_t byte2ufast16(char bytes[2], const bool isLittle=false){
    unsigned char* ubytes = reinterpret_cast<unsigned char*>(bytes);
    if(isLittle){
        return static_cast<uint_fast16_t>(ubytes[0]) | (static_cast<uint_fast16_t>(ubytes[1]) << 8);
    }else{
        return (static_cast<uint_fast16_t>(ubytes[0]) << 8) | static_cast<uint_fast16_t>(ubytes[1]);
    }
}
uint_fast32_t byte2ufast32(char bytes[4], const bool isLittle=false){
    unsigned char* ubytes = reinterpret_cast<unsigned char*>(bytes);
    if(isLittle){
        return static_cast<uint_fast32_t>(ubytes[0]) | (static_cast<uint_fast32_t>(ubytes[1]) << 8) | (static_cast<uint_fast32_t>(ubytes[2]) << 16) | (static_cast<uint_fast32_t>(ubytes[3]) << 24);
    }else{
        return (static_cast<uint_fast32_t>(ubytes[0]) << 24) | (static_cast<uint_fast32_t>(ubytes[1]) << 16) | (static_cast<uint_fast32_t>(ubytes[2]) << 8) | static_cast<uint_fast32_t>(ubytes[3]);
    }
}
uint_fast64_t byte2ufast64(char bytes[8], const bool isLittle=false){
    unsigned char* ubytes = reinterpret_cast<unsigned char*>(bytes);
    if(isLittle){
        return static_cast<uint_fast64_t>(ubytes[0]) | (static_cast<uint_fast64_t>(ubytes[1]) << 8) | (static_cast<uint_fast64_t>(ubytes[2]) << 16) | (static_cast<uint_fast64_t>(ubytes[3]) << 24) | (static_cast<uint_fast64_t>(ubytes[4]) << 32) | (static_cast<uint_fast64_t>(ubytes[5]) << 40) | (static_cast<uint_fast64_t>(ubytes[6]) << 48) | (static_cast<uint_fast64_t>(ubytes[7]) << 56);
    }else{
        return static_cast<uint_fast64_t>(ubytes[7]) | (static_cast<uint_fast64_t>(ubytes[6]) << 8) | (static_cast<uint_fast64_t>(ubytes[5]) << 16) | (static_cast<uint_fast64_t>(ubytes[4]) << 24) | (static_cast<uint_fast64_t>(ubytes[3]) << 32) | (static_cast<uint_fast64_t>(ubytes[2]) << 40) | (static_cast<uint_fast64_t>(ubytes[1]) << 48) | (static_cast<uint_fast64_t>(ubytes[0]) << 56);
    }
}
std::array<char,2> ufast162byte(const uint_fast16_t value, const bool isLittle=false){
    std::array<char,2> arr;
    if(isLittle){
        arr[0] = (value & 0xFF);
        arr[1] = ((value>>8) & 0xFF);
    }else{
        arr[0] = ((value>>8) & 0xFF);
        arr[1] = (value & 0xFF);
    }
    return arr;
}
std::array<char,4> ufast322byte(const uint_fast32_t value, const bool isLittle=false){
    std::array<char,4 > arr;
    if(isLittle){
        arr[0] = (value & 0xFF);
        arr[1] = ((value>>8) & 0xFF);
        arr[2] = ((value>>16) & 0xFF);
        arr[3] = ((value>>24) & 0xFF);
    }else{
        arr[3] = (value & 0xFF);
        arr[2] = ((value>>8) & 0xFF);
        arr[1] = ((value>>16) & 0xFF);
        arr[0] = ((value>>24) & 0xFF);
    }
    return arr;
}
std::array<char,8> ufast642byte(const uint_fast64_t value, const bool isLittle=false){
    std::array<char,8> arr;
    if(isLittle){
        arr[0] = (value & 0xFF);
        arr[1] = ((value>>8) & 0xFF);
        arr[2] = ((value>>16) & 0xFF);
        arr[3] = ((value>>24) & 0xFF);
        arr[4] = ((value>>32) & 0xFF);
        arr[5] = ((value>>40) & 0xFF);
        arr[6] = ((value>>48) & 0xFF);
        arr[7] = ((value>>56) & 0xFF);
    }else{
        arr[7] = (value & 0xFF);
        arr[6] = ((value>>8) & 0xFF);
        arr[5] = ((value>>16) & 0xFF);
        arr[4] = ((value>>24) & 0xFF);
        arr[3] = ((value>>32) & 0xFF);
        arr[2] = ((value>>40) & 0xFF);
        arr[1] = ((value>>48) & 0xFF);
        arr[0] = ((value>>56) & 0xFF);
    }
    return arr;
}
}
#endif // DATATOOL_H
