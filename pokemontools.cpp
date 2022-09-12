#include "pokemontools.h"

void DisplayLevelMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int lvl, int move) {

	byte* pointer = new byte[3];
	unsigned int startAddress = 0;
	unsigned int currentAddress = 0;
	int segment = 0;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * ((unsigned int)pokemon - 1))];
	pointer[1] = data[address + (2 * ((unsigned int)pokemon - 1)) + 1];

	currentAddress = PointerToAddress(pointer);
	startAddress = currentAddress;

	//Iterate through evolution data
	while (segment < 2) {
		while (segment < 1) {
			//Check to see if No Evolution Data, or end of Evolution data
			if (data[currentAddress] == (byte)0x00) {
				currentAddress = currentAddress + 1;
				segment = segment + 1;
				break;
			}
			//Check to see if Tyrogue Evolution, because data is 3 bytes not 2
			if (data[currentAddress] == (byte)0x05) {
				currentAddress = currentAddress + 3;
			}
			//Check to see Evolution Type and Condition
			else {
				currentAddress = currentAddress + 2;
			}
			//Skipping the identifier byte for Pokemon to be evolved into
			currentAddress = currentAddress + 1;

			if (data[currentAddress] == (byte)0x00) {
				currentAddress = currentAddress + 1;
				segment = segment + 1;
				break;
			}
		}

		// Enter 2nd loop for Move data
		SendMessage(GetDlgItem(hWnd, lvl), LB_ADDSTRING, 0, (LPARAM)std::to_wstring(InterpretNumbers(data[currentAddress])).c_str());
		currentAddress = currentAddress + 1;
		SendMessage(GetDlgItem(hWnd, move), LB_ADDSTRING, 0, (LPARAM)(InterpretMoves(data[currentAddress])).c_str());
		currentAddress = currentAddress + 1;

		//Check for end of Move data
		if (data[currentAddress] == (byte)0x00) {
			segment = segment + 1;
			break;
		}
	}
}

std::vector<byte> InsertLevelMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte lvl, byte move) {

	byte* pointer = new byte[3];
	unsigned int currentAddress;
	int segment = 0;
	std::vector<byte> copy;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * ((unsigned int)pokemon - 1))];
	pointer[1] = data[address + (2 * ((unsigned int)pokemon - 1)) + 1];

	//Create variable for iterating through data
	currentAddress = PointerToAddress(pointer);

	//Iterate through evolution data
	while (segment < 1) {

		if (data[currentAddress] == (byte)0x00) {
			segment++;
		}
		currentAddress = currentAddress + 1;
	}

	//Iterate though move data while comparing level of old moves to the new move
	//This is to keep moves organized and find an insertion point
	while (lvl >= data[currentAddress]) {

		if (data[currentAddress] == 0x00) {
			break;
		}
		currentAddress = currentAddress + 2;
	}

	//Fill pointer pieces to get address of the end of the current ROM Bank
	pointer[2] = pointer[2] + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;

	//Copy data from insertion point to the end of ROM Bank
	//Minus 2 byte to keep room for the new byte from insertion
	copy = CopyData(currentAddress, PointerToAddress(pointer) - 3, data);

	//Fill insertion point with new move data
	data[currentAddress] = lvl;
	currentAddress = currentAddress + 1;
	data[currentAddress] = move;
	currentAddress = currentAddress + 1;;

	//Paste data over remaining ROM Bank data to shift data over 2 bytes
	data = PasteData(currentAddress, data, copy);

	//Load Pointer Table into copy and update the Pointer Table
	//Only update the pointers of all Pokemon past selected Pokemon
	copy = CopyData(address + (pokemon * 2), address + 502, data);
	copy = UpdatePointerTable(copy, 0x0002);

	//Paste new Pointer Table over old Pointer Table
	data = PasteData(address + (pokemon * 2), data, copy);

	return data;
}

