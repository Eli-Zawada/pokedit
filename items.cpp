#include "items.h"
#include "address.h"

int FillMarts(std::vector<byte>& data, HWND hWnd) {
	int amount = data[GetAddress(ADD_MARTS_TOTAL)];
	SendMessage(GetDlgItem(hWnd, CB_MART), CB_RESETCONTENT, 0, 0);
	
	for (int i = 0; i < amount; i++) {
		std::wstring text = L"Mart ";
		text += std::to_wstring(i);
		SendMessage(GetDlgItem(hWnd, CB_MART), CB_ADDSTRING, 0, (LPARAM)text.c_str());
	}

	SendMessage(GetDlgItem(hWnd, LB_MART_ITEMS), LB_RESETCONTENT, 0, 0);

	return 0;
}

int DisplayMart(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;

	unsigned int table = GetAddress(ADD_MARTS);
	byte mart = SendMessage(GetDlgItem(hWnd, CB_MART), CB_GETCURSEL, 0, 0);
	if (mart == -1) return -1;
	byte* pointer = new byte[3];
	pointer[2] = FindBank(table);
	pointer[0] = data[table + (2 * mart)];
	pointer[1] = data[table + (2 * mart) + 1];
	unsigned int cur = PointerToAddress(pointer);
	byte amount = data[cur++];
	byte count = 0;
	std::wstring item = L"";

	SendMessage(GetDlgItem(hWnd, LB_MART_ITEMS), LB_RESETCONTENT, 0, 0);
	while (data[cur] != 0xFF) {
		if (count > amount) item = L"U ";
		else item = L"";
		item += InterpretItems(data[cur]);
		SendMessage(GetDlgItem(hWnd, LB_MART_ITEMS), LB_ADDSTRING, 0 , (LPARAM)item.c_str());
		count++;
		cur++;
	}

	return 0;
}

int ChangeMartItem(std::vector<byte>& data, HWND hWnd) {
	unsigned int cur = GetAddress(ADD_MARTS);
	int item = SendMessage(GetDlgItem(hWnd, LB_MART_ITEMS), LB_GETCURSEL, 0, 0);
	int mart = SendMessage(GetDlgItem(hWnd, CB_MART), CB_GETCURSEL, 0, 0);

	if (item == -1 || mart == -1 || data.empty() == true) return -1;

	byte* pointer = new byte[3];
	pointer[2] = FindBank(cur);
	pointer[0] = data[cur + (2 * mart)];
	pointer[1] = data[cur + (2 * mart) + 1];
	cur = PointerToAddress(pointer) + item + 1;

	if (SendMessage(GetDlgItem(hWnd, CB_MART_ITEMS), CB_GETCURSEL, 0, 0) == -1) return -1;

	data[cur] = SendMessage(GetDlgItem(hWnd, CB_MART_ITEMS), CB_GETCURSEL, 0, 0) + 1;

	return 0;
}

int DisplayTMs(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	
	unsigned int cur = GetAddress(ADD_TM_MOVES);
	std::wstring str = L"";

	SendMessage(GetDlgItem(hWnd, LB_TM_MOVES), LB_RESETCONTENT, 0, 0);

	for (int i = 0; i < 50; i++) {
		str = L"TM ";
		if (i + 1 < 10) str += L" " + std::to_wstring(i + 1) + L": ";
		else str += std::to_wstring(i + 1) + L": ";
		str += InterpretMoves(data[cur + i]);

		SendMessage(GetDlgItem(hWnd, LB_TM_MOVES), LB_ADDSTRING, 0, (LPARAM)str.c_str());
	}

	return 0;
}

int ChangeTMMoves(std::vector<byte>& data, HWND hWnd) {
	unsigned int cur = GetAddress(ADD_TM_MOVES);
	int tm = SendMessage(GetDlgItem(hWnd, LB_TM_MOVES), LB_GETCURSEL, 0, 0);
	int move = SendMessage(GetDlgItem(hWnd, CB_CHNG_TM), CB_GETCURSEL, 0, 0);

	if (tm == -1 || move == -1 || data.empty() == true) return -1;

	cur += tm;

	data[cur] = move + 1;

	return 0;
}

int DisplayItemPrice(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += item * 7;
	byte lo = data[cur++];
	int hi = data[cur];
	hi = hi << 8;
	hi += lo;

	SetDlgItemText(hWnd, EB_ITEM_PRICE, std::to_wstring(hi).c_str());

	return 0;
}

