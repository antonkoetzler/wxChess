#pragma once

#include <wx/wx.h>

class Scoreboard : public wxBoxSizer
{
 public:
  Scoreboard(wxFrame*);

 private:
  wxPanel* playerOne;
  wxPanel* playerTwo;
};

