#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileMenu = new wxMenuItem(nullptr, MENU, "Goto Menu\tCtrl+N");
  fileQuit = new wxMenuItem(nullptr, wxID_EXIT, "Quit\tCtrl+Q");
  file = new wxMenu();
  file->Append(fileMenu);
  file->Append(fileQuit);
  Append(file, "File");
}

