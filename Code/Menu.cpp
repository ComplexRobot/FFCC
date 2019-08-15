#include "CommonIncludes.h"
#include "Menu.h"

enum MenuOptions
{
  MENU_FILE_OPEN,
};

HMENU CreateWindowMenu()
{
  HMENU fileMenu = CreateMenu();
  FatalErrorTest(fileMenu == NULL, "CreateMenu: Error code (0x%X)", GetLastError());
  HMENU fileOpenMenu = CreateMenu();
  FatalErrorTest(fileOpenMenu == NULL, "CreateMenu: Error code (0x%X)", GetLastError());
  FatalErrorTest(AppendMenu(fileMenu, MF_POPUP, (UINT_PTR) fileOpenMenu, "File") == FALSE, "AppendMenu: Error code (0x%X)", GetLastError());
  FatalErrorTest(AppendMenu(fileOpenMenu, MF_ENABLED, MENU_FILE_OPEN, "Open") == FALSE, "AppendMenu: Error code (0x%X)", GetLastError());
  return fileMenu;
}

void HandleMenuCommand(size_t menuID)
{
  switch (menuID)
  {
  case MENU_FILE_OPEN:
    AlertMessage("File", OpenDialog().c_str());
    break;
  }
}

std::string OpenDialog()
{
  char buffer[1024];
  buffer[0] = '\0';
  OPENFILENAME openFileName = { };
  openFileName.lStructSize = sizeof(OPENFILENAME);
  openFileName.hwndOwner = mainWindowHandle;
  openFileName.lpstrFilter = "FFCC File (*.chm, *.cha, *.tex, *.brres)\0*.chm;*.cha;*.tex;*.brres\0All Files (*.*)\0*.*\0";
  openFileName.nFilterIndex = 1;
  openFileName.lpstrFile = buffer;
  openFileName.nMaxFile = sizeof(buffer);
  openFileName.Flags = OFN_FILEMUSTEXIST;
  if (GetOpenFileName(&openFileName) == TRUE)
  {
    return openFileName.lpstrFile;
  }
  DWORD error = CommDlgExtendedError();
  if (error)
  {
    AlertMessage("Error", "GetOpenFileName: Error code (0x%X)", error);
  }
  return "";
}