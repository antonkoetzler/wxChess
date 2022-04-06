#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "StartMenu.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  // Event functions
  void exit(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  StartMenu* startMenu;
};

