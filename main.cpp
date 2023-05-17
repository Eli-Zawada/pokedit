#include "main.h"

#include "address.h"
#include "combobox.h"
#include "dataeditor.h"
#include "encounters.h"
#include "resource.h"
#include "guicodes.h"
#include "interpreter.h"
#include "pointertools.h"
#include "pokemontools.h"
#include "randomencounters.h"
#include "trainertools.h"
#include "profile.h"

std::vector<BYTE> rom;

HMENU hMenu;
HWND hTabCntrl;
HWND hStat;

int tab_sel = 0;
int desk_width = GetSystemMetrics(SM_CXSCREEN);
int desk_height = GetSystemMetrics(SM_CYSCREEN);

unsigned char pokemon = 0;
unsigned char prev = 0;
unsigned char level = 0;
unsigned char move = 0;
unsigned char egg = 0;
unsigned char tm = 0;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HTREEITEM hti = TreeView_GetSelection(GetDlgItem(hWnd, TV_TRAINERS));
	char item23_sel = SendMessage(GetDlgItem(hWnd, CB_ITEM_23), CB_GETCURSEL, 0, 0);
	char item2_sel = SendMessage(GetDlgItem(hWnd, CB_ITEM_2), CB_GETCURSEL, 0, 0);
	char type1_sel = SendMessage(GetDlgItem(hWnd, CB_TYPE_1), CB_GETCURSEL, 0, 0);
	char type2_sel = SendMessage(GetDlgItem(hWnd, CB_TYPE_2), CB_GETCURSEL, 0, 0);
	bool filled = true;

	switch (msg) {

	case WM_CREATE:
		AddMenus(hWnd);
		AddTabs(hWnd);
		AddPokemonControls(hWnd);
		AddTrainerControls(hWnd);
		AddEncounterControls(hWnd);
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
				TogglePokemonEnables(true, hWnd);
				FillTrainerTree(rom, hWnd);
				FillEncountersTree(rom, GetDlgItem(hWnd, TV_ENCOUNTERS));
			}
			break;
		case SAVE_FILE:
			SaveFile(hWnd);
			break;
		case SAVE_PROFILE:
			SaveProfile(hWnd);
			break;
		case OPEN_PROFILE:
			OpenProfile(hWnd);
			break;
		case BTN_ROM:
			SelectRom(GetDlgItem(hWnd, CB_ROM));
			if (rom.empty() == false) {
				SelectPokemon(hWnd);
				FillTrainerTree(rom, hWnd);
				GetTrainerData(rom, hti, hWnd);
			}
			break;
		case BTN_ADD_MOVE:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			level = SendMessage(GetDlgItem(hWnd, CB_LEVELS), CB_GETCURSEL, NULL, NULL);
			move = SendMessage(GetDlgItem(hWnd, CB_MOVES), CB_GETCURSEL, NULL, NULL);
			if (level != 255 && move != 255) {
				InsertLevelMoves(rom, pokemon + 1, level + 1, move + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Level and Move", L"", MB_OK);
			}
			break;

		case BTN_DEL_MOVE:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			if(SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_GETCURSEL, NULL, NULL) != LB_ERR) {
				DeleteLevelMoves(rom, pokemon + 1, hWnd);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Level and Move", L"", MB_OK);
			}
			break;

		case BTN_CHNG_MOVE:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			if (SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_GETCURSEL, NULL, NULL) != LB_ERR &&
				SendMessage(GetDlgItem(hWnd, CB_LEVELS), CB_GETCURSEL, NULL, NULL) != -1 &&
				SendMessage(GetDlgItem(hWnd, CB_MOVES), CB_GETCURSEL, NULL, NULL) != -1) {
				ChangeLevelMoves(rom, pokemon + 1, hWnd);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Level and Move", L"", MB_OK);
			}
			break;

		case BTN_ADD_EGG:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			move = SendMessage(GetDlgItem(hWnd, CB_EGG_MOVES), CB_GETCURSEL, NULL, NULL);
			if (move != 255) {
				UnsertEggMoves(rom, pokemon + 1, move + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select Move", L"", MB_OK);
			}
			break;

		case BTN_DEL_EGG:
			pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);
			SeleteEggMoves(rom, pokemon + 1, hWnd);
			SelectPokemon(hWnd);
			break;

		case BTN_TOGGLE_TM:
			tm = SendMessage(GetDlgItem(hWnd, CB_TMS), CB_GETCURSEL, NULL, NULL);

			if (tm != 255) {
				ToggleTMs(rom, pokemon + 1, tm + 1);
				SelectPokemon(hWnd);
			}
			else {
				MessageBox(NULL, L"Please Select a TM", L"", MB_OK);
			}
			break;

		case BTN_EVO:
			ChangeEvoCombos(GetDlgItem(hWnd, CB_EVO_MET), GetDlgItem(hWnd, CB_EVO_CON),
				GetDlgItem(hWnd, CB_EVO_POK), GetDlgItem(hWnd, CB_EVO_STAT));
			break;

		case BTN_ADD_EVO:
			if (SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) != -1 &&
				SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0) != -1 &&
				SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) != -1) {

				InsertEvolution(rom, pokemon + 1, hWnd);
			}
			SelectPokemon(hWnd);
			break;

		case BTN_DEL_EVO:
			if (SendMessage(GetDlgItem(hWnd, CB_EVO_MET), CB_GETCURSEL, 0, 0) != -1 &&
				SendMessage(GetDlgItem(hWnd, CB_EVO_CON), CB_GETCURSEL, 0, 0) != -1 &&
				SendMessage(GetDlgItem(hWnd, CB_EVO_POK), CB_GETCURSEL, 0, 0) != -1) {

				DeleteEvolution(rom, pokemon + 1, hWnd);
			}
			SelectPokemon(hWnd);
			break;

		case BTN_UPDATE_STATS:
			ChangeBaseStats(rom, pokemon + 1, hWnd);
			ChangeCaptureRate(rom, pokemon + 1, hWnd);
			ChangeBaseExp(rom, pokemon + 1, hWnd);
			ChangeEggGroup(rom, pokemon + 1, hWnd);
			ChangeGenderRatio(rom, pokemon + 1, hWnd);
			ChangeHatchSteps(rom, pokemon + 1, hWnd);
			ChangeGrowthType(rom, pokemon + 1, hWnd);
			ChangeSpriteSize(rom, pokemon + 1, hWnd);
			if (type1_sel != -1 && type2_sel != -1) {
				ChangeTyping(rom, pokemon + 1, hWnd);
			}
			if (item23_sel != -1 && item2_sel != -1) {
				ChangeHoldItems(rom, pokemon + 1, hWnd);
			}

			SelectPokemon(hWnd);
			break;

		case BTN_SYNCH_POKE:
			SynchTable(rom, GetAddress(ADD_LEVEL_TABLE), 0x00, 2);
			break;

		case BTN_UPDATE_TRAINER:
			ChangeTrainerData(rom, hti, hWnd);
			FillTrainerTree(rom, hWnd);
			GetTrainerData(rom, hti, hWnd);
			break;

		case BTN_ADD_TRAINER:
			AddTrainerData(rom, hti, hWnd);
			FillTrainerTree(rom, hWnd);
			GetTrainerData(rom, hti, hWnd);
			break;

		case BTN_UPDATE_ENCOUNTER:
			hti = TreeView_GetSelection(GetDlgItem(hWnd, TV_ENCOUNTERS));
			for (int i = 0; i < 21; i++) {
				if (SendMessage(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), CB_GETCURSEL, 0, 0) == -1 &&
					SendMessage(GetDlgItem(hWnd, CB_MOR_LVL_1 + i), CB_GETCURSEL, 0, 0) == -1) {
					filled = false;
				}
			}
			if (filled == true) {
				ChangeGrassEncounterData(rom, hti, hWnd);
			}
			filled = true;
			for (int i = 0; i < 3; i++) {
				if (SendMessage(GetDlgItem(hWnd, CB_SURF_POKE_1 + i), CB_GETCURSEL, 0, 0) == -1 &&
					SendMessage(GetDlgItem(hWnd, CB_SURF_LVL_1 + i), CB_GETCURSEL, 0, 0) == -1) {
					filled = false;
				}
			}
			if (filled == true) {
				ChangeSurfEncounterData(rom, hti, hWnd);
			}
			filled = true;
			break;

		case BTN_RAND_ENCOUNTER:
			//RandomizeEncounters(hWnd);
			RandomizeTables(rom);
			break;

		case BTN_ADD_TAG:
			AddTag(hWnd);
			break;
		}

		if (CBN_SELCHANGE == HIWORD(wParam)) {
			if (LOWORD(wParam) == CB_POKEMON) {
				SelectPokemon(hWnd);
				DisplayRandomPokemon(hWnd, SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL) + 1);
			}
			if (LOWORD(wParam) == CB_TRAINER_CONTROL) {
				DisableTrainerControls(hWnd, SendMessage(GetDlgItem(hWnd, CB_TRAINER_CONTROL), CB_GETCURSEL, NULL, NULL));
			}
			if (LOWORD(wParam) == CB_EVO_MET) {
				ChangeEvoCombos(GetDlgItem(hWnd, CB_EVO_MET), GetDlgItem(hWnd, CB_EVO_CON), GetDlgItem(hWnd, CB_EVO_POK), GetDlgItem(hWnd, CB_EVO_STAT));
			}
			if (LOWORD(wParam) == CB_ROM) {
				SelectRom(GetDlgItem(hWnd, CB_ROM));
				if (rom.empty() == false) {
					SelectPokemon(hWnd);
					FillTrainerTree(rom, hWnd);
					GetTrainerData(rom, hti, hWnd);
				}

			}
		}
		
		return 0;

	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == TCN_SELCHANGE) {
			tab_sel = TabCtrl_GetCurSel(hTabCntrl);

			switch (tab_sel) {
			case 0:
				TogglePokemonTab(true, hWnd);
				ToggleTrainerTab(false, hWnd);
				ToggleEncountersTab(false, hWnd);
				ToggleRandomElements(true, hWnd);
				break;
			case 1:
				TogglePokemonTab(false, hWnd);
				ToggleTrainerTab(true, hWnd);
				ToggleEncountersTab(false, hWnd);
				ToggleRandomElements(false, hWnd);
				break;
			case 2:
				TogglePokemonTab(false, hWnd);
				ToggleTrainerTab(false, hWnd);
				ToggleEncountersTab(true, hWnd);
				ToggleRandomElements(true, hWnd);
				break;
			case 3:
				TogglePokemonTab(false, hWnd);
				ToggleTrainerTab(false, hWnd);
				ToggleEncountersTab(false, hWnd);
				ToggleRandomElements(false, hWnd);
				break;
			case 4:
				TogglePokemonTab(false, hWnd);
				ToggleTrainerTab(false, hWnd);
				ToggleEncountersTab(false, hWnd);
				ToggleRandomElements(false, hWnd);
				break;
			}
		}
		if (((LPNMHDR)lParam)->code == TVN_SELCHANGED) {
			switch (((LPNMHDR)lParam)->idFrom) {
			
			case TV_TRAINERS:
				hti = TreeView_GetSelection(GetDlgItem(hWnd, TV_TRAINERS));
				if (TreeView_GetChild(GetDlgItem(hWnd, TV_TRAINERS), hti) == NULL) {
					GetTrainerData(rom, hti, hWnd);
				}
				break;
			case TV_ENCOUNTERS:
				hti = TreeView_GetSelection(GetDlgItem(hWnd, TV_ENCOUNTERS));
				if (TreeView_GetChild(GetDlgItem(hWnd, TV_ENCOUNTERS), hti) == NULL) {
					GetGrassEncounterData(rom, hti, hWnd);
					GetGrassSwarmData(rom, hti, hWnd);
					GetSurfEncounterData(rom, hti, hWnd);
					GetSurfSwarmData(rom, hti, hWnd);
					DisplayRandomMap(hWnd, hti);
				}
				break;
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

HWND CreateCheckBox(HWND hWnd, std::wstring name, int x, int y, int w, int h, int id) {
	return CreateWindowEx(NULL, L"BUTTON", name.c_str(), BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD, x, y, w, h, hWnd, (HMENU) id, NULL, NULL);
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hProfileMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_STRING, OPEN_FILE, L"Open");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, SAVE_FILE, L"Save");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, CLOSE_WINDOW, L"Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

	AppendMenu(hProfileMenu, MF_STRING, OPEN_PROFILE, L"Open");
	AppendMenu(hProfileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hProfileMenu, MF_STRING, SAVE_PROFILE, L"Save");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hProfileMenu, L"Profiles");

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
	CreateWindowW(L"Static", L"Level Up Moves", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, LVL_CONS_X, LVL_CONS_Y, 150, 25, hWnd,
		(HMENU)STC_MOVE_LEVEL, NULL, NULL);
	CreateWindowW(L"Static", L"Egg Moves", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, EGG_CONS_X, EGG_CONS_Y, 150, 25, hWnd,
		(HMENU)STC_MOVE_EGG, NULL, NULL);
	CreateWindowW(L"Static", L"TM Compatability", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TM_CONS_X, TM_CONS_Y, 170, 25, hWnd,
		(HMENU)STC_MOVE_TM, NULL, NULL);

	CreateWindowW(L"Static", L"HP", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y, BS_CONS_W, 25, hWnd,
		(HMENU)STC_STAT_HP, NULL, NULL);
	CreateWindowW(L"Static", L"Attack", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 50, BS_CONS_W, 25, hWnd,
		(HMENU)STC_STAT_ATK, NULL, NULL);
	CreateWindowW(L"Static", L"Defense", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 100, BS_CONS_W, 25, hWnd,
		(HMENU)STC_STAT_DEF, NULL, NULL);
	CreateWindowW(L"Static", L"Speed", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 150, BS_CONS_W, 25, hWnd,
		(HMENU)STC_STAT_SPD, NULL, NULL);
	CreateWindowW(L"Static", L"Special Atk", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 200, BS_CONS_W, 25, hWnd,
		(HMENU)STC_STAT_SATK, NULL, NULL);
	CreateWindowW(L"Static", L"Special Def", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X, BS_CONS_Y + 250, BS_CONS_W, 25, hWnd,
		(HMENU)STC_STAT_SDEF, NULL, NULL);
	CreateWindowW(L"Static", L"Capture Rate", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y, 100, 25, hWnd,
		(HMENU)STC_CATCH_RATE, NULL, NULL);
	CreateWindowW(L"Static", L"Base EXP", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 50, 100, 25, hWnd,
		(HMENU)STC_BASE_EXP, NULL, NULL);
	CreateWindowW(L"Static", L"Growth Rate", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 100, 100, 25, hWnd,
		(HMENU)STC_GROWTH_RATE, NULL, NULL);
	CreateWindowW(L"Static", L"Gender Ratio", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 150, 100, 25, hWnd,
		(HMENU)STC_GENDER_RATIO, NULL, NULL);
	CreateWindowW(L"Static", L"Steps to Hatch", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 200, 100, 25, hWnd,
		(HMENU)STC_HATCH_STEPS, NULL, NULL);
	CreateWindowW(L"Static", L"Sprite Size", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 250, 100, 25, hWnd,
		(HMENU)STC_SPRITE_SIZE, NULL, NULL);
	CreateWindowW(L"Static", L"Hold Item 23%", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y, 150, 25, hWnd,
		(HMENU)STC_ITEM_23, NULL, NULL);
	CreateWindowW(L"Static", L"Hold Item 2%", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 50, 150, 25, hWnd,
		(HMENU)STC_ITEM_2, NULL, NULL);
	CreateWindowW(L"Static", L"Egg Group 1", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 100, 150, 25, hWnd,
		(HMENU)STC_EGG_1, NULL, NULL);
	CreateWindowW(L"Static", L"Egg Group 2", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 150, 150, 25, hWnd,
		(HMENU)STC_EGG_2, NULL, NULL);
	CreateWindowW(L"Static", L"Type 1", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 200, 150, 25, hWnd,
		(HMENU)STC_TYPE_1, NULL, NULL);
	CreateWindowW(L"Static", L"Type 2", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 250, 150, 25, hWnd,
		(HMENU)STC_TYPE_2, NULL, NULL);
	CreateWindowW(L"Static", L"Evolution", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, EVO_CONS_X, EVO_CONS_Y, 150, 25, hWnd,
		(HMENU)STC_EVOLUTION, NULL, NULL);

	AddRomCombo(hWnd, ROM_CONS_X, ROM_CONS_Y, 125, 100, CB_ROM);
	AddPokemonCombo(hWnd, (desk_width / 2) - 75, 25, 170, 150, CB_POKEMON, 1);
	AddMovesCombo(hWnd, LVL_CONS_X, LVL_CONS_Y + 25, 150, 175, CB_MOVES, 1);
	AddLevelsCombo(hWnd, LVL_CONS_X, LVL_CONS_Y + 50, 150, 175, CB_LEVELS, 1);
	AddMovesCombo(hWnd, EGG_CONS_X, EGG_CONS_Y + 25, 150, 175, CB_EGG_MOVES, 1);
	AddTMCombo(hWnd, TM_CONS_X, TM_CONS_Y + 25, 170, 175, CB_TMS);
	AddGrowthCombo(hWnd, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 125, 100, 175, CB_GROWTH);
	AddGenderCombo(hWnd, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 175, 100, 175, CB_GENDER);
	AddSizeCombo(hWnd, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 275, 100, 175, CB_SPR_SIZE);
	AddItemsCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 25, 150, 175, CB_ITEM_23, 0);
	AddItemsCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 75, 150, 175, CB_ITEM_2, 0);
	AddEggGroupCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 125, 150, 175, CB_EGG_1);
	AddEggGroupCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 175, 150, 175, CB_EGG_2);
	AddTypeCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 225, 150, 175, CB_TYPE_1);
	AddTypeCombo(hWnd, BS_CONS_X + BS_CONS_W + 150, BS_CONS_Y + 275, 150, 175, CB_TYPE_2);
	AddEvoMethodCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 25, 150, 175, CB_EVO_MET);
	AddLevelsCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 75, 150, 175, CB_EVO_CON, 1);
	AddPokemonCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 100, 150, 175, CB_EVO_POK, 1);
	AddEvoStatCombo(hWnd, EVO_CONS_X, EVO_CONS_Y + 125, 150, 175, CB_EVO_STAT);
	AddLevelsCombo(hWnd, RAND_CONS_X, RAND_CONS_Y, 50, 200, CB_MIN_LVL, 1);
	AddLevelsCombo(hWnd, RAND_CONS_X, RAND_CONS_Y + 50, 50, 200, CB_MAX_LVL, 1);
	CreateTagsCombo(hWnd, RAND_CONS_X + 200, RAND_CONS_Y, 150, 100, CB_TAGS);

	CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, LVL_CONS_X + 12, LVL_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_ADD_MOVE, NULL, NULL);
	CreateWindow(L"Button", L"Delete", WS_VISIBLE | WS_CHILD, LVL_CONS_X + 88, LVL_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_DEL_MOVE, NULL, NULL);
	CreateWindow(L"Button", L"Change", WS_VISIBLE | WS_CHILD, LVL_CONS_X + 41, LVL_CONS_Y + 410, 60, 25, hWnd, (HMENU)BTN_CHNG_MOVE, NULL, NULL);
	CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, EGG_CONS_X + 12, EGG_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_ADD_EGG, NULL, NULL);
	CreateWindow(L"Button", L"Delete", WS_VISIBLE | WS_CHILD, EGG_CONS_X + 88, EGG_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_DEL_EGG, NULL, NULL);
	CreateWindow(L"Button", L"Toggle", WS_VISIBLE | WS_CHILD, TM_CONS_X + 50, TM_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_TOGGLE_TM, NULL, NULL);
	CreateWindow(L"Button", L"Update", WS_VISIBLE | WS_CHILD, BS_CONS_X + 15, BS_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_UPDATE_STATS, NULL, NULL);
	CreateWindow(L"Button", L"Select Method", WS_VISIBLE | WS_CHILD, EVO_CONS_X, EVO_CONS_Y + 50, 150, 25, hWnd, (HMENU)BTN_EVO, NULL, NULL);
	CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, EVO_CONS_X, EVO_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_ADD_EVO, NULL, NULL);
	CreateWindow(L"Button", L"Delete", WS_VISIBLE | WS_CHILD, EVO_CONS_X + 75, EVO_CONS_Y + 375, 50, 25, hWnd, (HMENU)BTN_DEL_EVO, NULL, NULL);
	CreateWindow(L"Button", L"Synch", WS_VISIBLE | WS_CHILD, EVO_CONS_X + 75, ROM_CONS_Y, 50, 25, hWnd, (HMENU)BTN_SYNCH_POKE, NULL, NULL);
	CreateWindow(L"Button", L"Add", WS_VISIBLE | WS_CHILD, RAND_CONS_X + 800, RAND_CONS_Y + 75, 50, 25, hWnd, (HMENU)BTN_ADD_TAG, NULL, NULL);

	CreateCheckBox(hWnd, L"Morning", RAND_CONS_X + 100, RAND_CONS_Y, 100, 25, CHB_MOR);
	CreateCheckBox(hWnd, L"Day", RAND_CONS_X + 100, RAND_CONS_Y + 25, 100, 25, CHB_DAY);
	CreateCheckBox(hWnd, L"Night", RAND_CONS_X + 100, RAND_CONS_Y + 50, 100, 25, CHB_NGT);
	CreateCheckBox(hWnd, L"Exclusive", RAND_CONS_X + 800, RAND_CONS_Y + 25, 100, 25, CHB_EXCLUSIVE);

	CreateWindow(L"ListBox", L"Tags", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, RAND_CONS_X + 400, RAND_CONS_Y, 150, 100, hWnd, (HMENU)LB_TAGS, NULL, NULL);
	CreateWindow(L"ListBox", L"Tags", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, RAND_CONS_X + 600, RAND_CONS_Y, 150, 100, hWnd, (HMENU)LB_EXCLUSIVES, NULL, NULL);
	CreateWindow(L"ListBox", L"Level", WS_VISIBLE | WS_CHILD | WS_BORDER, LVL_CONS_X, LVL_CONS_Y + 75, 150, 300, hWnd, (HMENU)LB_LEVEL, NULL, NULL);
	CreateWindow(L"ListBox", L"Egg Moves", WS_VISIBLE | WS_CHILD | WS_BORDER, EGG_CONS_X, EGG_CONS_Y + 75, 150, 300, hWnd, (HMENU)LB_EGG_MOVES, NULL, NULL);
	CreateWindow(L"ListBox", L"TMs", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, TM_CONS_X, TM_CONS_Y + 75, 170, 300, hWnd, (HMENU)LB_TMS, NULL, NULL);
	CreateWindow(L"ListBox", L"Evolution", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL, EVO_CONS_X, EVO_CONS_Y + 150, 150, 225, hWnd, (HMENU)LB_EVO, NULL, NULL);

	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 25, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_HP, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 75, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_ATK, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 125, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_DEF, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 175, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_SPD, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 225, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_SATK, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X, BS_CONS_Y + 275, BS_CONS_W, 20, hWnd, (HMENU)EB_STAT_SDEF, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 25, 100, 20, hWnd, (HMENU)EB_CR, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 75, 100, 20, hWnd, (HMENU)EB_BASE_EXP, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, BS_CONS_X + BS_CONS_W + 25, BS_CONS_Y + 225, 100, 20, hWnd, (HMENU)EB_HATCH_STEP, NULL, NULL);
	CreateWindow(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | DT_CENTER, RAND_CONS_X + 800, RAND_CONS_Y, 150, 25, hWnd, (HMENU)EB_TAG_NAMES, NULL, NULL);

	TogglePokemonEnables(false, hWnd);
	EnableWindow(GetDlgItem(hWnd, CB_EVO_CON), false);
	EnableWindow(GetDlgItem(hWnd, CB_EVO_POK), false);
	EnableWindow(GetDlgItem(hWnd, CB_EVO_STAT), false);
}

