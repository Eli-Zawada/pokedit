#include "interpreter.h"

std::wstring InterpretCharacter(byte code) {
	std::wstring character;
	switch (code) {
	case 0x4F: {
		character = L"=";
		break;
	}
	case 0x51: {
		character = L"*";
		break;
	}
	case 0x52: {
		character = L"PLAYER";
		break;
	}
	case 0x53: {
		character = L"RIVAL";
		break;
	}
	case 0x54: {
		character = L"POKE";
		break;
	}
	case 0x55: {
		character = L"+";
		break;
	}
	case 0x56: {
		character = L"....";
		break;
	}
	case 0x57: {
		character = L"#";
		break;
	}
	case 0x60: {
		character = L"A";
		break;
	}
	case 0x61: {
		character = L"B";
		break;
	}
	case 0x72: {
		character = L"P";
		break;
	}
	case 0x75: {
		character = L"...";
		break;
	}
	case 0x7F: {
		character = L" ";
		break;
	}
	case 0x1F: {
		character = L" ";
		break;
	}
	case 0x80: {
		character = L"A";
		break;
	}
	case 0x81: {
		character = L"B";
		break;
	}
	case 0x82: {
		character = L"C";
		break;
	}
	case 0x83: {
		character = L"D";
		break;
	}
	case 0x84: {
		character = L"E";
		break;
	}
	case 0x85: {
		character = L"F";
		break;
	}
	case 0x86: {
		character = L"G";
		break;
	}
	case 0x87: {
		character = L"H";
		break;
	}
	case 0x88: {
		character = L"I";
		break;
	}
	case 0x89: {
		character = L"J";
		break;
	}
	case 0x8A: {
		character = L"K";
		break;
	}
	case 0x8B: {
		character = L"L";
		break;
	}
	case 0x8C: {
		character = L"M";
		break;
	}
	case 0x8D: {
		character = L"N";
		break;
	}
	case 0x8E: {
		character = L"O";
		break;
	}
	case 0x8F: {
		character = L"P";
		break;
	}
	case 0x90: {
		character = L"Q";
		break;
	}
	case 0x91: {
		character = L"R";
		break;
	}
	case 0x92: {
		character = L"S";
		break;
	}
	case 0x93: {
		character = L"T";
		break;
	}
	case 0x94: {
		character = L"U";
		break;
	}
	case 0x95: {
		character = L"V";
		break;
	}
	case 0x96: {
		character = L"W";
		break;
	}
	case 0x97: {
		character = L"X";
		break;
	}
	case 0x98: {
		character = L"Y";
		break;
	}
	case 0x99: {
		character = L"Z";
		break;
	}
	case 0x9A: {
		character = L"(";
		break;
	}
	case 0x9B: {
		character = L")";
		break;
	}
	case 0x9C: {
		character = L":";
		break;
	}
	case 0x9D: {
		character = L";";
		break;
	}
	case 0x9E: {
		character = L"[";
		break;
	}
	case 0x9F: {
		character = L"]";
		break;
	}
	case 0xA0: {
		character = L"a";
		break;
	}
	case 0xA1: {
		character = L"b";
		break;
	}
	case 0xA2: {
		character = L"c";
		break;
	}
	case 0xA3: {
		character = L"d";
		break;
	}
	case 0xA4: {
		character = L"e";
		break;
	}
	case 0xA5: {
		character = L"f";
		break;
	}
	case 0xA6: {
		character = L"g";
		break;
	}
	case 0xA7: {
		character = L"h";
		break;
	}
	case 0xA8: {
		character = L"i";
		break;
	}
	case 0xA9: {
		character = L"j";
		break;
	}
	case 0xAA: {
		character = L"k";
		break;
	}
	case 0xAB: {
		character = L"l";
		break;
	}
	case 0xAC: {
		character = L"m";
		break;
	}
	case 0xAD: {
		character = L"n";
		break;
	}
	case 0xAE: {
		character = L"o";
		break;
	}
	case 0xAF: {
		character = L"p";
		break;
	}
	case 0xB0: {
		character = L"q";
		break;
	}
	case 0xB1: {
		character = L"r";
		break;
	}
	case 0xB2: {
		character = L"s";
		break;
	}
	case 0xB3: {
		character = L"t";
		break;
	}
	case 0xB4: {
		character = L"u";
		break;
	}
	case 0xB5: {
		character = L"v";
		break;
	}
	case 0xB6: {
		character = L"w";
		break;
	}
	case 0xB7: {
		character = L"x";
		break;
	}
	case 0xB8: {
		character = L"y";
		break;
	}
	case 0xB9: {
		character = L"z";
		break;
	}
	case 0xBA: {
		character = L"?";
		break;
	}
	case 0xBB: {
		character = L"'d";
		break;
	}
	case 0xBC: {
		character = L"'l";
		break;
	}
	case 0xBD: {
		character = L"'s";
		break;
	}
	case 0xBE: {
		character = L"'t";
		break;
	}
	case 0xBF: {
		character = L"'v";
		break;
	}
	case 0xD0: {
		character = L"'d";
		break;
	}
	case 0xD1: {
		character = L"'l";
		break;
	}
	case 0xD2: {
		character = L"'m";
		break;
	}
	case 0xD3: {
		character = L"'r";
		break;
	}
	case 0xD4: {
		character = L"'s";
		break;
	}
	case 0xD5: {
		character = L"'t";
		break;
	}
	case 0xD6: {
		character = L"'v";
		break;
	}
	case 0xE0: {
		character = L"'";
		break;
	}
	case 0xE1: {
		character = L"PK";
		break;
	}
	case 0xE2: {
		character = L"MN";
		break;
	}
	case 0xE3: {
		character = L"-";
		break;
	}
	case 0xE4: {
		character = L"'r";
		break;
	}
	case 0xE5: {
		character = L"'m";
		break;
	}
	case 0xE6: {
		character = L"?";
		break;
	}
	case 0xE7: {
		character = L"!";
		break;
	}
	case 0xE8: {
		character = L".";
		break;
	}
	case 0xE9: {
		character = L"&";
		break;
	}
	case 0xEA: {
		character = L"é";
		break;
	}
	case 0xED: {
		character = L"-->";
		break;
	}
	case 0xEF: {
		character = L"(M)";
		break;
	}
	case 0xF0: {
		character = L"£";
		break;
	}
	case 0xF1: {
		character = L"x";
		break;
	}
	case 0xF2: {
		character = L".";
		break;
	}
	case 0xF3: {
		character = L"/";
		break;
	}
	case 0xF4: {
		character = L",";
		break;
	}
	case 0xF5: {
		character = L"(F)";
		break;
	}
	case 0xF6: {
		character = L"0";
		break;
	}
	case 0xF7: {
		character = L"1";
		break;
	}
	case 0xF8: {
		character = L"2";
		break;
	}
	case 0xF9: {
		character = L"3";
		break;
	}
	case 0xFA: {
		character = L"4";
		break;
	}
	case 0xFB: {
		character = L"5";
		break;
	}
	case 0xFC: {
		character = L"6";
		break;
	}
	case 0xFD: {
		character = L"7";
		break;
	}
	case 0xFE: {
		character = L"8";
		break;
	}
	case 0xFF: {
		character = L"9";
		break;
	}

	}
	return character;
}

int InterpretNumbers(byte value) {
	return (int)value;
}

std::wstring InterpretEvos(byte code) {
	std::wstring name = L"UNKNOWN";

	switch (code) {
	case (char)0x00: {
		name = L"DOES NOT EVOLVE";
		break;
	}
	case (char)0x01: {
		name = L"LEVEL UP";
		break;
	}
	case (char)0x02: {
		name = L"ITEM";
		break;
	}
	case (char)0x03: {
		name = L"TRADE ITEM";
		break;
	}
	case (char)0x04: {
		name = L"HAPPINESS";
		break;
	}
	case (char)0x05: {
		name = L"STATS";
		break;
	}
	}

	return name;
}

std::wstring InterpretHapp(byte code) {
	std::wstring name = L"";

	switch (code) {
	case (char)0x01: {
		name = L"ANY TIME";
		break;
	}
	case (char)0x02: {
		name = L"DAY TIME";
		break;
	}
	case (char)0x03: {
		name = L"NIGHT TIME";
		break;
	}
	}

	return name;
}

std::wstring InterpretStats(byte code) {
	std::wstring name = L"UNKNOWN";

	switch (code) {
	case (char)0x01: {
		name = L"ATK > DEF";
		break;
	}
	case (char)0x02: {
		name = L"ATK < DEF";
		break;
	}
	case (char)0x03: {
		name = L"ATK = DEF";
		break;
	}
	}

	return name;
}

std::wstring InterpretEggGroup(byte code) {
	std::wstring name = L"UNKNOWN";

	switch (code) {
	case (char)0x01: {
		name = L"MONSTER";
		break;
	}
	case (char)0x02: {
		name = L"WATER 1";
		break;
	}
	case (char)0x03: {
		name = L"BUG";
		break;
	}
	case (char)0x04: {
		name = L"FLYING";
		break;
	}
	case (char)0x05: {
		name = L"FIELD";
		break;
	}
	case (char)0x06: {
		name = L"FAIRY";
		break;
	}
	case (char)0x07: {
		name = L"GRASS";
		break;
	}
	case (char)0x08: {
		name = L"HUMAN-LIKE";
		break;
	}
	case (char)0x09: {
		name = L"WATER 3";
		break;
	}
	case (char)0x0A: {
		name = L"MINERAL";
		break;
	}
	case (char)0x0B: {
		name = L"AMORPHOUS";
		break;
	}
	case (char)0x0C: {
		name = L"WATER 2";
		break;
	}
	case (char)0x0D: {
		name = L"DITTO";
		break;
	}
	case (char)0x0E: {
		name = L"DRAGON";
		break;
	}
	case (char)0x0F: {
		name = L"UNKNOWN";
		break;
	}
	}
	return name;
}

int InterpretGenderRatio(byte code) {
	int ratio = 0xFF;

	switch (code) {
	case 0x00: {
		ratio = 0;
		break;
	}
	case 0x1F: {
		ratio = 1;
		break;
	}
	case 0x3F: {
		ratio = 2;
		break;
	}
	case 0x7F: {
		ratio = 3;
		break;
	}
	case 0xBF: {
		ratio = 4;
		break;
	}
	case 0xFE: {
		ratio = 5;
		break;
	}
	case 0xFF: {
		ratio = 6;
		break;
	}
	}

	return ratio;
}

byte InterpretGenderCombo(int code) {
	byte sel = 0xFF;

	switch (code) {
	case 0: {
		sel = 0x00;
		break;
	}
	case 1: {
		sel = 0x1F;
		break;
	}
	case 2: {
		sel = 0x3F;
		break;
	}
	case 3: {
		sel = 0x7F;
		break;
	}
	case 4: {
		sel = 0xBF;
		break;
	}
	case 5: {
		sel = 0xFE;
		break;
	}
	case 6: {
		sel = 0xFF;
		break;
	}
	}

	return sel;
}

int InterpretTyping(byte code) {
	int name = -1;

	switch (code) {
	case (char)0x00: {
		name = 0;
		break;
	}
	case (char)0x01: {
		name = 1;
		break;
	}
	case (char)0x02: {
		name = 2;
		break;
	}
	case (char)0x03: {
		name = 3;
		break;
	}
	case (char)0x04: {
		name = 4;
		break;
	}
	case (char)0x05: {
		name = 5;
		break;
	}
	case (char)0x07: {
		name = 6;
		break;
	}
	case (char)0x08: {
		name = 7;
		break;
	}
	case (char)0x09: {
		name = 8;
		break;
	}
	case (char)0x14: {
		name = 9;
		break;
	}
	case (char)0x15: {
		name = 10;
		break;
	}
	case (char)0x16: {
		name = 11;
		break;
	}
	case (char)0x17: {
		name = 12;
		break;
	}
	case (char)0x18: {
		name = 13;
		break;
	}
	case (char)0x19: {
		name = 14;
		break;
	}
	case (char)0x1A: {
		name = 15;
		break;
	}
	case (char)0x1B: {
		name = 16;
		break;
	}
	}
	return name;
}

