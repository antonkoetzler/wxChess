#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileMenu = new wxMenuItem(nullptr, MENU, "Back to Menu");
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Quit\tCtrl+Q");
  file = new wxMenu();
  file->Append(fileMenu);
  file->Append(fileExit);

  Append(file, "File");
}

