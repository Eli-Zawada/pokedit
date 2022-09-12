#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "dataeditor.h"
#include "pointertools.h"
#include "interpreter.h"

void DisplayLevelMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int lvl, int move);

std::vector<byte> InsertLevelMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte lvl, byte move);

std::vector<byte> DeleteLevelMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte lvl, byte move);

std::vector<byte> InsertEggMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte move);

std::vector<byte> DeleteEggMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte move);

void DisplayEggMoves(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int inst);

void DisplayTM(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int inst);

std::vector<byte> ToggleTMs(unsigned int address, unsigned short pokemon, std::vector<byte> data, byte tm);

void DisplayEvolution(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int evo);

std::vector<byte> InsertEvolution(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int met, int con, int pok, int stat);

std::vector<byte> DeleteEvolution(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int met, int con, int pok, int stat);

void DisplayBaseStats(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int hp, int atk, int def, int spd, int satk, int sdef);
	std::vector<byte> ChangeBaseStats(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd,
	HWND hp, HWND atk, HWND def, HWND spd, HWND satk, HWND sdef);

void DisplayTyping(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int type1, int type2);

std::vector<byte> ChangeTyping(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int type1, int type2);

void DisplayHoldItems(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int item23, int item2);

std::vector<byte> ChangeHoldItems(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int item23, int item2);

void DisplayCaptureRate(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int cr);

void DisplayBaseExp(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int exp);

std::vector<byte> ChangeCaptureRate(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int cr);

std::vector<byte> ChangeBaseExp(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int exp);

void DisplayEggGroup(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int egg1, int egg2);

std::vector<byte> ChangeEggGroup(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int egg1, int egg2);

void DisplayGenderRatio(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int gen);

std::vector<byte> ChangeGenderRatio(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int gen);

void DisplayHatchSteps(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int hatch);

	std::vector<byte> ChangeHatchSteps(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int hatch);

void DisplayGrowthType(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int growth);

	std::vector<byte> ChangeGrowthType(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int growth);

void DisplaySpriteSize(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int growth);

	std::vector<byte> ChangeSpriteSize(unsigned int address, unsigned short pokemon, std::vector<byte> data, HWND hWnd, int size);
