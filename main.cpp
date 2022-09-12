#include "main.h"

std::vector<BYTE> rom;

HMENU hMenu;
HWND hTabCntrl;
HWND hStat;

HWND cb_poke;
HWND cb_moves;
HWND cb_levels;
HWND cb_egg_moves;
HWND cb_tms;
HWND cb_item23;
HWND cb_item2;
HWND cb_growth;
HWND cb_gender;
HWND cb_spr_size;
HWND cb_egg_1;
HWND cb_egg_2;
HWND cb_type_1;
HWND cb_type_2;
HWND cb_rom;
HWND cb_evo_met;
HWND cb_evo_con;
HWND cb_evo_pok;
HWND cb_evo_stat;

HWND btn_select;
HWND btn_rom;
HWND btn_add_moves;
HWND btn_del_moves;
HWND btn_add_egg;
HWND btn_del_egg;
HWND btn_tog_tm;
HWND btn_upd_bs;
HWND btn_sel_evo;
HWND btn_add_evo;
HWND btn_del_evo;

HWND eb_hp;
HWND eb_atk;
HWND eb_def;
HWND eb_spd;
HWND eb_satk;
HWND eb_sdef;
HWND eb_cap_rate;
HWND eb_base_exp;
HWND eb_spr_size;
HWND eb_hatch;

HWND stc_level_up;
HWND stc_egg_move;
HWND stc_tms;
HWND stc_hp;
HWND stc_atk;
HWND stc_def;
HWND stc_spd;
HWND stc_satk;
HWND stc_sdef;
HWND stc_cr;
HWND stc_exp;
HWND stc_growth;
HWND stc_gender;
HWND stc_hatch;
HWND stc_size;
HWND stc_item23;
HWND stc_item2;
HWND stc_egg_1;
HWND stc_egg_2;
HWND stc_type_1;
HWND stc_type_2;
HWND stc_evo;

HWND lb_level_up;
HWND lb_level_move;
HWND lb_egg_move;
HWND lb_tm;
HWND lb_evo;

int tab_sel = 0;
int desk_width = GetSystemMetrics(SM_CXSCREEN);
int desk_height = GetSystemMetrics(SM_CYSCREEN);

unsigned char pokemon = 0;
unsigned char prev = 0;
unsigned char level = 0;
unsigned char move = 0;
unsigned char egg = 0;
unsigned char tm = 0;

