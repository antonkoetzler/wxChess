#pragma once

#include <wx/wx.h>
#include <vector>
#include "MenuBar.h"
#include "StartMenu.h"
#include "Tile.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Event functions
  void showMenu(wxCommandEvent&);
  void exit(wxCommandEvent&);
  void launchOneOne(wxCommandEvent&);
  void launchOneMinute(wxCommandEvent&);
  void launchFiveFive(wxCommandEvent&);
  void leftDown(wxMouseEvent&);

  // Helper functions
  void launch(); // Creates: Scoreboard, chessboard, etc
  void initBoard();
  void clearCaptureIcons(); // Clears possible moves on clicked Piece*

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  StartMenu* startMenu;
  wxBoxSizer* sizer;
    wxBoxSizer* gameInfo;
      wxPanel* panel1;
      wxPanel* panel2;
    wxGridSizer* board;

  std::vector<std::vector<Tile*>> tiles = {{}, {}, {}, {}, {}, {}, {}, {}};
  wxString turn = "White"; // Controls the turn
};

