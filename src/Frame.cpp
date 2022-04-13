#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  //EVT_MENU(MENU, Frame::menu)
  EVT_MENU(wxID_EXIT, Frame::quit)
  EVT_BUTTON(ONE_ZERO, Frame::launchOneZero)
  EVT_BUTTON(ONE_ONE, Frame::launchOneOne)
  EVT_BUTTON(FIVE_FIVE, Frame::launchFiveFive)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "wxChess")
{
  wxImage::AddHandler(new wxPNGHandler);

  menuBar = new MenuBar();
  SetMenuBar(menuBar);

  startMenu = new StartMenu(this);

  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::quit(wxCommandEvent& evt) { Close(); }

void Frame::launchOneZero(wxCommandEvent& evt) { initGameUi(); }
void Frame::launchOneOne(wxCommandEvent& evt) { initGameUi(); }
void Frame::launchFiveFive(wxCommandEvent& evt) { initGameUi(); }

void Frame::initGameUi()
{
  delete startMenu; startMenu = nullptr;

  scoreboard = new Scoreboard(this);
  initBoard();

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->AddStretchSpacer();
  sizer->Add(scoreboard, 0, wxALIGN_CENTRE_HORIZONTAL);
  sizer->Add(board, 0, wxALIGN_CENTRE_HORIZONTAL);
  sizer->AddStretchSpacer();

  SetSizerAndFit(sizer);
  SetBackgroundColour(wxColour(112, 128, 144));
  Refresh(); Centre();
}

void Frame::initBoard()
{
  board = new wxGridSizer(8, 8, 0, 0);
  for (int i = 0; i < 8; i++)   // Column for loop
  {
    for (int o = 0; o < 8; o++) // Row for loop
    {
      tiles[i].push_back(new Tile(this));

      if (i % 2 == 0 && o % 2 == 0)      tiles[i][o]->SetBackgroundColour(wxColour(249, 246, 238));
      else if (i % 2 == 0 && o % 2 != 0) tiles[i][o]->SetBackgroundColour(wxColour(226, 223, 210));
      else if (i % 2 != 0 && o % 2 == 0) tiles[i][o]->SetBackgroundColour(wxColour(226, 223, 210));
      else if (i % 2 != 0 && o % 2 != 0) tiles[i][o]->SetBackgroundColour(wxColour(249, 246, 238));

      board->Add(tiles[i][o], 0);
    }
  }

  // Adding pieces
  tiles[0][0]->addPiece("Black", "Rook");
  tiles[0][1]->addPiece("Black", "Knight");
  tiles[0][2]->addPiece("Black", "Bishop");
  tiles[0][3]->addPiece("Black", "Queen");
  tiles[0][4]->addPiece("Black", "King");
  tiles[0][5]->addPiece("Black", "Bishop");
  tiles[0][6]->addPiece("Black", "Knight");
  tiles[0][7]->addPiece("Black", "Rook");
  for (int i = 0; i < 8; i++) tiles[1][i]->addPiece("Black", "Pawn");
  for (int i = 0; i < 8; i++) tiles[6][i]->addPiece("White", "Pawn");
  tiles[7][0]->addPiece("White", "Rook");
  tiles[7][1]->addPiece("White", "Knight");
  tiles[7][2]->addPiece("White", "Bishop");
  tiles[7][3]->addPiece("White", "Queen");
  tiles[7][4]->addPiece("White", "King");
  tiles[7][5]->addPiece("White", "Bishop");
  tiles[7][6]->addPiece("White", "Knight");
  tiles[7][7]->addPiece("White", "Rook");
}

