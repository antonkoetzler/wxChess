#include "Taskbar.h"

Taskbar::Taskbar(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 100))
{
  oneOne = new wxButton(
    this,
    wxID_ANY,
    "1 | 1",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );
  oneMinute = new wxButton(
    this,
    wxID_ANY,
    "One Minute",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );
  fiveFive = new wxButton(
    this,
    wxID_ANY,
    "5 | 5",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );

  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(oneOne, 1, wxEXPAND);
  sizer->Add(oneMinute, 1, wxEXPAND);
  sizer->Add(fiveFive, 1, wxEXPAND);

  SetSizer(sizer);
}

