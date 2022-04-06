#include "StartMenu.h"

StartMenu::StartMenu(wxFrame* parent) : wxPanel(parent, wxID_ANY)
{
  oneOne = new wxButton(
    this,
    ONE_ONE,
    "1 | 1",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );
  oneMinute = new wxButton(
    this,
    ONE_MINUTE,
    "One Minute",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );
  fiveFive = new wxButton(
    this,
    FIVE_FIVE,
    "5 | 5",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(oneOne, 1, wxEXPAND);
  sizer->Add(oneMinute, 1, wxEXPAND);
  sizer->Add(fiveFive, 1, wxEXPAND);
  SetSizerAndFit(sizer);
}

