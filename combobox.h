#pragma once
#include <Windows.h>
#include <string>

#include "interpreter.h"

HWND AddRomCombo(HWND, int, int, int, int, int);
HWND AddPokemonCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control);
HWND AddMovesCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control);
HWND AddItemsCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control);
HWND AddLevelsCombo(HWND hWnd, int x, int y, int width, int height, int inst, int control);
HWND AddTMCombo(HWND, int, int, int, int, int);
HWND AddTypeCombo(HWND, int, int, int, int, int);
HWND AddEggGroupCombo(HWND, int, int, int, int, int);
HWND AddGenderCombo(HWND, int, int, int, int, int);
HWND AddGrowthCombo(HWND, int, int, int, int, int);
HWND AddSizeCombo(HWND, int, int, int, int, int);
HWND AddEvoMethodCombo(HWND, int, int, int, int, int);
HWND AddEvoStatCombo(HWND, int, int, int, int, int);
void ChangeEvoCombos(HWND, HWND, HWND, HWND);