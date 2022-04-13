#include "Scoreboard.h"

Scoreboard::Scoreboard(wxFrame* parent) : wxBoxSizer(wxHORIZONTAL)
{
  playerOne = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(305, 60));
  playerTwo = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(305, 60));
  playerOne->SetBackgroundColour(wxColour(226, 223, 210));
  playerTwo->SetBackgroundColour(wxColour(226, 223, 210));

  Add(playerOne, 0, wxTOP | wxBOTTOM | wxRIGHT, 5);
  Add(playerTwo, 0, wxTOP | wxBOTTOM | wxLEFT, 5);
}

