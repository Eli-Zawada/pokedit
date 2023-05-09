#pragma once

#include <string>
#include <vector>
#include <windows.h>

#include "dataeditor.h"

void DisplayLevelMoves(std::vector<byte>& data, byte pokemon, HWND hWnd);

void InsertLevelMoves(std::vector<byte>& data, byte pokemon, byte lvl, byte move);

void DeleteLevelMoves(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeLevelMoves(std::vector<byte>& data, byte pokemon, HWND hWnd);

void InsertEggMoves(std::vector<byte>& data, byte pokemon, byte move);
void UnsertEggMoves(std::vector<byte>& data, byte pokemon, byte move);

int DeleteEggMoves(std::vector<byte>& data, byte pokemon, HWND hWnd);
int SeleteEggMoves(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayEggMoves(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayTM(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ToggleTMs(std::vector<byte>& data, byte pokemon, byte tm);

void DisplayEvolution(std::vector<byte>& data, byte pokemon, HWND hWnd);

void InsertEvolution(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DeleteEvolution(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayBaseStats(std::vector<byte>& data, byte pokemon, HWND hWnd);
	
void ChangeBaseStats(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayTyping(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeTyping(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayHoldItems(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeHoldItems(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayCaptureRate(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayBaseExp(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeCaptureRate(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeBaseExp(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayEggGroup(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeEggGroup(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayGenderRatio(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeGenderRatio(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayHatchSteps(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeHatchSteps(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplayGrowthType(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeGrowthType(std::vector<byte>& data, byte pokemon, HWND hWnd);

void DisplaySpriteSize(std::vector<byte>& data, byte pokemon, HWND hWnd);

void ChangeSpriteSize(std::vector<byte>& data, byte pokemon, HWND hWnd);

byte FindPokemonFamily(std::vector<byte>& data, byte pokemon);

void SynchTable(std::vector<byte>& data, unsigned int address, byte marker, byte loops);