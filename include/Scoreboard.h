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
    wxBoxSizer* playerOneSizer;
      wxStaticText* playerOneTime;
      wxPanel* playerOnePiecesTaken; // Replace with wxGridSizier
  wxPanel* playerTwo;
    wxBoxSizer* playerTwoSizer;
      wxStaticText* playerTwoTime;
      wxPanel* playerTwoPiecesTaken; // Replace with wxGridSizer
};

