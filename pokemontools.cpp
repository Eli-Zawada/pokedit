#include "pokemontools.h"

#include "address.h"
#include "pointertools.h"
#include "interpreter.h"
#include "guicodes.h"
#include "main.h"

void DisplayLevelMoves(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
	byte* pointer = new byte[3];
	unsigned int startAddress = 0;
	unsigned int currentAddress = 0;
	int segment = 0;
	std::wstring spacer;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (pokemon - 1))];
	pointer[1] = data[address + (2 * (pokemon - 1)) + 1];

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
		if (InterpretNumbers(data[currentAddress]) >= 100) spacer = L": ";
		if (InterpretNumbers(data[currentAddress]) < 100) spacer = L":  ";
		if (InterpretNumbers(data[currentAddress]) < 10) spacer = L":    ";

		SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_ADDSTRING, 0, (LPARAM)(
			std::to_wstring(InterpretNumbers(data[currentAddress])) +
			spacer +
			InterpretMoves(data[currentAddress + 1])).c_str());

		currentAddress += 2;
		
		//Check for end of Move data
		if (data[currentAddress] == (byte)0x00) {
			//segment = segment + 1;
			break;
		}
	}
}

void InsertLevelMoves(std::vector<byte>& data, byte pokemon, byte lvl, byte move) {
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);


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
	copy = CopyData(data, currentAddress, PointerToAddress(pointer) - 3);

	//Fill insertion point with new move data
	data[currentAddress] = lvl;
	currentAddress = currentAddress + 1;
	data[currentAddress] = move;
	currentAddress = currentAddress + 1;;

	//Paste data over remaining ROM Bank data to shift data over 2 bytes
	PasteData(data, currentAddress, copy);

	//Load Pointer Table into copy and update the Pointer Table
	//Only update the pointers of all Pokemon past selected Pokemon
	copy = CopyData(data, address + (pokemon * 2), address + 502);
	copy = UpdatePointerTable(copy, 0x0002);

	//Paste new Pointer Table over old Pointer Table
	PasteData(data, address + (pokemon * 2), copy);
}

void DeleteLevelMoves(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	byte* pointer = new byte[3];
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
	unsigned int current;
	int entry = SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_GETCURSEL, NULL, NULL);
	std::vector<byte> copy;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (pokemon - 1))];
	pointer[1] = data[address + (2 * (pokemon - 1)) + 1];

	//Create variable for iterating through data
	current = PointerToAddress(pointer);

	//Iterate through evolution data
	while (data[current] != 0x00) {
		current++;
	}
	current++;

	current += (entry + 1) * 2;
	
	//Fill pointer pieces to get address of the end of the current ROM Bank
	pointer[2] = pointer[2] + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;

	//
	copy = CopyData(data, current, PointerToAddress(pointer) - 1);

	//Paste data over remaining ROM Bank data to shift data over 2 bytes
	PasteData(data, current - 2, copy);

	//Load Pointer Table into copy and update the Pointer Table
	//Only update the pointers of all Pokemon past selected Pokemon
	copy = CopyData(data, address + (pokemon * 2), address + 502);
	copy = UpdatePointerTable(copy, -0x0002);

	//Paste new Pointer Table over old Pointer Table
	PasteData(data, address + (pokemon * 2), copy);

}

void ChangeLevelMoves(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	byte* pointer = new byte[3];
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
	unsigned int current;
	int entry = SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_GETCURSEL, NULL, NULL);
	std::vector<byte> copy;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (pokemon - 1))];
	pointer[1] = data[address + (2 * (pokemon - 1)) + 1];

	//Create variable for iterating through data
	current = PointerToAddress(pointer);

	//Iterate through evolution data
	while (data[current] != (byte)0x00) {
		current++;
	}
	current++;

	current += entry * 2;

	data[current] = SendMessage(GetDlgItem(hWnd, CB_LEVELS), CB_GETCURSEL, NULL, NULL) + 1;
	current++;
	data[current] = SendMessage(GetDlgItem(hWnd, CB_MOVES), CB_GETCURSEL, NULL, NULL) + 1;
}