int level_up_table = GS_TABLE_DATA;
int egg_table = GS_EGG_TABLE;
int base_stats_address = GS_BASE_STATS;
int trainer_class_address = GS_TRAINER_TYPES;
int trainer_table_address = GS_TRAINER_TABLE;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HTREEITEM hti = TreeView_GetSelection(GetDlgItem(hWnd, TV_TRAINERS));
	char item23_sel = SendMessage(GetDlgItem(hWnd, CB_ITEM_23), CB_GETCURSEL, 0, 0);
	char item2_sel = SendMessage(GetDlgItem(hWnd, CB_ITEM_2), CB_GETCURSEL, 0, 0);
	char type1_sel = SendMessage(GetDlgItem(hWnd, CB_TYPE_1), CB_GETCURSEL, 0, 0);
	char type2_sel = SendMessage(GetDlgItem(hWnd, CB_TYPE_2), CB_GETCURSEL, 0, 0);

	switch (msg) {

	case WM_CREATE:
		AddMenus(hWnd);
		AddTabs(hWnd);
		AddPokemonControls(hWnd);
		AddTrainerControls(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_COMMAND:
		int val;
		switch (wParam) {
		case CLOSE_WINDOW:
			val = MessageBoxW(hWnd, L"Are you sure?", L"Wait", MB_YESNO | MB_ICONEXCLAMATION);
			if (val == IDYES) {
				DestroyWindow(hWnd);
			}
			break;
		case OPEN_FILE:
			OpenFile(hWnd);
			if (rom.empty() == false) {
				TogglePokemonEnables(true);
				FillTrainerTree(rom, trainer_table_address, trainer_class_address, GetDlgItem(hWnd, TV_TRAINERS));
			}
			break;
		case SAVE_FILE:
			SaveFile(hWnd);
			break;
		case ROM_BUTTON:
			SelectRom(cb_rom);
			if (rom.empty() == false) {
				SelectPokemon(hWnd);
				FillTrainerTree(rom, trainer_table_address, trainer_class_address, GetDlgItem(hWnd, TV_TRAINERS));
				GetTrainerData(rom, hti, trainer_table_address, GetDlgItem(hWnd, TV_TRAINERS), hWnd);
			}
			break;
		case ADD_MOVE_BUTTON:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			level = SendMessage(GetDlgItem(hWnd, CB_LEVELS), CB_GETCURSEL, NULL, NULL);
			move = SendMessage(GetDlgItem(hWnd, CB_MOVES), CB_GETCURSEL, NULL, NULL);
			if (level != 255 && move != 255) {
				rom = InsertLevelMoves(level_up_table, pokemon + 1, rom, level + 1, move + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Level and Move", L"", MB_OK);
			}
			break;
		case DEL_MOVE_BUTTON:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			level = SendMessage(GetDlgItem(hWnd, CB_LEVELS), CB_GETCURSEL, NULL, NULL);
			move = SendMessage(GetDlgItem(hWnd, CB_MOVES), CB_GETCURSEL, NULL, NULL);
			if (level != 255 && move != 255) {
				rom = DeleteLevelMoves(level_up_table, pokemon + 1, rom, level + 1, move + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Level and Move", L"", MB_OK);
			}
			break;
		case SELECT_BUTTON:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			SelectPokemon(hWnd);
			break;
		case ADD_EGG_BUTTON:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			move = SendMessage(GetDlgItem(hWnd, CB_EGG_MOVES), CB_GETCURSEL, NULL, NULL);
			if (move != 255) {
				rom = InsertEggMoves(egg_table, pokemon + 1, rom, move + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Move", L"", MB_OK);
			}
			break;
		case DEL_EGG_BUTTON:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			move = SendMessage(GetDlgItem(hWnd, CB_EGG_MOVES), CB_GETCURSEL, NULL, NULL);
			if (move != 255) {
				rom = DeleteEggMoves(egg_table, pokemon + 1, rom, move + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select A Move", L"", MB_OK);
			}
			break;
		case TOGGLE_TM_BUTTON:
			tm = SendMessage(GetDlgItem(hWnd, CB_TMS), CB_GETCURSEL, NULL, NULL);

			if (tm != 255) {
				rom = ToggleTMs(base_stats_address, pokemon + 1, rom, tm + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select a TM", L"", MB_OK);
			}
			break;
		case EVO_BUTTON:
			ChangeEvoCombos(cb_evo_met, cb_evo_con, cb_evo_pok, cb_evo_stat);
			break;
		case ADD_EVO_BUTTON:
			if (SendMessage(cb_evo_met, CB_GETCURSEL, 0, 0) != -1 && SendMessage(cb_evo_con, CB_GETCURSEL, 0, 0) != -1 && SendMessage(cb_evo_pok, CB_GETCURSEL, 0, 0) != -1) {
				//if (SendMessage(cb_evo_met, CB_GETCURSEL, 0, 0) == 4 && SendMessage(cb_evo_stat, CB_GETCURSEL, 0, 0) != -1) {
				rom = InsertEvolution(level_up_table, pokemon + 1, rom, hWnd, CB_EVO_MET, CB_EVO_CON, CB_EVO_POK, CB_EVO_STAT);
				//}
			}
			SelectPokemon(hWnd);
			break;
		case DEL_EVO_BUTTON:
			if (SendMessage(cb_evo_met, CB_GETCURSEL, 0, 0) != -1 && SendMessage(cb_evo_con, CB_GETCURSEL, 0, 0) != -1 && SendMessage(cb_evo_pok, CB_GETCURSEL, 0, 0) != -1) {
				//if (SendMessage(cb_evo_met, CB_GETCURSEL, 0, 0) == 4 && SendMessage(cb_evo_stat, CB_GETCURSEL, 0, 0) != -1) {
				rom = DeleteEvolution(level_up_table, pokemon + 1, rom, hWnd, CB_EVO_MET, CB_EVO_CON, CB_EVO_POK, CB_EVO_STAT);
				//}
			}
			SelectPokemon(hWnd);
			break;
		case UPDATE_STATS_BUTTON:
			rom = ChangeBaseStats(base_stats_address, pokemon + 1, rom, hWnd, eb_hp, eb_atk, eb_def, eb_spd, eb_satk, eb_sdef);
			rom = ChangeCaptureRate(base_stats_address, pokemon + 1, rom, hWnd, EB_CR);
			rom = ChangeBaseExp(base_stats_address, pokemon + 1, rom, hWnd, EB_BASE_EXP);
			rom = ChangeEggGroup(base_stats_address, pokemon + 1, rom, hWnd, CB_EGG_1, CB_EGG_2);
			rom = ChangeGenderRatio(base_stats_address, pokemon + 1, rom, hWnd, CB_GENDER);
			rom = ChangeHatchSteps(base_stats_address, pokemon + 1, rom, hWnd, EB_HATCH_STEP);
			rom = ChangeGrowthType(base_stats_address, pokemon + 1, rom, hWnd, CB_GROWTH);
			rom = ChangeSpriteSize(base_stats_address, pokemon + 1, rom, hWnd, CB_SPR_SIZE);
			if (type1_sel != -1 && type2_sel != -1) {
				rom = ChangeTyping(base_stats_address, pokemon + 1, rom, hWnd, CB_TYPE_1, CB_TYPE_2);
			}
			if (item23_sel != -1 && item2_sel != -1) {
				rom = ChangeHoldItems(base_stats_address, pokemon + 1, rom, hWnd, CB_ITEM_23, CB_ITEM_2);
			}

			SelectPokemon(hWnd);
			break;
		case BTN_UPDATE_TRAINER:
			ChangeTrainerData(hWnd, rom, GS_TRAINER_TABLE, hti);
			FillTrainerTree(rom, trainer_table_address, trainer_class_address, GetDlgItem(hWnd, TV_TRAINERS));
			GetTrainerData(rom, hti, trainer_table_address, GetDlgItem(hWnd, TV_TRAINERS), hWnd);
			break;
		case BTN_ADD_TRAINER:
			AddTrainerData(hWnd, rom, trainer_table_address, hti);
			FillTrainerTree(rom, trainer_table_address, trainer_class_address, GetDlgItem(hWnd, TV_TRAINERS));
			GetTrainerData(rom, hti, trainer_table_address, GetDlgItem(hWnd, TV_TRAINERS), hWnd);
			break;
		}

		if (CBN_SELCHANGE == HIWORD(wParam)) {
			if (LOWORD(wParam) == CB_POKEMON) {
				SelectPokemon(hWnd);
			}
			if (LOWORD(wParam) == CB_TRAINER_CONTROL) {
				DisableTrainerControls(hWnd, SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_GETCURSEL, NULL, NULL));
			}
			if (LOWORD(wParam) == CB_EVO_MET) {
				ChangeEvoCombos(cb_evo_met, cb_evo_con, cb_evo_pok, cb_evo_stat);
			}
			if (LOWORD(wParam) == CB_ROM) {
				SelectRom(cb_rom);
				if (rom.empty() == false) {
					SelectPokemon(hWnd);
					FillTrainerTree(rom, trainer_table_address, trainer_class_address, GetDlgItem(hWnd, TV_TRAINERS));
					GetTrainerData(rom, hti, trainer_table_address, GetDlgItem(hWnd, TV_TRAINERS), hWnd);
				}

			}
		}
		
		return 0;

	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == TCN_SELCHANGE) {
			tab_sel = TabCtrl_GetCurSel(hTabCntrl);

			switch (tab_sel) {
			case 0:
				TogglePokemonTab(true);
				ToggleTrainerTab(false, hWnd);
				break;
			case 1:
				TogglePokemonTab(false);
				ToggleTrainerTab(true, hWnd);
				break;
			case 2:
				TogglePokemonTab(false);
				ToggleTrainerTab(false, hWnd);
				break;
			case 3:
				TogglePokemonTab(false);
				ToggleTrainerTab(false, hWnd);
				break;
			case 4:
				TogglePokemonTab(false);
				ToggleTrainerTab(false, hWnd);
				break;
			}
		}
		if (((LPNMHDR)lParam)->code == TVN_SELCHANGED) {
			if (TreeView_GetChild(GetDlgItem(hWnd, TV_TRAINERS), hti) == NULL) {
				GetTrainerData(rom, hti, trainer_table_address, GetDlgItem(hWnd, TV_TRAINERS), hWnd);
			}

		}
		
		return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

void StartCommonControls(DWORD flags) {
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC = flags;
	InitCommonControlsEx(&iccx);
}

HWND CreateTab(HWND hParent, HINSTANCE hInst, DWORD dwStyle, int x, int y, int width, int height, int id) {

	dwStyle |= WS_CHILD | WS_VISIBLE;

	return CreateWindowEx(0, WC_TABCONTROL, 0, dwStyle, x, y, width, height, hParent, (HMENU)id, hInst, 0);
}

int InsertTabItem(HWND hWnd, std::wstring txt, int item_index, int image_index) {
	UINT mask = TCIF_TEXT | TCIF_IMAGE;

	TCITEM tabPage = { 0 };

	tabPage.mask = mask;
	tabPage.pszText = (LPWSTR)txt.c_str();
	tabPage.cchTextMax = (int)txt.length();
	tabPage.iImage = image_index;

	return (int)SendMessage(hWnd, TCM_INSERTITEM, item_index, (LPARAM)&tabPage);
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_STRING, OPEN_FILE, L"Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, SAVE_FILE, L"Save");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, CLOSE_WINDOW, L"Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

	SetMenu(hWnd, hMenu);
}

void AddTabs(HWND hWnd) {
	StartCommonControls(ICC_TAB_CLASSES);

	hTabCntrl = CreateTab(hWnd, 0, TCS_FIXEDWIDTH, 0, 0, desk_width, desk_height, IDC_TAB);
	
	SendMessage(hTabCntrl, TCM_SETCURSEL, 0, 0);

	InsertTabItem(hTabCntrl, L"Pokemon", 0, 0);
	InsertTabItem(hTabCntrl, L"Trainers", 1, 0);
	InsertTabItem(hTabCntrl, L"Encounters", 2, 0);
	InsertTabItem(hTabCntrl, L"Shops", 3, 0);
	InsertTabItem(hTabCntrl, L"Addresses", 4, 0);
}

HTREEITEM InsertTreeItem(HWND hWndTV, LPWSTR name, int nLevel, HTREEITEM hPrev, HTREEITEM hPrevRootItem, HTREEITEM hPrevLev2Item, LPARAM lParam) {
	TVITEM item;
	TVINSERTSTRUCT insert;
	//static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST;
	//static HTREEITEM hPrevRootItem = NULL;
	//static HTREEITEM hPrevLev2Item = NULL;
	HTREEITEM hti;

	//Set up the item to be inserted into the tree
	item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	item.pszText = name;
	item.cchTextMax = sizeof(item.pszText) / sizeof(item.pszText[0]);
	item.lParam = lParam;
	//item.iItem = 
	//item.iSelectedImage = 

	//Set the insert info
	insert.item = item;
	insert.hInsertAfter = hPrev;
	//Set the parent of the insert depending on what level the new item is
	if (nLevel == 1) {
		insert.hParent = TVI_ROOT;
	}
	else if (nLevel == 2) {
		insert.hParent = hPrevRootItem;
	}
	else {
		insert.hParent = hPrevLev2Item;
	}
	
	//Sets the previous Tree item to this one for next function call
	hPrev = (HTREEITEM)TreeView_InsertItem(hWndTV, &insert);

	if (hPrev == NULL) {
		return NULL;
	}

	if (nLevel == 1) {
		hPrevRootItem = hPrev;
	}
	if (nLevel == 2) {
		hPrevLev2Item = hPrev;
	}

	if (nLevel > 1) {
		hti = TreeView_GetParent(hWndTV, hPrev);
		item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		item.hItem = hti;
		//item.iImage = 
		//item.iSelectedimage = 
		TreeView_SetItem(hWndTV, &item);
	}

	return hPrev;

}

void AddPokemonControls(HWND hWnd) {
	stc_level_up = CreateWindowW(L"Static", L"Level Up Moves", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, LVL_CONS_X, LVL_CONS_Y, 150, 25, hWnd,
		(HMENU)IDC_STATIC_LEVEL, NULL, NULL);
	stc_egg_move = CreateWindowW(L"Static", L"Egg Moves", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, EGG_CONS_X, EGG_CONS_Y, 150, 25, hWnd,
		(HMENU)IDC_STATIC_EGG, NULL, NULL);
	stc_tms = CreateWindowW(L"Static", L"TM Compatability", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TM_CONS_X, TM_CONS_Y, 170, 25, hWnd,
		(HMENU)IDC_STATIC_TM, NULL, NULL);

	stc_hp = CreateWindowW(L"Static", L"HP", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y, BS_CONS_W, 25, hWnd,
		0, NULL, NULL);
	stc_atk = CreateWindowW(L"Static", L"Attack", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 50, BS_CONS_W, 25, hWnd,
		0, NULL, NULL);
	stc_def = CreateWindowW(L"Static", L"Defense", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 100, BS_CONS_W, 25, hWnd,
		0, NULL, NULL);
	stc_spd = CreateWindowW(L"Static", L"Speed", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 150, BS_CONS_W, 25, hWnd,
		0, NULL, NULL);
	stc_satk = CreateWindowW(L"Static", L"Special Atk", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 200, BS_CONS_W, 25, hWnd,
		0, NULL, NULL);
	stc_sdef = CreateWindowW(L"Static", L"Special Def", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 250, BS_CONS_W, 25, hWnd,
		0, NULL, NULL);
	stc_cr = CreateWindowW(L"Static", L"Capture Rate", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y, 100, 25, hWnd,
		0, NULL, NULL);
	stc_exp = CreateWindowW(L"Static", L"Base EXP", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 50, 100, 25, hWnd,
		0, NULL, NULL);
	stc_growth = CreateWindowW(L"Static", L"Growth Rate", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 100, 100, 25, hWnd,
		0, NULL, NULL);
	stc_gender = CreateWindowW(L"Static", L"Gender Ratio", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 150, 100, 25, hWnd,
		0, NULL, NULL);
	stc_hatch = CreateWindowW(L"Static", L"Steps to Hatch", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 200, 100, 25, hWnd,
		0, NULL, NULL);
	stc_size = CreateWindowW(L"Static", L"Sprite Size", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 250, 100, 25, hWnd,
		0, NULL, NULL);
	stc_item23 = CreateWindowW(L"Static", L"Hold Item 23%", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y, 150, 25, hWnd,
		0, NULL, NULL);
	stc_item2 = CreateWindowW(L"Static", L"Hold Item 2%", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 50, 150, 25, hWnd,
		0, NULL, NULL);
	stc_egg_1 = CreateWindowW(L"Static", L"Egg Group 1", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 100, 150, 25, hWnd,
		0, NULL, NULL);
	stc_egg_2 = CreateWindowW(L"Static", L"Egg Group 2", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 150, 150, 25, hWnd,
		0, NULL, NULL);
	stc_type_1 = CreateWindowW(L"Static", L"Type 1", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 200, 150, 25, hWnd,
		0, NULL, NULL);
	stc_type_2 = CreateWindowW(L"Static", L"Type 2", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 250, 150, 25, hWnd,
		0, NULL, NULL);
	stc_evo = CreateWindowW(L"Static", L"Evolution", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, EVO_CONS_X, EVO_CONS_Y, 150, 25, hWnd,
		0, NULL, NULL);

	cb_rom = AddRomCombo(hWnd, ROM_CONS_X, ROM_CONS_Y, 125, 100, CB_ROM);
	cb_poke = AddPokemonCombo(hWnd, (desk_width / 2) - 75, 25, 170, 150, CB_POKEMON, 1);
	cb_moves = AddMovesCombo(hWnd, LVL_CONS_X, LVL_CONS_Y + 25, 150, 175, CB_MOVES, 1);
	cb_levels = AddLevelsCombo(hWnd, LVL_CONS_X, LVL_CONS_Y + 50, 150, 175, CB_LEVELS, 1);
	cb_egg_moves = AddMovesCombo(hWnd, EGG_CONS_X, EGG_CONS_Y + 25, 150, 175, CB_EGG_MOVES, 1);
	cb_tms = AddTMCombo(hWnd, TM_CONS_X, TM_CONS_Y + 25, 170, 175, CB_TMS);
	cb_growth = AddGrowthCombo(hWnd, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 125, 100, 175, CB_GROWTH);
	cb_gender = AddGenderCombo(hWnd, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 175, 100, 175, CB_GENDER);
	cb_spr_size = AddSizeCombo(hWnd, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 275, 100, 175, CB_SPR_SIZE);
	cb_item23 = AddItemsCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 25, 150, 175, CB_ITEM_23, 0);
	cb_item2 = AddItemsCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 75, 150, 175, CB_ITEM_2, 0);
	cb_egg_1 = AddEggGroupCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 125, 150, 175, CB_EGG_1);
	cb_egg_2 = AddEggGroupCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 175, 150, 175, CB_EGG_2);
	cb_type_1 = AddTypeCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 225, 150, 175, CB_TYPE_1);
	cb_type_2 = AddTypeCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 275, 150, 175, CB_TYPE_2);
	cb_evo_met = AddEvoMethodCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 25, 150, 175, CB_EVO_MET);
	cb_evo_con = AddLevelsCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 75, 150, 175, CB_EVO_CON, 1);
	cb_evo_pok = AddPokemonCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 100, 150, 175, CB_EVO_POK, 1);
	cb_evo_stat = AddEvoStatCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 125, 150, 175, CB_EVO_STAT);

	btn_select = CreateWindow(L"Button", L"Select", WS_VISIBLE | WS_CHILD, (desk_width / 2) - 25, 50, 50, 25, hWnd, (HMENU)SELECT_BUTTON, NULL, NULL);
	btn_rom = CreateWindow(L"Button", L"Select", WS_VISIBLE | WS_CHILD, ROM_CONS_X + 150, ROM_CONS_Y, 50, 25, hWnd, (HMENU)ROM_BUTTON, NULL, NULL);
	btn_add_moves = CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, LVL_CONS_X + 12, LVL_CONS_Y + 375, 50, 25, hWnd, (HMENU)ADD_MOVE_BUTTON, NULL, NULL);
	btn_del_moves = CreateWindow(L"Button", L"Delete", WS_VISIBLE | WS_CHILD, LVL_CONS_X + 88, LVL_CONS_Y + 375, 50, 25, hWnd, (HMENU)DEL_MOVE_BUTTON, NULL, NULL);
	btn_add_egg = CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, EGG_CONS_X + 12, EGG_CONS_Y + 375, 50, 25, hWnd, (HMENU)ADD_EGG_BUTTON, NULL, NULL);
	btn_del_egg = CreateWindow(L"Button", L"Delete", WS_VISIBLE | WS_CHILD, EGG_CONS_X + 88, EGG_CONS_Y + 375, 50, 25, hWnd, (HMENU)DEL_EGG_BUTTON, NULL, NULL);
	btn_tog_tm = CreateWindow(L"Button", L"Toggle", WS_VISIBLE | WS_CHILD, TM_CONS_X + 50, TM_CONS_Y + 375, 50, 25, hWnd, (HMENU)TOGGLE_TM_BUTTON, NULL, NULL);
	btn_upd_bs = CreateWindow(L"Button", L"Update", WS_VISIBLE | WS_CHILD, BS_CONS_X + 15, BS_CONS_Y + 375, 50, 25, hWnd, (HMENU)UPDATE_STATS_BUTTON, NULL, NULL);
	btn_sel_evo = CreateWindow(L"Button", L"Select Method", WS_VISIBLE | WS_CHILD, EVO_CONS_X, EVO_CONS_Y + 50, 150, 25, hWnd, (HMENU)EVO_BUTTON, NULL, NULL);
	btn_add_evo = CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, EVO_CONS_X, EVO_CONS_Y + 375, 50, 25, hWnd, (HMENU)ADD_EVO_BUTTON, NULL, NULL);
	btn_del_evo = CreateWindow(L"Button", L"Delete", WS_VISIBLE | WS_CHILD, EVO_CONS_X + 75, EVO_CONS_Y + 375, 50, 25, hWnd, (HMENU)DEL_EVO_BUTTON, NULL, NULL);


	lb_level_up = CreateWindow(L"ListBox", L"Level", WS_VISIBLE | WS_CHILD | WS_BORDER, LVL_CONS_X, LVL_CONS_Y + 75, 30, 300, hWnd, (HMENU)LB_LEVEL, NULL, NULL);
	lb_level_move = CreateWindow(L"ListBox", L"Moves", WS_VISIBLE | WS_CHILD | WS_BORDER, LVL_CONS_X + 30, LVL_CONS_Y + 75, 120, 300, hWnd, (HMENU)LB_MOVES, NULL, NULL);
	lb_egg_move = CreateWindow(L"ListBox", L"Egg Moves", WS_VISIBLE | WS_CHILD | WS_BORDER, EGG_CONS_X, EGG_CONS_Y + 75, 150, 300, hWnd, (HMENU)LB_EGG_MOVES, NULL, NULL);
	lb_tm = CreateWindow(L"ListBox", L"TMs", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, TM_CONS_X, TM_CONS_Y + 75, 170, 300, hWnd, (HMENU)LB_TMS, NULL, NULL);
	lb_evo = CreateWindow(L"ListBox", L"Evolution", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, EVO_CONS_X, EVO_CONS_Y + 150, 150, 225, hWnd, (HMENU)LB_EVO, NULL, NULL);

	eb_hp = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 25, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_HP, NULL, NULL);
	eb_atk = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 75, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_ATK, NULL, NULL);
	eb_def = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 125, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_DEF, NULL, NULL);
	eb_spd = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 175, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_SPD, NULL, NULL);
	eb_satk = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 225, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_SATK, NULL, NULL);
	eb_sdef = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 275, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_SDEF, NULL, NULL);
	eb_cap_rate = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 25, 100, 20, hWnd, (HMENU)EB_CR, NULL, NULL);
	eb_base_exp = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 75, 100, 20, hWnd, (HMENU)EB_BASE_EXP, NULL, NULL);
	eb_hatch = CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 225, 100, 20, hWnd, (HMENU)EB_HATCH_STEP, NULL, NULL);

	TogglePokemonEnables(false);
	EnableWindow(cb_evo_con, false);
	EnableWindow(cb_evo_pok, false);
	EnableWindow(cb_evo_stat, false);
}