int DisplayItemEffect(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 2;
	byte eff = data[cur];

	switch (eff) {
	case 0x00://None
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 0, 0);
		break;
	case 0x01://Berry
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 1, 0);
		break;
	case 0x02://HELD_2
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 2, 0);
		break;
	case 0x03://Leftovers
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 3, 0);
		break;
	case 0x05://HELD_5
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 4, 0);
		break;
	case 0x06://Restore PP
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 5, 0);
		break;
	case 0x08://Cleanse Tag
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 6, 0);
		break;

	case 0x0A://Heal Poison
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 7, 0);
		break;
	case 0x0B://Heal Freeze
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 8, 0);
		break;
	case 0x0C://Heal Burn
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 9, 0);
		break;
	case 0x0D://Heal Sleep
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 10, 0);
		break;
	case 0x0E://Heal Paralysis
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 11, 0);
		break;
	case 0x0F://Heal Status
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 12, 0);
		break;
	case 0x10://Heal Confusion
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 13, 0);
		break;

	case 0x14://Prevent Poison
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 14, 0);
		break;
	case 0x15://Prevent Burn
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 15, 0);
		break;
	case 0x16://Prevent Freeze
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 16, 0);
		break;
	case 0x17://Prevent Sleep
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 17, 0);
		break;
	case 0x18://Prevent Paralysis
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 18, 0);
		break;
	case 0x19://Prevent Confusion
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 19, 0);
		break;

	case 0x1E://HELD_30
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 20, 0);
		break;
	case 0x1F://Atk Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 21, 0);
		break;
	case 0x20://Def Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 22, 0);
		break;
	case 0x21://Spd Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 23, 0);
		break;
	case 0x22://SAtk Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 24, 0);
		break;
	case 0x23://SDef Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 25, 0);
		break;
	case 0x24://Acc Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 26, 0);
		break;
	case 0x25://Eva Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 27, 0);
		break;
	case 0x26://HELD_38
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 28, 0);
		break;

	case 0x2A://Metal Powder
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 29, 0);
		break;

	case 0x32://Normal Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 30, 0);
		break;
	case 0x33://Fighting Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 31, 0);
		break;
	case 0x34://Flying Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 32, 0);
		break;
	case 0x35://Poison Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 33, 0);
		break;
	case 0x36://Ground Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 34, 0);
		break;
	case 0x37://Rock Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 35, 0);
		break;
	case 0x38://Bug Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 36, 0);
		break;
	case 0x39://Ghost Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 37, 0);
		break;
	case 0x3A://Fire Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 38, 0);
		break;
	case 0x3B://Water Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 39, 0);
		break;
	case 0x3C://Grass Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 40, 0);
		break;
	case 0x3D://Electric Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 41, 0);
		break;
	case 0x3E://Psychic Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 42, 0);
		break;
	case 0x3F://Ice Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 43, 0);
		break;
	case 0x40://Dragon Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 44, 0);
		break;
	case 0x41://Dark Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 45, 0);
		break;
	case 0x42://Steel Boost
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 46, 0);
		break;

	case 0x46://Catch Chance
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 47, 0);
		break;
	case 0x47://HELD_71
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 48, 0);
		break;
	case 0x48://Held Escape
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 49, 0);
		break;
	case 0x49://Critical Up
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 50, 0);
		break;
	case 0x4A://Quick Claw
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 51, 0);
		break;
	case 0x4B://Flinch
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 52, 0);
		break;
	case 0x4C://Amulet Coin
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 53, 0);
		break;
	case 0x4D://Brightpowder
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 54, 0);
		break;
	case 0x4F://Focus Band
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 55, 0);
		break;

	default:
		SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_SETCURSEL, 56, 0);
		break;
	}

	cur++;
	SendMessage(GetDlgItem(hWnd, CB_HOLD_CHANCE), CB_SETCURSEL, data[cur], 0);

	return 0;
}

int DisplayItemType(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 5;

	SendMessage(GetDlgItem(hWnd, CB_ITEM_TYPE), CB_SETCURSEL, data[cur] - 1, 0);

	return 0;
}

int DisplayItemLimits(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 4;


	switch (data[cur]) {
	case 0x00://No Limits
		SendMessage(GetDlgItem(hWnd, CB_ITEM_USE), CB_SETCURSEL, 0, 0);
		break;
	case 0x40://Can't Use
		SendMessage(GetDlgItem(hWnd, CB_ITEM_USE), CB_SETCURSEL, 1, 0);
		break;
	case 0x80://Can't Toss
		SendMessage(GetDlgItem(hWnd, CB_ITEM_USE), CB_SETCURSEL, 2, 0);
		break;
	}

	return 0;
}