void InsertEggMoves(std::vector<byte>& data, byte pokemon, byte move) {
	unsigned int address = GetAddress(ADD_EGG_TABLE);
	byte* pointer = new byte[3];
	unsigned int current;
	int segment = 0;
	std::vector<byte> copy;
	byte poke = FindPokemonFamily(data, pokemon);
	byte po = poke;

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];

	//Create variable for iterating through data
	current = PointerToAddress(pointer);

	//If Pokemon has no Egg Moves
	if (data[current] == 0xFF) {
		//Scroll back to Pokemon that does have an Egg move entry
		while (data[current] == 0xFF) {
			po--;

			pointer[2] = FindBank(address);
			pointer[0] = data[address + (2 * (po - 1))];
			pointer[1] = data[address + (2 * (po - 1)) + 1];
			current = PointerToAddress(pointer);
		}
		//Then find the end marker of previous valid Egg Move entry
		while (data[current] != 0xFF) {
			current++;
		}

		pointer = CreatePointer(current);

		data[address + (2 * (poke - 1))] = pointer[0] + 1;
		data[address + (2 * (poke - 1)) + 1] = pointer[1];
		
		pointer[2] += 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;
		//Copying Data from insertion point to end of ROM bank, Handling double 0xFF exception
		if(data[current + 1] == 0xFF) copy = CopyData(data, current + 1, PointerToAddress(pointer) - 1);
		else copy = CopyData(data, current, PointerToAddress(pointer) - 1);

		//Add the new move into the data
		current++;
		data[current] = move;
		current++;

		//Iterate through all Pokemon in the table until the point of insertion
		for (int p = 0; p < poke; p++) {
			unsigned int temp_add = 0;
			pointer[2] = FindBank(address);
			pointer[0] = data[address + (2 * p)];
			pointer[1] = data[address + (2 * p) + 1];
			temp_add = address + (p * 2);
			//Check each iteration if the current check has no Egg Moves
			if (data[PointerToAddress(pointer)] == 0xFF) {
				//Update the Pointer by 2 bytes, one for the move, one for the end marker 0xFF
				pointer = UpdatePointer(pointer, 0x02);
				data[temp_add] = pointer[0];
				data[temp_add + 1] = pointer[1];
			}
		}

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		PasteData(data, current, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(data, address + (poke * 2), address + 502);
		copy = UpdatePointerTable(copy, 0x02);
		
		//Paste new Pointer Table over old Pointer Table
		PasteData(data, address + (poke * 2), copy);
	}
	//If Pokemon does have Egg Moves
	else {
		pointer[2] = pointer[2] + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		copy = CopyData(data, current, PointerToAddress(pointer) - 1);

		//Fill insertion point with new move data
		data[current++] = move;

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		PasteData(data, current, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(data, address + (poke * 2), address + 502);
		copy = UpdatePointerTable(copy, 0x01);

		//Paste new Pointer Table over old Pointer Table
		PasteData(data, address + (poke * 2), copy);

		//Iterate through all Pokemon in the table until the point of insertion
		for (int p = 0; p < poke; p++) {
			pointer[2] = FindBank(address);
			pointer[0] = data[address + (2 * p)];
			pointer[1] = data[address + (2 * p) + 1];
			current = address + (p * 2);
			//Check each iteration if the current check has no Egg Moves
			if (data[PointerToAddress(pointer)] == 0xFF) {
				data[current] += 0x01;
			}
		}
	}
}

void UnsertEggMoves(std::vector<byte>& data, byte pokemon, byte move) {
	unsigned int address = GetAddress(ADD_EGG_TABLE);
	unsigned int current = 0;
	std::vector<byte> copy;
	byte* pointer = new byte[3];
	byte poke = FindPokemonFamily(data, pokemon);
	byte shift = 0x00;

	pointer[2] = FindBank(address);
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];
	current = PointerToAddress(pointer);

	//Handles Results of Removing the last egg move with DeleteEggMove
	if ((data[current] == 0xFF && data[current - 1] == 0xFF && data[current + 1] != 0x00) || data[current] != 0xFF) {

		pointer[2] = FindBank(address) + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		copy = CopyData(data, current, PointerToAddress(pointer) - 2);
		PasteData(data, current + 1, copy);
		data[current] = move;
		shift = 0x01;
	}

	//Handles Pokemon that don't have Egg Moves
	if (data[current] == 0xFF) {
		byte prev = poke;
		while (data[current] == 0xFF) {
			prev--;

			pointer[2] = FindBank(address);
			pointer[0] = data[address + (2 * (prev - 1))];
			pointer[1] = data[address + (2 * (prev - 1)) + 1];
			current = PointerToAddress(pointer);
		}
		while (data[current] != 0xFF) {
			current++;
		}

		current++;
		pointer = CreatePointer(current);

		data[address + (2 * (poke - 1))] = pointer[0];
		data[address + (2 * (poke - 1)) + 1] = pointer [1];

		pointer[2] += 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		copy = CopyData(data, current - 1, PointerToAddress(pointer) - 3);
		PasteData(data, current + 1, copy);

		data[current] = move;

		shift = 0x02;
	}

	//All pointer before Pokemon
	for (byte p = 0; p < poke - 1; p++) {
		unsigned int temp_add = 0;
		pointer[2] = FindBank(address);
		pointer[0] = data[address + (2 * p)];
		pointer[1] = data[address + (2 * p) + 1];
		temp_add = address + (p * 2);
		if (data[PointerToAddress(pointer) + 1] == 0xFF) {
			pointer = UpdatePointer(pointer, shift);
			data[temp_add] = pointer[0];
			data[temp_add + 1] = pointer[1];
		}
	}
	//All Pointers After Selected Pokemon
	copy = CopyData(data, address + (poke * 2), address + 502);
	copy = UpdatePointerTable(copy, shift);
	PasteData(data, address + (poke * 2), copy);
}

