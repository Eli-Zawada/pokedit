#pragma once

#include <vector>
#include <wtypes.h>

byte FindBank(unsigned int address);
unsigned short FindBankAddress(unsigned int address);
unsigned short CombineBytes(byte a, byte b);
byte* SeperateBytes(unsigned short word);
byte* CreatePointer(unsigned int address);
unsigned int PointerToAddress(byte* pointer);
unsigned int LoadPointer(unsigned int address, std::vector<byte> data);
std::vector<byte> UpdatePointerTable(std::vector<byte> table, unsigned short offset);