#pragma once
#include "dataeditor.h"
#include "guicodes.h"

std::vector<random_pokemon> LoadDefaultPokemonProfile();
std::vector<random_pokemon> GetPokemonProfile();
void SetPokemonProfile(std::vector<random_pokemon>& p);

std::vector<random_encounter> LoadDefaultMapProfile();
std::vector<random_encounter> GetMapProfile();
void SetMapProfile(std::vector<random_encounter>& m);

std::vector<std::wstring> GetTagNames();
void SetTagNames(std::vector<std::wstring>& s);
void AddTag(HWND hWnd);
void ChangePokemonTags(HWND hWnd);
int UpdatePokemonTag(HWND hWnd, byte value);