int DeleteEggMoves(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_EGG_TABLE);
	unsigned int current = 0;
	byte move = SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_GETCURSEL, NULL, NULL);
	byte* pointer = new byte[3];
	std::vector<byte> copy;
	byte poke = FindPokemonFamily(data, pokemon);
	byte p = poke;

	if (SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_GETCOUNT, NULL, NULL) == 0) {
		return -1;
	}

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];

	//Create variable for iterating through data
	current = PointerToAddress(pointer);
	//Set the current Address to the Address of the move
	current += move;

	//Fill pointer pieces to get address of the end of the current ROM Bank
	pointer[2] = pointer[2] + 1;
	pointer[0] = 0x00;
	pointer[1] = 0x40;

	//Copy data from insertion point to the end of ROM Bank
	//Minus 1 bytes to keep room for the new byte from insertion
	if (data[current + 1] == 0xFF && data[current - 1] == 0xFF) {
		copy = CopyData(data, current + 2, PointerToAddress(pointer) - 1);
	}
	else {
		copy = CopyData(data, current + 1, PointerToAddress(pointer) - 1);
	}

	pointer = CreatePointer(current);

	data[address + (2 * (poke - 1))] = pointer[0] + 1;
	data[address + (2 * (poke - 1)) + 1] = pointer[1];

	//Paste data over remaining ROM Bank data to shift data over 2 bytes
	PasteData(data, current, copy);

	//Load Pointer Table into copy and update the Pointer Table
	//Only update the pointers of all Pokemon past selected Pokemon
	copy = CopyData(data, address + (poke * 2), address + 502);
	copy = UpdatePointerTable(copy, -0x01);

	//Paste new Pointer Table over old Pointer Table
	PasteData(data, address + (poke * 2), copy);

	//Iterate through all Pokemon in the table until the point of insertion
	for (poke = 0; poke < p - 1; poke++) {
		unsigned int temp_add = 0;
		pointer[2] = FindBank(address);
		pointer[0] = data[address + (2 * poke)];
		pointer[1] = data[address + (2 * poke) + 1];
		temp_add = address + (poke * 2);
		//Check each iteration if the current check has no Egg Moves
		if (data[PointerToAddress(pointer)] == 0xFF) {
			//Update the Pointer by 2 bytes, one for the move, one for the end marker 0xFF
			pointer = UpdatePointer(pointer, -0x01);
			data[temp_add] = pointer[0];
			data[temp_add + 1] = pointer[1];
		}
	}
	return 0;
}

int SeleteEggMoves(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_EGG_TABLE);
	unsigned int current = 0;
	std::vector<byte> copy;
	byte* pointer = new byte[3];
	byte poke = FindPokemonFamily(data, pokemon);
	byte move = SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_GETCURSEL, NULL, NULL);

	if (SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_GETCOUNT, NULL, NULL) == 0) {
		return -1;
	}

	pointer[2] = FindBank(address);
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];
	current = PointerToAddress(pointer);

	//If no Egg Moves
	if (data[current] == 0xFF) {
		return 0;
	}
	else {
		current += move;

		pointer[2] = FindBank(address) + 1;
		pointer[0] = 0x00;
		pointer[1] = 0x40;

		copy = CopyData(data, current + 1, PointerToAddress(pointer) - 1);
		PasteData(data, current, copy);

		//All Pointers Before selected Pokemon
		for (byte p = 0; p < poke - 1; p++) {
			unsigned int temp_add = 0;
			pointer[2] = FindBank(address);
			pointer[0] = data[address + (2 * p)];
			pointer[1] = data[address + (2 * p) + 1];
			temp_add = address + (p * 2);
			//Check each iteration if the current check has no Egg Moves
			if (data[PointerToAddress(pointer)] == 0x00) {
				//Update the Pointer by 2 bytes, one for the move, one for the end marker 0xFF
				pointer = UpdatePointer(pointer, -0x01);
				data[temp_add] = pointer[0];
				data[temp_add + 1] = pointer[1];
			}
		}
		//All Pointers After Selected Pokemon
		copy = CopyData(data, address + (poke * 2), address + 502);
		copy = UpdatePointerTable(copy, -0x01);
		PasteData(data, address + (poke * 2), copy);
	}

	return 0;
}