void AddTrainerControls(HWND hWnd) {
	CreateWindowEx(0, WC_TREEVIEW, L"Tree", WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 20, 50, 150, 500, hWnd, (HMENU)TV_TRAINERS, 0, 0);
	
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X - BS_CONS_W - 50, 50, 50, 25, hWnd,
		(HMENU)STC_TRAINER_CODE, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X - BS_CONS_W - 100, 50, 50, 25, hWnd,
		(HMENU)STC_TRAINER_TYPE, NULL, NULL);

	AddPokemonCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y, 170, 150, CB_TRA_POKE1, 0);
	AddPokemonCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y, 170, 150, CB_TRA_POKE2, 0);
	AddPokemonCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y, 170, 150, CB_TRA_POKE3, 0);
	AddPokemonCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y, 170, 150, CB_TRA_POKE4, 0);
	AddPokemonCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y, 170, 150, CB_TRA_POKE5, 0);
	AddPokemonCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y, 170, 150, CB_TRA_POKE6, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 100, 170, 150, CB_TRA_MOVE1_1, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 125, 170, 150, CB_TRA_MOVE1_2, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 150, 170, 150, CB_TRA_MOVE1_3, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 175, 170, 150, CB_TRA_MOVE1_4, 0);
	AddItemsCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 225, 170, 150, CB_TRA_ITEM_1, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 100, 170, 150, CB_TRA_MOVE2_1, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 125, 170, 150, CB_TRA_MOVE2_2, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 150, 170, 150, CB_TRA_MOVE2_3, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 175, 170, 150, CB_TRA_MOVE2_4, 0);
	AddItemsCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 225, 170, 150, CB_TRA_ITEM_2, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 100, 170, 150, CB_TRA_MOVE3_1, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 125, 170, 150, CB_TRA_MOVE3_2, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 150, 170, 150, CB_TRA_MOVE3_3, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 175, 170, 150, CB_TRA_MOVE3_4, 0);
	AddItemsCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 225, 170, 150, CB_TRA_ITEM_3, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 100, 170, 150, CB_TRA_MOVE4_1, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 125, 170, 150, CB_TRA_MOVE4_2, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 150, 170, 150, CB_TRA_MOVE4_3, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 175, 170, 150, CB_TRA_MOVE4_4, 0);
	AddItemsCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 225, 170, 150, CB_TRA_ITEM_4, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 100, 170, 150, CB_TRA_MOVE5_1, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 125, 170, 150, CB_TRA_MOVE5_2, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 150, 170, 150, CB_TRA_MOVE5_3, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 175, 170, 150, CB_TRA_MOVE5_4, 0);
	AddItemsCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 225, 170, 150, CB_TRA_ITEM_5, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 100, 170, 150, CB_TRA_MOVE6_1, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 125, 170, 150, CB_TRA_MOVE6_2, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 150, 170, 150, CB_TRA_MOVE6_3, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 175, 170, 150, CB_TRA_MOVE6_4, 0);
	AddItemsCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 225, 170, 150, CB_TRA_ITEM_6, 0);
	AddLevelsCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 50, 170, 150, CB_TRA_LVL_1, 0);
	AddLevelsCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 50, 170, 150, CB_TRA_LVL_2, 0);
	AddLevelsCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 50, 170, 150, CB_TRA_LVL_3, 0);
	AddLevelsCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 50, 170, 150, CB_TRA_LVL_4, 0);
	AddLevelsCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 50, 170, 150, CB_TRA_LVL_5, 0);
	AddLevelsCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 50, 170, 150, CB_TRA_LVL_6, 0);

	CreateWindow(L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN |
		CBS_HASSTRINGS | WS_VSCROLL, desk_width - 200, 100, 50, 150, hWnd, (HMENU)CB_TRAINER_CONTROL, NULL, NULL );

	SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_ADDSTRING, 0, (LPARAM)L"0");
	SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_ADDSTRING, 0, (LPARAM)L"1");
	SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_ADDSTRING, 0, (LPARAM)L"2");
	SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_ADDSTRING, 0, (LPARAM)L"3");

	CreateWindow(L"Button", L"Update", WS_VISIBLE | WS_CHILD, (desk_width / 2) - 25, 100, 50, 25, hWnd, (HMENU)BTN_UPDATE_TRAINER, NULL, NULL);
	CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, (desk_width / 2) + 100, 100, 50, 25, hWnd, (HMENU)BTN_ADD_TRAINER, NULL, NULL);

	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, desk_width / 2, 50, BS_CONS_W + 100, 25, hWnd, (HMENU)EB_TRAINER_NAME, NULL, NULL);
	
	ToggleTrainerTab(false, hWnd);
}