int DisplayItemMenu(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 6;
	byte menu = data[cur];

	switch (menu >> 4) {
	case 0x00://No Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU), CB_SETCURSEL, 0, 0);
		break;
	case 0x04://Current Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU), CB_SETCURSEL, 1, 0);
		break;
	case 0x05://Party Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU), CB_SETCURSEL, 2, 0);
		break;
	case 0x06://Close Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU), CB_SETCURSEL, 3, 0);
		break;
	}

	switch (menu & 0x0F) {
	case 0x00://No Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU2), CB_SETCURSEL, 0, 0);
		break;
	case 0x04://Current Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU2), CB_SETCURSEL, 1, 0);
		break;
	case 0x05://Party Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU2), CB_SETCURSEL, 2, 0);
		break;
	case 0x06://Close Menu
		SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU2), CB_SETCURSEL, 3, 0);
		break;
	}

	return 0;
}

int ChangeItemPrice(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	
	cur += (item * 7);

	wchar_t buff[7];
	GetWindowText(GetDlgItem(hWnd, EB_ITEM_PRICE), (LPWSTR)buff, 7);
	std::wstring str = buff;
	int price = 0;
	if (CheckIfNumber(str) == true) {
		price = std::stoi(str);
	}
	else return -1;

	byte lo = price & 0xFF;
	byte hi = price >> 8;

	data[cur++] = lo;
	data[cur] = hi;

	return 0;
}

int ChangeItemEffect(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);

	cur += (item * 7) + 2;

	byte eff = SendMessage(GetDlgItem(hWnd, CB_ITEM_HOLD), CB_GETCURSEL, 0, 0);
	if (eff == -1) return -1;

	switch (eff) {
	case 0://None
		data[cur] = 0x00;
		break;
	case 1://Berry
		data[cur] = 0x01;
		break;
	case 2://HELD_2
		data[cur] = 0x02;
		break;
	case 3://Leftovers
		data[cur] = 0x03;
		break;
	case 4://HELD_5
		data[cur] = 0x05;
		break;
	case 5://Restore PP
		data[cur] = 0x06;
		break;
	case 6://Cleanse Tag
		data[cur] = 0x08;
		break;

	case 7://Heal Poison
		data[cur] = 0x0A;
		break;
	case 8://Heal Freeze
		data[cur] = 0x0B;
		break;
	case 9://Heal Burn
		data[cur] = 0x0C;
		break;
	case 10://Heal Sleep
		data[cur] = 0x0D;
		break;
	case 11://Heal Paralysis
		data[cur] = 0x0E;
		break;
	case 12://Heal Status
		data[cur] = 0x0F;
		break;
	case 13://Heal Confusion
		data[cur] = 0x10;
		break;

	case 14://Prevent Poison
		data[cur] = 0x14;
		break;
	case 15://Prevent Burn
		data[cur] = 0x15;
		break;
	case 16://Prevent Freeze
		data[cur] = 0x16;
		break;
	case 17://Prevent Sleep
		data[cur] = 0x17;
		break;
	case 18://Prevent Paralysis
		data[cur] = 0x18;
		break;
	case 19://Prevent Confusion
		data[cur] = 0x19;
		break;

	case 20://HELD_30
		data[cur] = 0x1E;
		break;
	case 21://Atk Up
		data[cur] = 0x1F;
		break;
	case 22://Def Up
		data[cur] = 0x20;
		break;
	case 23://Spd Up
		data[cur] = 0x21;
		break;
	case 24://SAtk Up
		data[cur] = 0x22;
		break;
	case 25://SDef Up
		data[cur] = 0x23;
		break;
	case 26://Acc Up
		data[cur] = 0x24;
		break;
	case 27://Eva Up
		data[cur] = 0x25;
		break;
	case 28://HELD_38
		data[cur] = 0x26;
		break;

	case 29://Metal Powder
		data[cur] = 0x2A;
		break;

	case 30://Normal Boost
		data[cur] = 0x32;
		break;
	case 31://Fighting Boost
		data[cur] = 0x33;
		break;
	case 32://Flying Boost
		data[cur] = 0x34;
		break;
	case 33://Poison Boost
		data[cur] = 0x35;
		break;
	case 34://Ground Boost
		data[cur] = 0x36;
		break;
	case 35://Rock Boost
		data[cur] = 0x37;
		break;
	case 36://Bug Boost
		data[cur] = 0x38;
		break;
	case 37://Ghost Boost
		data[cur] = 0x39;
		break;
	case 38://Fire Boost
		data[cur] = 0x3A;
		break;
	case 39://Water Boost
		data[cur] = 0x3B;
		break;
	case 40://Grass Boost
		data[cur] = 0x3C;
		break;
	case 41://Electric Boost
		data[cur] = 0x3D;
		break;
	case 42://Psychic Boost
		data[cur] = 0x3E;
		break;
	case 43://Ice Boost
		data[cur] = 0x3F;
		break;
	case 44://Dragon Boost
		data[cur] = 0x40;
		break;
	case 45://Dark Boost
		data[cur] = 0x41;
		break;
	case 46://Steel Boost
		data[cur] = 0x42;
		break;

	case 47://Catch Chance
		data[cur] = 0x46;
		break;
	case 48://HELD_71
		data[cur] = 0x47;
		break;
	case 49://Held Escape
		data[cur] = 0x48;
		break;
	case 50://Critical Up
		data[cur] = 0x49;
		break;
	case 51://Quick Claw
		data[cur] = 0x4A;
		break;
	case 52://Flinch
		data[cur] = 0x4B;
		break;
	case 53://Amulet Coin
		data[cur] = 0x4C;
		break;
	case 54://Brightpowder
		data[cur] = 0x4D;
		break;
	case 55://Focus Band
		data[cur] = 0x4F;
		break;

	default:
		data[cur] = 0;
		break;
	}

	cur++;

	data[cur] = (byte)SendMessage(GetDlgItem(hWnd, CB_HOLD_CHANCE), CB_GETCURSEL, 0, 0);

	return 0;
}