char InterpretTypingCombo(int code) {
	char type = -1;

	switch (code) {
	case 0: {
		type = 0x00;
		break;
	}
	case 1: {
		type = 0x01;
		break;
	}
	case 2: {
		type = 0x02;
		break;
	}
	case 3: {
		type = 0x03;
		break;
	}
	case 4: {
		type = 0x04;
		break;
	}
	case 5: {
		type = 0x05;
		break;
	}
	case 6: {
		type = 0x07;
		break;
	}
	case 7: {
		type = 0x08;
		break;
	}
	case 8: {
		type = 0x09;
		break;
	}
	case 9: {
		type = 0x14;
		break;
	}
	case 10: {
		type = 0x15;
		break;
	}
	case 11: {
		type = 0x16;
		break;
	}
	case 12: {
		type = 0x17;
		break;
	}
	case 13: {
		type = 0x18;
		break;
	}
	case 14: {
		type = 0x19;
		break;
	}
	case 15: {
		type = 0x1A;
		break;
	}
	case 16: {
		type = 0x1B;
		break;
	}
	}

	return type;
}

byte TextToHex(wchar_t character) {
	byte code = 0x57;
	switch (character) {
	case L'=': {
		code = 0x4F;
		break;
	}
	case L'*': {
		code = 0x51;
		break;
	}
	case L'+': {
		code = 0x55;
		break;
	}
	case L'#': {
		code = 0x57;
		break;
	}
	case L' ': {
		code = 0x7F;
		break;
	}
	case L'A': {
		code = 0x80;
		break;
	}
	case L'B': {
		code = 0x81;
		break;
	}
	case L'C': {
		code = 0x82;
		break;
	}
	case L'D': {
		code = 0x83;
		break;
	}
	case L'E': {
		code = 0x84;
		break;
	}
	case L'F': {
		code = 0x85;
		break;
	}
	case L'G': {
		code = 0x86;
		break;
	}
	case L'H': {
		code = 0x87;
		break;
	}
	case L'I': {
		code = 0x88;
		break;
	}
	case L'J': {
		code = 0x89;
		break;
	}
	case L'K': {
		code = 0x8A;
		break;
	}
	case L'L': {
		code = 0x8B;
		break;
	}
	case L'M': {
		code = 0x8C;
		break;
	}
	case L'N': {
		code = 0x8D;
		break;
	}
	case L'O': {
		code = 0x8E;
		break;
	}
	case L'P': {
		code = 0x8F;
		break;
	}
	case L'Q': {
		code = 0x90;
		break;
	}
	case L'R': {
		code = 0x91;
		break;
	}
	case L'S': {
		code = 0x92;
		break;
	}
	case L'T': {
		code = 0x93;
		break;
	}
	case L'U': {
		code = 0x94;
		break;
	}
	case L'V': {
		code = 0x95;
		break;
	}
	case L'W': {
		code = 0x96;
		break;
	}
	case L'X': {
		code = 0x97;
		break;
	}
	case L'Y': {
		code = 0x98;
		break;
	}
	case L'Z': {
		code = 0x99;
		break;
	}
	case L'(': {
		code = 0x9A;
		break;
	}
	case L')': {
		code = 0x9B;
		break;
	}
	case L':': {
		code = 0x9C;
		break;
	}
	case L';': {
		code = 0x9D;
		break;
	}
	case L'[': {
		code = 0x9E;
		break;
	}
	case L']': {
		code = 0x9F;
		break;
	}
	case L'a': {
		code = 0xA0;
		break;
	}
	case L'b': {
		code = 0xA1;
		break;
	}
	case L'c': {
		code = 0xA2;
		break;
	}
	case L'd': {
		code = 0xA3;
		break;
	}
	case L'e': {
		code = 0xA4;
		break;
	}
	case L'f': {
		code = 0xA5;
		break;
	}
	case L'g': {
		code = 0xA6;
		break;
	}
	case L'h': {
		code = 0xA7;
		break;
	}
	case L'i': {
		code = 0xA8;
		break;
	}
	case L'j': {
		code = 0xA9;
		break;
	}
	case L'k': {
		code = 0xAA;
		break;
	}
	case L'l': {
		code = 0xAB;
		break;
	}
	case L'm': {
		code = 0xAC;
		break;
	}
	case L'n': {
		code = 0xAD;
		break;
	}
	case L'o': {
		code = 0xAE;
		break;
	}
	case L'p': {
		code = 0xAF;
		break;
	}
	case L'q': {
		code = 0xB0;
		break;
	}
	case L'r': {
		code = 0xB1;
		break;
	}
	case L's': {
		code = 0xB2;
		break;
	}
	case L't': {
		code = 0xB3;
		break;
	}
	case L'u': {
		code = 0xB4;
		break;
	}
	case L'v': {
		code = 0xB5;
		break;
	}
	case L'w': {
		code = 0xB6;
		break;
	}
	case L'x': {
		code = 0xB7;
		break;
	}
	case L'y': {
		code = 0xB8;
		break;
	}
	case L'z': {
		code = 0xB9;
		break;
	}
	case L'?': {
		code = 0xE6;
		break;
	}
	case L'-': {
		code = 0xE3;
		break;
	}
	case L'!': {
		code = 0xE7;
		break;
	}
	case L'.': {
		code = 0xE8;
		break;
	}
	case L'&': {
		code = 0xE9;
		break;
	}
	case L'é': {
		code = 0xEA;
		break;
	}
	//case 0xEF: {
	//	code = (M)";
	//	break;
	//}
	case L'£': {
		code = 0xF0;
		break;
	}
	case L'/': {
		code = 0xF3;
		break;
	}
	case L',': {
		code = 0xF4;
		break;
	}
	//case 0xF5: {
	//	code = (F)";
	//	break;
	//}
	case L'0': {
		code = 0xF6;
		break;
	}
	case L'1': {
		code = 0xF7;
		break;
	}
	case L'2': {
		code = 0xF8;
		break;
	}
	case L'3': {
		code = 0xF9;
		break;
	}
	case L'4': {
		code = 0xFA;
		break;
	}
	case L'5': {
		code = 0xFB;
		break;
	}
	case L'6': {
		code = 0xFC;
		break;
	}
	case L'7': {
		code = 0xFD;
		break;
	}
	case L'8': {
		code = 0xFE;
		break;
	}
	case L'9': {
		code = 0xFF;
		break;
	}

	}
	return code;
}

char InterpretSizeCombo(int code) {
	char size = -1;

	switch (code) {
	case 0: {
		size = 0x55;
		break;
	}
	case 1: {
		size = 0x66;
		break;
	}
	case 2: {
		size = 0x77;
		break;
	}
	}

	return size;
}