void SynchTable(std::vector<byte>& data, unsigned int address, byte marker, byte loops) {
	byte* pointer = new byte[3];
	pointer[0] = data[address];
	pointer[1] = data[address + 1];
	pointer[2] = FindBank(address);
	unsigned int content = PointerToAddress(pointer);

	unsigned int table_size = (content - address) / 2;
	unsigned int current_pointer = address + 2;

	for (int i = 1; i < table_size; i++) {
		for (int j = 0; j < loops; j++) {
			while (data[content] != marker) content++;
			content++;
		}
		pointer = CreatePointer(content);
		data[current_pointer] = pointer[0];
		current_pointer++;
		data[current_pointer] = pointer[1];
		current_pointer++;
	}
	
}

void DisplayEggMoves(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_EGG_TABLE);
	byte* pointer = new byte[3];
	unsigned int startAddress = 0;
	unsigned int currentAddress = 0;
	//short poke = InterpretFamily(pokemon);
	byte poke = FindPokemonFamily(data, pokemon);

	//Create Pointer pieces for address at the start of the pointer table
	pointer[2] = FindBank(address);
	//Pointer is 2 bytes so location in table is 2x Pokemon's number
	pointer[0] = data[address + (2 * (poke - 1))];
	pointer[1] = data[address + (2 * (poke - 1)) + 1];

	currentAddress = PointerToAddress(pointer);
	startAddress = currentAddress;

	//Iterate through evolution data
	while (data[currentAddress] != (byte)0xff) {
		SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_ADDSTRING, 0, (LPARAM)InterpretMoves(data[currentAddress]).c_str());
		currentAddress++;
	}
}

void DisplayTM(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int dataAddress = GetAddress(ADD_BASE_STATS) + 24;
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
				SendMessage(GetDlgItem(hWnd, LB_TMS), LB_ADDSTRING, 0, (LPARAM)tm_text.c_str());
			}
		}
	}
}

void ToggleTMs(std::vector<byte>& data, byte pokemon, byte tm) {

	byte tm_byte = (tm - 1) / 8;
	byte tm_bit = (tm - 1) % 8;

	unsigned int dataAddress = GetAddress(ADD_BASE_STATS) + 24;
	dataAddress = dataAddress + ((pokemon - 1) * 32);
	dataAddress = dataAddress + tm_byte;

	byte value = data[dataAddress];

	value ^= 1 << tm_bit;


	data[dataAddress] = value;
}

void DisplayEvolution(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
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

	SendMessage(GetDlgItem(hWnd, LB_EVO), LB_RESETCONTENT, 0, 0);

	//Iterate through evolution data
	while (true) {
		switch (data[current_address]) {
		case 0x00:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x01:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = L"LVL: ";
			str.append(std::to_wstring((int)data[current_address]));
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x02:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretItems(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x03:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretItems(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x04:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretHapp(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;

		case 0x05:
			str = InterpretEvos(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = L"LVL: ";
			str.append(std::to_wstring((int)data[current_address]));
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretStats(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			current_address++;
			str = InterpretPokemon(data[current_address]);
			SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)str.c_str());
			break;
		}

		if (data[current_address] != 0x00)current_address++;
		//If End Marker found break loop
		if (data[current_address] == 0x00) {
			break;
		}

		SendMessage(GetDlgItem(hWnd, LB_EVO), LB_ADDSTRING, 0, (LPARAM)L"");
	}

}

void InsertEvolution(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
	byte* pointer = new byte[3];
	unsigned int current_address;
	byte method = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
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
		copy = CopyData(data, current_address, PointerToAddress(pointer) - 4);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x02:
		copy = CopyData(data, current_address, PointerToAddress(pointer) - 4);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0);
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x03:
		copy = CopyData(data, current_address, PointerToAddress(pointer) - 4);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0);
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x04:
		copy = CopyData(data, current_address, PointerToAddress(pointer) - 4);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	case 0x05:
		copy = CopyData(data, current_address, PointerToAddress(pointer) - 5);
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_STAT), CB_GETCURSEL, 0, 0) + 0x01;
		current_address++;
		data[current_address] = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) + 0x01;
		break;
	}

	current_address++;

	//Paste data over remaining ROM Bank data to shift data over 2 bytes
	PasteData(data, current_address, copy);

	//Load Pointer Table into copy and update the Pointer Table
	//Only update the pointers of all Pokemon past selected Pokemon
	copy = CopyData(data, address + (pokemon * 2), address + 502);
	if (method == 0x05) {
		copy = UpdatePointerTable(copy, 0x0004);
	}
	else {
		copy = UpdatePointerTable(copy, 0x0003);
	}

	//Paste new Pointer Table over old Pointer Table
	PasteData(data, address + (pokemon * 2), copy);
}

