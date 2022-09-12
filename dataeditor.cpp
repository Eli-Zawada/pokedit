#include "dataeditor.h"

int GetFileSize(std::wstring fileName) {

	std::ifstream ROMFile(fileName, std::ios::binary | std::ios::ate);
	int size = (int)ROMFile.tellg();

	ROMFile.close();

	return size;
}

std::vector<byte> LoadData(std::wstring fileName) {

	std::ifstream ROMFile(fileName, std::ios::binary);

	ROMFile.unsetf(std::ios::skipws);

	int size = GetFileSize(fileName);

	std::vector<byte> vec;
	vec.reserve(size);

	vec.insert(vec.begin(),
		std::istream_iterator<byte>(ROMFile),
		std::istream_iterator<byte>());

	return vec;
}

void SaveData(std::wstring fileName, std::vector<byte> vec) {

	std::ofstream ROMFile(fileName, std::ios::out | std::ios::binary);


	int size = GetFileSize(fileName);
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<byte>(ROMFile));
}

std::vector<byte> CopyData(int startAdd, int endAdd, std::vector<byte> data) {

	std::vector<byte> copy;

	for (int i = startAdd; i < endAdd + 1; i++) {
		copy.push_back(data.at(i));
	}

	return copy;
}

std::vector<byte> PasteData(int startAdd, std::vector<byte> data, std::vector<byte> copy) {

	int copySize = (int)copy.size();

	for (int i = startAdd; i < startAdd + copySize; i++)
	{
		data[i] = copy[i - startAdd];
	}

	return data;
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

game_string GetGameString(std::vector<byte> data, int address, byte end) {
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

bool CheckValidPointerTableEntry(std::vector<byte> data, int address, int entry) {
	byte* pointer = new byte[3];

	pointer[2] = FindBank(address);
	pointer[0] = data[address];
	pointer[1] = data[address + 1];

	return (address + ((entry - 1) * 2) + 1) < PointerToAddress(pointer);
}