std::wstring InterpretPokemon(char code) {
	std::wstring name = L"BAD EGG";

	switch (code) {
	case (char)0x01: {
		name = L"BULBASAUR";
		break;
	}
	case (char)0x02: {
		name = L"IVYSAUR";
		break;
	}
	case (char)0x03: {
		name = L"VENUSAUR";
		break;
	}
	case (char)0x04: {
		name = L"CHARMANDER";
		break;
	}
	case (char)0x05: {
		name = L"CHARMELEON";
		break;
	}
	case (char)0x06: {
		name = L"CHARIZARD";
		break;
	}
	case (char)0x07: {
		name = L"SQUIRTLE";
		break;
	}
	case (char)0x08: {
		name = L"WARTORTLE";
		break;
	}
	case (char)0x09: {
		name = L"BLASTOISE";
		break;
	}
	case (char)0x0A: {
		name = L"CATERPIE";
		break;
	}
	case (char)0x0B: {
		name = L"METAPOD";
		break;
	}
	case (char)0x0C: {
		name = L"BUTTERFREE";
		break;
	}
	case (char)0x0D: {
		name = L"WEEDLE";
		break;
	}
	case (char)0x0E: {
		name = L"KAKUNA";
		break;
	}
	case (char)0x0F: {
		name = L"BEEDRILL";
		break;
	}
	case (char)0x10: {
		name = L"PIDGEY";
		break;
	}
	case (char)0x11: {
		name = L"PIDGEOTTO";
		break;
	}
	case (char)0x12: {
		name = L"PIDGEOT";
		break;
	}
	case (char)0x13: {
		name = L"RATTATA";
		break;
	}
	case (char)0x14: {
		name = L"RATICATE";
		break;
	}
	case (char)0x15: {
		name = L"SPEAROW";
		break;
	}
	case (char)0x16: {
		name = L"FEAROW";
		break;
	}
	case (char)0x17: {
		name = L"EKANS";
		break;
	}
	case (char)0x18: {
		name = L"ARBOK";
		break;
	}
	case (char)0x19: {
		name = L"PIKACHU";
		break;
	}
	case (char)0x1A: {
		name = L"RAICHU";
		break;
	}
	case (char)0x1B: {
		name = L"SANDSHREW";
		break;
	}
	case (char)0x1C: {
		name = L"SANDSLASH";
		break;
	}
	case (char)0x1D: {
		name = L"NIDORAN F";
		break;
	}
	case (char)0x1E: {
		name = L"NIDORINA";
		break;
	}
	case (char)0x1F: {
		name = L"NIDOQUEEN";
		break;
	}
	case (char)0x20: {
		name = L"NIDORAN M";
		break;
	}
	case (char)0x21: {
		name = L"NIDORINO";
		break;
	}
	case (char)0x22: {
		name = L"NIDOKING";
		break;
	}
	case (char)0x23: {
		name = L"CLEFAIRY";
		break;
	}
	case (char)0x24: {
		name = L"CLEFABLE";
		break;
	}
	case (char)0x25: {
		name = L"VULPIX";
		break;
	}
	case (char)0x26: {
		name = L"NINETALES";
		break;
	}
	case (char)0x27: {
		name = L"JIGGLYPUFF";
		break;
	}
	case (char)0x28: {
		name = L"WIGGLYTUFF";
		break;
	}
	case (char)0x29: {
		name = L"ZUBAT";
		break;
	}
	case (char)0x2A: {
		name = L"GOLBAT";
		break;
	}
	case (char)0x2B: {
		name = L"ODDISH";
		break;
	}
	case (char)0x2C: {
		name = L"GLOOM";
		break;
	}
	case (char)0x2D: {
		name = L"VILEPLUME";
		break;
	}
	case (char)0x2E: {
		name = L"PARAS";
		break;
	}
	case (char)0x2F: {
		name = L"PARASECT";
		break;
	}
	case (char)0x30: {
		name = L"VENONAT";
		break;
	}
	case (char)0x31: {
		name = L"VENOMOTH";
		break;
	}
	case (char)0x32: {
		name = L"DIGLETT";
		break;
	}
	case (char)0x33: {
		name = L"DUGTRIO";
		break;
	}
	case (char)0x34: {
		name = L"MEOWTH";
		break;
	}
	case (char)0x35: {
		name = L"PERSIAN";
		break;
	}
	case (char)0x36: {
		name = L"PSYDUCK";
		break;
	}
	case (char)0x37: {
		name = L"GOLDUCK";
		break;
	}
	case (char)0x38: {
		name = L"MANKEY";
		break;
	}
	case (char)0x39: {
		name = L"PRIMEAPE";
		break;
	}
	case (char)0x3A: {
		name = L"GROWLITHE";
		break;
	}
	case (char)0x3B: {
		name = L"ARCANINE";
		break;
	}
	case (char)0x3C: {
		name = L"POLIWAG";
		break;
	}
	case (char)0x3D: {
		name = L"POLIWHIRL";
		break;
	}
	case (char)0x3E: {
		name = L"POLIWRATH";
		break;
	}
	case (char)0x3F: {
		name = L"ABRA";
		break;
	}
	case (char)0x40: {
		name = L"KADABRA";
		break;
	}
	case (char)0x41: {
		name = L"ALAKAZAM";
		break;
	}
	case (char)0x42: {
		name = L"MACHOP";
		break;
	}
	case (char)0x43: {
		name = L"MACHOKE";
		break;
	}
	case (char)0x44: {
		name = L"MACHAMP";
		break;
	}
	case (char)0x45: {
		name = L"BELLSPROUT";
		break;
	}
	case (char)0x46: {
		name = L"WEEPINBELL";
		break;
	}
	case (char)0x47: {
		name = L"VICTREEBEL";
		break;
	}
	case (char)0x48: {
		name = L"TENTACOOL";
		break;
	}
	case (char)0x49: {
		name = L"TENTACRUEL";
		break;
	}
	case (char)0x4A: {
		name = L"GEODUDE";
		break;
	}
	case (char)0x4B: {
		name = L"GRAVELER";
		break;
	}
	case (char)0x4C: {
		name = L"GOLEM";
		break;
	}
	case (char)0x4D: {
		name = L"PONYTA";
		break;
	}
	case (char)0x4E: {
		name = L"RAPIDASH";
		break;
	}
	case (char)0x4F: {
		name = L"SLOWPOKE";
		break;
	}
	case (char)0x50: {
		name = L"SLOWBRO";
		break;
	}
	case (char)0x51: {
		name = L"MAGNEMITE";
		break;
	}
	case (char)0x52: {
		name = L"MAGNETON";
		break;
	}
	case (char)0x53: {
		name = L"FARFETCH'D";
		break;
	}
	case (char)0x54: {
		name = L"DODUO";
		break;
	}
	case (char)0x55: {
		name = L"DODRIO";
		break;
	}
	case (char)0x56: {
		name = L"SEEL";
		break;
	}
	case (char)0x57: {
		name = L"DEWGONG";
		break;
	}
	case (char)0x58: {
		name = L"GRIMER";
		break;
	}
	case (char)0x59: {
		name = L"MUK";
		break;
	}
	case (char)0x5A: {
		name = L"SHELLDER";
		break;
	}
	case (char)0x5B: {
		name = L"CLOYSTER";
		break;
	}
	case (char)0x5C: {
		name = L"GASTLY";
		break;
	}
	case (char)0x5D: {
		name = L"HAUNTER";
		break;
	}
	case (char)0x5E: {
		name = L"GENGAR";
		break;
	}
	case (char)0x5F: {
		name = L"ONIX";
		break;
	}
	case (char)0x60: {
		name = L"DROWZEE";
		break;
	}
	case (char)0x61: {
		name = L"HYPNO";
		break;
	}
	case (char)0x62: {
		name = L"KRABBY";
		break;
	}
	case (char)0x63: {
		name = L"KINGLER";
		break;
	}
	case (char)0x64: {
		name = L"VOLTORB";
		break;
	}
	case (char)0x65: {
		name = L"ELECTRODE";
		break;
	}
	case (char)0x66: {
		name = L"EXEGGCUTE";
		break;
	}
	case (char)0x67: {
		name = L"EXEGGUTOR";
		break;
	}
	case (char)0x68: {
		name = L"CUBONE";
		break;
	}
	case (char)0x69: {
		name = L"MAROWAK";
		break;
	}
	case (char)0x6A: {
		name = L"HITMONLEE";
		break;
	}
	case (char)0x6B: {
		name = L"HITMONCHAN";
		break;
	}
	case (char)0x6C: {
		name = L"LICKITUNG";
		break;
	}
	case (char)0x6D: {
		name = L"KOFFING";
		break;
	}
	case (char)0x6E: {
		name = L"WEEZING";
		break;
	}
	case (char)0x6F: {
		name = L"RHYHORN";
		break;
	}
	case (char)0x70: {
		name = L"RHYDON";
		break;
	}
	case (char)0x71: {
		name = L"CHANSEY";
		break;
	}
	case (char)0x72: {
		name = L"TANGELA";
		break;
	}
	case (char)0x73: {
		name = L"KANGASKHAN";
		break;
	}
	case (char)0x74: {
		name = L"HORSEA";
		break;
	}
	case (char)0x75: {
		name = L"SEADRA";
		break;
	}
	case (char)0x76: {
		name = L"GOLDEEN";
		break;
	}
	case (char)0x77: {
		name = L"SEAKING";
		break;
	}
	case (char)0x78: {
		name = L"STARYU";
		break;
	}
	case (char)0x79: {
		name = L"STARMIE";
		break;
	}
	case (char)0x7A: {
		name = L"MR. MIME";
		break;
	}
	case (char)0x7B: {
		name = L"SCYTHER";
		break;
	}
	case (char)0x7C: {
		name = L"JYNX";
		break;
	}
	case (char)0x7D: {
		name = L"ELECTABUZZ";
		break;
	}
	case (char)0x7E: {
		name = L"MAGMAR";
		break;
	}
	case (char)0x7F: {
		name = L"PINSIR";
		break;
	}
	case (char)0x80: {
		name = L"TAUROS";
		break;
	}
	case (char)0x81: {
		name = L"MAGIKARP";
		break;
	}
	case (char)0x82: {
		name = L"GYARADOS";
		break;
	}
	case (char)0x83: {
		name = L"LAPRAS";
		break;
	}
	case (char)0x84: {
		name = L"DITTO";
		break;
	}
	case (char)0x85: {
		name = L"EEVEE";
		break;
	}
	case (char)0x86: {
		name = L"VAPOREON";
		break;
	}
	case (char)0x87: {
		name = L"JOLTEON";
		break;
	}
	case (char)0x88: {
		name = L"FLAREON";
		break;
	}
	case (char)0x89: {
		name = L"PORYGON";
		break;
	}
	case (char)0x8A: {
		name = L"OMANYTE";
		break;
	}
	case (char)0x8B: {
		name = L"OMASTAR";
		break;
	}
	case (char)0x8C: {
		name = L"KABUTO";
		break;
	}
	case (char)0x8D: {
		name = L"KABUTOPS";
		break;
	}
	case (char)0x8E: {
		name = L"AERODACTYL";
		break;
	}
	case (char)0x8F: {
		name = L"SNORLAX";
		break;
	}
	case (char)0x90: {
		name = L"ARTICUNO";
		break;
	}
	case (char)0x91: {
		name = L"ZAPDOS";
		break;
	}
	case (char)0x92: {
		name = L"MOLTRES";
		break;
	}
	case (char)0x93: {
		name = L"DRATINI";
		break;
	}
	case (char)0x94: {
		name = L"DRAGONAIR";
		break;
	}
	case (char)0x95: {
		name = L"DRAGONITE";
		break;
	}
	case (char)0x96: {
		name = L"MEWTWO";
		break;
	}
	case (char)0x97: {
		name = L"MEW";
		break;
	}
	case (char)0x98: {
		name = L"CHIKORITA";
		break;
	}
	case (char)0x99: {
		name = L"BAYLEEF";
		break;
	}
	case (char)0x9A: {
		name = L"MEGANIUM";
		break;
	}
	case (char)0x9B: {
		name = L"CYNDAQUIL";
		break;
	}
	case (char)0x9C: {
		name = L"QUILAVA";
		break;
	}
	case (char)0x9D: {
		name = L"TYPHLOSION";
		break;
	}
	case (char)0x9E: {
		name = L"TOTODILE";
		break;
	}
	case (char)0x9F: {
		name = L"CROCONAW";
		break;
	}
	case (char)0xA0: {
		name = L"FERALIGATR";
		break;
	}
	case (char)0xA1: {
		name = L"SENTRET";
		break;
	}
	case (char)0xA2: {
		name = L"FURRET";
		break;
	}
	case (char)0xA3: {
		name = L"HOOTHOOT";
		break;
	}
	case (char)0xA4: {
		name = L"NOCTOWL";
		break;
	}
	case (char)0xA5: {
		name = L"LEDYBA";
		break;
	}
	case (char)0xA6: {
		name = L"LEDIAN";
		break;
	}
	case (char)0xA7: {
		name = L"SPINARAK";
		break;
	}
	case (char)0xA8: {
		name = L"ARIADOS";
		break;
	}
	case (char)0xA9: {
		name = L"CROBAT";
		break;
	}
	case (char)0xAA: {
		name = L"CHINCHOU";
		break;
	}
	case (char)0xAB: {
		name = L"LANTURN";
		break;
	}
	case (char)0xAC: {
		name = L"PICHU";
		break;
	}
	case (char)0xAD: {
		name = L"CLEFFA";
		break;
	}
	case (char)0xAE: {
		name = L"IGGLYBUFF";
		break;
	}
	case (char)0xAF: {
		name = L"TOGEPI";
		break;
	}
	case (char)0xB0: {
		name = L"TOGETIC";
		break;
	}
	case (char)0xB1: {
		name = L"NATU";
		break;
	}
	case (char)0xB2: {
		name = L"XATU";
		break;
	}
	case (char)0xB3: {
		name = L"MAREEP";
		break;
	}
	case (char)0xB4: {
		name = L"FLAAFFY";
		break;
	}
	case (char)0xB5: {
		name = L"AMPHAROS";
		break;
	}
	case (char)0xB6: {
		name = L"BELLOSSOM";
		break;
	}
	case (char)0xB7: {
		name = L"MARILL";
		break;
	}
	case (char)0xB8: {
		name = L"AZUMARILL";
		break;
	}
	case (char)0xB9: {
		name = L"SUDOWOODO";
		break;
	}
	case (char)0xBA: {
		name = L"POLITOED";
		break;
	}
	case (char)0xBB: {
		name = L"HOPPIP";
		break;
	}
	case (char)0xBC: {
		name = L"SKIPLOOM";
		break;
	}
	case (char)0xBD: {
		name = L"JUMPLUFF";
		break;
	}
	case (char)0xBE: {
		name = L"AIPOM";
		break;
	}
	case (char)0xBF: {
		name = L"SUNKERN";
		break;
	}
	case (char)0xC0: {
		name = L"SUNFLORA";
		break;
	}
	case (char)0xC1: {
		name = L"YANMA";
		break;
	}
	case (char)0xC2: {
		name = L"WOOPER";
		break;
	}
	case (char)0xC3: {
		name = L"QUAGSIRE";
		break;
	}
	case (char)0xC4: {
		name = L"ESPEON";
		break;
	}
	case (char)0xC5: {
		name = L"UMBREON";
		break;
	}
	case (char)0xC6: {
		name = L"MURKROW";
		break;
	}
	case (char)0xC7: {
		name = L"SLOWKING";
		break;
	}
	case (char)0xC8: {
		name = L"MISDREAVUS";
		break;
	}
	case (char)0xC9: {
		name = L"UNOWN";
		break;
	}
	case (char)0xCA: {
		name = L"WOBBUFFET";
		break;
	}
	case (char)0xCB: {
		name = L"GIRAFARIG";
		break;
	}
	case (char)0xCC: {
		name = L"PINECO";
		break;
	}
	case (char)0xCD: {
		name = L"FORRETRESS";
		break;
	}
	case (char)0xCE: {
		name = L"DUNSPARCE";
		break;
	}
	case (char)0xCF: {
		name = L"GLIGAR";
		break;
	}
	case (char)0xD0: {
		name = L"STEELIX";
		break;
	}
	case (char)0xD1: {
		name = L"SNUBBULL";
		break;
	}
	case (char)0xD2: {
		name = L"GRANBULL";
		break;
	}
	case (char)0xD3: {
		name = L"QWILFISH";
		break;
	}
	case (char)0xD4: {
		name = L"SCIZOR";
		break;
	}
	case (char)0xD5: {
		name = L"SHUCKLE";
		break;
	}
	case (char)0xD6: {
		name = L"HERACROSS";
		break;
	}
	case (char)0xD7: {
		name = L"SNEASEL";
		break;
	}
	case (char)0xD8: {
		name = L"TEDDIURSA";
		break;
	}
	case (char)0xD9: {
		name = L"URSARING";
		break;
	}
	case (char)0xDA: {
		name = L"SLUGMA";
		break;
	}
	case (char)0xDB: {
		name = L"MAGCARGO";
		break;
	}
	case (char)0xDC: {
		name = L"SWINUB";
		break;
	}
	case (char)0xDD: {
		name = L"PILOSWINE";
		break;
	}
	case (char)0xDE: {
		name = L"CORSOLA";
		break;
	}
	case (char)0xDF: {
		name = L"REMORAID";
		break;
	}
	case (char)0xE0: {
		name = L"OCTILLERY";
		break;
	}
	case (char)0xE1: {
		name = L"DELIBIRD";
		break;
	}
	case (char)0xE2: {
		name = L"MANTINE";
		break;
	}
	case (char)0xE3: {
		name = L"SKARMORY";
		break;
	}
	case (char)0xE4: {
		name = L"HOUNDOUR";
		break;
	}
	case (char)0xE5: {
		name = L"HOUNDOOM";
		break;
	}
	case (char)0xE6: {
		name = L"KINGDRA";
		break;
	}
	case (char)0xE7: {
		name = L"PHANPY";
		break;
	}
	case (char)0xE8: {
		name = L"DONPHAN";
		break;
	}
	case (char)0xE9: {
		name = L"PORYGON2";
		break;
	}
	case (char)0xEA: {
		name = L"STANTLER";
		break;
	}
	case (char)0xEB: {
		name = L"SMEARGLE";
		break;
	}
	case (char)0xEC: {
		name = L"TYROGUE";
		break;
	}
	case (char)0xED: {
		name = L"HITMONTOP";
		break;
	}
	case (char)0xEE: {
		name = L"SMOOCHUM";
		break;
	}
	case (char)0xEF: {
		name = L"ELEKID";
		break;
	}
	case (char)0xF0: {
		name = L"MAGBY";
		break;
	}
	case (char)0xF1: {
		name = L"MILTANK";
		break;
	}
	case (char)0xF2: {
		name = L"BLISSEY";
		break;
	}
	case (char)0xF3: {
		name = L"RAIKOU";
		break;
	}
	case (char)0xF4: {
		name = L"ENTEI";
		break;
	}
	case (char)0xF5: {
		name = L"SUICUNE";
		break;
	}
	case (char)0xF6: {
		name = L"LARVITAR";
		break;
	}
	case (char)0xF7: {
		name = L"PUPITAR";
		break;
	}
	case (char)0xF8: {
		name = L"TYRANITAR";
		break;
	}
	case (char)0xF9: {
		name = L"LUGIA";
		break;
	}
	case (char)0xFA: {
		name = L"HO-OH";
		break;
	}
	case (char)0xFB: {
		name = L"CELEBI";
		break;
	}
	}

	return name;
}

