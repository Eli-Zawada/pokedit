#include "dataeditor.h"
#include "randomencounters.h"
#include "profile.h"
#include "address.h"

unsigned int GetFileSize(std::wstring fileName) {

	std::ifstream file(fileName, std::ios::binary | std::ios::ate);
	unsigned int size = file.tellg();

	file.close();

	if (size == (unsigned int)-1) return 0;

	return size;
}

std::vector<byte> LoadData(std::wstring fileName) {

	std::ifstream file(fileName, std::ios::binary);

	file.unsetf(std::ios::skipws);

	unsigned int size = GetFileSize(fileName);

	std::vector<byte> vec;
	vec.reserve(size);

	vec.insert(vec.begin(),
		std::istream_iterator<byte>(file),
		std::istream_iterator<byte>());

	file.close();

	return vec;
}

void SaveData(std::vector<byte>& vec, std::wstring fileName) {

	std::ofstream file(fileName, std::ios::out | std::ios::binary);

	int size = GetFileSize(fileName);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<byte>(file));
}

void WriteVector(std::ofstream& ofs, std::vector<byte>& vec) {
	typename std::vector<byte>::size_type size = vec.size();
	ofs.write((char*)&size, sizeof(size));//Get the Size of the Pokemon Profile
	ofs.write((char*)&vec[0], vec.size() * sizeof(byte));
}

std::vector<byte> ReadVector(std::ifstream& ifs, size_t &size) {
	std::vector<byte> vec;
	byte temp = 0;
	for (size_t i = 0; i < size; i++) {
		ifs.read((char*)&temp, sizeof(byte));
		vec.push_back(temp);
	}

	return vec;
}

void WriteString(std::ofstream& ofs, std::wstring str) {
	typename std::wstring::size_type size = str.size();
	ofs.write((char*)&size, sizeof(size));//Get the Size of the Pokemon Profile
	ofs.write((char*)&str[0], str.size() * sizeof(wchar_t));
}

std::vector<std::wstring> ReadString(std::ifstream& ifs, size_t& vec_size) {
	std::vector<std::wstring> vec;
	wchar_t temp = 0;

	for (size_t i = 0; i < vec_size; i++) {
		size_t str_size = 0;
		ifs.read((char*)&str_size, sizeof(size_t));

		std::wstring str = L"";
		for (size_t j = 0; j < str_size; j++) {
			ifs.read((char*)&temp, sizeof(wchar_t));
			str += temp;
		}
		
		vec.push_back(str);
	}

	return vec;
}

void SaveProfileData(std::wstring fileName) {
	std::ofstream profile(fileName, std::ios::out | std::ios::binary);

	std::vector<random_pokemon> poke = GetPokemonProfile();
	std::vector<random_encounter> enc = GetMapProfile();
	std::vector<std::wstring> tags = GetTagNames();

	typename std::vector<random_pokemon>::size_type size_p = poke.size();
	profile.write((char*)&size_p, sizeof(size_p));//Get the Size of the Pokemon Profile

	for (random_pokemon& p : poke) {
		profile.write((char*)&p.pokemon, sizeof(byte));
		profile.write((char*)&p.level_min, sizeof(byte));
		profile.write((char*)&p.level_max, sizeof(byte));

		profile.write((char*)&p.morning, sizeof(byte));
		profile.write((char*)&p.day, sizeof(byte));
		profile.write((char*)&p.night, sizeof(byte));

		WriteVector(profile, p.tags);
	}

	typename std::vector<random_encounter>::size_type size_e = enc.size();
	profile.write((char*)&size_e, sizeof(size_e));

	for (random_encounter& e : enc) {
		profile.write((char*)&e.map_group, sizeof(byte));
		profile.write((char*)&e.map_id, sizeof(byte));
		profile.write((char*)&e.level_min, sizeof(byte));
		profile.write((char*)&e.level_max, sizeof(byte));

		WriteVector(profile, e.tags);
	}

	typename std::vector<std::wstring>::size_type size_n = tags.size();
	profile.write((char*)&size_n, sizeof(size_n));

	for (std::wstring& n : tags) {

		WriteString(profile, n);
	}
}