void AddTrainerControls(HWND hWnd) {
	CreateWindowEx(0, WC_TREEVIEW, L"Tree", WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 20, 50, 150, 500, hWnd, (HMENU)TV_TRAINERS, 0, 0);
	
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X - BS_CONS_W - 50, 50, 50, 25, hWnd,
		(HMENU)STC_TRAINER_CODE, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X - BS_CONS_W - 100, 50, 50, 25, hWnd,
		(HMENU)STC_TRAINER_TYPE, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_1_CONS_X, TRA_CONS_Y + 25, 148 , 20, hWnd,
		(HMENU)STC_POKE_EXP1, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_2_CONS_X, TRA_CONS_Y + 25, 148, 20, hWnd,
		(HMENU)STC_POKE_EXP2, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_3_CONS_X, TRA_CONS_Y + 25, 148, 20, hWnd,
		(HMENU)STC_POKE_EXP3, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_4_CONS_X, TRA_CONS_Y + 25, 148, 20, hWnd,
		(HMENU)STC_POKE_EXP4, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_5_CONS_X, TRA_CONS_Y + 25, 148, 20, hWnd,
		(HMENU)STC_POKE_EXP5, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_6_CONS_X, TRA_CONS_Y + 25, 148, 20, hWnd,
		(HMENU)STC_POKE_EXP6, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, TRA_2_CONS_X, TRA_CONS_Y + 300, 148, 25, hWnd,
		(HMENU)STC_EXP_TOTAL, NULL, NULL);

	AddPokemonCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y, 150, 150, CB_TRA_POKE1, 0);
	AddPokemonCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y, 150, 150, CB_TRA_POKE2, 0);
	AddPokemonCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y, 150, 150, CB_TRA_POKE3, 0);
	AddPokemonCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y, 150, 150, CB_TRA_POKE4, 0);
	AddPokemonCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y, 150, 150, CB_TRA_POKE5, 0);
	AddPokemonCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y, 150, 150, CB_TRA_POKE6, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 100, 150, 150, CB_TRA_MOVE1_1, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 125, 150, 150, CB_TRA_MOVE1_2, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 150, 150, 150, CB_TRA_MOVE1_3, 0);
	AddMovesCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 175, 150, 150, CB_TRA_MOVE1_4, 0);
	AddItemsCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 225, 150, 150, CB_TRA_ITEM_1, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 100, 150, 150, CB_TRA_MOVE2_1, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 125, 150, 150, CB_TRA_MOVE2_2, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 150, 150, 150, CB_TRA_MOVE2_3, 0);
	AddMovesCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 175, 150, 150, CB_TRA_MOVE2_4, 0);
	AddItemsCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 225, 150, 150, CB_TRA_ITEM_2, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 100, 150, 150, CB_TRA_MOVE3_1, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 125, 150, 150, CB_TRA_MOVE3_2, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 150, 150, 150, CB_TRA_MOVE3_3, 0);
	AddMovesCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 175, 150, 150, CB_TRA_MOVE3_4, 0);
	AddItemsCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 225, 150, 150, CB_TRA_ITEM_3, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 100, 150, 150, CB_TRA_MOVE4_1, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 125, 150, 150, CB_TRA_MOVE4_2, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 150, 150, 150, CB_TRA_MOVE4_3, 0);
	AddMovesCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 175, 150, 150, CB_TRA_MOVE4_4, 0);
	AddItemsCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 225, 150, 150, CB_TRA_ITEM_4, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 100, 150, 150, CB_TRA_MOVE5_1, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 125, 150, 150, CB_TRA_MOVE5_2, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 150, 150, 150, CB_TRA_MOVE5_3, 0);
	AddMovesCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 175, 150, 150, CB_TRA_MOVE5_4, 0);
	AddItemsCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 225, 150, 150, CB_TRA_ITEM_5, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 100, 150, 150, CB_TRA_MOVE6_1, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 125, 150, 150, CB_TRA_MOVE6_2, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 150, 150, 150, CB_TRA_MOVE6_3, 0);
	AddMovesCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 175, 150, 150, CB_TRA_MOVE6_4, 0);
	AddItemsCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 225, 150, 150, CB_TRA_ITEM_6, 0);
	AddLevelsCombo(hWnd, TRA_1_CONS_X, TRA_CONS_Y + 50, 150, 150, CB_TRA_LVL_1, 0);
	AddLevelsCombo(hWnd, TRA_2_CONS_X, TRA_CONS_Y + 50, 150, 150, CB_TRA_LVL_2, 0);
	AddLevelsCombo(hWnd, TRA_3_CONS_X, TRA_CONS_Y + 50, 150, 150, CB_TRA_LVL_3, 0);
	AddLevelsCombo(hWnd, TRA_4_CONS_X, TRA_CONS_Y + 50, 150, 150, CB_TRA_LVL_4, 0);
	AddLevelsCombo(hWnd, TRA_5_CONS_X, TRA_CONS_Y + 50, 150, 150, CB_TRA_LVL_5, 0);
	AddLevelsCombo(hWnd, TRA_6_CONS_X, TRA_CONS_Y + 50, 150, 150, CB_TRA_LVL_6, 0);

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

