// Used at program start to display game modes
#pragma once

#include <wx/wx.h>

enum
{
  ONE_ONE,
  ONE_MINUTE,
  FIVE_FIVE
};

class StartMenu : public wxPanel
{
 public:
  StartMenu(wxFrame*);

 private:
  wxBoxSizer* sizer;
  wxButton* oneOne;
  wxButton* oneMinute;
  wxButton* fiveFive;
};

