#pragma once

#include <wx/wx.h>

enum
{
  ONE_ZERO,
  ONE_ONE,
  FIVE_FIVE
};

class StartMenu : public wxPanel
{
 public:
  StartMenu(wxFrame*);

 private:
  wxBoxSizer* sizer;
  wxButton* oneZero;
  wxButton* oneOne;
  wxButton* fiveFive;
};

