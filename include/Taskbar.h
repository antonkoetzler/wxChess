#pragma once

#include <wx/wx.h>

class Taskbar : public wxPanel
{
 public:
  Taskbar(wxFrame*);

 private:
  wxBoxSizer* sizer;
  wxButton* oneOne;
  wxButton* oneMinute;
  wxButton* fiveFive;
};

