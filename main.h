#pragma once
#include <Windows.h>
#include <commctrl.h>
#include <string>
#include <vector>

#pragma comment(lib, "comctl32.lib")

HWND CreateCheckBox(HWND hWnd, std::wstring name, int x, int y, int w, int h, int id);
void AddMenus(HWND hWnd);
void AddTabs(HWND hWnd);
void AddPokemonControls(HWND hWnd);
void AddTrainerControls(HWND hWnd);
void AddEncounterControls(HWND hWnd);
void AddMartControls(HWND hWnd);
void OpenFile(HWND hWnd);
void SaveFile(HWND hWnd);
void SaveProfile(HWND hWnd);
void OpenProfile(HWND hWnd);
void SaveRandomOptions(HWND hWnd);
void TogglePokemonEnables(bool update, HWND hWnd);
void ToggleRandomElements(bool update, HWND hWnd);
void TogglePokemonTab(bool update, HWND hWnd);
void ToggleTrainerTab(bool update, HWND hWnd);
void ToggleEncountersTab(bool update, HWND hWnd);
void ToggleMartTab(bool update, HWND hWnd);
void StartCommonControls(DWORD flags);
HWND CreateTab(HWND hParent, HINSTANCE hInst, DWORD dwStyle, int x, int y, int width, int height, int id);
int InsertItem(HWND hWnd, std::wstring txt, int item_index, int image_index);
HTREEITEM InsertTreeItem(HWND hWndTV, LPWSTR name, int nLevel, HTREEITEM hPrev, HTREEITEM hPrevRootItem, HTREEITEM hPrevLev2Item, LPARAM lParam);
void SelectRom(HWND hWnd);
void SelectPokemon(HWND hWnd);
INT_PTR ColorStaticBackground(HWND& hWnd, HDC& hdcStatic, byte pal);
INT_PTR UpdateStaticColor(HWND hWnd, HDC hdcStatic, byte pal);