void AddEncounterControls(HWND hWnd) {
	CreateWindowEx(0, WC_TREEVIEW, L"Tree", WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 20, 50, 150, 500, hWnd, (HMENU)TV_ENCOUNTERS, 0, 0);

	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X - BS_CONS_W - 50, 50, 50, 25, hWnd,
		(HMENU)STC_ENCOUNTER_INDEX, NULL, NULL);
	CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, BS_CONS_X - BS_CONS_W - 100, 50, 50, 25, hWnd,
		(HMENU)STC_ENCOUNTER_MAP, NULL, NULL);

	for (int i = 0; i < 3; i++) {
		AddNumberCombo(hWnd, ENC_CONS_X + 150 + (i*230), ENC_CONS_Y - 50, LVL_COMBO_WIDTH, 150, CB_MOR_RATE + i, 256);
	}

	for (int i = 0; i < 3; i++) {
		CreateWindowW(L"Static", L"60%", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, ENC_CONS_X + 750,
			ENC_CONS_Y + (i * 30), 50, 25, hWnd, (HMENU)(STC_ENC_60 + i), NULL, NULL);

		AddLevelsCombo(hWnd, ENC_CONS_X + 820, ENC_CONS_Y + (i * 30), LVL_COMBO_WIDTH, 150, CB_SURF_LVL_1 + i, 1);
		AddPokemonCombo(hWnd, ENC_CONS_X + 900, ENC_CONS_Y + (i * 30), POKE_COMBO_WIDTH, 150, CB_SURF_POKE_1 + i, 1);
	}

	SetDlgItemText(hWnd, STC_ENC_32, L"30%");
	SetDlgItemText(hWnd, STC_ENC_11, L"10%");

	for (int i = 0; i < 7; i++) {
		CreateWindowW(L"Static", L"30%", WS_VISIBLE | WS_CHILD | DT_CENTER | WS_BORDER, ENC_CONS_X, 
			ENC_CONS_Y + (i*30), 50, 25, hWnd, (HMENU)(STC_ENC_30 + i), NULL, NULL);
		
		AddLevelsCombo(hWnd, ENC_CONS_X + 70, ENC_CONS_Y + (i*30), LVL_COMBO_WIDTH, 150, CB_MOR_LVL_1 + i, 1);
		AddPokemonCombo(hWnd, ENC_CONS_X + 150, ENC_CONS_Y + (i*30), POKE_COMBO_WIDTH, 150, CB_MOR_POKE_1 + i, 1);
		
		AddLevelsCombo(hWnd, ENC_CONS_X + 300, ENC_CONS_Y + (i*30), LVL_COMBO_WIDTH, 150, CB_DAY_LVL_1 + i, 1);
		AddPokemonCombo(hWnd, ENC_CONS_X + 380, ENC_CONS_Y + (i*30), POKE_COMBO_WIDTH, 150, CB_DAY_POKE_1 + i, 1);
		
		AddLevelsCombo(hWnd, ENC_CONS_X + 530, ENC_CONS_Y + (i*30), LVL_COMBO_WIDTH, 150, CB_NGT_LVL_1 + i, 1);
		AddPokemonCombo(hWnd, ENC_CONS_X + 610, ENC_CONS_Y + (i*30), POKE_COMBO_WIDTH, 150, CB_NGT_POKE_1 + i, 1);
	}

	CreateWindow(L"Button", L"Update", WS_VISIBLE | WS_CHILD, (desk_width / 2) - 25, 50, 50, 25, hWnd, (HMENU)BTN_UPDATE_ENCOUNTER, NULL, NULL);
	CreateWindow(L"Button", L"Randomize", WS_VISIBLE | WS_CHILD, (desk_width / 2) + 50, 50, 80, 25, hWnd, (HMENU)BTN_RAND_ENCOUNTER, NULL, NULL);

	AddNumberCombo(hWnd, ENC_CONS_X + 880, ENC_CONS_Y - 50, LVL_COMBO_WIDTH, 150, CB_SURF_RATE, 256);

	SetDlgItemText(hWnd, STC_ENC_20, L"20%");
	SetDlgItemText(hWnd, STC_ENC_10, L"10%");
	SetDlgItemText(hWnd, STC_ENC_5, L"5%");
	SetDlgItemText(hWnd, STC_ENC_4, L"4%");
	SetDlgItemText(hWnd, STC_ENC_1, L"1%");

	ToggleEncountersTab(false, hWnd);
}