std::vector<byte> DeleteLevelMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte lvl, byte move) {

	byte* pointer = new byte[3];
	unsigned int currentAddress;
	bool exists = false;
	std::vector<byte> copy;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (pokemon - 1))];
	pointer[1] = data[address + (2 * (pokemon - 1)) + 1];

	//Create variable for iterating through data
	currentAddress = PointerToAddress(pointer);

	//Iterate through evolution data
	while (data[currentAddress] != (byte)0x00) {
		currentAddress = currentAddress + 1;
	}
	currentAddress++;

	//Find 
	while (data[currentAddress] != (byte)0x00) {
		if (data[currentAddress] == lvl && data[currentAddress + 1] == move) {
			exists = true;
			break;
		}
		currentAddress = currentAddress + 2;
	}

	if (exists == true) {
		//Fill pointer pieces to get address of the end of the current ROM Bank
		pointer[2] = pointer[2] + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		//
		copy = CopyData(currentAddress + 2, PointerToAddress(pointer) - 1, data);

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		data = PasteData(currentAddress, data, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(address + (pokemon * 2), address + 502, data);
		copy = UpdatePointerTable(copy, -0x0002);

		//Paste new Pointer Table over old Pointer Table
		data = PasteData(address + (pokemon * 2), data, copy);
	}

	return data;
}

std::vector<byte> InsertEggMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte move) {

	byte* pointer = new byte[3];
	unsigned int current_add;
	int segment = 0;
	std::vector<byte> copy;
	short poke = InterpretFamily(pokemon);

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];

	//Create variable for iterating through data
	current_add = PointerToAddress(pointer);

	if (data[current_add] == 0xFF) {
		while (data[current_add] == 0xFF) {
			poke--;

			pointer[2] = FindBank(address);
			pointer[0] = data[address + (2 * (poke - 1))];
			pointer[1] = data[address + (2 * (poke - 1)) + 1];
			current_add = PointerToAddress(pointer);
		}

		while (data[current_add] != 0xFF) {
			current_add++;
		}

		pointer = CreatePointer(current_add);

		data[address + (2 * (InterpretFamily(pokemon) - 1))] = pointer[0] - 1;
		data[address + (2 * (InterpretFamily(pokemon) - 1)) + 1] = pointer[1];
		
		pointer[2] = pointer[2] + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		copy = CopyData(current_add, PointerToAddress(pointer) - 1, data);

		current_add++;
		data[current_add] = move;
		current_add++;

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		data = PasteData(current_add, data, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(address + (poke * 2), address + 502, data);
		copy = UpdatePointerTable(copy, 0x0002);

		//Paste new Pointer Table over old Pointer Table
		data = PasteData(address + (poke * 2), data, copy);
	}
	else {
		pointer[2] = pointer[2] + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		copy = CopyData(current_add, PointerToAddress(pointer) - 1, data);

		//Fill insertion point with new move data
		data[current_add] = move;
		current_add++;

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		data = PasteData(current_add, data, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(address + (poke * 2), address + 502, data);
		copy = UpdatePointerTable(copy, 0x0001);

		//Paste new Pointer Table over old Pointer Table
		data = PasteData(address + (poke * 2), data, copy);
	}

	return data;
}

std::vector<byte> DeleteEggMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte move) {

	byte* pointer = new byte[3];
	unsigned int currentAddress;
	bool exists = false;
	std::vector<byte> copy;
	short poke = InterpretFamily(pokemon);

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];

	//Create variable for iterating through data
	currentAddress = PointerToAddress(pointer);

	while (data[currentAddress] != (byte)0xff) {
		if (data[currentAddress] == move) {
			exists = true;
			break;
		}
		currentAddress = currentAddress + 1;
	}

	if (exists == true) {
		//Fill pointer pieces to get address of the end of the current ROM Bank
		pointer[2] = pointer[2] + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		//Copy data from insertion point to the end of ROM Bank
		//Minus 1 bytes to keep room for the new byte from insertion
		copy = CopyData(currentAddress + 1, PointerToAddress(pointer) - 1, data);

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		data = PasteData(currentAddress, data, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(address + (poke * 2), address + 502, data);
		copy = UpdatePointerTable(copy, -0x0001);

		//Paste new Pointer Table over old Pointer Table
		data = PasteData(address + (poke * 2), data, copy);
	}

	return data;
}

void DisplayEggMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int inst) {

	byte* pointer = new byte[3];
	unsigned int startAddress = 0;
	unsigned int currentAddress = 0;
	short poke = InterpretFamily(pokemon);

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];

	currentAddress = PointerToAddress(pointer);
	startAddress = currentAddress;

	//Iterate through evolution data
	while (data[currentAddress] != (byte)0xff) {
		SendMessage(GetDlgItem(hWnd, inst), LB_ADDSTRING, 0, (LPARAM)InterpretMoves(data[currentAddress]).c_str());
		currentAddress++;
	}
}

void DisplayTM(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int inst) {
	unsigned int dataAddress = address + 24;
	dataAddress = dataAddress + ((pokemon - 1) * 32);

	byte tm = data[dataAddress];
	std::wstring tm_text;


	for (int j = 0; j < 8; j++) {
		tm = data[dataAddress + j];
		for (byte i = 0; i < 8; i++) {

			switch (j) {
			case 0: {
				tm_text = InterpretTM1(i);
				break;
			}
			case 1: {
				tm_text = InterpretTM2(i);
				break;
			}
			case 2: {
				tm_text = InterpretTM3(i);
				break;
			}
			case 3: {
				tm_text = InterpretTM4(i);
				break;
			}
			case 4: {
				tm_text = InterpretTM5(i);
				break;
			}
			case 5: {
				tm_text = InterpretTM6(i);
				break;
			}
			case 6: {
				tm_text = InterpretTM7(i);
				break;
			}
			case 7: {
				tm_text = InterpretTM8(i);
				break;
			}
			}

			if (((tm >> i) & 1) == 1) {
				SendMessage(GetDlgItem(hWnd, inst), LB_ADDSTRING, 0, (LPARAM)tm_text.c_str());
			}
		}
	}
}

std::vector<byte> ToggleTMs(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte tm) {

	byte tm_byte = (tm - 1) / 8;
	byte tm_bit = (tm - 1) % 8;

	unsigned int dataAddress = address + 24;
	dataAddress = dataAddress + ((pokemon - 1) * 32);
	dataAddress = dataAddress + tm_byte;

	byte value = data[dataAddress];

	value ^= 1 << tm_bit;


	data[dataAddress] = value;

	return data;
}

void DisplayEvolution(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int evo) {

	byte* pointer = new byte[3];
	unsigned int start_address = 0;
	unsigned int current_address = 0;
	int segment = 0;
	std::wstring str = L"";

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * ((unsigned int)pokemon - 1))];
	pointer[1] = data[address + (2 * ((unsigned int)pokemon - 1)) + 1];

	current_address = PointerToAddress(pointer);
	start_address = current_address;

	SendMessage(GetDlgItem(hWnd, evo), LB_RESETCONTENT, 0, 0);

	//Iterate through evolution data
	while (true) {
		switch (data[current_address]) {
		case 0x00:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x01:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = L"LVL: ";
			str.append(std::to_wstring((int)data[current_address]));
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x02:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretItems(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x03:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretItems(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x04:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretHapp(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x05:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = L"LVL: ";
			str.append(std::to_wstring((int)data[current_address]));
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretStats(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;
		}

		if (data[current_address] != 0x00)current_address++;
		//If End Marker found break loop
		if (data[current_address] == 0x00) {
			break;
		}

		SendMessage(GetDlgItem(hWnd, evo), LB_ADDSTRING, 0, (LPARAM)L"");
	}

}

std::vector<byte> InsertEvolution(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int met, int con, int pok, int stat) {

	byte* pointer = new byte[3];
	unsigned int current_address;
	byte method = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
	std::vector<byte> copy;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * ((unsigned int)pokemon - 1))];
	pointer[1] = data[address + (2 * ((unsigned int)pokemon - 1)) + 1];

	//Create variable for iterating through data
	current_address = PointerToAddress(pointer);

	//Fill pointer pieces to get address of the end of the current ROM Bank
	pointer[2] = pointer[2] + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;

	switch (method) {
	case 0x01:
		copy = CopyData(current_address, PointerToAddress(pointer) - 4, data);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, pok), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x02:
		copy = CopyData(current_address, PointerToAddress(pointer) - 4, data);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0);
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, pok), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x03:
		copy = CopyData(current_address, PointerToAddress(pointer) - 4, data);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0);
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, pok), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x04:
		copy = CopyData(current_address, PointerToAddress(pointer) - 4, data);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, pok), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x05:
		copy = CopyData(current_address, PointerToAddress(pointer) - 5, data);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, stat), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, pok), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	}

	current_address++;

	//Paste data over remaining ROM Bank data to shift data over 2 bytes
	data = PasteData(current_address, data, copy);

	//Load Pointer Table into copy and update the Pointer Table
	//Only update the pointers of all Pokemon past selected Pokemon
	copy = CopyData(address + (pokemon * 2), address + 502, data);
	if (method == 0x05) {
		copy = UpdatePointerTable(copy, 0x0004);
	}
	else {
		copy = UpdatePointerTable(copy, 0x0003);
	}

	//Paste new Pointer Table over old Pointer Table
	data = PasteData(address + (pokemon * 2), data, copy);

	return data;
}

