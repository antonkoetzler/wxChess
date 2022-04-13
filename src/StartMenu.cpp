#include "StartMenu.h"

StartMenu::StartMenu(wxFrame* parent) : wxPanel(parent, wxID_ANY)
{
  oneZero = new wxButton(
    this,
    ONE_ZERO,
    "1 | 0",
    wxDefaultPosition,
    wxDefaultSize,
    wxBORDER_NONE
  );
  oneOne = new wxButton(
    this,
    ONE_ONE,
    "1 | 1",
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
  sizer->Add(oneZero, 1, wxEXPAND);
  sizer->Add(oneOne, 1, wxEXPAND);
  sizer->Add(fiveFive, 1, wxEXPAND);

  SetSizer(sizer);
}

