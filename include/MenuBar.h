#pragma once

#include <wx/wx.h>

enum { MENU };

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileMenu;
    wxMenuItem* fileQuit;
};

