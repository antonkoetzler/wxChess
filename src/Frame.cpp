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
  for (int i = 1; i < 65; i++)
  {
    tiles.push_back(new Tile(this));
    if (inRange(i, 1, 8) || inRange(i, 17, 24) || inRange(i, 33, 40) || inRange(i, 49, 56))
    {
      if (i % 2 == 0) tiles[i - 1]->SetBackgroundColour(wxColour(48, 48, 48));
      else            tiles[i - 1]->SetBackgroundColour(wxColour(255, 239, 213));
    }
    else
    {
      if (i % 2 == 0) tiles[i - 1]->SetBackgroundColour(wxColour(255, 239, 213));
      else            tiles[i - 1]->SetBackgroundColour(wxColour(48, 48, 48));
    }
    board->Add(tiles[i - 1], 0, wxSHAPED);
  }

  wxImage::AddHandler(new wxPNGHandler);
  // Placing pieces onto the tiles
  tiles[0]->addPiece("Black", "Rook");
  tiles[1]->addPiece("Black", "Knight");
  tiles[2]->addPiece("Black", "Bishop");
  tiles[3]->addPiece("Black", "Queen");
  tiles[4]->addPiece("Black", "King");
  tiles[5]->addPiece("Black", "Bishop");
  tiles[6]->addPiece("Black", "Knight");
  tiles[7]->addPiece("Black", "Rook");
  for (int i = 8; i < 16; i++) tiles[i]->addPiece("Black", "Pawn");
  for (int i = 48; i < 56; i++) tiles[i]->addPiece("White", "Pawn");
  tiles[56]->addPiece("White", "Rook");
  tiles[57]->addPiece("White", "Knight");
  tiles[58]->addPiece("White", "Bishop");
  tiles[59]->addPiece("White", "Queen");
  tiles[60]->addPiece("White", "King");
  tiles[61]->addPiece("White", "Bishop");
  tiles[62]->addPiece("White", "Knight");
  tiles[63]->addPiece("White", "Rook");
}

bool Frame::inRange(int n, int x, int y) { return (x <= n && n <= y); }