void DeleteEvolution(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
	byte* pointer = new byte[3];
	unsigned int current_address;
	unsigned int paste_address;
	byte method = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) + 0x01;
	byte condition = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0) + 0x01;
	byte evo_poke = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) + 0x01;
	byte stat_con = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_STAT), CB_GETCURSEL, 0, 0) + 0x01;
	std::vector<byte> copy;
	bool exists = true;
	bool found[4] = { false };
	//These methods use items whose combobox items are one to one, so no need to add 1
	if (method == 0x02 || method == 0x03) {
		condition = (byte)SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0);
	}
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
				copy = CopyData(data, current_address, PointerToAddress(pointer) - 1);
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
				copy = CopyData(data, current_address, PointerToAddress(pointer) - 1);
				break;
			}
		}


		if (found[0] == false && found[1] == false && found[2] == false) current_address++;
	}

	if (exists == true) {

		//Paste data over remaining ROM Bank data to shift data over 2 bytes
		PasteData(data, paste_address, copy);

		//Load Pointer Table into copy and update the Pointer Table
		//Only update the pointers of all Pokemon past selected Pokemon
		copy = CopyData(data, address + (pokemon * 2), address + 502);
		if (method == 0x05) {
			copy = UpdatePointerTable(copy, -0x0004);
		}
		else {
			copy = UpdatePointerTable(copy, -0x0003);
		}

		//Paste new Pointer Table over old Pointer Table
		PasteData(data, address + (pokemon * 2), copy);

	}
}

////////////////////////////////////////////////////Base Stat Information//////////////////////////////////////////////////////

void DisplayBaseStats(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +1 because Stats start on byte 2 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 1;

	SetDlgItemText(hWnd, EB_STAT_HP, std::to_wstring(InterpretNumbers(data[cur_address++])).c_str());

	SetDlgItemText(hWnd, EB_STAT_ATK, std::to_wstring(InterpretNumbers(data[cur_address++])).c_str());

	SetDlgItemText(hWnd, EB_STAT_DEF, std::to_wstring(InterpretNumbers(data[cur_address++])).c_str());

	SetDlgItemText(hWnd, EB_STAT_SPD, std::to_wstring(InterpretNumbers(data[cur_address++])).c_str());

	SetDlgItemText(hWnd, EB_STAT_SATK, std::to_wstring(InterpretNumbers(data[cur_address++])).c_str());

	SetDlgItemText(hWnd, EB_STAT_SDEF, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());
}

void ChangeBaseStats(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +1 because Stats start on byte 2 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 1;

	wchar_t buff[4];
	std::wstring value;

	GetWindowText(GetDlgItem(hWnd, EB_STAT_HP), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address++] = (byte)std::stoi(value);
	}
	
	GetWindowText(GetDlgItem(hWnd, EB_STAT_ATK), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address++] = (byte)std::stoi(value);
	}

	GetWindowText(GetDlgItem(hWnd, EB_STAT_DEF), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address++] = (byte)std::stoi(value);
	}

	GetWindowText(GetDlgItem(hWnd, EB_STAT_SPD), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address++] = (byte)std::stoi(value);
	}

	GetWindowText(GetDlgItem(hWnd, EB_STAT_SATK), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address++] = (byte)std::stoi(value);
	}

	GetWindowText(GetDlgItem(hWnd, EB_STAT_SDEF), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address] = (byte)std::stoi(value);
	}
}

void DisplayTyping(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +7 because Typing is bytes 8 and 9 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 7;

	SendMessage(GetDlgItem(hWnd, CB_TYPE_1), CB_SETCURSEL, (WPARAM)InterpretTyping(data[cur_address++]), 0);
	SendMessage(GetDlgItem(hWnd, CB_TYPE_2), CB_SETCURSEL, (WPARAM)InterpretTyping(data[cur_address]), 0);
}

