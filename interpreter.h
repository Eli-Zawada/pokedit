#pragma once

#include <string>
#include <vector>
#include <wtypes.h>

std::wstring InterpretCharacter(byte code);
int InterpretNumbers(unsigned char value);
std::wstring InterpretEvos(unsigned char code);
std::wstring InterpretHapp(unsigned char code);
std::wstring InterpretStats(unsigned char code);
std::wstring InterpretEggGroup(byte code);
int InterpretGenderRatio(byte code);
byte InterpretGenderCombo(int code);
int InterpretTyping(unsigned char code);
char InterpretTypingCombo(int code);
char InterpretSizeCombo(int code);
std::wstring InterpretPokemon(char code);
std::wstring InterpretMoves(char code);
std::wstring InterpretItems(char code);
std::wstring InterpretItems(std::vector<byte>& data, byte code);
std::wstring InterpretTrainerClass(std::vector<byte>& data, byte code);
std::wstring InterpretPokemon(std::vector<byte>& data, byte code);
std::wstring InterpretMoves(std::vector<byte>& data, byte code);
std::wstring InterpretConds(unsigned char type, unsigned char code);
std::wstring InterpretTM1(byte bit);
std::wstring InterpretTM2(byte bit);
std::wstring InterpretTM3(byte bit);
std::wstring InterpretTM4(byte bit);
std::wstring InterpretTM5(byte bit);
std::wstring InterpretTM6(byte bit);
std::wstring InterpretTM7(byte bit);
std::wstring InterpretTM8(byte bit);
short InterpretFamily(char code);
byte TextToHex(wchar_t character);