#pragma once

#include <wx/wx.h>
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

  // Helper functions
  void initBoard();
  bool inRange(int, int, int); // Checks if int is in range of other ints

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  StartMenu* startMenu;
  wxBoxSizer* sizer;
    wxBoxSizer* gameInfo;
    wxGridSizer* board;

  wxVector<Tile*> tiles;
};

