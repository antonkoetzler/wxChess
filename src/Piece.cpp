#include "Piece.h"

Piece::Piece(wxPanel* parent, wxBitmap bitmap, wxString colourArg, wxString pieceArg) : wxStaticBitmap(parent, wxID_ANY, bitmap)
{
  colour = colourArg;
  piece = pieceArg;
  SetCursor(wxCursor(wxCURSOR_HAND));
}

wxString Piece::getPiece() { return piece; }
wxString Piece::getColour() { return colour; }

