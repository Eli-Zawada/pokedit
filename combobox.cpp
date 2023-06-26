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

void AddHoldEffectsCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst, NULL, NULL);

	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"NONE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEALING");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HELD 2");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"LEFTOVERS");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HELD 5");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PP RESTORE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"CLEANSE TAG");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL POISON");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL FREEZE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL BURN");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL SLEEP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL PARALYZE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL STATUS");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HEAL CONFUSION");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PREVENT POISON");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PREVENT BURN");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PREVENT FREEZE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PREVENT SLEEP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PREVENT PARALYZE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PREVENT CONFUSION");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HELD 3O");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"ATTACK UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"DEFENSE UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"SPEED UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"SPECIAL ATTACK UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"SPECIAL DEFENSE UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"ACCURACY UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"EVASION UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HELD 38");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"METAL POWDER");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"NORMAL BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"FIGHTING BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"FLYING BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"POISON BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"GROUND BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"ROCK BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"BUG BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"GHOST BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"FIRE BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"WATER BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"GRASS BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"ELECTRIC BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"PSYCHIC BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"ICE BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"DRAGON BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"DARK BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"STEEL BOOST");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"CATCH CHANCE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"HELD 71");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"ESCAPE");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"CRITICAL UP");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"QUICK CLAW");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"FLINCH");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"AMULET COIN");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"BRIGHTPOWDER");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"FOCUS BAND");
	SendMessage(GetDlgItem(hWnd, inst), CB_ADDSTRING, 0, (LPARAM)L"UNDEFINED");

}

void AddBlankCombo(HWND hWnd, int x, int y, int width, int height, int inst) {
	CreateWindow(L"COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, x, y, width, height, hWnd, (HMENU)inst, NULL, NULL);
}

int UpdateComboBox(std::vector<byte>& data, HWND hWnd, byte code) {
	if (data.empty() == true) return -1;
	SendMessage(hWnd, CB_RESETCONTENT, 0, 0);
	std::wstring str = L"";

	switch (code) {
	case 0:
		for (int i = 0; i < 256; i++) {
			str = InterpretItems(data, i);
			SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;

	case 1:
		for (int i = 0; i < 256; i++) {
			str = InterpretTrainerClass(data, i);
			SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;

	case 2:
		for (int i = 0; i < 256; i++) {
			str = InterpretPokemon(data, i);
			SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;

	case 3:
		for (int i = 0; i < 256; i++) {
			str = InterpretMoves(data, i);
			SendMessage(hWnd, CB_ADDSTRING, 0, (LPARAM)str.c_str());
		}
		break;
	}

	return 0;
}

int UpdateItemCombos(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;

	UpdateComboBox(data, GetDlgItem(hWnd, CB_ITEM_23), 0);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_ITEM_2), 0);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_ITEM_1), 0);
	SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_ITEM_2), 0);
	SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_ITEM_3), 0);
	SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_ITEM_4), 0);
	SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_ITEM_5), 0);
	SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_5), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_ITEM_6), 0);
	SendMessage(GetDlgItem(hWnd, CB_TRA_ITEM_6), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MART_ITEMS), 0);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_ITEMS), 0);

	return 0;
}

int UpdatePokemonCombos(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;

	UpdateComboBox(data, GetDlgItem(hWnd, CB_POKEMON), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_EVO_POK), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_POKE1), 2);
	SendMessage(GetDlgItem(hWnd, CB_TRA_POKE1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_POKE2), 2);
	SendMessage(GetDlgItem(hWnd, CB_TRA_POKE2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_POKE3), 2);
	SendMessage(GetDlgItem(hWnd, CB_TRA_POKE3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_POKE4), 2);
	SendMessage(GetDlgItem(hWnd, CB_TRA_POKE4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_POKE5), 2);
	SendMessage(GetDlgItem(hWnd, CB_TRA_POKE5), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_POKE6), 2);
	SendMessage(GetDlgItem(hWnd, CB_TRA_POKE6), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_1), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_2), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_3), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_4), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_5), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_6), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOR_POKE_7), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_1), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_2), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_3), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_4), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_5), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_6), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_DAY_POKE_7), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_1), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_2), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_3), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_4), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_5), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_6), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_NGT_POKE_7), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_SURF_POKE_1), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_SURF_POKE_2), 2);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_SURF_POKE_3), 2);

	return 0;
}

int UpdateMoveCombos(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;

	UpdateComboBox(data, GetDlgItem(hWnd, CB_MOVES), 3);
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE1_1), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE1_2), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE1_3), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE1_4), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE1_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE2_1), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE2_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE2_2), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE2_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE2_3), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE2_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE2_4), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE2_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE3_1), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE3_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE3_2), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE3_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE3_3), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE3_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE3_4), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE3_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE4_1), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE4_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE4_2), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE4_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE4_3), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE4_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE4_4), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE4_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE5_1), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE5_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE5_2), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE5_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE5_3), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE5_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE5_4), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE5_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE6_1), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE6_1), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE6_2), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE6_2), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE6_3), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE6_3), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_TRA_MOVE6_4), 3);
	SendMessage(GetDlgItem(hWnd, CB_TRA_MOVE6_4), CB_INSERTSTRING, 0, (LPARAM)L"NONE");
	UpdateComboBox(data, GetDlgItem(hWnd, CB_CHNG_TM), 3);

	return 0;
}