void SelectRom(HWND hWnd) {
	int cur_sel = (int)SendMessage(hWnd, CB_GETCURSEL, 0, 0);

	switch (cur_sel) {
	case 0: {
		SetAddress(ADD_LEVEL_TABLE, GS_LEVEL_TABLE);
		SetAddress(ADD_EGG_TABLE, GS_EGG_TABLE);
		SetAddress(ADD_BASE_STATS, GS_BASE_STATS);
		SetAddress(ADD_TRAINER_TABLE, GS_TRAINER_TABLE);
		SetAddress(ADD_TRAINER_CLASSES, GS_TRAINER_TYPES);
		SetAddress(ADD_MAP_HEADER_TABLE, GS_MAP_TABLE);
		SetAddress(ADD_MAP_NAME_TABLE, GS_LOCATION_NAME_TABLE);

		SetAddress(ADD_JOHTO_GRASS, GS_JOHTO_GRASS);
		SetAddress(ADD_KANTO_GRASS, GS_KANTO_GRASS);
		SetAddress(ADD_JOHTO_SURF, GS_JOHTO_SURF);
		SetAddress(ADD_KANTO_SURF, GS_KANTO_SURF);
		SetAddress(ADD_SWARM_GRASS, GS_SWARM_GRASS);
		SetAddress(ADD_SWARM_SURF, GS_SWARM_SURF);
		break;
	}
	case 1: {
		SetAddress(ADD_LEVEL_TABLE, C_LEVEL_TABLE);
		SetAddress(ADD_EGG_TABLE, C_EGG_TABLE);
		SetAddress(ADD_BASE_STATS, C_BASE_STATS);
		SetAddress(ADD_TRAINER_TABLE, C_TRAINER_TABLE);
		SetAddress(ADD_TRAINER_CLASSES, C_TRAINER_TYPES);
		SetAddress(ADD_MAP_HEADER_TABLE, C_MAP_TABLE);
		SetAddress(ADD_MAP_NAME_TABLE, C_LOCATION_NAME_TABLE);

		SetAddress(ADD_JOHTO_GRASS, C_JOHTO_GRASS);
		SetAddress(ADD_KANTO_GRASS, C_KANTO_GRASS);
		SetAddress(ADD_JOHTO_SURF, C_JOHTO_SURF);
		SetAddress(ADD_KANTO_SURF, C_KANTO_SURF);
		SetAddress(ADD_SWARM_GRASS, C_SWARM_GRASS);
		SetAddress(ADD_SWARM_SURF, C_SWARM_SURF);
		break;
	}
	case 2: {
		SetAddress(ADD_LEVEL_TABLE, GS_JP_LEVEL_TABLE);
		SetAddress(ADD_EGG_TABLE, GS_JP_EGG_TABLE);
		SetAddress(ADD_BASE_STATS, GS_JP_BASE_STATS);
		SetAddress(ADD_TRAINER_TABLE, GS_JP_TRAINER_TABLE);
		SetAddress(ADD_TRAINER_CLASSES, GS_JP_TRAINER_TYPES);
		SetAddress(ADD_MAP_HEADER_TABLE, GS_JP_MAP_TABLE);
		SetAddress(ADD_MAP_NAME_TABLE, GS_JP_LOCATION_NAME_TABLE);

		SetAddress(ADD_JOHTO_GRASS, GS_JP_JOHTO_GRASS);
		SetAddress(ADD_KANTO_GRASS, GS_JP_KANTO_GRASS);
		SetAddress(ADD_JOHTO_SURF, GS_JP_JOHTO_SURF);
		SetAddress(ADD_KANTO_SURF, GS_JP_KANTO_SURF);
		SetAddress(ADD_SWARM_GRASS, GS_JP_SWARM_GRASS);
		SetAddress(ADD_SWARM_SURF, GS_JP_SWARM_SURF);
	}
		break;
	case 3: {
		SetAddress(ADD_LEVEL_TABLE, C_JP_LEVEL_TABLE);
		SetAddress(ADD_EGG_TABLE, C_JP_EGG_TABLE);
		SetAddress(ADD_BASE_STATS, C_JP_BASE_STATS);
		SetAddress(ADD_TRAINER_TABLE, C_JP_TRAINER_TABLE);
		SetAddress(ADD_TRAINER_CLASSES, C_JP_TRAINER_TYPES);
		SetAddress(ADD_MAP_HEADER_TABLE, C_JP_MAP_TABLE);
		SetAddress(ADD_MAP_NAME_TABLE, C_JP_LOCATION_NAME_TABLE);

		SetAddress(ADD_JOHTO_GRASS, C_JP_JOHTO_GRASS);
		SetAddress(ADD_KANTO_GRASS, C_JP_KANTO_GRASS);
		SetAddress(ADD_JOHTO_SURF, C_JP_JOHTO_SURF);
		SetAddress(ADD_KANTO_SURF, C_JP_KANTO_SURF);
		SetAddress(ADD_SWARM_GRASS, C_JP_SWARM_GRASS);
		SetAddress(ADD_SWARM_SURF, C_JP_SWARM_SURF);
		break;
	}
	default:
		SetAddress(ADD_LEVEL_TABLE, GS_LEVEL_TABLE);
		SetAddress(ADD_EGG_TABLE, GS_EGG_TABLE);
		SetAddress(ADD_BASE_STATS, GS_BASE_STATS);
		SetAddress(ADD_TRAINER_TABLE, GS_TRAINER_TABLE);
		SetAddress(ADD_TRAINER_CLASSES, GS_TRAINER_TYPES);
		SetAddress(ADD_MAP_HEADER_TABLE, GS_MAP_TABLE);
		SetAddress(ADD_MAP_NAME_TABLE, GS_LOCATION_NAME_TABLE);
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
		SaveData(rom, ofn.lpstrFile);
		MessageBox(NULL, ofn.lpstrFile, L"", MB_OK);
	}
}

