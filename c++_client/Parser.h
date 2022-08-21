#pragma once
#include "AESUtils.h"
#include <string>

class Parser {
public:
 static std::string DecryptData(const uint8_t* data, size_t bufferSize);
 
};