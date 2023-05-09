#include "pointertools.h"

byte FindBank(unsigned int address) {
	return (byte)(address / 0x4000);
}

unsigned short FindBankAddress(unsigned int address) {
	unsigned short bank = address % 0x4000;

	return bank;
}

unsigned short CombineBytes(byte a, byte b) {
	unsigned short word = a;
	word = word << 8;
	word = word + b;

	return word;
}

byte* SeperateBytes(unsigned short word) {
	byte* bytes = new byte[2];

	bytes[0] = word;
	bytes[1] = word >> 8;

	return bytes;
}

byte* CreatePointer(unsigned int address) {
	byte* bytes = new byte[3];

	unsigned short bankAddress = FindBankAddress(address);
	unsigned short pointer = bankAddress + 0x4000;

	byte value = pointer;
	bytes[0] = value;
	value = pointer >> 8;
	bytes[1] = value;

	bytes[2] = FindBank(address);

	return bytes;
}

unsigned int PointerToAddress(byte* pointer) {
	unsigned int bankAddress = pointer[2] * 0x4000;
	unsigned int address = pointer[1] - 0x40;
	address = (address << 8) + pointer[0];

	return bankAddress + address;
}

unsigned int LoadPointer(unsigned int address, std::vector<byte> data) {
	byte* pointer = new byte[3];
	unsigned short pokemon = 2;

	pointer[2] = FindBank(address);
	pointer[0] = data[address + (2 * (pokemon - 1))];
	pointer[1] = data[address + (2 * (pokemon - 1)) + 1];

	return PointerToAddress(pointer);
}

std::vector<byte> UpdatePointerTable(std::vector<byte> table, unsigned short offset) {
	int tableSize = (unsigned int)table.size();
	unsigned short word = 0;
	byte* bytes = new byte[2];


	for (int i = 0; i < tableSize; i++) {
		if (i % 2 == 0) {
			bytes[0] = table[i];
		}
		else {
			bytes[1] = table[i];
			word = CombineBytes(bytes[1], bytes[0]);
			word = word + offset;
			bytes = SeperateBytes(word);
			table[i] = bytes[1];
			table[i - 1] = bytes[0];
		}
	}

	return table;
}

byte* UpdatePointer(byte* pointer, unsigned short offset) {
	unsigned short word = 0;
	
	word = CombineBytes(pointer[1], pointer[0]);
	word = word + offset;
	pointer = SeperateBytes(word);

	return pointer;
}

void UpdateDuplicatePointers(std::vector<byte>& data, unsigned int address, int range, byte lw, byte hw) {
	for (int i = 0; i < range; i++) {
		if (data[address + (i * 2)] == lw && data[address + (i * 2)] + 1 == hw) {
			data[address + (i * 2)] = lw;
			data[address + (i * 2) + 1] == hw;
		}
	}
}