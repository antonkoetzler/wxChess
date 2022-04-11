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
  void exit(wxCommandEvent&);
  void launchOneOne(wxCommandEvent&);
  void leftDown(wxMouseEvent&);

  // Helper functions
  void initBoard();

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  StartMenu* startMenu;
  wxBoxSizer* sizer;
    wxBoxSizer* gameInfo;
    wxGridSizer* board;

  std::vector<std::vector<Tile*>> tiles = {{}, {}, {}, {}, {}, {}, {}, {}};
  wxString turn = "White"; // Controls the turn
};