short InterpretFamily(char code) {
	short fam = 0;

	switch (code) {
	case (char)0x01: {
		fam = 1;
		break;
	}
	case (char)0x02: {
		fam = 1;
		break;
	}
	case (char)0x03: {
		fam = 1;
		break;
	}
	case (char)0x04: {
		fam = 4;
		break;
	}
	case (char)0x05: {
		fam = 4;
		break;
	}
	case (char)0x06: {
		fam = 4;
		break;
	}
	case (char)0x07: {
		fam = 7;
		break;
	}
	case (char)0x08: {
		fam = 7;
		break;
	}
	case (char)0x09: {
		fam = 7;
		break;
	}
	case (char)0x0A: {
		fam = 10;
		break;
	}
	case (char)0x0B: {
		fam = 10;
		break;
	}
	case (char)0x0C: {
		fam = 10;
		break;
	}
	case (char)0x0D: {
		fam = 13;
		break;
	}
	case (char)0x0E: {
		fam = 13;
		break;
	}
	case (char)0x0F: {
		fam = 13;
		break;
	}
	case (char)0x10: {
		fam = 16;
		break;
	}
	case (char)0x11: {
		fam = 16;
		break;
	}
	case (char)0x12: {
		fam = 16;
		break;
	}
	case (char)0x13: {
		fam = 19;
		break;
	}
	case (char)0x14: {
		fam = 19;
		break;
	}
	case (char)0x15: {
		fam = 21;
		break;
	}
	case (char)0x16: {
		fam = 21;
		break;
	}
	case (char)0x17: {
		fam = 23;
		break;
	}
	case (char)0x18: {
		fam = 23;
		break;
	}
	case (char)0x19: {
		fam = 172;
		break;
	}
	case (char)0x1A: {
		fam = 172;
		break;
	}
	case (char)0x1B: {
		fam = 27;
		break;
	}
	case (char)0x1C: {
		fam = 27;
		break;
	}
	case (char)0x1D: {
		fam = 29;
		break;
	}
	case (char)0x1E: {
		fam = 29;
		break;
	}
	case (char)0x1F: {
		fam = 29;
		break;
	}
	case (char)0x20: {
		fam = 32;
		break;
	}
	case (char)0x21: {
		fam = 32;
		break;
	}
	case (char)0x22: {
		fam = 32;
		break;
	}
	case (char)0x23: {
		fam = 173;
		break;
	}
	case (char)0x24: {
		fam = 173;
		break;
	}
	case (char)0x25: {
		fam = 37;
		break;
	}
	case (char)0x26: {
		fam = 37;
		break;
	}
	case (char)0x27: {
		fam = 174;
		break;
	}
	case (char)0x28: {
		fam = 174;
		break;
	}
	case (char)0x29: {
		fam = 41;
		break;
	}
	case (char)0x2A: {
		fam = 41;
		break;
	}
	case (char)0x2B: {
		fam = 43;
		break;
	}
	case (char)0x2C: {
		fam = 43;
		break;
	}
	case (char)0x2D: {
		fam = 43;
		break;
	}
	case (char)0x2E: {
		fam = 46;
		break;
	}
	case (char)0x2F: {
		fam = 46;
		break;
	}
	case (char)0x30: {
		fam = 48;
		break;
	}
	case (char)0x31: {
		fam = 48;
		break;
	}
	case (char)0x32: {
		fam = 50;
		break;
	}
	case (char)0x33: {
		fam = 50;
		break;
	}
	case (char)0x34: {
		fam = 52;
		break;
	}
	case (char)0x35: {
		fam = 52;
		break;
	}
	case (char)0x36: {
		fam = 54;
		break;
	}
	case (char)0x37: {
		fam = 54;
		break;
	}
	case (char)0x38: {
		fam = 56;
		break;
	}
	case (char)0x39: {
		fam = 56;
		break;
	}
	case (char)0x3A: {
		fam = 58;
		break;
	}
	case (char)0x3B: {
		fam = 58;
		break;
	}
	case (char)0x3C: {
		fam = 60;
		break;
	}
	case (char)0x3D: {
		fam = 60;
		break;
	}
	case (char)0x3E: {
		fam = 60;
		break;
	}
	case (char)0x3F: {
		fam = 63;
		break;
	}
	case (char)0x40: {
		fam = 63;
		break;
	}
	case (char)0x41: {
		fam = 63;
		break;
	}
	case (char)0x42: {
		fam = 66;
		break;
	}
	case (char)0x43: {
		fam = 66;
		break;
	}
	case (char)0x44: {
		fam = 66;
		break;
	}
	case (char)0x45: {
		fam = 69;
		break;
	}
	case (char)0x46: {
		fam = 69;
		break;
	}
	case (char)0x47: {
		fam = 69;
		break;
	}
	case (char)0x48: {
		fam = 72;
		break;
	}
	case (char)0x49: {
		fam = 72;
		break;
	}
	case (char)0x4A: {
		fam = 74;
		break;
	}
	case (char)0x4B: {
		fam = 74;
		break;
	}
	case (char)0x4C: {
		fam = 74;
		break;
	}
	case (char)0x4D: {
		fam = 77;
		break;
	}
	case (char)0x4E: {
		fam = 77;
		break;
	}
	case (char)0x4F: {
		fam = 79;
		break;
	}
	case (char)0x50: {
		fam = 79;
		break;
	}
	case (char)0x51: {
		fam = 81;
		break;
	}
	case (char)0x52: {
		fam = 81;
		break;
	}
	case (char)0x53: {
		fam = 83;
		break;
	}
	case (char)0x54: {
		fam = 84;
		break;
	}
	case (char)0x55: {
		fam = 84;
		break;
	}
	case (char)0x56: {
		fam = 86;
		break;
	}
	case (char)0x57: {
		fam = 86;
		break;
	}
	case (char)0x58: {
		fam = 88;
		break;
	}
	case (char)0x59: {
		fam = 88;
		break;
	}
	case (char)0x5A: {
		fam = 90;
		break;
	}
	case (char)0x5B: {
		fam = 90;
		break;
	}
	case (char)0x5C: {
		fam = 92;
		break;
	}
	case (char)0x5D: {
		fam = 92;
		break;
	}
	case (char)0x5E: {
		fam = 92;
		break;
	}
	case (char)0x5F: {
		fam = 95;
		break;
	}
	case (char)0x60: {
		fam = 96;
		break;
	}
	case (char)0x61: {
		fam = 96;
		break;
	}
	case (char)0x62: {
		fam = 98;
		break;
	}
	case (char)0x63: {
		fam = 98;
		break;
	}
	case (char)0x64: {
		fam = 100;
		break;
	}
	case (char)0x65: {
		fam = 100;
		break;
	}
	case (char)0x66: {
		fam = 102;
		break;
	}
	case (char)0x67: {
		fam = 102;
		break;
	}
	case (char)0x68: {
		fam = 104;
		break;
	}
	case (char)0x69: {
		fam = 104;
		break;
	}
	case (char)0x6A: {
		fam = 236;
		break;
	}
	case (char)0x6B: {
		fam = 236;
		break;
	}
	case (char)0x6C: {
		fam = 108;
		break;
	}
	case (char)0x6D: {
		fam = 109;
		break;
	}
	case (char)0x6E: {
		fam = 109;
		break;
	}
	case (char)0x6F: {
		fam = 111;
		break;
	}
	case (char)0x70: {
		fam = 111;
		break;
	}
	case (char)0x71: {
		fam = 113;
		break;
	}
	case (char)0x72: {
		fam = 114;
		break;
	}
	case (char)0x73: {
		fam = 115;
		break;
	}
	case (char)0x74: {
		fam = 116;
		break;
	}
	case (char)0x75: {
		fam = 116;
		break;
	}
	case (char)0x76: {
		fam = 118;
		break;
	}
	case (char)0x77: {
		fam = 118;
		break;
	}
	case (char)0x78: {
		fam = 120;
		break;
	}
	case (char)0x79: {
		fam = 120;
		break;
	}
	case (char)0x7A: {
		fam = 122;
		break;
	}
	case (char)0x7B: {
		fam = 123;
		break;
	}
	case (char)0x7C: {
		fam = 238;
		break;
	}
	case (char)0x7D: {
		fam = 239;
		break;
	}
	case (char)0x7E: {
		fam = 240;
		break;
	}
	case (char)0x7F: {
		fam = 127;
		break;
	}
	case (char)0x80: {
		fam = 128;
		break;
	}
	case (char)0x81: {
		fam = 129;
		break;
	}
	case (char)0x82: {
		fam = 129;
		break;
	}
	case (char)0x83: {
		fam = 131;
		break;
	}
	case (char)0x84: {
		fam = 132;
		break;
	}
	case (char)0x85: {
		fam = 133;
		break;
	}
	case (char)0x86: {
		fam = 133;
		break;
	}
	case (char)0x87: {
		fam = 133;
		break;
	}
	case (char)0x88: {
		fam = 133;
		break;
	}
	case (char)0x89: {
		fam = 137;
		break;
	}
	case (char)0x8A: {
		fam = 138;
		break;
	}
	case (char)0x8B: {
		fam = 138;
		break;
	}
	case (char)0x8C: {
		fam = 140;
		break;
	}
	case (char)0x8D: {
		fam = 140;
		break;
	}
	case (char)0x8E: {
		fam = 142;
		break;
	}
	case (char)0x8F: {
		fam = 143;
		break;
	}
	case (char)0x90: {
		fam = 144;
		break;
	}
	case (char)0x91: {
		fam = 145;
		break;
	}
	case (char)0x92: {
		fam = 146;
		break;
	}
	case (char)0x93: {
		fam = 147;
		break;
	}
	case (char)0x94: {
		fam = 147;
		break;
	}
	case (char)0x95: {
		fam = 147;
		break;
	}
	case (char)0x96: {
		fam = 150;
		break;
	}
	case (char)0x97: {
		fam = 151;
		break;
	}
	case (char)0x98: {
		fam = 152;
		break;
	}
	case (char)0x99: {
		fam = 152;
		break;
	}
	case (char)0x9A: {
		fam = 152;
		break;
	}
	case (char)0x9B: {
		fam = 155;
		break;
	}
	case (char)0x9C: {
		fam = 155;
		break;
	}
	case (char)0x9D: {
		fam = 155;
		break;
	}
	case (char)0x9E: {
		fam = 158;
		break;
	}
	case (char)0x9F: {
		fam = 158;
		break;
	}
	case (char)0xA0: {
		fam = 158;
		break;
	}
	case (char)0xA1: {
		fam = 161;
		break;
	}
	case (char)0xA2: {
		fam = 161;
		break;
	}
	case (char)0xA3: {
		fam = 163;
		break;
	}
	case (char)0xA4: {
		fam = 163;
		break;
	}
	case (char)0xA5: {
		fam = 165;
		break;
	}
	case (char)0xA6: {
		fam = 165;
		break;
	}
	case (char)0xA7: {
		fam = 167;
		break;
	}
	case (char)0xA8: {
		fam = 167;
		break;
	}
	case (char)0xA9: {
		fam = 41;
		break;
	}
	case (char)0xAA: {
		fam = 170;
		break;
	}
	case (char)0xAB: {
		fam = 170;
		break;
	}
	case (char)0xAC: {
		fam = 172;
		break;
	}
	case (char)0xAD: {
		fam = 173;
		break;
	}
	case (char)0xAE: {
		fam = 174;
		break;
	}
	case (char)0xAF: {
		fam = 175;
		break;
	}
	case (char)0xB0: {
		fam = 175;
		break;
	}
	case (char)0xB1: {
		fam = 177;
		break;
	}
	case (char)0xB2: {
		fam = 177;
		break;
	}
	case (char)0xB3: {
		fam = 179;
		break;
	}
	case (char)0xB4: {
		fam = 179;
		break;
	}
	case (char)0xB5: {
		fam = 179;
		break;
	}
	case (char)0xB6: {
		fam = 43;
		break;
	}
	case (char)0xB7: {
		fam = 183;
		break;
	}
	case (char)0xB8: {
		fam = 183;
		break;
	}
	case (char)0xB9: {
		fam = 185;
		break;
	}
	case (char)0xBA: {
		fam = 60;
		break;
	}
	case (char)0xBB: {
		fam = 187;
		break;
	}
	case (char)0xBC: {
		fam = 187;
		break;
	}
	case (char)0xBD: {
		fam = 187;
		break;
	}
	case (char)0xBE: {
		fam = 190;
		break;
	}
	case (char)0xBF: {
		fam = 191;
		break;
	}
	case (char)0xC0: {
		fam = 191;
		break;
	}
	case (char)0xC1: {
		fam = 193;
		break;
	}
	case (char)0xC2: {
		fam = 194;
		break;
	}
	case (char)0xC3: {
		fam = 194;
		break;
	}
	case (char)0xC4: {
		fam = 133;
		break;
	}
	case (char)0xC5: {
		fam = 133;
		break;
	}
	case (char)0xC6: {
		fam = 198;
		break;
	}
	case (char)0xC7: {
		fam = 79;
		break;
	}
	case (char)0xC8: {
		fam = 200;
		break;
	}
	case (char)0xC9: {
		fam = 201;
		break;
	}
	case (char)0xCA: {
		fam = 202;
		break;
	}
	case (char)0xCB: {
		fam = 203;
		break;
	}
	case (char)0xCC: {
		fam = 204;
		break;
	}
	case (char)0xCD: {
		fam = 204;
		break;
	}
	case (char)0xCE: {
		fam = 206;
		break;
	}
	case (char)0xCF: {
		fam = 207;
		break;
	}
	case (char)0xD0: {
		fam = 95;
		break;
	}
	case (char)0xD1: {
		fam = 209;
		break;
	}
	case (char)0xD2: {
		fam = 209;
		break;
	}
	case (char)0xD3: {
		fam = 211;
		break;
	}
	case (char)0xD4: {
		fam = 123;
		break;
	}
	case (char)0xD5: {
		fam = 213;
		break;
	}
	case (char)0xD6: {
		fam = 214;
		break;
	}
	case (char)0xD7: {
		fam = 215;
		break;
	}
	case (char)0xD8: {
		fam = 216;
		break;
	}
	case (char)0xD9: {
		fam = 216;
		break;
	}
	case (char)0xDA: {
		fam = 218;
		break;
	}
	case (char)0xDB: {
		fam = 218;
		break;
	}
	case (char)0xDC: {
		fam = 220;
		break;
	}
	case (char)0xDD: {
		fam = 220;
		break;
	}
	case (char)0xDE: {
		fam = 222;
		break;
	}
	case (char)0xDF: {
		fam = 223;
		break;
	}
	case (char)0xE0: {
		fam = 223;
		break;
	}
	case (char)0xE1: {
		fam = 225;
		break;
	}
	case (char)0xE2: {
		fam = 226;
		break;
	}
	case (char)0xE3: {
		fam = 227;
		break;
	}
	case (char)0xE4: {
		fam = 228;
		break;
	}
	case (char)0xE5: {
		fam = 228;
		break;
	}
	case (char)0xE6: {
		fam = 116;
		break;
	}
	case (char)0xE7: {
		fam = 231;
		break;
	}
	case (char)0xE8: {
		fam = 231;
		break;
	}
	case (char)0xE9: {
		fam = 233;
		break;
	}
	case (char)0xEA: {
		fam = 234;
		break;
	}
	case (char)0xEB: {
		fam = 235;
		break;
	}
	case (char)0xEC: {
		fam = 236;
		break;
	}
	case (char)0xED: {
		fam = 236;
		break;
	}
	case (char)0xEE: {
		fam = 238;
		break;
	}
	case (char)0xEF: {
		fam = 239;
		break;
	}
	case (char)0xF0: {
		fam = 240;
		break;
	}
	case (char)0xF1: {
		fam = 241;
		break;
	}
	case (char)0xF2: {
		fam = 113;
		break;
	}
	case (char)0xF3: {
		fam = 243;
		break;
	}
	case (char)0xF4: {
		fam = 244;
		break;
	}
	case (char)0xF5: {
		fam = 245;
		break;
	}
	case (char)0xF6: {
		fam = 246;
		break;
	}
	case (char)0xF7: {
		fam = 246;
		break;
	}
	case (char)0xF8: {
		fam = 246;
		break;
	}
	case (char)0xF9: {
		fam = 249;
		break;
	}
	case (char)0xFA: {
		fam = 250;
		break;
	}
	case (char)0xFB: {
		fam = 251;
		break;
	}
	}

	return fam;
}

