#pragma once
#include <Windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>

#include "dataeditor.h"

std::vector<random_pokemon> LoadPokemonProfile();
std::vector<random_encounter> LoadMapProfile();
void DisplayRandomPokemon(HWND hWnd, byte id);
void DisplayRandomMap(HWND hWnd, HTREEITEM hti);
void RandomizeEncounters(HWND hWnd);
int RandomizeGrassEntry(std::vector<byte>& data, random_encounter enc);
int RandomizeSurfEntry(std::vector<byte>& data, random_encounter enc);
int RandomizeTables(std::vector<byte>& data);
std::vector<std::wstring> GetTagNames();

