void ChangeTyping(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +7 because Typing is bytes 8 and 9 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 7;
	byte type_code = 0;

	type_code = InterpretTypingCombo(SendMessage(GetDlgItem(hWnd, CB_TYPE_1), CB_GETCURSEL, 0, 0));
	data[cur_address++] = type_code;

	type_code = InterpretTypingCombo(SendMessage(GetDlgItem(hWnd, CB_TYPE_2), CB_GETCURSEL, 0, 0));
	data[cur_address] = type_code;
}

void DisplayHoldItems(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +11 because Hold Items are bytes 12 and 13 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 11;

	SendMessage(GetDlgItem(hWnd, CB_ITEM_23), CB_SETCURSEL, (WPARAM)data[cur_address++], 0);
	SendMessage(GetDlgItem(hWnd, CB_ITEM_2), CB_SETCURSEL, (WPARAM)data[cur_address], 0);
}

void ChangeHoldItems(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +11 because Hold Items are bytes 12 and 13 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 11;
	byte item_code = 0;

	item_code = (byte)SendMessage(GetDlgItem(hWnd, CB_ITEM_23), CB_GETCURSEL, 0, 0);
	data[cur_address++] = item_code;

	item_code = (byte)SendMessage(GetDlgItem(hWnd, CB_ITEM_2), CB_GETCURSEL, 0, 0);
	data[cur_address] = item_code;
}

void DisplayCaptureRate(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +9 because Capture Rate is byte 10 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 9;

	SetDlgItemText(hWnd, EB_CR, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());
}

void ChangeCaptureRate(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +9 because Capture Rate is byte 10 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 9;

	wchar_t buff[4];
	std::wstring value;

	GetWindowText(GetDlgItem(hWnd, EB_CR), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address] = (byte)std::stoi(value);
	}
}

void DisplayBaseExp(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +10 because Base Exp is byte 11 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 10;

	SetDlgItemText(hWnd, EB_BASE_EXP, std::to_wstring(InterpretNumbers(data[cur_address])).c_str());
}

void ChangeBaseExp(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +10 because Base Exp is byte 11 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 10;

	wchar_t buff[4];
	std::wstring value;

	GetWindowText(GetDlgItem(hWnd, EB_BASE_EXP), (LPWSTR)buff, 4);
	value = buff;
	if (CheckIfNumber(value) == true) {
		data[cur_address] = (byte)std::stoi(value);
	}
}

void DisplayEggGroup(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +23 because Egg Group is byte 24 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 23;

	byte group1 = data[cur_address];
	byte group2 = data[cur_address];

	group1 = group1 >> 4;
	group2 = group2 & 0x0F;

	SendMessage(GetDlgItem(hWnd, CB_EGG_1), CB_SETCURSEL, group1 - 1, 0);
	SendMessage(GetDlgItem(hWnd, CB_EGG_2), CB_SETCURSEL, group2 - 1, 0);
}

void ChangeEggGroup(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	//Base Stats data struct is 32 bytes, and +23 because Egg Group is byte 24 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 23;

	byte group = (byte)SendMessage(GetDlgItem(hWnd, CB_EGG_1), CB_GETCURSEL, 0, 0) + 1;
	group = group << 4;
	group = group + (byte)SendMessage(GetDlgItem(hWnd, CB_EGG_2), CB_GETCURSEL, 0, 0) + 1;

	data[cur_address] = group;
}

void DisplayGenderRatio(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +13 because Gender Ratio is byte 14 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 13;

	SendMessage(GetDlgItem(hWnd, CB_GENDER), CB_SETCURSEL, (LPARAM)InterpretGenderRatio(data[cur_address]), 0);
}

void ChangeGenderRatio(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +13 because Gender Ratio is byte 14 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 13;

	byte gender_code = SendMessage(GetDlgItem(hWnd, CB_GENDER), CB_GETCURSEL, 0, 0);

	data[cur_address] = InterpretGenderCombo(gender_code);
}

void DisplayHatchSteps(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +15 because Steps to Hatch is byte 16 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 15;

	//Steps to Hatch byte is multiplied by 256 to get the total steps required
	SetDlgItemText(hWnd, EB_HATCH_STEP, std::to_wstring(InterpretNumbers(data[cur_address]) * 256).c_str());
}

void ChangeHatchSteps(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +13 because Gender Ratio is byte 14 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 15;

	wchar_t buff[6];
	std::wstring string;

	GetWindowText(GetDlgItem(hWnd, EB_HATCH_STEP), (LPWSTR)buff, 6);
	string = buff;
	if (CheckIfNumber(string) == true) {
		unsigned int value = std::stoi(string) / 256;
		data[cur_address] = (byte)value;
	}
}

