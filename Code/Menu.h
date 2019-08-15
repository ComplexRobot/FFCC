#pragma once

extern HWND mainWindowHandle;

HMENU CreateWindowMenu();
void HandleMenuCommand(size_t menuId);
std::string OpenDialog();