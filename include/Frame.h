#pragma once

#include <wx/wx.h>
#include "MenuBar.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Event functions
  void exit(wxCommandEvent&);

  // Calculation functions
  bool inRange(int, int, int); // Returns true if arg is in range of x and y

 private:
  DECLARE_EVENT_TABLE();
  MenuBar* menubar;
  wxGridSizer* board;
  wxVector<wxPanel*> tiles;
};

