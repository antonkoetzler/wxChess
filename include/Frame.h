#pragma once

#include <wx/wx.h>
#include <vector> // wxVector didn't want to corporate
#include "MenuBar.h"
#include "StartMenu.h"
#include "Tile.h"
#include "Scoreboard.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Event functions
  void quit(wxCommandEvent&);
  void launchOneZero(wxCommandEvent&);
  void launchOneOne(wxCommandEvent&);
  void launchFiveFive(wxCommandEvent&);

  // Helper functions
  void initBoard();
  void initGameUi(); // Creates Scoreboard* and chess board
                     // Used with Frame::launch*

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menuBar;
  StartMenu* startMenu;
  wxBoxSizer* sizer;
    Scoreboard* scoreboard;
    wxGridSizer* board;

  std::vector<std::vector<Tile*>> tiles = {{}, {}, {}, {}, {}, {}, {}, {}};
};

