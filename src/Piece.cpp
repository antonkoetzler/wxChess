#include "Piece.h"

Piece::Piece(wxPanel* parent, wxBitmap bitmap, wxString colourArg, wxString pieceArg) : wxStaticBitmap(parent, wxID_ANY, bitmap)
{
  colour = colourArg;
  piece = pieceArg;
  SetCursor(wxCursor(wxCURSOR_HAND));
}

Piece::Piece(wxPanel* parent, wxBitmap bitmap, wxString colourArg, wxString pieceArg, bool isCaptureIconArg) : wxStaticBitmap(parent, wxID_ANY, bitmap)
{
  colour = colourArg;
  piece = pieceArg;
  isCaptureIcon = isCaptureIconArg;
}

wxString Piece::getPiece() { return piece; }
wxString Piece::getColour() { return colour; }
bool Piece::getIsCaptureIcon() { return isCaptureIcon; }

