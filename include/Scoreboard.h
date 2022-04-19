#pragma once

#include <wx/wx.h>

class Scoreboard : public wxBoxSizer
{
 public:
  Scoreboard(wxFrame*);

  // Initializes playerOne and playerTwo
  void setScores(wxString);
    void initPanel(wxString);
  wxStaticText* getPlayerOneTime();
  wxStaticText* getPlayerTwoTime();

 private:
  wxPanel* playerOne;
    wxStaticText* playerOneTime;
  wxPanel* playerTwo;
    wxStaticText* playerTwoTime;
};