void SelectRom(HWND hWnd) {
	int cur_sel = (int)SendMessage(hWnd, CB_GETCURSEL, 0, 0);

	switch (cur_sel) {
	case 0: {
		level_up_table = GS_TABLE_DATA;
		egg_table = GS_EGG_TABLE;
		base_stats_address = GS_BASE_STATS;
		trainer_table_address = GS_TRAINER_TABLE;
		trainer_class_address = GS_TRAINER_TYPES;
		break;
	}
	case 1: {
		level_up_table = C_TABLE_DATA;
		egg_table = C_EGG_TABLE;
		base_stats_address = C_BASE_STATS;
		trainer_table_address = C_TRAINER_TABLE;
		trainer_class_address = C_TRAINER_TYPES;
		break;
	}
	case 2: {
		level_up_table = GS_TABLE_DATA;
		egg_table = GS_EGG_TABLE;
		base_stats_address = GS_BASE_STATS;
		trainer_table_address = GS_TRAINER_TABLE;
		trainer_class_address = GS_TRAINER_TYPES;
		break;
	}
	default:
		level_up_table = GS_TABLE_DATA;
		egg_table = GS_EGG_TABLE;
		base_stats_address = GS_BASE_STATS;
		trainer_table_address = GS_TRAINER_TABLE;
		trainer_class_address = GS_TRAINER_TYPES;
		break;
	}

}