void DisplayGrowthType(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +22 because Growth Rate is byte 23 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 22;
	byte gro_code = data[cur_address];

	if (gro_code != 0x00) gro_code -= 0x02;

	SendMessage(GetDlgItem(hWnd, CB_GROWTH), CB_SETCURSEL, (WPARAM)gro_code, 0);

}

void ChangeGrowthType(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +22 because Growth Rate is byte 23 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 22;
	byte gro = (byte)SendMessage(GetDlgItem(hWnd, CB_GROWTH), CB_GETCURSEL, 0, 0);
	
	if (gro != 0x00) gro += 0x02;

	data[cur_address] = gro;
}

void DisplaySpriteSize(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +17 because Growth Rate is byte 18 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 17;
	byte sze_code = data[cur_address];

	switch (sze_code) {
	case 0x55:
		//Sprite Size of 40 x 40 pixels
		sze_code = 0x00;
		break;
	case 0x66:
		//Sprite Size of 48 x 48 pixels
		sze_code = 0x01;
		break;
	case 0x77:
		//Spriet Size of 56 x 56 pixels
		sze_code = 0x02;
		break;
	}

	SendMessage(GetDlgItem(hWnd, CB_SPR_SIZE), CB_SETCURSEL, (WPARAM)sze_code, 0);

}

void ChangeSpriteSize(std::vector<byte>& data, byte pokemon, HWND hWnd) {
	// Base Stats data struct is 32 bytes, and +17 because Growth Rate is byte 18 of the struct
	unsigned int cur_address = GetAddress(ADD_BASE_STATS) + ((pokemon - 1) * 32) + 17;

	byte sze_code = (byte)SendMessage(GetDlgItem(hWnd, CB_SPR_SIZE), CB_GETCURSEL, 0, 0);

	data[cur_address] = InterpretSizeCombo(sze_code);
}

byte FindPokemonFamily(std::vector<byte>& data, byte pokemon) {
	byte* pointer = new byte[3];
	unsigned int address = GetAddress(ADD_LEVEL_TABLE);
	pointer[0] = data[address];
	pointer[1] = data[address + 1];
	pointer[2] = FindBank(address);
	unsigned int current = PointerToAddress(pointer);
	int size = GetNumberOfTableElements(address, data);

	for (byte i = 0; i < size; i++) {
		pointer[0] = data[address + (i*2)];
		pointer[1] = data[address + 1 + (i*2)];
		pointer[2] = FindBank(address);
		current = PointerToAddress(pointer);
		
		while (data[current] != 0x00) {
			switch (data[current]) {
			case 0x01://Evolution by Level Up
				if (data[current + 2] == pokemon) {
					return FindPokemonFamily(data, i + 1);
				}
				current += 3;
				break;
			case 0x02://Evolution by Item
				if (data[current + 2] == pokemon) {
					return FindPokemonFamily(data, i + 1);
				}
				current += 3;
				break;
			case 0x03://Evolution by Trade
				if (data[current + 2] == pokemon) {
					return FindPokemonFamily(data, i + 1);
				}
				current += 3;
				break;
			case 0x04://Evolution by Happiness
				if (data[current + 2] == pokemon) {
					return FindPokemonFamily(data, i + 1);
				}
				current += 3;
				break;
			case 0x05://Evolution by Stats
				if (data[current + 3] == pokemon) {
					return FindPokemonFamily(data, i + 1);
				}
				current += 4;
				break;
			default://No Evolution Type
				break;
			}
		}
	}

	return pokemon;
}

byte GetRedValue(std::vector<byte>& data, HWND hWnd, byte pal) {
	unsigned int current = GetAddress(ADD_POKEMON_COLORS);
	byte id = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, 0, 0);
	byte buff = 0;
	byte red = 0;

	if (data.size() == 0) return 0xFF;

	current += (id * 8) + (pal * 2);

	red = data[current++];
	red &= 0x1F;//Keep bits 0001 1111

	switch (pal) {
	case 0:
		SetDlgItemText(hWnd, EB_POKE_RED1, std::to_wstring(InterpretNumbers(red) * 8).c_str());
		break;
	case 1:
		SetDlgItemText(hWnd, EB_POKE_RED2, std::to_wstring(InterpretNumbers(red) * 8).c_str());
		break;
	case 2:
		SetDlgItemText(hWnd, EB_SHINY_RED1, std::to_wstring(InterpretNumbers(red) * 8).c_str());
		break;
	case 3:
		SetDlgItemText(hWnd, EB_SHINY_RED2, std::to_wstring(InterpretNumbers(red) * 8).c_str());
		break;
	}

	return red * 8;
}