std::wstring InterpretMoves(char code) {
	std::wstring name = L"-";

	switch (code) {
	case (char)0x01: {
		name = L"POUND";
		break;
	}
	case (char)0x02: {
		name = L"KARATE CHOP";
		break;
	}
	case (char)0x03: {
		name = L"DOUBLESLAP";
		break;
	}
	case (char)0x04: {
		name = L"COMET PUNCH";
		break;
	}
	case (char)0x05: {
		name = L"MEGA PUNCH";
		break;
	}
	case (char)0x06: {
		name = L"PAY DAY";
		break;
	}
	case (char)0x07: {
		name = L"FIRE PUNCH";
		break;
	}
	case (char)0x08: {
		name = L"ICE PUNCH";
		break;
	}
	case (char)0x09: {
		name = L"THUNDERPUNCH";
		break;
	}
	case (char)0x0A: {
		name = L"SCRATCH";
		break;
	}
	case (char)0x0B: {
		name = L"VICEGRIP";
		break;
	}
	case (char)0x0C: {
		name = L"GUILLOTINE";
		break;
	}
	case (char)0x0D: {
		name = L"RAZOR WIND";
		break;
	}
	case (char)0x0E: {
		name = L"SWORDS DANCE";
		break;
	}
	case (char)0x0F: {
		name = L"CUT";
		break;
	}
	case (char)0x10: {
		name = L"GUST";
		break;
	}
	case (char)0x11: {
		name = L"WING ATTACK";
		break;
	}
	case (char)0x12: {
		name = L"WHIRLWIND";
		break;
	}
	case (char)0x13: {
		name = L"FLY";
		break;
	}
	case (char)0x14: {
		name = L"BIND";
		break;
	}
	case (char)0x15: {
		name = L"SLAM";
		break;
	}
	case (char)0x16: {
		name = L"VINE WHIP";
		break;
	}
	case (char)0x17: {
		name = L"STOMP";
		break;
	}
	case (char)0x18: {
		name = L"DOUBLE KICK";
		break;
	}
	case (char)0x19: {
		name = L"MEGA KICK";
		break;
	}
	case (char)0x1A: {
		name = L"JUMP KICK";
		break;
	}
	case (char)0x1B: {
		name = L"ROLLING KICK";
		break;
	}
	case (char)0x1C: {
		name = L"SAND-ATTACK";
		break;
	}
	case (char)0x1D: {
		name = L"HEADBUTT";
		break;
	}
	case (char)0x1E: {
		name = L"HORN ATTACK";
		break;
	}
	case (char)0x1F: {
		name = L"FURY ATTACK";
		break;
	}
	case (char)0x20: {
		name = L"HORN DRILL";
		break;
	}
	case (char)0x21: {
		name = L"TACKLE";
		break;
	}
	case (char)0x22: {
		name = L"BODY SLAM";
		break;
	}
	case (char)0x23: {
		name = L"WRAP";
		break;
	}
	case (char)0x24: {
		name = L"TAKE DOWN";
		break;
	}
	case (char)0x25: {
		name = L"THRASH";
		break;
	}
	case (char)0x26: {
		name = L"DOUBLE-EDGE";
		break;
	}
	case (char)0x27: {
		name = L"TAIL WHIP";
		break;
	}
	case (char)0x28: {
		name = L"POISON STING";
		break;
	}
	case (char)0x29: {
		name = L"TWIN NEEDLE";
		break;
	}
	case (char)0x2A: {
		name = L"PIN MISSLE";
		break;
	}
	case (char)0x2B: {
		name = L"LEER";
		break;
	}
	case (char)0x2C: {
		name = L"BITE";
		break;
	}
	case (char)0x2D: {
		name = L"GROWL";
		break;
	}
	case (char)0x2E: {
		name = L"ROAR";
		break;
	}
	case (char)0x2F: {
		name = L"SING";
		break;
	}
	case (char)0x30: {
		name = L"SUPERSONIC";
		break;
	}
	case (char)0x31: {
		name = L"SONICBOOM";
		break;
	}
	case (char)0x32: {
		name = L"DISABLE";
		break;
	}
	case (char)0x33: {
		name = L"ACID";
		break;
	}
	case (char)0x34: {
		name = L"EMBER";
		break;
	}
	case (char)0x35: {
		name = L"FLAMETHROWER";
		break;
	}
	case (char)0x36: {
		name = L"MIST";
		break;
	}
	case (char)0x37: {
		name = L"WATER GUN";
		break;
	}
	case (char)0x38: {
		name = L"HYDRO PUMP";
		break;
	}
	case (char)0x39: {
		name = L"SURF";
		break;
	}
	case (char)0x3A: {
		name = L"ICE BEAM";
		break;
	}
	case (char)0x3B: {
		name = L"BLIZZARD";
		break;
	}
	case (char)0x3C: {
		name = L"PSYBEAM";
		break;
	}
	case (char)0x3D: {
		name = L"BUBBLEBEAM";
		break;
	}
	case (char)0x3E: {
		name = L"AURORA BEAM";
		break;
	}
	case (char)0x3F: {
		name = L"HYPER BEAM";
		break;
	}
	case (char)0x40: {
		name = L"PECK";
		break;
	}
	case (char)0x41: {
		name = L"DRILL PECK";
		break;
	}
	case (char)0x42: {
		name = L"SUBMISSION";
		break;
	}
	case (char)0x43: {
		name = L"LOW KICK";
		break;
	}
	case (char)0x44: {
		name = L"COUNTER";
		break;
	}
	case (char)0x45: {
		name = L"SEISMIC TOSS";
		break;
	}
	case (char)0x46: {
		name = L"STRENGTH";
		break;
	}
	case (char)0x47: {
		name = L"ABSORB";
		break;
	}
	case (char)0x48: {
		name = L"MEGA DRAIN";
		break;
	}
	case (char)0x49: {
		name = L"LEECH SEED";
		break;
	}
	case (char)0x4A: {
		name = L"GROWTH";
		break;
	}
	case (char)0x4B: {
		name = L"RAZOR LEAF";
		break;
	}
	case (char)0x4C: {
		name = L"SOLARBEAM";
		break;
	}
	case (char)0x4D: {
		name = L"POISONPOWDER";
		break;
	}
	case (char)0x4E: {
		name = L"STUN SPORE";
		break;
	}
	case (char)0x4F: {
		name = L"SLEEP POWDER";
		break;
	}
	case (char)0x50: {
		name = L"PETAL DANCE";
		break;
	}
	case (char)0x51: {
		name = L"STRINGSHOT";
		break;
	}
	case (char)0x52: {
		name = L"DRAGON RAGE";
		break;
	}
	case (char)0x53: {
		name = L"FIRE SPIN";
		break;
	}
	case (char)0x54: {
		name = L"THUNDERSHOCK";
		break;
	}
	case (char)0x55: {
		name = L"THUNDERBOLT";
		break;
	}
	case (char)0x56: {
		name = L"THUNDER WAVE";
		break;
	}
	case (char)0x57: {
		name = L"THUNDER";
		break;
	}
	case (char)0x58: {
		name = L"ROCK THROW";
		break;
	}
	case (char)0x59: {
		name = L"EARTHQUAKE";
		break;
	}
	case (char)0x5A: {
		name = L"FISSURE";
		break;
	}
	case (char)0x5B: {
		name = L"DIG";
		break;
	}
	case (char)0x5C: {
		name = L"TOXIC";
		break;
	}
	case (char)0x5D: {
		name = L"CONFUSION";
		break;
	}
	case (char)0x5E: {
		name = L"PSYCHIC";
		break;
	}
	case (char)0x5F: {
		name = L"HYPNOSIS";
		break;
	}
	case (char)0x60: {
		name = L"MEDITATE";
		break;
	}
	case (char)0x61: {
		name = L"AGILITY";
		break;
	}
	case (char)0x62: {
		name = L"QUICK ATTACK";
		break;
	}
	case (char)0x63: {
		name = L"RAGE";
		break;
	}
	case (char)0x64: {
		name = L"TELEPORT";
		break;
	}
	case (char)0x65: {
		name = L"NIGHT SHADE";
		break;
	}
	case (char)0x66: {
		name = L"MIMIC";
		break;
	}
	case (char)0x67: {
		name = L"SCREECH";
		break;
	}
	case (char)0x68: {
		name = L"DOUBLE TEAM";
		break;
	}
	case (char)0x69: {
		name = L"RECOVER";
		break;
	}
	case (char)0x6A: {
		name = L"HARDEN";
		break;
	}
	case (char)0x6B: {
		name = L"MINIMIZE";
		break;
	}
	case (char)0x6C: {
		name = L"SMOKESCREEN";
		break;
	}
	case (char)0x6D: {
		name = L"CONFUSE RAY";
		break;
	}
	case (char)0x6E: {
		name = L"WITHDRAW";
		break;
	}
	case (char)0x6F: {
		name = L"DEFENCE CURL";
		break;
	}
	case (char)0x70: {
		name = L"BARRIER";
		break;
	}
	case (char)0x71: {
		name = L"LIGHT SCREEN";
		break;
	}
	case (char)0x72: {
		name = L"HAZE";
		break;
	}
	case (char)0x73: {
		name = L"REFLECT";
		break;
	}
	case (char)0x74: {
		name = L"FOCUS ENERGY";
		break;
	}
	case (char)0x75: {
		name = L"BIDE";
		break;
	}
	case (char)0x76: {
		name = L"METRONOME";
		break;
	}
	case (char)0x77: {
		name = L"MIRROR MOVE";
		break;
	}
	case (char)0x78: {
		name = L"SELFDESTRUCT";
		break;
	}
	case (char)0x79: {
		name = L"EGG BOMB";
		break;
	}
	case (char)0x7A: {
		name = L"LICK";
		break;
	}
	case (char)0x7B: {
		name = L"SMOG";
		break;
	}
	case (char)0x7C: {
		name = L"SLUDGE";
		break;
	}
	case (char)0x7D: {
		name = L"BONE CLUB";
		break;
	}
	case (char)0x7E: {
		name = L"FIRE BLAST";
		break;
	}
	case (char)0x7F: {
		name = L"WATERFALL";
		break;
	}
	case (char)0x80: {
		name = L"CLAMP";
		break;
	}
	case (char)0x81: {
		name = L"SWIFT";
		break;
	}
	case (char)0x82: {
		name = L"SKULL BASH";
		break;
	}
	case (char)0x83: {
		name = L"SPIKE CANNON";
		break;
	}
	case (char)0x84: {
		name = L"CONSTRICT";
		break;
	}
	case (char)0x85: {
		name = L"AMNESIA";
		break;
	}
	case (char)0x86: {
		name = L"KINESIS";
		break;
	}
	case (char)0x87: {
		name = L"SOFTBOILED";
		break;
	}
	case (char)0x88: {
		name = L"HI JUMP KICK";
		break;
	}
	case (char)0x89: {
		name = L"GLARE";
		break;
	}
	case (char)0x8A: {
		name = L"DREAM EATER";
		break;
	}
	case (char)0x8B: {
		name = L"POISON GAS";
		break;
	}
	case (char)0x8C: {
		name = L"BARRAGE";
		break;
	}
	case (char)0x8D: {
		name = L"LEECH LIFE";
		break;
	}
	case (char)0x8E: {
		name = L"LOVELY KISS";
		break;
	}
	case (char)0x8F: {
		name = L"SKY ATTACK";
		break;
	}
	case (char)0x90: {
		name = L"TRANSFORM";
		break;
	}
	case (char)0x91: {
		name = L"BUBBLE";
		break;
	}
	case (char)0x92: {
		name = L"DIZZY PUNCH";
		break;
	}
	case (char)0x93: {
		name = L"SPORE";
		break;
	}
	case (char)0x94: {
		name = L"FLASH";
		break;
	}
	case (char)0x95: {
		name = L"PSYWAVE";
		break;
	}
	case (char)0x96: {
		name = L"SPLASH";
		break;
	}
	case (char)0x97: {
		name = L"ACID ARMOR";
		break;
	}
	case (char)0x98: {
		name = L"CRABHAMMER";
		break;
	}
	case (char)0x99: {
		name = L"EXPLOSION";
		break;
	}
	case (char)0x9A: {
		name = L"FURY SWIPES";
		break;
	}
	case (char)0x9B: {
		name = L"BONEMERANG";
		break;
	}
	case (char)0x9C: {
		name = L"REST";
		break;
	}
	case (char)0x9D: {
		name = L"ROCK SLIDE";
		break;
	}
	case (char)0x9E: {
		name = L"HYPER FANG";
		break;
	}
	case (char)0x9F: {
		name = L"SHARPEN";
		break;
	}
	case (char)0xA0: {
		name = L"CONVERSION";
		break;
	}
	case (char)0xA1: {
		name = L"TRI ATTACK";
		break;
	}
	case (char)0xA2: {
		name = L"SUPER FANG";
		break;
	}
	case (char)0xA3: {
		name = L"SLASH";
		break;
	}
	case (char)0xA4: {
		name = L"SUBSTITUTE";
		break;
	}
	case (char)0xA5: {
		name = L"STRUGGLE";
		break;
	}
	case (char)0xA6: {
		name = L"SKETCH";
		break;
	}
	case (char)0xA7: {
		name = L"TRIPLE KICK";
		break;
	}
	case (char)0xA8: {
		name = L"THIEF";
		break;
	}
	case (char)0xA9: {
		name = L"SPIDER WEB";
		break;
	}
	case (char)0xAA: {
		name = L"MIND READER";
		break;
	}
	case (char)0xAB: {
		name = L"NIGHTMARE";
		break;
	}
	case (char)0xAC: {
		name = L"FLAME WHEEL";
		break;
	}
	case (char)0xAD: {
		name = L"SNORE";
		break;
	}
	case (char)0xAE: {
		name = L"CURSE";
		break;
	}
	case (char)0xAF: {
		name = L"FLAIL";
		break;
	}
	case (char)0xB0: {
		name = L"CONVERSION2";
		break;
	}
	case (char)0xB1: {
		name = L"AREOBLAST";
		break;
	}
	case (char)0xB2: {
		name = L"COTTON SPORE";
		break;
	}
	case (char)0xB3: {
		name = L"REVERSAL";
		break;
	}
	case (char)0xB4: {
		name = L"SPITE";
		break;
	}
	case (char)0xB5: {
		name = L"POWDER SNOW";
		break;
	}
	case (char)0xB6: {
		name = L"PROTECT";
		break;
	}
	case (char)0xB7: {
		name = L"MACH PUNCH";
		break;
	}
	case (char)0xB8: {
		name = L"SCARY FACE";
		break;
	}
	case (char)0xB9: {
		name = L"FAINT ATTACK";
		break;
	}
	case (char)0xBA: {
		name = L"SWEET KISS";
		break;
	}
	case (char)0xBB: {
		name = L"BELLY DRUM";
		break;
	}
	case (char)0xBC: {
		name = L"SLUDGE BOMB";
		break;
	}
	case (char)0xBD: {
		name = L"MUD SLAP";
		break;
	}
	case (char)0xBE: {
		name = L"OCTAZOOKA";
		break;
	}
	case (char)0xBF: {
		name = L"SPIKES";
		break;
	}
	case (char)0xC0: {
		name = L"ZAP CANNON";
		break;
	}
	case (char)0xC1: {
		name = L"FORESIGHT";
		break;
	}
	case (char)0xC2: {
		name = L"DESTINY BOND";
		break;
	}
	case (char)0xC3: {
		name = L"PERISH SONG";
		break;
	}
	case (char)0xC4: {
		name = L"ICY WIND";
		break;
	}
	case (char)0xC5: {
		name = L"DETECT";
		break;
	}
	case (char)0xC6: {
		name = L"BONE RUSH";
		break;
	}
	case (char)0xC7: {
		name = L"LOCK-ON";
		break;
	}
	case (char)0xC8: {
		name = L"OUTRAGE";
		break;
	}
	case (char)0xC9: {
		name = L"SANDSTORM";
		break;
	}
	case (char)0xCA: {
		name = L"GIGA DRAIN";
		break;
	}
	case (char)0xCB: {
		name = L"ENDURE";
		break;
	}
	case (char)0xCC: {
		name = L"CHARM";
		break;
	}
	case (char)0xCD: {
		name = L"ROLLOUT";
		break;
	}
	case (char)0xCE: {
		name = L"FALSE SWIPE";
		break;
	}
	case (char)0xCF: {
		name = L"SWAGGER";
		break;
	}
	case (char)0xD0: {
		name = L"MILK DRINK";
		break;
	}
	case (char)0xD1: {
		name = L"SPARK";
		break;
	}
	case (char)0xD2: {
		name = L"FURY CUTTER";
		break;
	}
	case (char)0xD3: {
		name = L"STEEL WING";
		break;
	}
	case (char)0xD4: {
		name = L"MEAN LOOK";
		break;
	}
	case (char)0xD5: {
		name = L"ATTRACT";
		break;
	}
	case (char)0xD6: {
		name = L"SLEEP TALK";
		break;
	}
	case (char)0xD7: {
		name = L"HEAL BELL";
		break;
	}
	case (char)0xD8: {
		name = L"RETURN";
		break;
	}
	case (char)0xD9: {
		name = L"PRESENT";
		break;
	}
	case (char)0xDA: {
		name = L"FRUSTRATION";
		break;
	}
	case (char)0xDB: {
		name = L"SAFEGUARD";
		break;
	}
	case (char)0xDC: {
		name = L"PAIN SPLIT";
		break;
	}
	case (char)0xDD: {
		name = L"SACRED FIRE";
		break;
	}
	case (char)0xDE: {
		name = L"MAGNITUDE";
		break;
	}
	case (char)0xDF: {
		name = L"DYNAMICPUNCH";
		break;
	}
	case (char)0xE0: {
		name = L"MEGAHORN";
		break;
	}
	case (char)0xE1: {
		name = L"DRAGONBREATH";
		break;
	}
	case (char)0xE2: {
		name = L"BATON PASS";
		break;
	}
	case (char)0xE3: {
		name = L"ENCORE";
		break;
	}
	case (char)0xE4: {
		name = L"PURSUIT";
		break;
	}
	case (char)0xE5: {
		name = L"RAPID SPIN";
		break;
	}
	case (char)0xE6: {
		name = L"SWEET SCENT";
		break;
	}
	case (char)0xE7: {
		name = L"IRON TAIL";
		break;
	}
	case (char)0xE8: {
		name = L"METAL CLAW";
		break;
	}
	case (char)0xE9: {
		name = L"VITAL THROW";
		break;
	}
	case (char)0xEA: {
		name = L"MORNING SUN";
		break;
	}
	case (char)0xEB: {
		name = L"SYNTHESIS";
		break;
	}
	case (char)0xEC: {
		name = L"MOONLIGHT";
		break;
	}
	case (char)0xED: {
		name = L"HIDDEN POWER";
		break;
	}
	case (char)0xEE: {
		name = L"CROSS CHOP";
		break;
	}
	case (char)0xEF: {
		name = L"TWISTER";
		break;
	}
	case (char)0xF0: {
		name = L"RAIN DANCE";
		break;
	}
	case (char)0xF1: {
		name = L"SUNNY DAY";
		break;
	}
	case (char)0xF2: {
		name = L"CRUNCH";
		break;
	}
	case (char)0xF3: {
		name = L"MIRROR COAT";
		break;
	}
	case (char)0xF4: {
		name = L"PSYCH UP";
		break;
	}
	case (char)0xF5: {
		name = L"EXTREMESPEED";
		break;
	}
	case (char)0xF6: {
		name = L"ANCIENTPOWER";
		break;
	}
	case (char)0xF7: {
		name = L"SHADOW BALL";
		break;
	}
	case (char)0xF8: {
		name = L"FUTURE SIGHT";
		break;
	}
	case (char)0xF9: {
		name = L"ROCK SMASH";
		break;
	}
	case (char)0xFA: {
		name = L"WHIRLPOOL";
		break;
	}
	case (char)0xFB: {
		name = L"BEAT UP";
		break;
	}
	}

	return name;
}