void OpenFile(HWND hWnd) {
	OPENFILENAME ofn;

	wchar_t file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = L"GBC Files\0*.gbc\0";
	ofn.nFilterIndex = 1;

	GetOpenFileName(&ofn);

	if (ofn.lpstrFile[0] != '\0') {
		rom = LoadData(ofn.lpstrFile);
	}

}

void SaveFile(HWND hWnd) {
	OPENFILENAME ofn;

	wchar_t file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = L"GBC Files\0*.gbc\0";
	ofn.nFilterIndex = 1;

	GetSaveFileName(&ofn);

	if (ofn.lpstrFile[0] != '\0') {
		SaveData(ofn.lpstrFile, rom);
		MessageBox(NULL, ofn.lpstrFile, L"", MB_OK);
	}
}

void TogglePokemonEnables(bool update) {
	EnableWindow(cb_poke, update);
	EnableWindow(cb_moves, update);
	EnableWindow(cb_levels, update);
	EnableWindow(cb_egg_moves, update);
	EnableWindow(cb_tms, update);
	EnableWindow(cb_item23, update);
	EnableWindow(cb_item2, update);
	EnableWindow(cb_type_1, update);
	EnableWindow(cb_type_2, update);
	EnableWindow(cb_egg_1, update);
	EnableWindow(cb_egg_2, update);
	EnableWindow(cb_gender, update);
	EnableWindow(cb_growth, update);
	EnableWindow(cb_spr_size, update);
	EnableWindow(cb_evo_met, update);

	//EnableWindow(btn_rom, update);
	EnableWindow(btn_select, update);
	EnableWindow(btn_add_moves, update);
	EnableWindow(btn_del_moves, update);
	EnableWindow(btn_add_egg, update);
	EnableWindow(btn_del_egg, update);
	EnableWindow(btn_tog_tm, update);
	EnableWindow(btn_upd_bs, update);
	EnableWindow(btn_sel_evo, update);
	EnableWindow(btn_add_evo, update);
	EnableWindow(btn_del_evo, update);
}

