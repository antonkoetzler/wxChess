#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Quit\tCtrl+Q");
  file = new wxMenu();
  file->Append(fileExit);

  Append(file, "File");
}