std::vector<byte> DeleteEvolution(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int met, int con, int pok, int stat) {

	byte* pointer = new byte[3];
	unsigned int current_address;
	unsigned int paste_address;
	byte method = (byte)SendMessage(GetDlgItem(hWnd, met), CB_GETCURSEL, 0, 0) + 0x01;
	byte condition = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0) + 0x01;
	byte evo_poke = (byte)SendMessage(GetDlgItem(hWnd, pok), CB_GETCURSEL, 0, 0) + 0x01;
	byte stat_con = (byte)SendMessage(GetDlgItem(hWnd, stat), CB_GETCURSEL, 0, 0) + 0x01;
	std::vector<byte> copy;
	bool exists = true;
	bool found[4] = { false };
	//These methods use items whose combobox items are one to one, so no need to add 1
	if (method == 0x02 || method == 0x03) condition = (byte)SendMessage(GetDlgItem(hWnd, con), CB_GETCURSEL, 0, 0);

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * ((unsigned int)pokemon - 1))];
	pointer[1] = data[address + (2 * ((unsigned int)pokemon - 1)) + 1];

	//Create variable for iterating through data
	current_address = PointerToAddress(pointer);


	//Fill pointer pieces to get address of the end of the current ROM Bank
	pointer[2] = pointer[2] + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;

	while (exists == true) {
		paste_address = current_address;

		if (data[current_address] == 0x00) {
			exists = false;
			break;
		}

		if (data[current_address] != 0x05) {

			if (data[current_address] == method) {
				found[0] = true;
			}
			else found[0] = false;

			current_address++;

			if (data[current_address] == condition) {
				found[1] = true;
			}
			else found[1] = false;

			current_address++;

			if (data[current_address] == evo_poke) {
				found[2] = true;
			}
			else found[2] = false;

			current_address++;

			if (found[0] == true && found[1] == true && found[2] == true) {
				copy = CopyData(current_address, PointerToAddress(pointer) - 1, data);
				break;
			}
		}

		if (data[current_address] == 0x05) {

			if (data[current_address] == method) {
				found[0] = true;
			}
			else found[0] = false;
			current_address++;
			if (data[current_address] == condition) {
				found[1] = true;
			}
			else found[1] = false;
			current_address++;
			if (data[current_address] == stat_con) {
				found[3] = true;
			}
			else found[3] = false;
			current_address++;
			if (data[current_address] == evo_poke) {
				found[2] = true;
			}
			else found[2] = false;
			current_address++;
			if (found[0] == true && found[1] == true && found[2] == true && found[3] == true) {
				copy = CopyData(current_address, PointerToAddress(pointer) - 1, data);
				break;
			}
		}


		if (found[0] == false && found[1] == false && found[2] == false) current_address++;
	}

	if (exists == true) {

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		data = PasteData(paste_address, data, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(address + (pokemon * 2), address + 502, data);
		if (method == 0x05) {
			copy = UpdatePointerTable(copy, -0x0004);
		}
		else {
			copy = UpdatePointerTable(copy, -0x0003);
		}

		//Paste new Pointer Table over old Pointer Table
		data = PasteData(address + (pokemon * 2), data, copy);

	}

	return data;
}

////////////////////////////////////////////////////Base Stat Information//////////////////////////////////////////////////////

