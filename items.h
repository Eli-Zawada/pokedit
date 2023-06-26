#pragma once
#include "guicodes.h"
#include "dataeditor.h"

int FillMarts(std::vector<byte>& data, HWND hWnd);
int DisplayMart(std::vector<byte>& data, HWND hWnd);
int ChangeMartItem(std::vector<byte>& data, HWND hWnd);
int DisplayTMs(std::vector<byte>& data, HWND hWnd);
int ChangeTMMoves(std::vector<byte>& data, HWND hWnd);
int DisplayItemPrice(std::vector<byte>& data, HWND hWnd);
int DisplayItemEffect(std::vector<byte>& data, HWND hWnd);
int DisplayItemType(std::vector<byte>& data, HWND hWnd);
int DisplayItemLimits(std::vector<byte>& data, HWND hWnd);
int DisplayItemMenu(std::vector<byte>& data, HWND hWnd);
int ChangeItemPrice(std::vector<byte>& data, HWND hWnd);
int ChangeItemEffect(std::vector<byte>& data, HWND hWnd);
int ChangeItemType(std::vector<byte>& data, HWND hWnd);
int ChangeItemLimits(std::vector<byte>& data, HWND hWnd);
int ChangeItemMenu(std::vector<byte>& data, HWND hWnd);
int UpdateItemName(std::vector<byte>& data, HWND hWnd);