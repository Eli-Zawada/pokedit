#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <wtypes.h>
#include <iomanip>
#include <sstream>

#include "pointertools.h"
#include "interpreter.h"

struct game_string {
	std::wstring wstring;
	int characters;
};

struct trainer_pokemon {
	byte level;
	byte pokemon;
	byte move1;
	byte move2;
	byte move3;
	byte move4;
	byte item;
};

int GetFileSize(std::wstring fileName);
std::vector<byte> LoadData(std::wstring fileName);
void SaveData(std::wstring fileName, std::vector<byte> vec);
std::vector<byte> CopyData(int startAdd, int endAdd, std::vector<byte> data);
std::vector<byte> PasteData(int startAdd, std::vector<byte> data, std::vector<byte> copy);
bool CheckForRom(std::vector<byte> rom);
bool CheckIfNumber(std::wstring& input);
game_string GetGameString(std::vector<byte> data, int address, byte end);
std::wstring IntToHexString(int number);
bool CheckValidPointerTableEntry(std::vector<byte> data, int address, int entry);
