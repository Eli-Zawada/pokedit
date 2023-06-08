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