std::wstring InterpretItems(char code) {
	std::wstring name = L"-";

	switch (code) {
	case (char)0x00: {
		name = L"NONE";
		break;
	}
	case (char)0x01: {
		name = L"MASTER BALL";
		break;
	}
	case (char)0x02: {
		name = L"ULTRA BALL";
		break;
	}
	case (char)0x03: {
		name = L"BRIGHTPOWDER";
		break;
	}
	case (char)0x04: {
		name = L"GREAT BALL";
		break;
	}
	case (char)0x05: {
		name = L"POKEBALL";
		break;
	}
	case (char)0x06: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x07: {
		name = L"BICYCLE";
		break;
	}
	case (char)0x08: {
		name = L"MOON STONE";
		break;
	}
	case (char)0x09: {
		name = L"ANTIDOTE";
		break;
	}
	case (char)0x0A: {
		name = L"BURN HEAL";
		break;
	}
	case (char)0x0B: {
		name = L"ICE HEAL";
		break;
	}
	case (char)0x0C: {
		name = L"AWAKENING";
		break;
	}
	case (char)0x0D: {
		name = L"PARALYZE HEAL";
		break;
	}
	case (char)0x0E: {
		name = L"FULL RESTORE";
		break;
	}
	case (char)0x0F: {
		name = L"MAX POTION";
		break;
	}
	case (char)0x10: {
		name = L"HYPER POTION";
		break;
	}
	case (char)0x11: {
		name = L"SUPER POTION";
		break;
	}
	case (char)0x12: {
		name = L"POTION";
		break;
	}
	case (char)0x13: {
		name = L"ESCAPE ROPE";
		break;
	}
	case (char)0x14: {
		name = L"REPEL";
		break;
	}
	case (char)0x15: {
		name = L"MAX ELIXIR";
		break;
	}
	case (char)0x16: {
		name = L"FIRE STONE";
		break;
	}
	case (char)0x17: {
		name = L"THUNDERSTONE";
		break;
	}
	case (char)0x18: {
		name = L"WATER STONE";
		break;
	}
	case (char)0x19: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x1A: {
		name = L"HP UP";
		break;
	}
	case (char)0x1B: {
		name = L"PROTEIN";
		break;
	}
	case (char)0x1C: {
		name = L"IRON";
		break;
	}
	case (char)0x1D: {
		name = L"CARBOS";
		break;
	}
	case (char)0x1E: {
		name = L"LUCKY PUNCH";
		break;
	}
	case (char)0x1F: {
		name = L"CALCIUM";
		break;
	}
	case (char)0x20: {
		name = L"RARE CANDY";
		break;
	}
	case (char)0x21: {
		name = L"X ACCURACY";
		break;
	}
	case (char)0x22: {
		name = L"LEAF STONE";
		break;
	}
	case (char)0x23: {
		name = L"METAL POWDER";
		break;
	}
	case (char)0x24: {
		name = L"NUGGET";
		break;
	}
	case (char)0x25: {
		name = L"POKEDOLL";
		break;
	}
	case (char)0x26: {
		name = L"FULL HEAL";
		break;
	}
	case (char)0x27: {
		name = L"REVIVE";
		break;
	}
	case (char)0x28: {
		name = L"MAX REVIVE";
		break;
	}
	case (char)0x29: {
		name = L"GUARD SPEC.";
		break;
	}
	case (char)0x2A: {
		name = L"SUPER REPEL";
		break;
	}
	case (char)0x2B: {
		name = L"MAX REPEL";
		break;
	}
	case (char)0x2C: {
		name = L"DIRE HIT";
		break;
	}
	case (char)0x2D: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x2E: {
		name = L"FRESH WATER";
		break;
	}
	case (char)0x2F: {
		name = L"SODA POP";
		break;
	}
	case (char)0x30: {
		name = L"LEMONADE";
		break;
	}
	case (char)0x31: {
		name = L"X ATTACK";
		break;
	}
	case (char)0x32: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x33: {
		name = L"X DEFEND";
		break;
	}
	case (char)0x34: {
		name = L"X SPEED";
		break;
	}
	case (char)0x35: {
		name = L"X SPECIAL";
		break;
	}
	case (char)0x36: {
		name = L"COIN CASE";
		break;
	}
	case (char)0x37: {
		name = L"ITEMFINDER";
		break;
	}
	case (char)0x38: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x39: {
		name = L"EXP. SHARE";
		break;
	}
	case (char)0x3A: {
		name = L"OLD ROD";
		break;
	}
	case (char)0x3B: {
		name = L"GOOD ROD";
		break;
	}
	case (char)0x3C: {
		name = L"SILVER LEAF";
		break;
	}
	case (char)0x3D: {
		name = L"SUPER ROD";
		break;
	}
	case (char)0x3E: {
		name = L"PP UP";
		break;
	}
	case (char)0x3F: {
		name = L"ETHER";
		break;
	}
	case (char)0x40: {
		name = L"MAX ETHER";
		break;
	}
	case (char)0x41: {
		name = L"ELIXIR";
		break;
	}
	case (char)0x42: {
		name = L"RED SCALE";
		break;
	}
	case (char)0x43: {
		name = L"SECRET POTION";
		break;
	}
	case (char)0x44: {
		name = L"S.S. TICKET";
		break;
	}
	case (char)0x45: {
		name = L"MYSTERY EGG";
		break;
	}
	case (char)0x46: {
		name = L"CLEAR BELL";
		break;
	}
	case (char)0x47: {
		name = L"SILVER WING";
		break;
	}
	case (char)0x48: {
		name = L"MOOMOO MILK";
		break;
	}
	case (char)0x49: {
		name = L"QUICK CLAW";
		break;
	}
	case (char)0x4A: {
		name = L"PSNCUREBERRY";
		break;
	}
	case (char)0x4B: {
		name = L"GOLD LEAF";
		break;
	}
	case (char)0x4C: {
		name = L"SOFTSAND";
		break;
	}
	case (char)0x4D: {
		name = L"SHARP BEAK";
		break;
	}
	case (char)0x4E: {
		name = L"PRZCUREBERRY";
		break;
	}
	case (char)0x4F: {
		name = L"BURNT BERRY";
		break;
	}
	case (char)0x50: {
		name = L"ICE BERRY";
		break;
	}
	case (char)0x51: {
		name = L"POISON BARB";
		break;
	}
	case (char)0x52: {
		name = L"KING'S ROCK";
		break;
	}
	case (char)0x53: {
		name = L"BITTER BERRY";
		break;
	}
	case (char)0x54: {
		name = L"MINT BERRY";
		break;
	}
	case (char)0x55: {
		name = L"RED APRICORN";
		break;
	}
	case (char)0x56: {
		name = L"TINYMUSHROOM";
		break;
	}
	case (char)0x57: {
		name = L"BIGMUSHROOM";
		break;
	}
	case (char)0x58: {
		name = L"SILVER POWDER";
		break;
	}
	case (char)0x59: {
		name = L"BLU APRICORN";
		break;
	}
	case (char)0x5A: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x5B: {
		name = L"AMULET COIN";
		break;
	}
	case (char)0x5C: {
		name = L"YLW APRICORN";
		break;
	}
	case (char)0x5D: {
		name = L"GRN APRICORN";
		break;
	}
	case (char)0x5E: {
		name = L"CLEANSE TAG";
		break;
	}
	case (char)0x5F: {
		name = L"MYSTICWATER";
		break;
	}
	case (char)0x60: {
		name = L"TWISTEDSPOON";
		break;
	}
	case (char)0x61: {
		name = L"WHT APRICORN";
		break;
	}
	case (char)0x62: {
		name = L"BLACKBELT";
		break;
	}
	case (char)0x63: {
		name = L"BLK APRICORN";
		break;
	}
	case (char)0x64: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x65: {
		name = L"PNK APRICORN";
		break;
	}
	case (char)0x66: {
		name = L"BLACKGLASSES";
		break;
	}
	case (char)0x67: {
		name = L"SLOWPOKETAIL";
		break;
	}
	case (char)0x68: {
		name = L"PINK BOW";
		break;
	}
	case (char)0x69: {
		name = L"STICK";
		break;
	}
	case (char)0x6A: {
		name = L"SMOKEBALL";
		break;
	}
	case (char)0x6B: {
		name = L"NEVERMELTICE";
		break;
	}
	case (char)0x6C: {
		name = L"MAGNET";
		break;
	}
	case (char)0x6D: {
		name = L"MIRACLEBERRY";
		break;
	}
	case (char)0x6E: {
		name = L"PEARL";
		break;
	}
	case (char)0x6F: {
		name = L"BIG PEARL";
		break;
	}
	case (char)0x70: {
		name = L"EVERSTONE";
		break;
	}
	case (char)0x71: {
		name = L"SPELL TAG";
		break;
	}
	case (char)0x72: {
		name = L"RAGECANDYBAR";
		break;
	}
	case (char)0x73: {
		name = L"GS BALL";
		break;
	}
	case (char)0x74: {
		name = L"BLUE CARD";
		break;
	}
	case (char)0x75: {
		name = L"MIRACLESEED";
		break;
	}
	case (char)0x76: {
		name = L"THICK CLUB";
		break;
	}
	case (char)0x77: {
		name = L"FOCUS BAND";
		break;
	}
	case (char)0x78: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x79: {
		name = L"ENERGYPOWDER";
		break;
	}
	case (char)0x7A: {
		name = L"ENERGYROOT";
		break;
	}
	case (char)0x7B: {
		name = L"HEALPOWDER";
		break;
	}
	case (char)0x7C: {
		name = L"REVIVALHERB";
		break;
	}
	case (char)0x7D: {
		name = L"HARD STONE";
		break;
	}
	case (char)0x7E: {
		name = L"LUCKY EGG";
		break;
	}
	case (char)0x7F: {
		name = L"CARD KEY";
		break;
	}
	case (char)0x80: {
		name = L"MACHINE PART";
		break;
	}
	case (char)0x81: {
		name = L"EGG TICKET";
		break;
	}
	case (char)0x82: {
		name = L"LOST ITEM";
		break;
	}
	case (char)0x83: {
		name = L"STARDUST";
		break;
	}
	case (char)0x84: {
		name = L"STAR PIECE";
		break;
	}
	case (char)0x85: {
		name = L"BASEMENT KEY";
		break;
	}
	case (char)0x86: {
		name = L"PASS";
		break;
	}
	case (char)0x87: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x88: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x89: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x8A: {
		name = L"CHARCOAL";
		break;
	}
	case (char)0x8B: {
		name = L"BERRY JUICE";
		break;
	}
	case (char)0x8C: {
		name = L"SCOPE LENS";
		break;
	}
	case (char)0x8D: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x8E: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x8F: {
		name = L"METAL COAT";
		break;
	}
	case (char)0x90: {
		name = L"DRAGONFANG";
		break;
	}
	case (char)0x91: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x92: {
		name = L"LEFTOVERS";
		break;
	}
	case (char)0x93: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x94: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x95: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x96: {
		name = L"MYSTERYBERRY";
		break;
	}
	case (char)0x97: {
		name = L"DRAGONSCALE";
		break;
	}
	case (char)0x98: {
		name = L"BERSERK GENE";
		break;
	}
	case (char)0x99: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x9A: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x9B: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0x9C: {
		name = L"SACRED ASH";
		break;
	}
	case (char)0x9D: {
		name = L"HEAVY BALL";
		break;
	}
	case (char)0x9E: {
		name = L"FLOWER MAIL";
		break;
	}
	case (char)0x9F: {
		name = L"LEVEL BALL";
		break;
	}
	case (char)0xA0: {
		name = L"LURE BALL";
		break;
	}
	case (char)0xA1: {
		name = L"FAST BALL";
		break;
	}
	case (char)0xA2: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0xA3: {
		name = L"LIGHT BALL";
		break;
	}
	case (char)0xA4: {
		name = L"FRIEND BALL";
		break;
	}
	case (char)0xA5: {
		name = L"MOON BALL";
		break;
	}
	case (char)0xA6: {
		name = L"LOVE BALL";
		break;
	}
	case (char)0xA7: {
		name = L"NORMAL BOX";
		break;
	}
	case (char)0xA8: {
		name = L"GORGEOUS BOX";
		break;
	}
	case (char)0xA9: {
		name = L"SUN STONE";
		break;
	}
	case (char)0xAA: {
		name = L"POLKADOT BOW";
		break;
	}
	case (char)0xAB: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0xAC: {
		name = L"UPGRADE";
		break;
	}
	case (char)0xAD: {
		name = L"BERRY";
		break;
	}
	case (char)0xAE: {
		name = L"GOLD BERRY";
		break;
	}
	case (char)0xAF: {
		name = L"SQUIRTBOTTLE";
		break;
	}
	case (char)0xB0: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0xB1: {
		name = L"PARK BALL";
		break;
	}
	case (char)0xB2: {
		name = L"RAINBOW WING";
		break;
	}
	case (char)0xB3: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0xB4: {
		name = L"BRICK PIECE";
		break;
	}
	case (char)0xB5: {
		name = L"SURF MAIL";
		break;
	}
	case (char)0xB6: {
		name = L"LITEBLUEMAIL";
		break;
	}
	case (char)0xB7: {
		name = L"PORTRIAT MAIL";
		break;
	}
	case (char)0xB8: {
		name = L"LOVELY MAIL";
		break;
	}
	case (char)0xB9: {
		name = L"EON MAIL";
		break;
	}
	case (char)0xBA: {
		name = L"MORPH MAIL";
		break;
	}
	case (char)0xBB: {
		name = L"BLUESKY MAIL";
		break;
	}
	case (char)0xBC: {
		name = L"MUSIC MAIL";
		break;
	}
	case (char)0xBD: {
		name = L"MIRAGE MAIL";
		break;
	}
	case (char)0xBE: {
		name = L"TERU-SAMA";
		break;
	}
	case (char)0xBF: {
		name = L"TM01";
		break;
	}
	case (char)0xC0: {
		name = L"TM02";
		break;
	}
	case (char)0xC1: {
		name = L"TM03";
		break;
	}
	case (char)0xC2: {
		name = L"TM04";
		break;
	}
	case (char)0xC3: {
		name = L"TM04 (FAKE)";
		break;
	}
	case (char)0xC4: {
		name = L"TM05";
		break;
	}
	case (char)0xC5: {
		name = L"TM06";
		break;
	}
	case (char)0xC6: {
		name = L"TM07";
		break;
	}
	case (char)0xC7: {
		name = L"TM08";
		break;
	}
	case (char)0xC8: {
		name = L"TM09";
		break;
	}
	case (char)0xC9: {
		name = L"TM10";
		break;
	}
	case (char)0xCA: {
		name = L"TM11";
		break;
	}
	case (char)0xCB: {
		name = L"TM12";
		break;
	}
	case (char)0xCC: {
		name = L"TM13";
		break;
	}
	case (char)0xCD: {
		name = L"TM14";
		break;
	}
	case (char)0xCE: {
		name = L"TM15";
		break;
	}
	case (char)0xCF: {
		name = L"TM16";
		break;
	}
	case (char)0xD0: {
		name = L"TM17";
		break;
	}
	case (char)0xD1: {
		name = L"TM18";
		break;
	}
	case (char)0xD2: {
		name = L"TM19";
		break;
	}
	case (char)0xD3: {
		name = L"TM20";
		break;
	}
	case (char)0xD4: {
		name = L"TM21";
		break;
	}
	case (char)0xD5: {
		name = L"TM22";
		break;
	}
	case (char)0xD6: {
		name = L"TM23";
		break;
	}
	case (char)0xD7: {
		name = L"TM24";
		break;
	}
	case (char)0xD8: {
		name = L"TM25";
		break;
	}
	case (char)0xD9: {
		name = L"TM26";
		break;
	}
	case (char)0xDA: {
		name = L"TM27";
		break;
	}
	case (char)0xDB: {
		name = L"TM28";
		break;
	}
	case (char)0xDC: {
		name = L"TM28 (FAKE)";
		break;
	}
	case (char)0xDD: {
		name = L"TM29";
		break;
	}
	case (char)0xDE: {
		name = L"TM30";
		break;
	}
	case (char)0xDF: {
		name = L"TM31";
		break;
	}
	case (char)0xE0: {
		name = L"TM32";
		break;
	}
	case (char)0xE1: {
		name = L"TM33";
		break;
	}
	case (char)0xE2: {
		name = L"TM34";
		break;
	}
	case (char)0xE3: {
		name = L"TM35";
		break;
	}
	case (char)0xE4: {
		name = L"TM36";
		break;
	}
	case (char)0xE5: {
		name = L"TM37";
		break;
	}
	case (char)0xE6: {
		name = L"TM38";
		break;
	}
	case (char)0xE7: {
		name = L"TM39";
		break;
	}
	case (char)0xE8: {
		name = L"TM40";
		break;
	}
	case (char)0xE9: {
		name = L"TM41";
		break;
	}
	case (char)0xEA: {
		name = L"TM42";
		break;
	}
	case (char)0xEB: {
		name = L"TM43";
		break;
	}
	case (char)0xEC: {
		name = L"TM44";
		break;
	}
	case (char)0xED: {
		name = L"TM45";
		break;
	}
	case (char)0xEE: {
		name = L"TM46";
		break;
	}
	case (char)0xEF: {
		name = L"TM47";
		break;
	}
	case (char)0xF0: {
		name = L"TM48";
		break;
	}
	case (char)0xF1: {
		name = L"TM49";
		break;
	}
	case (char)0xF2: {
		name = L"TM50";
		break;
	}
	case (char)0xF3: {
		name = L"HM01";
		break;
	}
	case (char)0xF4: {
		name = L"HM02";
		break;
	}
	case (char)0xF5: {
		name = L"HM03";
		break;
	}
	case (char)0xF6: {
		name = L"HM04";
		break;
	}
	case (char)0xF7: {
		name = L"HM05";
		break;
	}
	case (char)0xF8: {
		name = L"HM06";
		break;
	}
	case (char)0xF9: {
		name = L"HM07";
		break;
	}
	case (char)0xFA: {
		name = L"HM08 (FAKE)";
		break;
	}
	case (char)0xFB: {
		name = L"HM09 (FAKE)";
		break;
	}
	case (char)0xFC: {
		name = L"HM10 (FAKE)";
		break;
	}
	case (char)0xFD: {
		name = L"HM11 (FAKE)";
		break;
	}
	case (char)0xFE: {
		name = L"HM12 (FAKE)";
		break;
	}
	case (char)0xFF: {
		name = L"CANCEL";
		break;
	}
	}

	return name;
}

