#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "dataeditor.h"
#include "pointertools.h"
#include "interpreter.h"
#include "main.h"

void FillTrainerTree(std::vector<byte> data, int train_add, int type_add, HWND hWndtv);
void GetTrainerTypes(std::vector<byte>& data, int trainer_add, int type_add, HWND hWndtv);
void GetTrainerData(std::vector<byte> data, HTREEITEM item, int address, HWND hWndtv, HWND hWnd);
trainer_pokemon GetTrainerPokemon(std::vector<byte> data, int address, byte control);
void DisableTrainerControls(HWND hWnd, int control);
void ChangeTrainerData(HWND hWnd, std::vector<byte>& data, int address, HTREEITEM hti);
void AddTrainerData(HWND hWnd, std::vector<byte>& data, int address, HTREEITEM hti);
int GetNumberOfClasses(int address, std::vector<byte>& data);