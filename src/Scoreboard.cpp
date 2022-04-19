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

void Scoreboard::setScores(wxString mode)
{
  if (mode == "1 | 0") initPanel("1:00");
  else if (mode == "1 | 1") initPanel("1:00");
  else initPanel("5:00");
}

void Scoreboard::initPanel(wxString time)
{
  playerOneTime = new wxStaticText(
    playerOne,
    wxID_ANY,
    time,
    wxDefaultPosition,
    wxSize(100, 15),
    wxALIGN_CENTRE_HORIZONTAL
  );
  playerOneTime->SetFont(wxFont(
    14,
    wxFONTFAMILY_DEFAULT,
    wxFONTSTYLE_NORMAL,
    wxFONTWEIGHT_NORMAL
  ));
  playerOneTime->SetForegroundColour(wxColour(0, 0, 0));

  playerOnePiecesTaken = new wxPanel(playerOne, wxID_ANY, wxDefaultPosition, wxSize(205, 60));
  playerOnePiecesTaken->SetBackgroundColour(wxColour(255, 255, 255));

  playerOneSizer = new wxBoxSizer(wxHORIZONTAL);
  playerOneSizer->Add(playerOneTime, 0, wxALIGN_CENTRE);
  playerOneSizer->Add(playerOnePiecesTaken, 0);
  
  playerOne->SetSizer(playerOneSizer);



  playerTwoTime = new wxStaticText(
    playerTwo,
    wxID_ANY,
    time,
    wxDefaultPosition,
    wxSize(100, 15),
    wxALIGN_CENTRE_HORIZONTAL
  );
  playerTwoTime->SetFont(wxFont(
    14,
    wxFONTFAMILY_DEFAULT,
    wxFONTSTYLE_NORMAL,
    wxFONTWEIGHT_NORMAL
  ));
  playerTwoTime->SetForegroundColour(wxColour(0, 0, 0));

  playerTwoPiecesTaken = new wxPanel(playerTwo, wxID_ANY, wxDefaultPosition, wxSize(205, 60));
  playerTwoPiecesTaken->SetBackgroundColour(wxColour(255, 255, 255));

  playerTwoSizer = new wxBoxSizer(wxHORIZONTAL);
  playerTwoSizer->Add(playerTwoTime, 0, wxALIGN_CENTRE);
  playerTwoSizer->Add(playerTwoPiecesTaken, 0);

  playerTwo->SetSizer(playerTwoSizer);
}

wxStaticText* Scoreboard::getPlayerOneTime() { return playerOneTime; }
wxStaticText* Scoreboard::getPlayerTwoTime() { return playerTwoTime; }

