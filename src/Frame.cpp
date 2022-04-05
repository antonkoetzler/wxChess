#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "wxChess", wxDefaultPosition, wxSize(1200, 1000))
{
  menubar = new MenuBar();
  SetMenuBar(menubar);

  // Creating the chess board
  board = new wxGridSizer(8, 8, 0, 0);
  // Filling tiles vector and chess board
  for (int i = 1; i < 65; i++)
  {
    tiles.push_back(new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(80, 80)));

    if (inRange(1, 8, i) || inRange(17, 24, i) || inRange(33, 40, i) || inRange(49, 56, i))
    {
      if (i % 2 == 0) tiles[i - 1]->SetBackgroundColour(wxColour(255, 239, 213));
      else            tiles[i - 1]->SetBackgroundColour(wxColour(48, 48, 48));
    }
    else
    {
      if (i % 2 == 0) tiles[i - 1]->SetBackgroundColour(wxColour(48, 48, 48));
      else            tiles[i - 1]->SetBackgroundColour(wxColour(255, 239, 213));
    }

    board->Add(tiles[i - 1], 0);
  }
  SetSizerAndFit(board);

  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

bool Frame::inRange(int x, int y, int arg) { return ((arg - y) * (arg - x) <= 0); }

