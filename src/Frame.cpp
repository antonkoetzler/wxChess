#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(MENU, Frame::showMenu)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_BUTTON(ONE_ONE, Frame::launchOneOne)
  EVT_BUTTON(ONE_MINUTE, Frame::launchOneMinute)
  EVT_BUTTON(FIVE_FIVE, Frame::launchFiveFive)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "wxChess", wxDefaultPosition, wxSize(300, 200))
{
  wxImage::AddHandler(new wxPNGHandler);

  menubar = new MenuBar();
  SetMenuBar(menubar);

  startMenu = new StartMenu(this);

  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::showMenu(wxCommandEvent& evt)
{
  if (sizer != nullptr)
  {
    // Clears objects and deletes all objects
    sizer->Clear(true);
    delete sizer; sizer = nullptr;
    startMenu = new StartMenu(this);
    Refresh();
  }
}

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::launch()
{
  delete startMenu; startMenu = nullptr;

  panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(310, 50));
  panel1->SetBackgroundColour(wxColour(32, 32, 32));
  panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(310, 50));
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

void Frame::launchOneOne(wxCommandEvent& evt) { launch(); }
void Frame::launchOneMinute(wxCommandEvent& evt) { launch(); }
void Frame::launchFiveFive(wxCommandEvent& evt) { launch(); }

void Frame::leftDown(wxMouseEvent& evt)
{
  Piece* clickedPiece = wxDynamicCast(evt.GetEventObject(), Piece);
  int tileI, tileO; // Coordinates to where clicked Tile is in tiles

  // Finding the tile where the piece was clicked
  bool found = false;
  for (int i = 0; i < 8; i++)
  {
    for (int o = 0; o < 8; o++)
    {
      if (tiles[i][o]->getPiece() == clickedPiece)
      {
        tileI = i; tileO = o;
        found = true;
        break;
      }
    }

    if (found) break;
  }

  // Piece assertion & rules
  wxString clickedPiecePiece = clickedPiece->getPiece();   // Piece name
  wxString clickedPieceColour = clickedPiece->getColour(); // Piece colour
  clearCaptureIcons();
  if (turn == "White" && clickedPieceColour == turn)
  {
    if (clickedPiecePiece == "Pawn")
    {
      // Checking if there is a piece one column up
      if (tiles[tileI - 1][tileO]->getPiece() == nullptr)
      {
        tiles[tileI - 1][tileO]->addMove("Tile");
        // Checking if there is a piece two columns up
        if (tiles[tileI - 2][tileO]->getPiece() == nullptr)
          tiles[tileI - 2][tileO]->addMove("Tile");
      }
      // Checking if there are pieces on the pawn's diagonals
      if (tileO > 0 && tileI < 7) // Left diagonal
        if (tiles[tileI - 1][tileO - 1]->getPiece() != nullptr)
          tiles[tileI - 1][tileO - 1]->addMove(tiles[tileI - 1][tileO - 1]->getPiece()->getPiece(), "Black");
      if (tileO < 7 && tileI < 7) // Right diagonal
        if (tiles[tileI - 1][tileO + 1]->getPiece() != nullptr)
          tiles[tileI - 1][tileO + 1]->addMove(tiles[tileI - 1][tileO + 1]->getPiece()->getPiece(), "Black");
    } else if (clickedPiecePiece == "Knight")
    {
      std::cout << "White Knight" << std::endl;
    } else if (clickedPiecePiece == "Bishop")
    {
      std::cout << "White Bishop" << std::endl;
    } else if (clickedPiecePiece == "Rook")
    {
      std::cout << "White Rook" << std::endl;
    } else if (clickedPiecePiece == "Queen")
    {
      std::cout << "White Queen" << std::endl;
    } else if (clickedPiecePiece == "King")
    {
      std::cout << "White King" << std::endl;
    }
  } else if (turn == "Black" && clickedPieceColour == turn)
  {
    if (clickedPiecePiece == "Pawn")
    {
      std::cout << "Black Pawn" << std::endl;
    } else if (clickedPiecePiece == "Knight")
    {
      std::cout << "Black Knight" << std::endl;
    } else if (clickedPiecePiece == "Bishop")
    {
      std::cout << "Black Bishop" << std::endl;
    } else if (clickedPiecePiece == "Rook")
    {
      std::cout << "Black Rook" << std::endl;
    } else if (clickedPiecePiece == "Queen")
    {
      std::cout << "Black Queen" << std::endl;
    } else if (clickedPiecePiece == "King")
    {
      std::cout << "Black King" << std::endl;
    }
  }
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
  tiles[0][0]->addPiece("Black", "Rook");
  tiles[0][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this); // Binds left click to a function that
                                                                          // handles movement in Frame class
  tiles[0][1]->addPiece("Black", "Knight");
  tiles[0][1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[0][2]->addPiece("Black", "Bishop");
  tiles[0][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[0][3]->addPiece("Black", "Queen");
  tiles[0][3]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[0][4]->addPiece("Black", "King");
  tiles[0][4]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[0][5]->addPiece("Black", "Bishop");
  tiles[0][5]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[0][6]->addPiece("Black", "Knight");
  tiles[0][6]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[0][7]->addPiece("Black", "Rook");
  tiles[0][7]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  for (int i = 0; i < 8; i++)
  {
    tiles[1][i]->addPiece("Black", "Pawn");
    tiles[1][i]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  }
  for (int i = 0; i < 8; i++)
  {
    tiles[6][i]->addPiece("White", "Pawn");
    tiles[6][i]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  }

  tiles[7][0]->addPiece("White", "Rook");
  tiles[7][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][1]->addPiece("White", "Knight");
  tiles[7][1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][2]->addPiece("White", "Bishop");
  tiles[7][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][3]->addPiece("White", "Queen");
  tiles[7][3]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][4]->addPiece("White", "King");
  tiles[7][4]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][5]->addPiece("White", "Bishop");
  tiles[7][5]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][6]->addPiece("White", "Knight");
  tiles[7][6]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[7][7]->addPiece("White", "Rook");
  tiles[7][7]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

  tiles[5][0]->addPiece("Black", "Pawn");
  tiles[5][2]->addPiece("Black", "Pawn");
}

void Frame::clearCaptureIcons()
{
  wxString pieces[7] = {"Tile", "Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};
  for (int i = 0; i < 8; i++)
  {
    for (int o = 0; o < 8; o++)
    {
      if (tiles[i][o]->getPiece() != nullptr)
      {
        if (tiles[i][o]->getPiece()->getIsCaptureIcon())
        {
          for (int p = 0; p < 7; p++)
          {
            if (tiles[i][o]->getPiece()->getPiece() == pieces[p])
            {
              tiles[i][o]->resetTile();
              break;
            }
          }
        }
      }
    }
  }
}