void DisplayBaseStats(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int hp, int atk, int def, int spd, int satk, int sdef) {
	int cur_address = address + ((pokemon - 1) * 32);

	cur_address++;
	SetDlgItemText(hWnd, hp, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());

	cur_address++;
	SetDlgItemText(hWnd, atk, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());

	cur_address++;
	SetDlgItemText(hWnd, def, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());

	cur_address++;
	SetDlgItemText(hWnd, spd, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());

	cur_address++;
	SetDlgItemText(hWnd, satk, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());

	cur_address++;
	SetDlgItemText(hWnd, sdef, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());
}

std::vector<byte> ChangeBaseStats(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd,
	HWND hp, HWND atk, HWND def, HWND spd, HWND satk, HWND sdef) {
	bool is_number = false;
	int cur_address = address + ((pokemon - 1) * 32);

	cur_address++;

	wchar_t buff[4];

	GetWindowText(hp, (LPWSTR)buff, 4);
	std::wstring hp_text(buff);
	is_number = CheckIfNumber(hp_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(hp_text);
	}
	cur_address++;

	GetWindowText(atk, (LPWSTR)buff, 4);
	std::wstring atk_text(buff);
	is_number = CheckIfNumber(atk_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(atk_text);
	}
	cur_address++;

	GetWindowText(def, (LPWSTR)buff, 4);
	std::wstring def_text(buff);
	is_number = CheckIfNumber(def_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(def_text);
	}
	cur_address++;

	GetWindowText(spd, (LPWSTR)buff, 4);
	std::wstring spd_text(buff);
	is_number = CheckIfNumber(spd_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(spd_text);
	}
	cur_address++;

	GetWindowText(satk, (LPWSTR)buff, 4);
	std::wstring satk_text(buff);
	is_number = CheckIfNumber(satk_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(satk_text);
	}
	cur_address++;

	GetWindowText(sdef, (LPWSTR)buff, 4);
	std::wstring sdef_text(buff);
	is_number = CheckIfNumber(sdef_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(sdef_text);
	}

	return data;
}

void DisplayTyping(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int type1, int type2) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 7;

	SendMessage(GetDlgItem(hWnd, type1), CB_SETCURSEL, (WPARAM)InterpretTyping(data[cur_address]), 0);
	cur_address++;
	SendMessage(GetDlgItem(hWnd, type2), CB_SETCURSEL, (WPARAM)InterpretTyping(data[cur_address]), 0);

}

std::vector<byte> ChangeTyping(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int type1, int type2) {
	int cur_address = address + ((pokemon - 1) * 32);
	byte type_code = 0;
	cur_address += 7;

	type_code = InterpretTypingCombo(SendMessage(GetDlgItem(hWnd, type1), CB_GETCURSEL, 0, 0));
	data[cur_address] = type_code;

	cur_address++;

	type_code = InterpretTypingCombo(SendMessage(GetDlgItem(hWnd, type2), CB_GETCURSEL, 0, 0));
	data[cur_address] = type_code;

	return data;
}

void DisplayHoldItems(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int item23, int item2) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 11;

	SendMessage(GetDlgItem(hWnd, item23), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
	cur_address++;
	SendMessage(GetDlgItem(hWnd, item2), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
}

std::vector<byte> ChangeHoldItems(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int item23, int item2) {
	int cur_address = address + ((pokemon - 1) * 32);
	byte item_code = 0;
	cur_address += 11;

	item_code = (byte)SendMessage(GetDlgItem(hWnd, item23), CB_GETCURSEL, 0, 0);
	data[cur_address] = item_code;

	cur_address++;

	item_code = (byte)SendMessage(GetDlgItem(hWnd, item2), CB_GETCURSEL, 0, 0);
	data[cur_address] = item_code;

	return data;
}

void DisplayCaptureRate(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int cr) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 9;

	SetDlgItemText(hWnd, cr, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());
}

std::vector<byte> ChangeCaptureRate(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int cr) {
	bool is_number = false;
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 9;

	wchar_t buff[4];

	GetWindowText(GetDlgItem(hWnd, cr), (LPWSTR)buff, 4);
	std::wstring cr_text(buff);
	is_number = CheckIfNumber(cr_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(cr_text);
	}

	return data;
}