std::wstring InterpretConds(byte type, byte code) {
	std::wstring name = L"";

	switch (type) {
	case (char)0x00: {
		name = L"";
		break;
	}
	case (char)0x01: {
		name = std::to_wstring(InterpretNumbers(code));
		break;
	}
	case (char)0x02: {
		name = InterpretItems(code);
		break;
	}
	case (char)0x03: {
		name = InterpretItems(code);
		break;
	}
	case (char)0x04: {
		name = InterpretHapp(code);
		break;
	}
	case (char)0x05: {
		name = L"STATS";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM1(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM01 DYNAMICPUNCH";
		break;
	}
	case (char)0x01: {
		name = L"TM02 HEADBUTT";
		break;
	}
	case (char)0x02: {
		name = L"TM03 CURSE";
		break;
	}
	case (char)0x03: {
		name = L"TM04 ROLLOUT";
		break;
	}
	case (char)0x04: {
		name = L"TM05 ROAR";
		break;
	}
	case (char)0x05: {
		name = L"TM06 TOXIC";
		break;
	}
	case (char)0x06: {
		name = L"TM07 ZAP CANNON";
		break;
	}
	case (char)0x07: {
		name = L"TM08 ROCK SMASH";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM2(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM09 PSYCH UP";
		break;
	}
	case (char)0x01: {
		name = L"TM10 HIDDEN POWER";
		break;
	}
	case (char)0x02: {
		name = L"TM11 SUNNY DAY";
		break;
	}
	case (char)0x03: {
		name = L"TM12 SWEET SCENT";
		break;
	}
	case (char)0x04: {
		name = L"TM13 SNORE";
		break;
	}
	case (char)0x05: {
		name = L"TM14 BLIZZARD";
		break;
	}
	case (char)0x06: {
		name = L"TM15 HYPER BEAM";
		break;
	}
	case (char)0x07: {
		name = L"TM16 ICY WIND";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM3(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM17 PROTECT";
		break;
	}
	case (char)0x01: {
		name = L"TM18 RAIN DANCE";
		break;
	}
	case (char)0x02: {
		name = L"TM19 GIGA DRAIN";
		break;
	}
	case (char)0x03: {
		name = L"TM20 ENDURE";
		break;
	}
	case (char)0x04: {
		name = L"TM21 FRUSTRATION";
		break;
	}
	case (char)0x05: {
		name = L"TM22 SOLARBEAM";
		break;
	}
	case (char)0x06: {
		name = L"TM23 IRON TAIL";
		break;
	}
	case (char)0x07: {
		name = L"TM24 DRAGONBREATH";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM4(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM25 THUNDER";
		break;
	}
	case (char)0x01: {
		name = L"TM26 EARTHQUAKE";
		break;
	}
	case (char)0x02: {
		name = L"TM27 RETURN";
		break;
	}
	case (char)0x03: {
		name = L"TM28 DIG";
		break;
	}
	case (char)0x04: {
		name = L"TM29 PSYCHIC";
		break;
	}
	case (char)0x05: {
		name = L"TM30 SHADOW BALL";
		break;
	}
	case (char)0x06: {
		name = L"TM31 MUD SLAP";
		break;
	}
	case (char)0x07: {
		name = L"TM32 DOUBLE TEAM";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM5(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM33 ICE PUNCH";
		break;
	}
	case (char)0x01: {
		name = L"TM34 SWAGGER";
		break;
	}
	case (char)0x02: {
		name = L"TM35 SLEEP TALK";
		break;
	}
	case (char)0x03: {
		name = L"TM36 SLUDGE BOMB";
		break;
	}
	case (char)0x04: {
		name = L"TM37 SANDSTORM";
		break;
	}
	case (char)0x05: {
		name = L"TM38 FIRE BLAST";
		break;
	}
	case (char)0x06: {
		name = L"TM39 SWIFT";
		break;
	}
	case (char)0x07: {
		name = L"TM40 DEFENSE CURL";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM6(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM41 THUNDERPUNCH";
		break;
	}
	case (char)0x01: {
		name = L"TM42 DREAM EATER";
		break;
	}
	case (char)0x02: {
		name = L"TM43 DETECT";
		break;
	}
	case (char)0x03: {
		name = L"TM44 REST";
		break;
	}
	case (char)0x04: {
		name = L"TM45 ATTRACT";
		break;
	}
	case (char)0x05: {
		name = L"TM46 THIEF";
		break;
	}
	case (char)0x06: {
		name = L"TM47 STEEL WING";
		break;
	}
	case (char)0x07: {
		name = L"TM48 FIRE PUNCH";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM7(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"TM49 FURY CUTTER";
		break;
	}
	case (char)0x01: {
		name = L"TM50 NIGHTMARE";
		break;
	}
	case (char)0x02: {
		name = L"HM01 CUT";
		break;
	}
	case (char)0x03: {
		name = L"HM02 FLY";
		break;
	}
	case (char)0x04: {
		name = L"HM03 SURF";
		break;
	}
	case (char)0x05: {
		name = L"HM04 STRENGTH";
		break;
	}
	case (char)0x06: {
		name = L"HM05 FLASH";
		break;
	}
	case (char)0x07: {
		name = L"HM06 WHIRL POOL";
		break;
	}
	}

	return name;
}

std::wstring InterpretTM8(byte bit) {
	std::wstring name = L"";

	switch (bit) {
	case (char)0x00: {
		name = L"HM07 WATERFALL";
		break;
	}
	case (char)0x01: {
		name = L"UNDEFINED";
		break;
	}
	case (char)0x02: {
		name = L"UNDEFINED";
		break;
	}
	case (char)0x03: {
		name = L"UNDEFINED";
		break;
	}
	case (char)0x04: {
		name = L"UNDEFINED";
		break;
	}
	case (char)0x05: {
		name = L"UNDEFINED";
		break;
	}
	case (char)0x06: {
		name = L"UNDEFINED";
		break;
	}
	case (char)0x07: {
		name = L"UNDEFINED";
		break;
	}
	}

	return name;
}