void OpenProfile(HWND hWnd) {
	OPENFILENAME ofn;

	wchar_t file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = L"Profile Files\0*.pl\0";
	ofn.nFilterIndex = 1;

	GetOpenFileName(&ofn);

	if (ofn.lpstrFile[0] != '\0') {
		LoadProfileData(ofn.lpstrFile);
	}

}

void SaveProfile(HWND hWnd) {
	OPENFILENAME ofn;

	wchar_t file_name[100];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = L"Profile Files\0*.pl\0";
	ofn.nFilterIndex = 1;

	GetSaveFileName(&ofn);

	if (ofn.lpstrFile[0] != '\0') {
		SaveProfileData(ofn.lpstrFile);
		MessageBox(NULL, ofn.lpstrFile, L"", MB_OK);
	}
}

void SaveRandomOptions(HWND hWnd) {
	static unsigned int values[20];

	unsigned int temp;
	int n;

	for (int i = 0; i < 3; i++) {
		temp = SendMessage(GetDlgItem(hWnd, CHB_MOR + i), BM_GETCHECK, NULL, NULL);
		if (values[i] != 0) {
			SendMessage(GetDlgItem(hWnd, CHB_MOR + i), BM_SETCHECK, values[i], NULL);
		}
		else SendMessage(GetDlgItem(hWnd, CHB_MOR + i), BM_SETCHECK, BST_UNCHECKED, NULL);
		values[i] = temp;
	}

	for (int i = 0; i < 2; i++) {
		temp = SendMessage(GetDlgItem(hWnd, CB_MIN_LVL + i), CB_GETCURSEL, NULL, NULL);
		if (values[i + 18] != 0) {
			SendMessage(GetDlgItem(hWnd, CB_MIN_LVL + i), CB_SETCURSEL, values[i + 18], NULL);
		}
		else SendMessage(GetDlgItem(hWnd, CB_MIN_LVL + i), CB_SETCURSEL, -1, NULL);
		values[i + 18] = temp;
	}
}