void TogglePokemonTab(bool update) {
	ShowWindow(cb_poke, update);
	ShowWindow(cb_moves, update);
	ShowWindow(cb_levels, update);
	ShowWindow(cb_egg_moves, update);
	ShowWindow(cb_tms, update);
	ShowWindow(cb_item23, update);
	ShowWindow(cb_item2, update);
	ShowWindow(cb_type_1, update);
	ShowWindow(cb_type_2, update);
	ShowWindow(cb_egg_1, update);
	ShowWindow(cb_egg_2, update);
	ShowWindow(cb_gender, update);
	ShowWindow(cb_growth, update);
	ShowWindow(cb_spr_size, update);
	ShowWindow(cb_evo_met, update);
	ShowWindow(cb_evo_con, update);
	ShowWindow(cb_evo_pok, update);
	ShowWindow(cb_evo_stat, update);

	ShowWindow(btn_rom, update);
	ShowWindow(btn_select, update);
	ShowWindow(btn_add_moves, update);
	ShowWindow(btn_del_moves, update);
	ShowWindow(btn_add_egg, update);
	ShowWindow(btn_del_egg, update);
	ShowWindow(btn_tog_tm, update);
	ShowWindow(btn_upd_bs, update);
	ShowWindow(btn_sel_evo, update);
	ShowWindow(btn_add_evo, update);
	ShowWindow(btn_del_evo, update);

	ShowWindow(eb_hp, update);
	ShowWindow(eb_atk, update);
	ShowWindow(eb_def, update);
	ShowWindow(eb_spd, update);
	ShowWindow(eb_satk, update);
	ShowWindow(eb_sdef, update);
	ShowWindow(eb_cap_rate, update);
	ShowWindow(eb_base_exp, update);
	ShowWindow(eb_hatch, update);

	ShowWindow(stc_level_up, update);
	ShowWindow(stc_egg_move, update);
	ShowWindow(stc_tms, update);
	ShowWindow(stc_hp, update);
	ShowWindow(stc_atk, update);
	ShowWindow(stc_def, update);
	ShowWindow(stc_spd, update);
	ShowWindow(stc_satk, update);
	ShowWindow(stc_sdef, update);
	ShowWindow(stc_cr, update);
	ShowWindow(stc_exp, update);
	ShowWindow(stc_growth, update);
	ShowWindow(stc_gender, update);
	ShowWindow(stc_hatch, update);
	ShowWindow(stc_size, update);
	ShowWindow(stc_item23, update);
	ShowWindow(stc_item2, update);
	ShowWindow(stc_egg_1, update);
	ShowWindow(stc_egg_2, update);
	ShowWindow(stc_type_1, update);
	ShowWindow(stc_type_2, update);
	ShowWindow(stc_evo, update);
	//ShowWindow(GetDlgItem(hWnd, ))

	ShowWindow(lb_level_up, update);
	ShowWindow(lb_level_move, update);
	ShowWindow(lb_egg_move , update);
	ShowWindow(lb_tm, update);
	ShowWindow(lb_evo, update);
}