byte GetGreenValue(std::vector<byte>& data, HWND hWnd, byte pal) {
	unsigned int current = GetAddress(ADD_POKEMON_COLORS);
	byte id = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, 0, 0);
	byte buff = 0;
	byte green = 0;

	if (data.size() == 0) return 0xFF;

	current += (id * 8) + (pal * 2);

	green = data[current++];
	green = green >> 5;//1110 0000 -> 0000 0111
	green &= 7;//Keep bits 0000 0111
	buff = data[current++];
	buff &= 0x03;//Keep bits 0000 0011
	buff = buff << 3;//0000 0011 -> 0001 1000
	green += buff;//Merge bits 0001 1000 + 0000 0111 = 0001 1111

	switch (pal) {
	case 0:
		SetDlgItemText(hWnd, EB_POKE_GRN1, std::to_wstring(InterpretNumbers(green) * 8).c_str());
		break;
	case 1:
		SetDlgItemText(hWnd, EB_POKE_GRN2, std::to_wstring(InterpretNumbers(green) * 8).c_str());
		break;
	case 2:
		SetDlgItemText(hWnd, EB_SHINY_GRN1, std::to_wstring(InterpretNumbers(green) * 8).c_str());
		break;
	case 3:
		SetDlgItemText(hWnd, EB_SHINY_GRN2, std::to_wstring(InterpretNumbers(green) * 8).c_str());
		break;
	}

	return green * 8;
}

byte GetBlueValue(std::vector<byte>& data, HWND hWnd, byte pal) {
	unsigned int current = GetAddress(ADD_POKEMON_COLORS);
	byte id = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, 0, 0);
	byte blue = 0;

	if (data.size() == 0) return 0xFF;

	current += (id * 8) + (pal * 2) + 1;

	blue = data[current++];
	blue = blue >> 2;//0111 1100 -> 0001 1111
	blue &= 0x1F;//Keep bits 0001 1111

	switch (pal) {
	case 0:
		SetDlgItemText(hWnd, EB_POKE_BLU1, std::to_wstring(InterpretNumbers(blue) * 8).c_str());
		break;
	case 1:
		SetDlgItemText(hWnd, EB_POKE_BLU2, std::to_wstring(InterpretNumbers(blue) * 8).c_str());
		break;
	case 2:
		SetDlgItemText(hWnd, EB_SHINY_BLU1, std::to_wstring(InterpretNumbers(blue) * 8).c_str());
		break;
	case 3:
		SetDlgItemText(hWnd, EB_SHINY_BLU2, std::to_wstring(InterpretNumbers(blue) * 8).c_str());
		break;
	}

	return blue * 8;
}

int SetColorValue(std::vector<byte>& data, HWND hWnd, byte pal) {
	unsigned int current = GetAddress(ADD_POKEMON_COLORS);
	byte id = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, 0, 0);
	byte red = 0;
	byte green = 0;
	byte blue = 0;
	short color = 0;
	unsigned int temp = 0;
	wchar_t buff[4];
	std::wstring string;

	GetWindowText(GetDlgItem(hWnd, EB_POKE_RED1 + pal), (LPWSTR)buff, 4);
	string = buff;
	if (CheckIfNumber(string) == true) {
		temp = std::stoi(string) / 8;
		red = (byte)temp;
		red &= 0x1F;

	}
	else return - 1;
	GetWindowText(GetDlgItem(hWnd, EB_POKE_GRN1 + pal), (LPWSTR)buff, 4);
	string = buff;
	if (CheckIfNumber(string) == true) {
		temp = std::stoi(string) / 8;
		green = (byte)temp;
		green &= 0x1F;
	}
	else return -1;
	GetWindowText(GetDlgItem(hWnd, EB_POKE_BLU1 + pal), (LPWSTR)buff, 4);
	string = buff;
	if (CheckIfNumber(string) == true) {
		temp = std::stoi(string) / 8;
		blue = (byte)temp;
		blue &= 0x1F;
	}
	else return -1;

	color = blue;
	color = color << 5;
	color += green;
	color = color << 5;
	color += red;

	red = color;//Save the first byte
	color = color >> 8;
	blue = color;//Save the second byte

	current += (id * 8) + (2 * pal);

	data[current++] = red;
	data[current] = blue;

	return 0;
}