int ChangeItemType(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 5;

	data[cur] = (byte) SendMessage(GetDlgItem(hWnd, CB_ITEM_TYPE), CB_GETCURSEL, 0, 0) + 1;

	return 0;
}

int ChangeItemLimits(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 4;

	switch (SendMessage(GetDlgItem(hWnd, CB_ITEM_USE), CB_GETCURSEL, 0, 0)) {
	case 0://No Limits
		data[cur] = 0x00;
		break;
	case 1://Can't Use
		data[cur] = 0x40;
		break;
	case 2://Can't Toss
		data[cur] = 0x80;
		break;
	}

	return 0;
}

int ChangeItemMenu(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;
	unsigned int cur = GetAddress(ADD_ITEMS);
	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0, 0);
	cur += (item * 7) + 6;
	byte menu = 0;

	switch (SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU), CB_GETCURSEL, 0, 0)) {
	case 0://No Menu
		menu = 0x00;
		break;
	case 1://Current Menu
		menu = 0x04;
		break;
	case 2://Party Menu
		menu = 0x05;
		break;
	case 3://Close Menu
		menu = 0x06;
		break;
	default:
		return -1;
	}

	menu = menu << 4;

	switch (SendMessage(GetDlgItem(hWnd, CB_ITEM_MENU2), CB_GETCURSEL, 0, 0)) {
	case 0://No Menu
		menu += 0x00;
		break;
	case 1://Current Menu
		menu += 0x04;
		break;
	case 2://Party Menu
		menu += 0x05;
		break;
	case 3://Close Menu
		menu += 0x06;
		break;
	default:
		return -1;
	}

	data[cur] = menu;

	return 0;
}

int UpdateItemName(std::vector<byte>& data, HWND hWnd) {
	if (data.empty() == true) return -1;

	unsigned int add = GetAddress(ADD_ITEM_STR_PNTR);
	byte pointer[3] = { 0 };

	pointer[2] = data[add - 1];
	pointer[1] = data[add + 1];
	pointer[0] = data[add];

	add = PointerToAddress(pointer);

	pointer[2] = FindBank(add) + 1;
	pointer[1] = 0x40;
	pointer[0] = 0x00;

	unsigned int end = PointerToAddress(pointer) - 1;

	byte item = SendMessage(GetDlgItem(hWnd, CB_ITEMS), CB_GETCURSEL, 0 ,0) + 1;
	for (int i = 0; i < item; i++) {
		while (data[add] != 0x50) {
			add++;
		}
		add++;
	}

	std::vector<byte> copy = CopyData(data, add - 1, end - 1);

	int old_size = 0;

	add -= 2;
	while (data[add] != 0x50) {
		add--;
		old_size++;
	}
	add++;

	wchar_t buff[14] = { L'\0' };
	GetWindowText(GetDlgItem(hWnd, EB_ITEM_NAME), buff, 14);
	int new_size = 0;

	for (wchar_t c: buff) {
		if (c != L'\0') {
			data[add++] = TextToHex(c);
			new_size++;
		}
	}

	PasteData(data, add, copy);

	UpdateStringPointers(data, new_size - old_size, 1);

	return 0;
}