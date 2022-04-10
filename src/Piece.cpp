#include "Piece.h"

BEGIN_EVENT_TABLE(Piece, wxStaticBitmap)
  EVT_LEFT_DOWN(Piece::leftDown)
END_EVENT_TABLE()

Piece::Piece(wxPanel* parent, wxBitmap bitmap, wxString colourArg, wxString pieceArg) : wxStaticBitmap(parent, wxID_ANY, bitmap)
{
  colour = colourArg;
  piece = pieceArg;
  SetCursor(wxCursor(wxCURSOR_HAND));
}

void Piece::leftDown(wxMouseEvent& evt)
{
  if (piece == "Pawn")
  {
    std::cout << "Pawn" << std::endl;
  }
  else if (piece == "Knight")
  {
    std::cout << "Knight" << std::endl;
  }
  else if (piece == "Bishop")
  {
    std::cout << "Bishop" << std::endl;
  }
  else if (piece == "Rook")
  {
    std::cout << "Rook" << std::endl;
  }
  else if (piece == "Queen")
  {
    std::cout << "Queen" << std::endl;
  }
  else if (piece == "King")
  {
    std::cout << "King" << std::endl;
  }
}