void TogglePokemonEnables(bool update, HWND hWnd) {
	EnableWindow(GetDlgItem(hWnd, CB_POKEMON), update);
	EnableWindow(GetDlgItem(hWnd, CB_MOVES), update);
	EnableWindow(GetDlgItem(hWnd, CB_LEVELS), update);
	EnableWindow(GetDlgItem(hWnd, CB_EGG_MOVES), update);
	EnableWindow(GetDlgItem(hWnd, CB_TMS), update);
	EnableWindow(GetDlgItem(hWnd, CB_ITEM_23), update);
	EnableWindow(GetDlgItem(hWnd, CB_ITEM_2), update);
	EnableWindow(GetDlgItem(hWnd, CB_TYPE_1), update);
	EnableWindow(GetDlgItem(hWnd, CB_TYPE_2), update);
	EnableWindow(GetDlgItem(hWnd, CB_EGG_1), update);
	EnableWindow(GetDlgItem(hWnd, CB_EGG_2), update);
	EnableWindow(GetDlgItem(hWnd, CB_GENDER), update);
	EnableWindow(GetDlgItem(hWnd, CB_GROWTH), update);
	EnableWindow(GetDlgItem(hWnd, CB_SPR_SIZE), update);
	EnableWindow(GetDlgItem(hWnd, CB_EVO_MET), update);

	EnableWindow(GetDlgItem(hWnd, BTN_ADD_MOVE), update);
	EnableWindow(GetDlgItem(hWnd, BTN_DEL_MOVE), update);
	EnableWindow(GetDlgItem(hWnd, BTN_CHNG_MOVE), update);
	EnableWindow(GetDlgItem(hWnd, BTN_ADD_EGG), update);
	EnableWindow(GetDlgItem(hWnd, BTN_DEL_EGG), update);
	EnableWindow(GetDlgItem(hWnd, BTN_TOGGLE_TM), update);
	EnableWindow(GetDlgItem(hWnd, BTN_UPDATE_STATS), update);
	EnableWindow(GetDlgItem(hWnd, BTN_EVO), update);
	EnableWindow(GetDlgItem(hWnd, BTN_ADD_EVO), update);
	EnableWindow(GetDlgItem(hWnd, BTN_DEL_EVO), update);
}

