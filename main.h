#pragma once
#include <Windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include "resource.h"

#include "dataeditor.h"
#include "pokemontools.h"
#include "trainertools.h"

#include "guicodes.h"
#include "address.h"
#include "combobox.h"

#pragma comment(lib, "comctl32.lib")

void AddMenus(HWND hWnd);
void AddTabs(HWND hWnd);
void AddPokemonControls(HWND hWnd);
void AddTrainerControls(HWND hWnd);
void OpenFile(HWND hWnd);
void SaveFile(HWND hWnd);
void TogglePokemonEnables(bool update);
void TogglePokemonTab(bool update);
void ToggleTrainerTab(bool update, HWND hWnd);
void StartCommonControls(DWORD flags);
HWND CreateTab(HWND hParent, HINSTANCE hInst, DWORD dwStyle, int x, int y, int width, int height, int id);
int InsertItem(HWND hWnd, std::wstring txt, int item_index, int image_index);
HTREEITEM InsertTreeItem(HWND hWndTV, LPWSTR name, int nLevel, HTREEITEM hPrev, HTREEITEM hPrevRootItem, HTREEITEM hPrevLev2Item, LPARAM lParam);
void SelectRom(HWND hWnd);
void SelectPokemon(HWND hWnd);