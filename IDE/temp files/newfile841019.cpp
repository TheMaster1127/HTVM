#include <algorithm>
#include <any>
#include <cstdint>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

int main(int argc, char* argv[]) {


// With values
double keyWordDouble = 3.14;
char keyWordChar = 'A';
uint8_t keyWordUint8 = 255;
uint16_t keyWordUint16 = 65535;
uint32_t keyWordUint32 = 4294967295;
uint64_t keyWordUint64 = 18446744073709551615ULL;
int keyWordINT = -42;
std::string keyWordSTR = "Hello";
bool keyWordBOOL = true;
float keyWordFLOAT = 3.14f;
int8_t keyWordINT8 = -128;
int16_t keyWordINT16 = 32767;
int32_t keyWordINT32 = -2147483648;
int64_t keyWordINT64 = 9223372036854775807LL;
const int keyWordConst = 100; // Const
int keyWordLet = 50;          // Mimicking let
auto keyWordVar = 25;         // Mimicking var


    return 0;
}