void ToggleRandomElements(bool update, HWND hWnd) {
	ShowWindow(GetDlgItem(hWnd, CHB_EXCLUSIVE), update);
	ShowWindow(GetDlgItem(hWnd, CHB_MOR), update);
	ShowWindow(GetDlgItem(hWnd, CHB_DAY), update);
	ShowWindow(GetDlgItem(hWnd, CHB_NGT), update);

	ShowWindow(GetDlgItem(hWnd, CB_MIN_LVL), update);
	ShowWindow(GetDlgItem(hWnd, CB_MAX_LVL), update);
	ShowWindow(GetDlgItem(hWnd, CB_TAGS), update);

	ShowWindow(GetDlgItem(hWnd, LB_TAGS), update);
	ShowWindow(GetDlgItem(hWnd, EB_TAG_NAMES), update);

	ShowWindow(GetDlgItem(hWnd, BTN_ADD_TAG), update);

	SaveRandomOptions(hWnd);
}

void TogglePokemonTab(bool update, HWND hWnd) {
	ShowWindow(GetDlgItem(hWnd, CB_POKEMON), update);
	ShowWindow(GetDlgItem(hWnd, CB_MOVES), update);
	ShowWindow(GetDlgItem(hWnd, CB_LEVELS), update);
	ShowWindow(GetDlgItem(hWnd, CB_EGG_MOVES), update);
	ShowWindow(GetDlgItem(hWnd, CB_TMS), update);
	ShowWindow(GetDlgItem(hWnd, CB_ITEM_23), update);
	ShowWindow(GetDlgItem(hWnd, CB_ITEM_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_TYPE_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_TYPE_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_EGG_1), update);
	ShowWindow(GetDlgItem(hWnd, CB_EGG_2), update);
	ShowWindow(GetDlgItem(hWnd, CB_GENDER), update);
	ShowWindow(GetDlgItem(hWnd, CB_GROWTH), update);
	ShowWindow(GetDlgItem(hWnd, CB_SPR_SIZE), update);
	ShowWindow(GetDlgItem(hWnd, CB_EVO_MET), update);
	ShowWindow(GetDlgItem(hWnd, CB_EVO_CON), update);
	ShowWindow(GetDlgItem(hWnd, CB_EVO_POK), update);
	ShowWindow(GetDlgItem(hWnd, CB_EVO_STAT), update);

	ShowWindow(GetDlgItem(hWnd, BTN_ROM), update);
	ShowWindow(GetDlgItem(hWnd, BTN_ADD_MOVE), update);
	ShowWindow(GetDlgItem(hWnd, BTN_DEL_MOVE), update);
	ShowWindow(GetDlgItem(hWnd, BTN_CHNG_MOVE), update);
	ShowWindow(GetDlgItem(hWnd, BTN_ADD_EGG), update);
	ShowWindow(GetDlgItem(hWnd, BTN_DEL_EGG), update);
	ShowWindow(GetDlgItem(hWnd, BTN_TOGGLE_TM), update);
	ShowWindow(GetDlgItem(hWnd, BTN_UPDATE_STATS), update);
	ShowWindow(GetDlgItem(hWnd, BTN_EVO), update);
	ShowWindow(GetDlgItem(hWnd, BTN_ADD_EVO), update);
	ShowWindow(GetDlgItem(hWnd, BTN_DEL_EVO), update);
	ShowWindow(GetDlgItem(hWnd, BTN_SYNCH_POKE), update);

	ShowWindow(GetDlgItem(hWnd, EB_STAT_HP), update);
	ShowWindow(GetDlgItem(hWnd, EB_STAT_ATK), update);
	ShowWindow(GetDlgItem(hWnd, EB_STAT_DEF), update);
	ShowWindow(GetDlgItem(hWnd, EB_STAT_SPD), update);
	ShowWindow(GetDlgItem(hWnd, EB_STAT_SATK), update);
	ShowWindow(GetDlgItem(hWnd, EB_STAT_SDEF), update);
	ShowWindow(GetDlgItem(hWnd, EB_CR), update);
	ShowWindow(GetDlgItem(hWnd, EB_BASE_EXP), update);
	ShowWindow(GetDlgItem(hWnd, EB_HATCH_STEP), update);

	ShowWindow(GetDlgItem(hWnd, STC_MOVE_LEVEL), update);
	ShowWindow(GetDlgItem(hWnd, STC_MOVE_EGG), update);
	ShowWindow(GetDlgItem(hWnd, STC_MOVE_TM), update);
	ShowWindow(GetDlgItem(hWnd, STC_STAT_HP), update);
	ShowWindow(GetDlgItem(hWnd, STC_STAT_ATK), update);
	ShowWindow(GetDlgItem(hWnd, STC_STAT_DEF), update);
	ShowWindow(GetDlgItem(hWnd, STC_STAT_SPD), update);
	ShowWindow(GetDlgItem(hWnd, STC_STAT_SATK), update);
	ShowWindow(GetDlgItem(hWnd, STC_STAT_SDEF), update);
	ShowWindow(GetDlgItem(hWnd, STC_CATCH_RATE), update);
	ShowWindow(GetDlgItem(hWnd, STC_BASE_EXP), update);
	ShowWindow(GetDlgItem(hWnd, STC_GROWTH_RATE), update);
	ShowWindow(GetDlgItem(hWnd, STC_GENDER_RATIO), update);
	ShowWindow(GetDlgItem(hWnd, STC_HATCH_STEPS), update);
	ShowWindow(GetDlgItem(hWnd, STC_SPRITE_SIZE), update);
	ShowWindow(GetDlgItem(hWnd, STC_ITEM_23), update);
	ShowWindow(GetDlgItem(hWnd, STC_ITEM_2), update);
	ShowWindow(GetDlgItem(hWnd, STC_EGG_1), update);
	ShowWindow(GetDlgItem(hWnd, STC_EGG_2), update);
	ShowWindow(GetDlgItem(hWnd, STC_TYPE_1), update);
	ShowWindow(GetDlgItem(hWnd, STC_TYPE_2), update);
	ShowWindow(GetDlgItem(hWnd, STC_EVOLUTION), update);

	ShowWindow(GetDlgItem(hWnd, LB_LEVEL), update);
	ShowWindow(GetDlgItem(hWnd, LB_EGG_MOVES), update);
	ShowWindow(GetDlgItem(hWnd, LB_TMS), update);
	ShowWindow(GetDlgItem(hWnd, LB_EVO), update);
}

