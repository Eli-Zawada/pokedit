#include <Windows.h>
#include <commctrl.h>
#include <string>
#include <vector>

#include "dataeditor.h"

void FillEncountersTree(std::vector<byte>& data, HWND hWndtv);
bool GrassSwarmCheck(std::vector<byte>& data, byte group, byte id);
bool SurfSwarmCheck(std::vector<byte>& data, byte group, byte id);
game_string GetMapName(std::vector<byte>& data, int name_add, int element);
void GetGrassEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);
void GetGrassSwarmData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);
void GetSurfEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);
void GetSurfSwarmData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);
void ChangeGrassEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);
void ChangeSurfEncounterData(std::vector<byte>& data, HTREEITEM item, HWND hWnd);