void ToggleTrainerTab(bool update, HWND hWnd) {
	ShowWindow(GetDlgItem(hWnd, TV_TRAINERS), update);

	ShowWindow(GetDlgItem(hWnd, STC_TRAINER_CODE), update);
	ShowWindow(GetDlgItem(hWnd, STC_TRAINER_TYPE), update);

	ShowWindow(GetDlgItem(hWnd, EB_TRAINER_NAME), update);

	ShowWindow(GetDlgItem(hWnd, CB_TRA_POKE1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_POKE2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_POKE3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_POKE4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_POKE5), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_POKE6), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE1_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE2_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE3_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE4_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE5_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_MOVE6_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_ITEM_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_ITEM_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_ITEM_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_ITEM_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_ITEM_5), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_ITEM_6), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_LVL_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_LVL_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_LVL_3), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_LVL_4), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_LVL_5), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRA_LVL_6), update);
	ShowWindow(GetDlgItem(hWnd, CB_TRAINER_CONTROL), update);

	ShowWindow(GetDlgItem(hWnd, BTN_UPDATE_TRAINER), update);
	ShowWindow(GetDlgItem(hWnd, BTN_ADD_TRAINER), update);
}

void SelectPokemon(HWND hWnd) {

	SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_RESETCONTENT, NULL, NULL);
	SendMessage(GetDlgItem(hWnd, LB_MOVES), LB_RESETCONTENT, NULL, NULL);
	SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_RESETCONTENT, NULL, NULL);
	SendMessage(GetDlgItem(hWnd, LB_TMS), LB_RESETCONTENT, NULL, NULL);

	pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);

	if (pokemon >= 0 && pokemon <= 250) {
		DisplayLevelMoves(level_up_table, pokemon + 1, rom, hWnd, LB_LEVEL, LB_MOVES);
		DisplayEggMoves(egg_table, pokemon + 1, rom, hWnd, LB_EGG_MOVES);
		DisplayTM(base_stats_address, pokemon + 1, rom, hWnd, LB_TMS);
		DisplayBaseStats(base_stats_address, pokemon + 1, rom, hWnd, EB_STAT_HP, EB_STAT_ATK, EB_STAT_DEF, EB_STAT_SPD, EB_STAT_SATK, EB_STAT_SDEF);
		DisplayTyping(base_stats_address, pokemon + 1, rom, hWnd, CB_TYPE_1, CB_TYPE_2);
		DisplayHoldItems(base_stats_address, pokemon + 1, rom, hWnd, CB_ITEM_23, CB_ITEM_2);
		DisplayCaptureRate(base_stats_address, pokemon + 1, rom, hWnd, EB_CR);
		DisplayBaseExp(base_stats_address, pokemon + 1, rom, hWnd, EB_BASE_EXP);
		DisplayEggGroup(base_stats_address, pokemon + 1, rom, hWnd, CB_EGG_1, CB_EGG_2);
		DisplayGenderRatio(base_stats_address, pokemon + 1, rom, hWnd, CB_GENDER);
		DisplayHatchSteps(base_stats_address, pokemon + 1, rom, hWnd, EB_HATCH_STEP);
		DisplayGrowthType(base_stats_address, pokemon + 1, rom, hWnd, CB_GROWTH);
		DisplaySpriteSize(base_stats_address, pokemon + 1, rom, hWnd, CB_SPR_SIZE);
		DisplayEvolution(level_up_table, pokemon + 1, rom, hWnd, LB_EVO);
	}


}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE prevInst, LPSTR pStr, int nCmd) {
	WNDCLASSEX wcx = { 0 };

	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.lpfnWndProc = WndProc;
	wcx.hInstance = hInst;
	//wcx.hbrBackground = (HBRUSH)COLOR_BTNFACE + 1;
	wcx.lpszClassName = L"WINDOWEX";

	if (!RegisterClassEx(&wcx)) {
		return -1;
	}

	HWND hWnd = CreateWindowEx(0, L"WINDOWEX", L"Pokedit", WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE, 0, 0, desk_width, desk_height, 0, 0, hInst, 0);

	if (!hWnd) {
		return -1;
	}

	ShowWindow(hWnd, nCmd);
	UpdateWindow(hWnd);
	MSG msg;

	while (GetMessage(&msg, 0, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;

}