void ToggleTrainerTab(bool update, HWND hWnd) {
	ShowWindow(GetDlgItem(hWnd, TV_TRAINERS), update);

	ShowWindow(GetDlgItem(hWnd, STC_TRAINER_CODE), update);
	ShowWindow(GetDlgItem(hWnd, STC_TRAINER_TYPE), update);
	ShowWindow(GetDlgItem(hWnd, STC_POKE_EXP1), update);
	ShowWindow(GetDlgItem(hWnd, STC_POKE_EXP2), update);
	ShowWindow(GetDlgItem(hWnd, STC_POKE_EXP3), update);
	ShowWindow(GetDlgItem(hWnd, STC_POKE_EXP4), update);
	ShowWindow(GetDlgItem(hWnd, STC_POKE_EXP5), update);
	ShowWindow(GetDlgItem(hWnd, STC_POKE_EXP6), update);
	ShowWindow(GetDlgItem(hWnd, STC_EXP_TOTAL), update);

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

void ToggleEncountersTab(bool update, HWND hWnd) {
	ShowWindow(GetDlgItem(hWnd, TV_ENCOUNTERS), update);

	ShowWindow(GetDlgItem(hWnd, CB_MOR_RATE), update);
	ShowWindow(GetDlgItem(hWnd, CB_DAY_RATE), update);
	ShowWindow(GetDlgItem(hWnd, CB_NGT_RATE), update);

	ShowWindow(GetDlgItem(hWnd, CB_SURF_RATE), update);

	for (int i = 0; i < 7; i++) {
		ShowWindow(GetDlgItem(hWnd, CB_MOR_LVL_1 + i), update);
		ShowWindow(GetDlgItem(hWnd, CB_MOR_POKE_1 + i), update);

		ShowWindow(GetDlgItem(hWnd, CB_DAY_LVL_1 + i), update);
		ShowWindow(GetDlgItem(hWnd, CB_DAY_POKE_1 + i), update);

		ShowWindow(GetDlgItem(hWnd, CB_NGT_LVL_1 + i), update);
		ShowWindow(GetDlgItem(hWnd, CB_NGT_POKE_1 + i), update);

		ShowWindow(GetDlgItem(hWnd, STC_ENC_30 + i), update);
	}

	for (int i = 0; i < 3; i++) {
		ShowWindow(GetDlgItem(hWnd, CB_SURF_LVL_1 + i), update);
		ShowWindow(GetDlgItem(hWnd, CB_SURF_POKE_1 + i), update);

		ShowWindow(GetDlgItem(hWnd, STC_ENC_60 + i), update);
	}

	ShowWindow(GetDlgItem(hWnd, STC_ENCOUNTER_MAP), update);
	ShowWindow(GetDlgItem(hWnd, STC_ENCOUNTER_INDEX), update);

	ShowWindow(GetDlgItem(hWnd, BTN_UPDATE_ENCOUNTER), update);
	ShowWindow(GetDlgItem(hWnd, BTN_RAND_ENCOUNTER), update);

	ShowWindow(GetDlgItem(hWnd, LB_EXCLUSIVES), update);
}

void SelectPokemon(HWND hWnd) {

	SendMessage(GetDlgItem(hWnd, LB_LEVEL), LB_RESETCONTENT, NULL, NULL);
	SendMessage(GetDlgItem(hWnd, LB_EGG_MOVES), LB_RESETCONTENT, NULL, NULL);
	SendMessage(GetDlgItem(hWnd, LB_TMS), LB_RESETCONTENT, NULL, NULL);
	SendMessage(GetDlgItem(hWnd, LB_TAGS), LB_RESETCONTENT, NULL, NULL);

	pokemon = SendMessage(GetDlgItem(hWnd, CB_POKEMON), CB_GETCURSEL, NULL, NULL);

	if (pokemon >= 0 && pokemon <= 250) {
		DisplayLevelMoves(rom, pokemon + 1, hWnd);
		DisplayEggMoves(rom, pokemon + 1, hWnd);
		DisplayTM(rom, pokemon + 1, hWnd);
		DisplayBaseStats(rom, pokemon + 1, hWnd);
		DisplayTyping(rom, pokemon + 1, hWnd);
		DisplayHoldItems(rom, pokemon + 1, hWnd);
		DisplayCaptureRate(rom, pokemon + 1, hWnd);
		DisplayBaseExp(rom, pokemon + 1, hWnd);
		DisplayEggGroup(rom, pokemon + 1, hWnd);
		DisplayGenderRatio(rom, pokemon + 1, hWnd);
		DisplayHatchSteps(rom, pokemon + 1, hWnd);
		DisplayGrowthType(rom, pokemon + 1, hWnd);
		DisplaySpriteSize(rom, pokemon + 1, hWnd);
		DisplayEvolution(rom, pokemon + 1, hWnd);
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