#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include <commctrl.h>

#include "dataeditor.h"

void FillTrainerTree(std::vector<byte>& data, HWND hWnd);
void GetTrainerTypes(std::vector<byte>& data, HWND hWndtv);
void GetTrainerData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);
trainer_pokemon GetTrainerPokemon(std::vector<byte>& data, int& address, byte control);
void DisableTrainerControls(HWND hWnd, int control);
void ChangeTrainerData(std::vector<byte>& data, HTREEITEM hti, HWND hWnd);
void AddTrainerData(std::vector<byte>& data, HTREEITEM hti, HWND hWnd);
int GetBaseExp(std::vector<byte>&, byte pokemon);