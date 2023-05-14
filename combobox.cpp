#include "combobox.h"
#include "profile.h"

HWND AddPokemonCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control) {
	HWND poke = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	switch (control) {
	case 0:
		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"NONE");

		for (int i = 0; i < 251; i++) {
			std::wstring name = InterpretPokemon(i + 1);

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	case 1:
		for (int i = 0; i < 251; i++) {
			std::wstring name = InterpretPokemon(i + 1);

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	}

	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"NONE");

	for (int i = 0; i < 251; i++) {
		std::wstring name = InterpretPokemon(i + 1);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}

	return poke;
}

HWND AddMovesCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control) {
	HWND move = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	switch (control) {
	case 0:
		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"NONE");

		for (int i = 0; i < 251; i++) {
			std::wstring name = InterpretMoves(i + 1);

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	case 1:
		for (int i = 0; i < 251; i++) {
			std::wstring name = InterpretMoves(i + 1);

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	}

	return move;
}

HWND AddItemsCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control) {
	HWND item = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	switch (control) {
	case 0:
		for (int i = 0; i < 251; i++) {
			std::wstring name = InterpretItems(i);

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	case 1:
		for (int i = 1; i < 251; i++) {
			std::wstring name = InterpretItems(i);

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	}

	return item;
}

HWND AddLevelsCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control) {
	HWND levels = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	switch (control) {
	case 0:
		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"NONE");

		for (int i = 0; i < 100; i++) {
			std::wstring name = std::to_wstring(InterpretNumbers(i + 1));

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	case 1:
		for (int i = 0; i < 100; i++) {
			std::wstring name = std::to_wstring(InterpretNumbers(i + 1));

			SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
		}
		break;
	}

	return levels;
}

HWND AddTMCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND tms = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM1(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}
	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM2(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}
	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM3(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}
	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM4(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}
	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM5(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}
	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM6(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}
	for (int i = 0; i < 8; i++) {
		std::wstring name = InterpretTM7(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}

	std::wstring name = InterpretTM8(0);
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());

	return tms;
}

HWND AddTypeCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND type = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	std::wstring name = L"NORMAL";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"FIGHTING";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"FLYING";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"POISON";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"GROUND";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"ROCK";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"BUG";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"GHOST";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"STEEL";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"FIRE";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"WATER";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"GRASS";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"ELECTRIC";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"PSYCHIC";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"ICE";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"DRAGON";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	name = L"DARK";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());

	return type;
}

HWND AddEggGroupCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND group = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	for (byte i = 1; i < 16; i++) {
		std::wstring name = InterpretEggGroup(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}

	return group;
}

HWND AddGenderCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND gen = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	std::wstring gender = L"MALE";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());
	gender = L"M 7:1 F";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());
	gender = L"M 3:1 F";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());
	gender = L"M 1:1 F";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());
	gender = L"M 1:3 F";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());
	gender = L"FEMALE";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());
	gender = L"UNKNOWN";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)gender.c_str());

	return gen;
}

HWND AddGrowthCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND combo = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	std::wstring rom_type = L"MED FAST";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());
	rom_type = L"MED SLOW";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());
	rom_type = L"FAST";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());
	rom_type = L"SLOW";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());

	return combo;
}

HWND AddSizeCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND combo = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	std::wstring sze_type = L"40x40";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)sze_type.c_str());
	sze_type = L"48x48";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)sze_type.c_str());
	sze_type = L"56x56";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)sze_type.c_str());

	return combo;
}

HWND AddRomCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND combo = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	std::wstring rom_type = L"GOLD/SILVER";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());
	rom_type = L"CRYSTAL";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());
	rom_type = L"GOLD/SILVER (JP)";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());
	rom_type = L"CRYSTAL (JP)";
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)rom_type.c_str());

	SendMessage(GetDlgItem(hWnd, inst), CB_SETCURSEL, 0, 0);

	return combo;
}

HWND AddEvoMethodCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND method = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	for (int i = 1; i < 6; i++) {
		std::wstring name = InterpretEvos(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}

	return method;
}

HWND AddEvoStatCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	HWND method = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst,
		NULL, NULL);

	for (int i = 1; i < 4; i++) {
		std::wstring name = InterpretStats(i);

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}

	return method;
}

HWND AddNumberCombo(HWND hWnd, int x, int y, int width, int height, int inst, int range) {
	HWND numbers = CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst, NULL, NULL);

	for (int i = 0; i < range; i++) {
		std::wstring name = std::to_wstring(InterpretNumbers(i));

		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)name.c_str());
	}

	return numbers;
}

void ChangeEvoCombos(HWND met, HWND con, HWND poke, HWND stat) {
	SendMessage(con, CB_RESETCONTENT, 0, 0);
	int index = (int)SendMessage(met, CB_GETCURSEL, 0, 0);
	std::wstring str = L"";

	EnableWindow(con, true);
	EnableWindow(poke, true);
	EnableWindow(stat, true);

	switch (index) {
	case 0:
		EnableWindow(stat, false);
		SendMessage(con, CB_RESETCONTENT, 0, 0);
		for (int i = 0; i < 100; i++) {
			str = std::to_wstring(InterpretNumbers(i + 1));

			SendMessage(con, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;
	case 1:
		EnableWindow(stat, false);
		SendMessage(con, CB_RESETCONTENT, 0, 0);
		for (int i = 0; i < 251; i++) {
			str = InterpretItems(i);

			SendMessage(con, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;
	case 2:
		EnableWindow(stat, false);
		SendMessage(con, CB_RESETCONTENT, 0, 0);
		for (int i = 0; i < 251; i++) {
			str = InterpretItems(i);

			SendMessage(con, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;
	case 3:
		EnableWindow(stat, false);
		SendMessage(con, CB_RESETCONTENT, 0, 0);
		for (int i = 1; i < 4; i++) {
			str = InterpretHapp(i);

			SendMessage(con, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;
	case 4:
		SendMessage(con, CB_RESETCONTENT, 0, 0);
		for (int i = 0; i < 100; i++) {
			str = std::to_wstring(InterpretNumbers(i + 1));

			SendMessage(con, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;
	default:
		EnableWindow(con, false);
		EnableWindow(poke, false);
		EnableWindow(stat, false);
		break;
	}


}

void CreateTagsCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	std::vector<std::wstring> tags = GetTagNames();

	CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst, NULL, NULL);

	for (std::wstring s : tags) {
		SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)s.c_str());
	}
}