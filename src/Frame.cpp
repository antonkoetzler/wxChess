#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_BUTTON(ONE_ONE, Frame::launchOneOne)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "wxChess", wxDefaultPosition, wxSize(300, 200))
{
  menubar = new MenuBar();
  SetMenuBar(menubar);

  startMenu = new StartMenu(this);

  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::launchOneOne(wxCommandEvent& evt)
{
  delete startMenu; startMenu = nullptr;

  wxPanel* panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(310, 50));
  panel1->SetBackgroundColour(wxColour(32, 32, 32));
  wxPanel* panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(310, 50));
  panel2->SetBackgroundColour(wxColour(32, 32, 32));

  gameInfo = new wxBoxSizer(wxHORIZONTAL);
  gameInfo->Add(panel1, 0, wxRIGHT, 5);
  gameInfo->Add(panel2, 0, wxLEFT, 5);

  initBoard();

  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(
    gameInfo,
    0,
    wxALIGN_CENTRE | wxTOP | wxBOTTOM,
    5
  );
  sizer->Add(
    board,
    1,
    wxSHAPED | wxALIGN_CENTRE_HORIZONTAL
  );

  SetSizerAndFit(sizer);
  Centre();
  SetBackgroundColour(wxColour(112, 128, 144));
  Refresh(); // This makes sure there are no visual bugs
}

void Frame::initBoard()
{
  board = new wxGridSizer(8, 8, 0, 0);

  // Placing tiles into board
  for (int i = 0; i < 8; i++) // Column for loop
  {
    for (int o = 0; o < 8; o++) // Row for loop
    {
      tiles[i].push_back(new Tile(this));
      if (i % 2 == 0 && o % 2 == 0)      tiles[i][o]->SetBackgroundColour(wxColour(255, 255, 255));
      else if (i % 2 == 0 && o % 2 != 0) tiles[i][o]->SetBackgroundColour(wxColour(240, 234, 214));
      else if (i % 2 != 0 && o % 2 == 0) tiles[i][o]->SetBackgroundColour(wxColour(240, 234, 214));
      else if (i % 2 != 0 && o % 2 != 0) tiles[i][o]->SetBackgroundColour(wxColour(255, 255, 255));
      board->Add(tiles[i][o], 0, wxSHAPED);
    }
  }

  // Setting the pieces
  wxImage::AddHandler(new wxPNGHandler);
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

