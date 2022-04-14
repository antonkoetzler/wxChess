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

void Frame::leftDown(wxMouseEvent& evt)
{
  // If we have clicked a capture piece
  Piece* clickedPieceTemp = wxDynamicCast(evt.GetEventObject(), Piece);

  if (!clickedPieceTemp->getIsCapture())
  {
    clickedPiece = clickedPieceTemp; // Storing the piece if it makes a move
    clearCaptureIcons();
  }

  // Getting the coordinates of clickedPiece within tiles
  int tileI, tileO;
  bool found = false;
  for (int i = 0; i < 8; i++)
  {
    for (int o = 0; o < 8; o++)
    {
      if (clickedPieceTemp == tiles[i][o]->getPiece())
      {
        tileI = i; tileO = o;
        found = true;
        break;
      }
    }
    if (found) break;
  }

  // Piece ruling
  wxString pieceName = clickedPieceTemp->getPiece();
  wxString pieceColour = clickedPieceTemp->getColour();
  if (turn == "White" && pieceColour == "White")
  {
    if (pieceName == "Pawn")
    {
      // Checking if there is a piece one column up
      if (tiles[tileI - 1][tileO]->getPiece() == nullptr)
      {
        tiles[tileI - 1][tileO]->addCapture("Open");
        tiles[tileI - 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

        // Checking if there is a piece two columns up
        if (tiles[tileI - 2][tileO]->getPiece() == nullptr)
        {
          tiles[tileI - 2][tileO]->addCapture("Open");
          tiles[tileI - 2][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // Checking left
      if (tileO > 0)
      {
        // Checking left diagonal for a piece
        if (tiles[tileI - 1][tileO - 1]->getPiece() != nullptr && tiles[tileI - 1][tileO - 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI - 1][tileO - 1]->addCapture("Black", tiles[tileI - 1][tileO - 1]->getPiece()->getPiece());
          tiles[tileI - 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        // En passant left
      }
      // Checking right
      if (tileO < 7)
      {
        // Checking right diagonal for a piece
        if (tiles[tileI - 1][tileO + 1]->getPiece() != nullptr && tiles[tileI - 1][tileO + 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI - 1][tileO + 1]->addCapture("Black", tiles[tileI - 1][tileO + 1]->getPiece()->getPiece());
          tiles[tileI - 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        // En passant right
      }
    }
    else if (pieceName == "Knight")
    {
      std::cout << "White Knight" << std::endl;
    }
    else if (pieceName == "Bishop")
    {
      std::cout << "White Bishop" << std::endl;
    }
    else if (pieceName == "Rook")
    {
      std::cout << "White Rook" << std::endl;
    }
    else if (pieceName == "Queen")
    {
      std::cout << "White Queen" << std::endl;
    }
    else if (pieceName == "King")
    {
      std::cout << "White King" << std::endl;
    }
  }
  else if (turn == "Black" && pieceColour == "Black")
  {
    if (pieceName == "Pawn")
    {
      // Checking if there is a piece one column down
      if (tiles[tileI + 1][tileO]->getPiece() == nullptr)
      {
        tiles[tileI + 1][tileO]->addCapture("Open");
        tiles[tileI + 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

        // Checking if there is a piece two columns down
        if (tiles[tileI + 2][tileO]->getPiece() == nullptr)
        {
          tiles[tileI + 2][tileO]->addCapture("Open");
          tiles[tileI + 2][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // Checking left
      if (tileO > 0)
      {
        // Checking left diagonal for a piece
        if (tiles[tileI + 1][tileO - 1]->getPiece() != nullptr && tiles[tileI + 1][tileO - 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI + 1][tileO - 1]->addCapture("White", tiles[tileI + 1][tileO - 1]->getPiece()->getPiece());
          tiles[tileI + 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        // En passant left
      }
      // Checking right
      if (tileO < 7)
      {
        // Checking right diagonal for a piece
        if (tiles[tileI + 1][tileO + 1]->getPiece() != nullptr && tiles[tileI + 1][tileO + 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI + 1][tileO + 1]->addCapture("White", tiles[tileI + 1][tileO + 1]->getPiece()->getPiece());
          tiles[tileI + 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        // En passant right
      }
    }
    else if (pieceName == "Knight")
    {
      std::cout << "Black Knight" << std::endl;
    }
    else if (pieceName == "Bishop")
    {
      std::cout << "Black Bishop" << std::endl;
    }
    else if (pieceName == "Rook")
    {
      std::cout << "Black Rook" << std::endl;
    }
    else if (pieceName == "Queen")
    {
      std::cout << "Black Queen" << std::endl;
    }
    else if (pieceName == "King")
    {
      std::cout << "Black King" << std::endl;
    }
  }
  else if (clickedPieceTemp->getIsCapture())
  {
    // Moving archived clickedPiece to clicked object
    tiles[tileI][tileO]->addPiece(clickedPiece->getColour(), clickedPiece->getPiece());
    tiles[tileI][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

    // Getting where the piece 'was' and removing it
    int moveI, moveO;
    for (int i = 0; i < 8; i++)
    {
      for (int o = 0; o < 8; o++)
      {
        if (clickedPiece == tiles[i][o]->getPiece())
        {
          moveI = i; moveO = o;
          tiles[i][o]->removePiece();
          clearCaptureIcons();

          if (turn == "White") turn = "Black";
          else                 turn = "White";

          break;
        }
      }
    }
  }
}

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
  tiles[0][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
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

  // ***TEST PIECES***
  tiles[5][0]->addPiece("Black", "Queen");
  tiles[5][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[4][0]->addPiece("Black", "Pawn");
  tiles[4][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[5][2]->addPiece("Black", "Pawn");
  tiles[5][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[2][0]->addPiece("White", "Bishop");
  tiles[2][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[3][2]->addPiece("White", "Pawn");
  tiles[3][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
}

void Frame::clearCaptureIcons()
{
  for (int i = 0; i < 8; i++)
    for (int o = 0; o < 8; o++)
      if (tiles[i][o]->getPiece() != nullptr && tiles[i][o]->getPiece()->getIsCapture())
        tiles[i][o]->resetTile();
}

