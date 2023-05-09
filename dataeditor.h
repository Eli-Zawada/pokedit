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

struct random_pokemon {
	byte pokemon;
	byte level_min;
	byte level_max;

	bool morning, day, night;

	std::vector<bool> tags = std::vector<bool>(15);
};

struct random_encounter {
	//std::wstring name;
	byte map_group;
	byte map_id;
	byte level_min;
	byte level_max;

	bool rare, legendary;

	bool morning, day, night;

	byte shore, salt_water, fresh_water;

	byte cave, mountain;

	byte urban, ruins;
	byte field, grasslands, forest;

	byte hot, cold, electric;
};

unsigned int GetFileSize(std::wstring fileName);
std::vector<byte> LoadData(std::wstring fileName);
void SaveData(std::vector<byte>& vec, std::wstring fileName);
std::vector<byte> CopyData(std::vector<byte>& data, unsigned int start_address, unsigned int end_address);
void PasteData(std::vector<byte>& data, unsigned int start_address, std::vector<byte>& copy);
bool CheckForRom(std::vector<byte> rom);
bool CheckIfNumber(std::wstring& input);
game_string GetGameString(std::vector<byte>& data, int address, byte end);
std::wstring IntToHexString(int number);
bool CheckValidPointerTableEntry(std::vector<byte>& data, int address, int entry);
int GetNumberOfTableElements(int table_add, std::vector<byte>& data);
bool CheckBit(byte b, byte p);