void LoadProfileData(std::wstring fileName, HWND hWnd) {
	std::ifstream profile(fileName, std::ios::binary);
	profile.unsetf(std::ios::skipws);

	std::vector<random_pokemon> poke;
	std::vector<random_encounter> enc;
	std::vector<std::wstring> tags;

	typename std::vector<random_pokemon>::size_type size = 0;
	profile.read((char*)&size, sizeof(size_t));

	for (typename std::vector<random_pokemon>::size_type i = 0; i < size; i++) {
		random_pokemon p = { 0 };
		typename std::vector<random_pokemon>::size_type size = 0;

		profile.read((char*)&p.pokemon, sizeof(byte));
		profile.read((char*)&p.level_min, sizeof(byte));
		profile.read((char*)&p.level_max, sizeof(byte));

		profile.read((char*)&p.morning, sizeof(byte));
		profile.read((char*)&p.day, sizeof(byte));
		profile.read((char*)&p.night, sizeof(byte));

		profile.read((char*)&size, sizeof(size));
		p.tags = ReadVector(profile, size);

		poke.push_back(p);
	}

	SetPokemonProfile(poke);

	profile.read((char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++) {
		random_encounter e = { 0 };
		size_t size = 0;

		profile.read((char*)&e.map_group, sizeof(byte));
		profile.read((char*)&e.map_id, sizeof(byte));

		profile.read((char*)&e.level_min, sizeof(byte));
		profile.read((char*)&e.level_max, sizeof(byte));

		profile.read((char*)&size, sizeof(size));
		e.tags = ReadVector(profile, size);

		enc.push_back(e);
	}

	SetMapProfile(enc);

	profile.read((char*)&size, sizeof(size_t));
	tags = ReadString(profile, size);

	SetTagNames(tags);
	SendMessage(GetDlgItem(hWnd, CB_TAGS), CB_RESETCONTENT, 0, 0);
	for (std::wstring& t: tags) {
		SendMessage(GetDlgItem(hWnd, CB_TAGS), CB_ADDSTRING, 0, (LPARAM)t.c_str());
	}

	profile.close();
}

std::vector<byte> CopyData(std::vector<byte>& data, unsigned int start_address, unsigned int end_address) {

	std::vector<byte> copy;

	for (int i = start_address; i < end_address + 1; i++) {
		copy.push_back(data.at(i));
	}

	return copy;
}

void PasteData(std::vector<byte>& data, unsigned int start_address, std::vector<byte>& copy) {

	unsigned int copySize = (unsigned int)copy.size();

	for (unsigned int i = start_address; i < start_address + copySize; i++)
	{
		data[i] = copy[i - start_address];
	}
}

bool CheckForRom(std::vector<byte> rom) {
	if (rom.empty()) {
		return false;
	}
	return true;
}

bool CheckIfNumber(std::wstring& input) {
	std::wstring::const_iterator it = input.begin();
	while (it != input.end() && iswdigit(*it)) {
		++it;
	}
	return !input.empty() && it == input.end();
}

game_string GetGameString(std::vector<byte>& data, int address, byte end) {
	int cur_address = address;
	game_string str;
	str.characters = 0;

	while (data[cur_address] != end) {

		str.wstring  += InterpretCharacter((byte)data[cur_address]);
		str.characters++;
		cur_address++;

	}

	return str;
}

std::wstring IntToHexString(int number) {
	std::wostringstream oss;
	if (number < 16) {
		oss << L"0x0" << std::hex << number;
	}
	else {
		oss << L"0x" << std::hex << towupper(number);
	}

	return oss.str();
}

bool CheckValidPointerTableEntry(std::vector<byte>& data, int address, int entry) {
	byte* pointer = new byte[3];

	pointer[2] = FindBank(address);
	pointer[0] = data[address];
	pointer[1] = data[address + 1];

	return (address + ((entry - 1) * 2) + 1) < PointerToAddress(pointer);
}

int GetNumberOfTableElements(int table_add, std::vector<byte>& data) {
	int count = 0;
	int destination = 0;
	byte pointer[3];

	pointer[2] = FindBank(table_add);
	pointer[0] = data[table_add];
	pointer[1] = data[table_add + 1];
	destination = PointerToAddress(pointer);

	count = (destination - table_add) / 2;

	return count;

}

bool CheckBit(byte b, byte p) {
	return (b>>p) & 1;
}

void UpdateStringPointers(std::vector<byte>& data, int offset, byte type) {
	unsigned int item = GetAddress(ADD_ITEM_STR_PNTR);
	unsigned int trainer = GetAddress(ADD_TRNR_STR_PNTR);
	unsigned int pokemon = GetAddress(ADD_POKE_STR_PNTR);
	unsigned int move = GetAddress(ADD_MOVE_STR_PNTR);
	unsigned int address = 0;

	byte* pointer = new byte[3];

	switch (type) {
	case 0:
		pointer[2] = data[item - 1];
		pointer[1] = data[item + 1];
		pointer[0] = data[item];

		address = PointerToAddress(pointer) + offset;
		pointer = CreatePointer(address);

		data[item - 1] = pointer[2];
		data[item + 1] = pointer[1];
		data[item] = pointer[0];

	case 1:
		pointer[2] = data[trainer - 1];
		pointer[1] = data[trainer + 1];
		pointer[0] = data[trainer];

		address = PointerToAddress(pointer) + offset;
		pointer = CreatePointer(address);

		data[trainer - 1] = pointer[2];
		data[trainer + 1] = pointer[1];
		data[trainer] = pointer[0];

	case 2:
		pointer[2] = data[pokemon - 7];
		pointer[1] = data[pokemon + 1];
		pointer[0] = data[pokemon];

		address = PointerToAddress(pointer) + offset;
		pointer = CreatePointer(address);

		data[pokemon - 1] = pointer[2];
		data[pokemon + 1] = pointer[1];
		data[pokemon] = pointer[0];

	case 3:
		pointer[2] = data[move - 1];
		pointer[1] = data[move + 1];
		pointer[0] = data[move];

		address = PointerToAddress(pointer) + offset;
		pointer = CreatePointer(address);

		data[move - 1] = pointer[2];
		data[move + 1] = pointer[1];
		data[move] = pointer[0];
	}


}