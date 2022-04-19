#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
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

void Frame::launchOneZero(wxCommandEvent& evt)
{
  initGameUi();
  scoreboard->setScores("1 | 0");
  mode = "1 | 0";
}
void Frame::launchOneOne(wxCommandEvent& evt)
{
  initGameUi();
  scoreboard->setScores("1 | 1");
  mode = "1 | 1";
}
void Frame::launchFiveFive(wxCommandEvent& evt)
{
  initGameUi();
  scoreboard->setScores("5 | 5");
  mode = "5 | 5";
}

void Frame::leftDown(wxMouseEvent& evt)
{
  // Starting the timing for whoever's turn
  if (updateTimer != nullptr) { delete updateTimer; updateTimer = nullptr; }
  if (turn == "White") updateTimer = new UpdateTimer(scoreboard->getPlayerOneTime());
  else                 updateTimer = new UpdateTimer(scoreboard->getPlayerTwoTime());

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
  if (turn == "White" && pieceColour == "White" && !clickedPieceTemp->getIsCapture())
  {
    if (pieceName == "Pawn")
    {
      // Checking if there is a piece one column up
      if (tiles[tileI - 1][tileO]->getPiece() == nullptr)
      {
        tiles[tileI - 1][tileO]->addCapture("Open");
        tiles[tileI - 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

        // Checking if there is a piece two columns up (if the pawn is on it's starting column)
        if (tiles[tileI - 2][tileO]->getPiece() == nullptr && tileI == 6)
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
        if (tiles[tileI][tileO - 1]->getPiece() != nullptr && tiles[tileI][tileO - 1]->getPiece()->getEnPassant())
        {
          tiles[tileI - 1][tileO - 1]->addCapture("Open", "Passant");
          tiles[tileI - 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
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
        if (tiles[tileI][tileO + 1]->getPiece() != nullptr && tiles[tileI][tileO + 1]->getPiece()->getEnPassant())
        {
          tiles[tileI - 1][tileO + 1]->addCapture("Open", "Passant");
          tiles[tileI - 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
    }
    else if (pieceName == "Knight")
    {
      // Up 2
      if (tileI >= 2)
      {
        // Left 1
        if (tileO > 0)
        {
          if (tiles[tileI - 2][tileO - 1]->getPiece() == nullptr)
          {
            tiles[tileI - 2][tileO - 1]->addCapture("Open");
            tiles[tileI - 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 2][tileO - 1]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - 2][tileO - 1]->addCapture("Black", tiles[tileI - 2][tileO - 1]->getPiece()->getPiece());
            tiles[tileI - 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Right 1
        if (tileO < 7)
        {
          if (tiles[tileI - 2][tileO + 1]->getPiece() == nullptr)
          {
            tiles[tileI - 2][tileO + 1]->addCapture("Open");
            tiles[tileI - 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 2][tileO + 1]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - 2][tileO + 1]->addCapture("Black", tiles[tileI - 2][tileO + 1]->getPiece()->getPiece());
            tiles[tileI - 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
      // Down 2
      if (tileI <= 5)
      {
        // Left 1
        if (tileO > 0)
        {
          if (tiles[tileI + 2][tileO - 1]->getPiece() == nullptr)
          {
            tiles[tileI + 2][tileO - 1]->addCapture("Open");
            tiles[tileI + 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 2][tileO - 1]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + 2][tileO - 1]->addCapture("Black", tiles[tileI + 2][tileO - 1]->getPiece()->getPiece());
            tiles[tileI + 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Right 1
        if (tileO < 7)
        {
          if (tiles[tileI + 2][tileO + 1]->getPiece() == nullptr)
          {
            tiles[tileI + 2][tileO + 1]->addCapture("Open");
            tiles[tileI + 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 2][tileO + 1]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + 2][tileO + 1]->addCapture("Black", tiles[tileI + 2][tileO + 1]->getPiece()->getPiece());
            tiles[tileI + 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
      // Left 2
      if (tileO >= 2)
      {
        // Up 1
        if (tileI > 0)
        {
          if (tiles[tileI - 1][tileO - 2]->getPiece() == nullptr)
          {
            tiles[tileI - 1][tileO - 2]->addCapture("Open");
            tiles[tileI - 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 1][tileO - 2]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - 1][tileO - 2]->addCapture("Black", tiles[tileI - 1][tileO - 2]->getPiece()->getPiece());
            tiles[tileI - 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Down 1
        if (tileI < 7)
        {
          if (tiles[tileI + 1][tileO - 2]->getPiece() == nullptr)
          {
            tiles[tileI + 1][tileO - 2]->addCapture("Open");
            tiles[tileI + 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 1][tileO - 2]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + 1][tileO - 2]->addCapture("Black", tiles[tileI + 1][tileO - 2]->getPiece()->getPiece());
            tiles[tileI + 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
      // Right 2
      if (tileO <= 5)
      {
        // Up 1
        if (tileI > 0)
        {
          if (tiles[tileI - 1][tileO + 2]->getPiece() == nullptr)
          {
            tiles[tileI - 1][tileO + 2]->addCapture("Open");
            tiles[tileI - 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 1][tileO + 2]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - 1][tileO + 2]->addCapture("Black", tiles[tileI - 1][tileO - 2]->getPiece()->getPiece());
            tiles[tileI - 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Down 1
        if (tileI < 7)
        {
          if (tiles[tileI + 1][tileO + 2]->getPiece() == nullptr)
          {
            tiles[tileI + 1][tileO + 2]->addCapture("Open");
            tiles[tileI + 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 1][tileO + 2]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + 1][tileO + 2]->addCapture("Black", tiles[tileI + 1][tileO + 2]->getPiece()->getPiece());
            tiles[tileI + 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
    }
    else if (pieceName == "Bishop")
    {
      // Increments by one for every while iteration
      int counter = 1;
      // Left up diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO - counter]->addCapture("Open");
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO - counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - counter][tileO - counter]->addCapture("Black", tiles[tileI - counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left down diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO - counter) >= 0)
        {
          if (tiles[tileI + counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO - counter]->addCapture("Open");
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO - counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + counter][tileO - counter]->addCapture("Black", tiles[tileI + counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right up diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO + counter) <= 7)
        {
          if (tiles[tileI - counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO + counter]->addCapture("Open");
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO + counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - counter][tileO + counter]->addCapture("Black", tiles[tileI - counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right down diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO + counter]->addCapture("Open");
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO + counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + counter][tileO + counter]->addCapture("Black", tiles[tileI + counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      }
    }
    else if (pieceName == "Rook")
    {
      // Increments by one for every while iteration
      int counter = 1;
      // Up
      while (true)
      {
        if ((tileI - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO]->addCapture("Open");
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - counter][tileO]->addCapture("Black", tiles[tileI - counter][tileO]->getPiece()->getPiece());
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Down
      while (true)
      {
        if ((tileI + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO]->addCapture("Open");
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + counter][tileO]->addCapture("Black", tiles[tileI + counter][tileO]->getPiece()->getPiece());
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left
      while (true)
      {
        if ((tileO - counter) >= 0)
        {
          if (tiles[tileI][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO - counter]->addCapture("Open");
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO - counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI][tileO - counter]->addCapture("Black", tiles[tileI][tileO - counter]->getPiece()->getPiece());
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1; 
      // Right
      while (true)
      {
        if ((tileO + counter) <= 7)
        {
          if (tiles[tileI][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO + counter]->addCapture("Open");
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO + counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI][tileO + counter]->addCapture("Black", tiles[tileI][tileO + counter]->getPiece()->getPiece());
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      }
    }
    else if (pieceName == "Queen")
    {
      // Increments by one for every while iteration
      int counter = 1;
      // Up
      while (true)
      {
        if ((tileI - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO]->addCapture("Open");
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - counter][tileO]->addCapture("Black", tiles[tileI - counter][tileO]->getPiece()->getPiece());
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Down
      while (true)
      {
        if ((tileI + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO]->addCapture("Open");
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + counter][tileO]->addCapture("Black", tiles[tileI + counter][tileO]->getPiece()->getPiece());
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left
      while (true)
      {
        if ((tileO - counter) >= 0)
        {
          if (tiles[tileI][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO - counter]->addCapture("Open");
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO - counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI][tileO - counter]->addCapture("Black", tiles[tileI][tileO - counter]->getPiece()->getPiece());
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right
      while (true)
      {
        if ((tileO + counter) <= 7)
        {
          if (tiles[tileI][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO + counter]->addCapture("Open");
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO + counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI][tileO + counter]->addCapture("Black", tiles[tileI][tileO + counter]->getPiece()->getPiece());
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left up diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO - counter]->addCapture("Open");
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO - counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - counter][tileO - counter]->addCapture("Black", tiles[tileI - counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left down diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO - counter) >= 0)
        {
          if (tiles[tileI + counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO - counter]->addCapture("Open");
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO - counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + counter][tileO - counter]->addCapture("Black", tiles[tileI + counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right up diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO + counter) <= 7)
        {
          if (tiles[tileI - counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO + counter]->addCapture("Open");
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO + counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI - counter][tileO + counter]->addCapture("Black", tiles[tileI - counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right down diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO + counter]->addCapture("Open");
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO + counter]->getPiece()->getColour() == "Black")
          {
            tiles[tileI + counter][tileO + counter]->addCapture("Black", tiles[tileI + counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      }
    }
    else if (pieceName == "King")
    {
      // 1 square up
      if (tileI > 0)
      {
        if (tiles[tileI - 1][tileO]->getPiece() == nullptr)
        {
          tiles[tileI - 1][tileO]->addCapture("Open");
          tiles[tileI - 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI - 1][tileO]->getPiece()->getColour() == "Black")
        {
          tiles[tileI - 1][tileO]->addCapture("Black", tiles[tileI - 1][tileO]->getPiece()->getPiece());
          tiles[tileI - 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 square down
      if (tileI < 7)
      {
        if (tiles[tileI + 1][tileO]->getPiece() == nullptr)
        {
          tiles[tileI + 1][tileO]->addCapture("Open");
          tiles[tileI + 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI + 1][tileO]->getPiece()->getColour() == "Black")
        {
          tiles[tileI + 1][tileO]->addCapture("Black", tiles[tileI + 1][tileO]->getPiece()->getPiece());
          tiles[tileI + 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 square left
      if (tileO > 0)
      {
        if (tiles[tileI][tileO - 1]->getPiece() == nullptr)
        {
          tiles[tileI][tileO - 1]->addCapture("Open");
          tiles[tileI][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI][tileO - 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI][tileO - 1]->addCapture("Black", tiles[tileI][tileO - 1]->getPiece()->getPiece());
          tiles[tileI][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 square right
      if (tileO < 7)
      {
        if (tiles[tileI][tileO + 1]->getPiece() == nullptr)
        {
          tiles[tileI][tileO + 1]->addCapture("Open");
          tiles[tileI][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI][tileO + 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI][tileO + 1]->addCapture("Black", tiles[tileI][tileO + 1]->getPiece()->getPiece());
          tiles[tileI][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 up left diagonal
      if (tileI > 0 && tileO > 0)
      {
        if (tiles[tileI - 1][tileO - 1]->getPiece() == nullptr)
        {
          tiles[tileI - 1][tileO - 1]->addCapture("Open");
          tiles[tileI - 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI - 1][tileO - 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI - 1][tileO - 1]->addCapture("Black", tiles[tileI - 1][tileO - 1]->getPiece()->getPiece());
          tiles[tileI - 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 down left diagonal
      if (tileI < 7 && tileO > 0)
      {
        if (tiles[tileI + 1][tileO - 1]->getPiece() == nullptr)
        {
          tiles[tileI + 1][tileO - 1]->addCapture("Open");
          tiles[tileI + 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI + 1][tileO - 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI + 1][tileO - 1]->addCapture("Black", tiles[tileI + 1][tileO - 1]->getPiece()->getPiece());
          tiles[tileI + 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 up right diagonal
      if (tileI > 0 && tileO < 7)
      {
        if (tiles[tileI - 1][tileO + 1]->getPiece() == nullptr)
        {
          tiles[tileI - 1][tileO + 1]->addCapture("Open");
          tiles[tileI - 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI - 1][tileO + 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI - 1][tileO + 1]->addCapture("Black", tiles[tileI - 1][tileO + 1]->getPiece()->getPiece());
          tiles[tileI - 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 down right diagonal
      if (tileI < 7 && tileO < 7)
      {
        if (tiles[tileI + 1][tileO + 1]->getPiece() == nullptr)
        {
          tiles[tileI + 1][tileO + 1]->addCapture("Open");
          tiles[tileI + 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI + 1][tileO + 1]->getPiece()->getColour() == "Black")
        {
          tiles[tileI + 1][tileO + 1]->addCapture("Black", tiles[tileI + 1][tileO + 1]->getPiece()->getPiece());
          tiles[tileI + 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // Left castle
      if (tileI == 7 && tileO == 4 && tiles[7][0]->getPiece() != nullptr && tiles[7][0]->getPiece()->getPiece() == "Rook" && tiles[7][0]->getPiece()->getColour() == "White")
      {
        // Checking for clear row
        bool castleOkay = true;
        for (int i = 1; i < 4; i++)
        {
          if (tiles[7][i]->getPiece() != nullptr && tiles[7][i]->getPiece()->getPiece() != wxEmptyString)
          {
            castleOkay = false;
            break;
          }
        }

        if (castleOkay)
        {
          tiles[7][0]->addCapture("White", "Rook");
          tiles[7][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // Right castle
      if (tileI == 7 && tileO == 4 && tiles[7][7]->getPiece() != nullptr && tiles[7][7]->getPiece()->getPiece() == "Rook" && tiles[7][7]->getPiece()->getColour() == "White")
      {
        bool castleOkay = true;
        for (int i = 5; i < 7; i++)
        {
          if (tiles[7][i]->getPiece() != nullptr && tiles[7][i]->getPiece()->getPiece() != wxEmptyString)
          {
            castleOkay = false;
            break;
          }
        }

        if (castleOkay)
        {
          tiles[7][7]->addCapture("White", "Rook");
          tiles[7][7]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
    }
  }
  else if (turn == "Black" && pieceColour == "Black" && !clickedPieceTemp->getIsCapture())
  {
    if (pieceName == "Pawn")
    {
      // Checking if there is a piece one column down
      if (tiles[tileI + 1][tileO]->getPiece() == nullptr)
      {
        tiles[tileI + 1][tileO]->addCapture("Open");
        tiles[tileI + 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);

        // Checking if there is a piece two columns down (if the pawn is on it's starting column)
        if (tiles[tileI + 2][tileO]->getPiece() == nullptr && tileI == 1)
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
        if (tiles[tileI][tileO - 1]->getPiece() != nullptr && tiles[tileI][tileO - 1]->getPiece()->getEnPassant())
        {
          tiles[tileI + 1][tileO - 1]->addCapture("Open", "Passant");
          tiles[tileI + 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
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
        if (tiles[tileI][tileO + 1]->getPiece() != nullptr && tiles[tileI][tileO + 1]->getPiece()->getEnPassant())
        {
          tiles[tileI + 1][tileO + 1]->addCapture("Open", "Passant");
          tiles[tileI + 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
    }
    else if (pieceName == "Knight")
    {
      // Up 2
      if (tileI <= 5)
      {
        // Left 1
        if (tileO > 0)
        {
          if (tiles[tileI + 2][tileO - 1]->getPiece() == nullptr)
          {
            tiles[tileI + 2][tileO - 1]->addCapture("Open");
            tiles[tileI + 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 2][tileO - 1]->getPiece()->getColour() == "White")
          {
            tiles[tileI + 2][tileO - 1]->addCapture("White", tiles[tileI + 2][tileO - 1]->getPiece()->getPiece());
            tiles[tileI + 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Right 1
        if (tileO < 7)
        {
          if (tiles[tileI + 2][tileO + 1]->getPiece() == nullptr)
          {
            tiles[tileI + 2][tileO + 1]->addCapture("Open");
            tiles[tileI + 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 2][tileO + 1]->getPiece()->getColour() == "White")
          {
            tiles[tileI + 2][tileO + 1]->addCapture("White", tiles[tileI + 2][tileO + 1]->getPiece()->getPiece());
            tiles[tileI + 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
      // Down 2
      if (tileI >= 2)
      {
        // Left 1
        if (tileO > 0)
        {
          if (tiles[tileI - 2][tileO - 1]->getPiece() == nullptr)
          {
            tiles[tileI - 2][tileO - 1]->addCapture("Open");
            tiles[tileI - 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 2][tileO - 1]->getPiece()->getColour() == "White")
          {
            tiles[tileI - 2][tileO - 1]->addCapture("White", tiles[tileI - 2][tileO - 1]->getPiece()->getPiece());
            tiles[tileI - 2][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Right 1
        if (tileO < 7)
        {
          if (tiles[tileI - 2][tileO + 1]->getPiece() == nullptr)
          {
            tiles[tileI - 2][tileO + 1]->addCapture("Open");
            tiles[tileI - 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 2][tileO + 1]->getPiece()->getColour() == "White")
          {
            tiles[tileI - 2][tileO + 1]->addCapture("White", tiles[tileI - 2][tileO + 1]->getPiece()->getPiece());
            tiles[tileI - 2][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
      // Left 2
      if (tileO >= 2)
      {
        // Up 1
        if (tileI < 7)
        {
          if (tiles[tileI + 1][tileO - 2]->getPiece() == nullptr)
          {
            tiles[tileI + 1][tileO - 2]->addCapture("Open");
            tiles[tileI + 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 1][tileO - 2]->getPiece()->getColour() == "White")
          {
            tiles[tileI + 1][tileO - 2]->addCapture("White", tiles[tileI + 1][tileO - 2]->getPiece()->getPiece());
            tiles[tileI + 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Down 1
        if (tileI > 0)
        {
          if (tiles[tileI - 1][tileO - 2]->getPiece() == nullptr)
          {
            tiles[tileI - 1][tileO - 2]->addCapture("Open");
            tiles[tileI - 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 1][tileO - 2]->getPiece()->getColour() == "White")
          {
            tiles[tileI - 1][tileO - 2]->addCapture("White", tiles[tileI - 1][tileO - 2]->getPiece()->getPiece());
            tiles[tileI - 1][tileO - 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
      // Right 2
      if (tileO <= 5)
      {
        // Up 1
        if (tileI < 7)
        {
          if (tiles[tileI + 1][tileO + 2]->getPiece() == nullptr)
          {
            tiles[tileI + 1][tileO + 2]->addCapture("Open");
            tiles[tileI + 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + 1][tileO + 2]->getPiece()->getColour() == "White")
          {
            tiles[tileI + 1][tileO + 2]->addCapture("White", tiles[tileI + 1][tileO + 2]->getPiece()->getPiece());
            tiles[tileI + 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
        // Down 1
        if (tileI > 0)
        {
          if (tiles[tileI - 1][tileO + 2]->getPiece() == nullptr)
          {
            tiles[tileI - 1][tileO + 2]->addCapture("Open");
            tiles[tileI - 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - 1][tileO + 2]->getPiece()->getColour() == "White")
          {
            tiles[tileI - 1][tileO + 2]->addCapture("White", tiles[tileI - 1][tileO + 2]->getPiece()->getPiece());
            tiles[tileI - 1][tileO + 2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
        }
      }
    }
    else if (pieceName == "Bishop")
    {
      // Increments by one for every while iteration
      int counter = 1;
      // Left up diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO - counter) >= 0)
        {
          if (tiles[tileI + counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO - counter]->addCapture("Open");
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO - counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI + counter][tileO - counter]->addCapture("White", tiles[tileI + counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left down diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO - counter]->addCapture("Open");
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO - counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI - counter][tileO - counter]->addCapture("White", tiles[tileI - counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right up diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO + counter]->addCapture("Open");
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO + counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI + counter][tileO + counter]->addCapture("White", tiles[tileI + counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right down diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO + counter) <= 7)
        {
          if (tiles[tileI - counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO + counter]->addCapture("Open");
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO + counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI - counter][tileO + counter]->addCapture("White", tiles[tileI - counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      }
    }
    else if (pieceName == "Rook")
    {
      // Increments by one for every while iteration
      int counter = 1;
      // Up
      while (true)
      {
        if ((tileI + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO]->addCapture("Open");
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO]->getPiece()->getColour() == "White")
          {
            tiles[tileI + counter][tileO]->addCapture("White", tiles[tileI + counter][tileO]->getPiece()->getPiece());
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Down
      while (true)
      {
        if ((tileI - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO]->addCapture("Open");
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO]->getPiece()->getColour() == "White")
          {
            tiles[tileI - counter][tileO]->addCapture("White", tiles[tileI - counter][tileO]->getPiece()->getPiece());
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left
      while (true)
      {
        if ((tileO - counter) >= 0)
        {
          if (tiles[tileI][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO - counter]->addCapture("Open");
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO - counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI][tileO - counter]->addCapture("White", tiles[tileI][tileO - counter]->getPiece()->getPiece());
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right
      while (true)
      {
        if ((tileO + counter) <= 7)
        {
          if (tiles[tileI][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO + counter]->addCapture("Open");
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO + counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI][tileO + counter]->addCapture("White", tiles[tileI][tileO + counter]->getPiece()->getPiece());
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      }
    }
    else if (pieceName == "Queen")
    {
      // Increments by one for every while iteration
      int counter = 1;
      // Up
      while (true)
      {
        if ((tileI + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO]->addCapture("Open");
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO]->getPiece()->getColour() == "White")
          {
            tiles[tileI + counter][tileO]->addCapture("White", tiles[tileI + counter][tileO]->getPiece()->getPiece());
            tiles[tileI + counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Down
      while (true)
      {
        if ((tileI - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO]->addCapture("Open");
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO]->getPiece()->getColour() == "White")
          {
            tiles[tileI - counter][tileO]->addCapture("White", tiles[tileI - counter][tileO]->getPiece()->getPiece());
            tiles[tileI - counter][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left
      while (true)
      {
        if ((tileO - counter) >= 0)
        {
          if (tiles[tileI][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO - counter]->addCapture("Open");
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO - counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI][tileO - counter]->addCapture("White", tiles[tileI][tileO - counter]->getPiece()->getPiece());
            tiles[tileI][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right
      while (true)
      {
        if ((tileO + counter) <= 7)
        {
          if (tiles[tileI][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI][tileO + counter]->addCapture("Open");
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI][tileO + counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI][tileO + counter]->addCapture("White", tiles[tileI][tileO + counter]->getPiece()->getPiece());
            tiles[tileI][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left up diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO - counter) >= 0)
        {
          if (tiles[tileI + counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO - counter]->addCapture("Open");
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO - counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI + counter][tileO - counter]->addCapture("White", tiles[tileI + counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Left down diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO - counter) >= 0)
        {
          if (tiles[tileI - counter][tileO - counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO - counter]->addCapture("Open");
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO - counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI - counter][tileO - counter]->addCapture("White", tiles[tileI - counter][tileO - counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO - counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right up diagonal
      while (true)
      {
        if ((tileI + counter) <= 7 && (tileO + counter) <= 7)
        {
          if (tiles[tileI + counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI + counter][tileO + counter]->addCapture("Open");
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI + counter][tileO + counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI + counter][tileO + counter]->addCapture("White", tiles[tileI + counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI + counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      } counter = 1;
      // Right down diagonal
      while (true)
      {
        if ((tileI - counter) >= 0 && (tileO + counter) <= 7)
        {
          if (tiles[tileI - counter][tileO + counter]->getPiece() == nullptr)
          {
            tiles[tileI - counter][tileO + counter]->addCapture("Open");
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
          }
          else if (tiles[tileI - counter][tileO + counter]->getPiece()->getColour() == "White")
          {
            tiles[tileI - counter][tileO + counter]->addCapture("White", tiles[tileI - counter][tileO + counter]->getPiece()->getPiece());
            tiles[tileI - counter][tileO + counter]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
            break;
          }
          else break;
          counter += 1;
        }
        else break;
      }
    }
    else if (pieceName == "King")
    {
      // 1 square up
      if (tileI < 7)
      {
        if (tiles[tileI + 1][tileO]->getPiece() == nullptr)
        {
          tiles[tileI + 1][tileO]->addCapture("Open");
          tiles[tileI + 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI + 1][tileO]->getPiece()->getColour() == "White")
        {
          tiles[tileI + 1][tileO]->addCapture("White", tiles[tileI + 1][tileO]->getPiece()->getPiece());
          tiles[tileI + 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 square down
      if (tileI > 0)
      {
        if (tiles[tileI - 1][tileO]->getPiece() == nullptr)
        {
          tiles[tileI - 1][tileO]->addCapture("Open");
          tiles[tileI - 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI - 1][tileO]->getPiece()->getColour() == "White")
        {
          tiles[tileI - 1][tileO]->addCapture("White", tiles[tileI - 1][tileO]->getPiece()->getPiece());
          tiles[tileI - 1][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 square left
      if (tileO > 0)
      {
        if (tiles[tileI][tileO - 1]->getPiece() == nullptr)
        {
          tiles[tileI][tileO - 1]->addCapture("Open");
          tiles[tileI][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI][tileO - 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI][tileO - 1]->addCapture("White", tiles[tileI][tileO - 1]->getPiece()->getPiece());
          tiles[tileI][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 square right
      if (tileO < 7)
      {
        if (tiles[tileI][tileO + 1]->getPiece() == nullptr)
        {
          tiles[tileI][tileO + 1]->addCapture("Open");
          tiles[tileI][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI][tileO + 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI][tileO + 1]->addCapture("White", tiles[tileI][tileO + 1]->getPiece()->getPiece());
          tiles[tileI][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 up left diagonal
      if (tileI < 7 && tileO > 0)
      {
        if (tiles[tileI + 1][tileO - 1]->getPiece() == nullptr)
        {
          tiles[tileI + 1][tileO - 1]->addCapture("Open");
          tiles[tileI + 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI + 1][tileO - 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI + 1][tileO - 1]->addCapture("White", tiles[tileI + 1][tileO - 1]->getPiece()->getPiece());
          tiles[tileI + 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 down left diagonal
      if (tileI > 0 && tileO > 0)
      {
        if (tiles[tileI - 1][tileO - 1]->getPiece() == nullptr)
        {
          tiles[tileI - 1][tileO - 1]->addCapture("Open");
          tiles[tileI - 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI - 1][tileO - 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI - 1][tileO - 1]->addCapture("White", tiles[tileI - 1][tileO - 1]->getPiece()->getPiece());
          tiles[tileI - 1][tileO - 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 up right diagonal
      if (tileI < 7 && tileO < 7)
      {
        if (tiles[tileI + 1][tileO + 1]->getPiece() == nullptr)
        {
          tiles[tileI + 1][tileO + 1]->addCapture("Open");
          tiles[tileI + 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI + 1][tileO + 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI + 1][tileO + 1]->addCapture("White", tiles[tileI + 1][tileO + 1]->getPiece()->getPiece());
          tiles[tileI + 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // 1 down right diagonal
      if (tileI > 0 && tileO < 7)
      {
        if (tiles[tileI - 1][tileO + 1]->getPiece() == nullptr)
        {
          tiles[tileI - 1][tileO + 1]->addCapture("Open");
          tiles[tileI - 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
        else if (tiles[tileI - 1][tileO + 1]->getPiece()->getColour() == "White")
        {
          tiles[tileI - 1][tileO + 1]->addCapture("White", tiles[tileI - 1][tileO + 1]->getPiece()->getPiece());
          tiles[tileI - 1][tileO + 1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      // Left castle
      if (tileI == 0 && tileO == 4 && tiles[0][0]->getPiece() != nullptr && tiles[0][0]->getPiece()->getPiece() == "Rook" && tiles[0][0]->getPiece()->getColour() == "Black")
      {
        bool castleOkay = true;
        for (int i = 1; i < 4; i++)
        {
          if (tiles[0][i]->getPiece() != nullptr && tiles[0][i]->getPiece()->getPiece() != wxEmptyString)
          {
            castleOkay = false;
            break;
          }
        }

        if (castleOkay)
        {
          tiles[0][0]->addCapture("Black", "Rook");
          tiles[0][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
      //  Right castle
      if (tileI == 0 && tileO == 4 && tiles[0][7]->getPiece() != nullptr && tiles[0][7]->getPiece()->getPiece() == "Rook" && tiles[0][7]->getPiece()->getColour() == "Black")
      {
        bool castleOkay = true;
        for (int i = 5; i < 7; i++)
        {
          if (tiles[0][i]->getPiece() != nullptr && tiles[0][i]->getPiece()->getPiece() != wxEmptyString)
          {
            castleOkay = false;
            break;
          }
        }

        if (castleOkay)
        {
          tiles[0][7]->addCapture("Black", "Rook");
          tiles[0][7]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        }
      }
    }
  }
  else if (clickedPieceTemp->getIsCapture())
  {
    // Moving archived clickedPiece to clicked object (and checks queen promotion)
    if (turn == "White" && tileI == 0 && clickedPiece->getPiece() == "Pawn")
    {
      tiles[tileI][tileO]->addPiece("White", "Queen");
      tiles[tileI][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
    }
    else if (turn == "Black" && tileI == 7 && clickedPiece->getPiece() == "Pawn")
    {
      tiles[tileI][tileO]->addPiece("Black", "Queen");
      tiles[tileI][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
    }

    // Checking for a king capture, win condition
    if (tiles[tileI][tileO]->getPiece()->getPiece() == "King") exit(0);

    // Castling
    else if (turn == "White" && clickedPieceTemp->getPiece() == "Rook" && clickedPieceTemp->getColour() == "White")
    {
      if (tileO == 0)
      {
        tiles[7][2]->addPiece("White", "King");
        tiles[7][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[7][3]->addPiece("White", "Rook");
        tiles[7][3]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[7][0]->removePiece();
      }
      else if (tileO == 7)
      {
        tiles[7][5]->addPiece("White", "Rook");
        tiles[7][5]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[7][6]->addPiece("White", "King");
        tiles[7][6]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[7][7]->removePiece();
      }
    }
    else if (turn == "Black" && clickedPieceTemp->getPiece() == "Rook" && clickedPieceTemp->getColour() == "Black")
    {
      if (tileO == 0)
      {
        tiles[0][2]->addPiece("Black", "King");
        tiles[0][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[0][3]->addPiece("Black", "Rook");
        tiles[0][3]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[0][0]->removePiece();
      }
      else if (tileO == 7)
      {
        tiles[0][5]->addPiece("Black", "Rook");
        tiles[0][5]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[0][6]->addPiece("Black", "King");
        tiles[0][6]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
        tiles[0][7]->removePiece();
      }
    }

    else
    {
      tiles[tileI][tileO]->addPiece(clickedPiece->getColour(), clickedPiece->getPiece());
      tiles[tileI][tileO]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
    }

    // Detects enPassant move
    if (tileI < 7 && turn == "White")
      if (tiles[tileI + 1][tileO]->getPiece() != nullptr && tiles[tileI + 1][tileO]->getPiece()->getEnPassant())
        tiles[tileI + 1][tileO]->removePiece();
    else if (tileI > 0 && turn == "Black")
      if (tiles[tileI - 1][tileO]->getPiece() != nullptr && tiles[tileI - 1][tileO]->getPiece()->getEnPassant())
        tiles[tileI - 1][tileO]->removePiece();

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

    delete updateTimer; updateTimer = nullptr;
    if (turn == "White") updateTimer = new UpdateTimer(scoreboard->getPlayerOneTime());
    else                 updateTimer = new UpdateTimer(scoreboard->getPlayerTwoTime());

    // Clearing all pawns that had Piece::enPassant being true
    for (int i = 0; i < 8; i++)
      for (int o = 0; o < 8; o++)
        if (tiles[i][o]->getPiece() != nullptr && tiles[i][o]->getPiece()->getEnPassant())
          tiles[i][o]->getPiece()->setEnPassant(false);

    // Checking for a pawn that satisfies Piece::enPassant being true
    if (moveO == tileO && tiles[tileI][tileO]->getPiece()->getPiece() == "Pawn")
    {
      if (tiles[tileI][tileO]->getPiece()->getColour() == "White" && tileI == (moveI - 2))
        tiles[tileI][tileO]->getPiece()->setEnPassant(true);
      else if (tiles[tileI][tileO]->getPiece()->getColour() == "Black" && tileI == (moveI + 2))
        tiles[tileI][tileO]->getPiece()->setEnPassant(true);
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

  tiles[0][0]->addPiece("Black", "Rook");
  tiles[0][0]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[0][1]->addPiece("Black", "Knight");
  tiles[0][1]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[0][2]->addPiece("Black", "Bishop");
  tiles[0][2]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[0][3]->addPiece("Black", "King");
  tiles[0][3]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[0][4]->addPiece("Black", "Queen");
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
  tiles[7][3]->addPiece("White", "King");
  tiles[7][3]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[7][4]->addPiece("White", "Queen");
  tiles[7][4]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[7][5]->addPiece("White", "Bishop");
  tiles[7][5]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[7][6]->addPiece("White", "Knight");
  tiles[7][6]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
  tiles[7][7]->addPiece("White", "Rook");
  tiles[7][7]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
}

void Frame::clearCaptureIcons()
{
  for (int i = 0; i < 8; i++)
  {
    for (int o = 0; o < 8; o++)
    {
      if (tiles[i][o]->getPiece() != nullptr && tiles[i][o]->getPiece()->getIsCapture())
      {
        tiles[i][o]->resetTile();
        if (tiles[i][o]->getPiece() != nullptr)
          tiles[i][o]->getPiece()->Bind(wxEVT_LEFT_DOWN, &Frame::leftDown, this);
      }
    }
  }
}