void DisplayBaseExp(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int exp) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 10;

	SetDlgItemText(hWnd, exp, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());
}

std::vector<byte> ChangeBaseExp(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int exp) {
	bool is_number = false;
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 10;

	wchar_t buff[4];

	GetWindowText(GetDlgItem(hWnd, exp), (LPWSTR)buff, 4);
	std::wstring exp_text(buff);
	is_number = CheckIfNumber(exp_text);
	if (is_number == true) {
		data[cur_address] = (byte)std::stoi(exp_text);
	}

	return data;
}

void DisplayEggGroup(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int egg1, int egg2) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 23;

	byte group1 = data[cur_address];
	byte group2 = data[cur_address];

	group1 = group1 >> 4;
	group2 = group2 & 0x0F;

	SendMessage(GetDlgItem(hWnd, egg1), CB_SETCURSEL, group1 - 1, 0);
	SendMessage(GetDlgItem(hWnd, egg2), CB_SETCURSEL, group2 - 1, 0);
}

std::vector<byte> ChangeEggGroup(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int egg1, int egg2) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 23;

	byte group = (byte)SendMessage(GetDlgItem(hWnd, egg1), CB_GETCURSEL, 0, 0) + 1;
	group = group << 4;
	group = group + (byte)SendMessage(GetDlgItem(hWnd, egg2), CB_GETCURSEL, 0, 0) + 1;

	data[cur_address] = group;

	return data;
}

void DisplayGenderRatio(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int gen) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 13;

	SendMessage(GetDlgItem(hWnd, gen), CB_SETCURSEL, (LPARAM)InterpretGenderRatio(data[cur_address]), 0);
}

std::vector<byte> ChangeGenderRatio(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int gen) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 13;

	int gender_code = (int)SendMessage(GetDlgItem(hWnd, gen), CB_GETCURSEL, 0, 0);


	data[cur_address] = InterpretGenderCombo(gender_code);

	return data;
}

void DisplayHatchSteps(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int hatch) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 15;

	SetDlgItemText(hWnd, hatch, std::to_wstring(InterpretNumbers(data[cur_address]) * 256).c_str());
}

std::vector<byte> ChangeHatchSteps(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int hatch) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 15;
	bool is_number = false;

	wchar_t buff[6];

	GetWindowText(GetDlgItem(hWnd, hatch), (LPWSTR)buff, 6);
	std::wstring hatch_text(buff);
	is_number = CheckIfNumber(hatch_text);
	if (is_number == true) {
		unsigned int value = std::stoi(hatch_text);
		value = value / 256;
		data[cur_address] = (byte)value;
	}

	return data;
}

void DisplayGrowthType(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int growth) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 22;
	byte gro_code = 0;

	gro_code = data[cur_address];
	if (gro_code != 0x00) gro_code -= 0x02;

	SendMessage(GetDlgItem(hWnd, growth), CB_SETCURSEL, (WPARAM)gro_code, 0);

}

std::vector<byte> ChangeGrowthType(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int growth) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 22;

	byte gro = (byte)SendMessage(GetDlgItem(hWnd, growth), CB_GETCURSEL, 0, 0);
	if (gro != 0x00) gro += 0x02;

	data[cur_address] = gro;

	return data;
}

void DisplaySpriteSize(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int size) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 17;
	byte sze_code = 0;

	sze_code = data[cur_address];

	switch (sze_code) {
	case 0x55:
		sze_code = 0x00;
		break;
	case 0x66:
		sze_code = 0x01;
		break;
	case 0x77:
		sze_code = 0x02;
		break;
	}

	SendMessage(GetDlgItem(hWnd, size), CB_SETCURSEL, (WPARAM)sze_code, 0);

}

std::vector<byte> ChangeSpriteSize(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int size) {
	int cur_address = address + ((pokemon - 1) * 32);
	cur_address += 17;

	int sze_code = (int)SendMessage(GetDlgItem(hWnd, size), CB_GETCURSEL, 0, 0);

	data[cur_address] = InterpretSizeCombo(sze_code);

	return data;
}
