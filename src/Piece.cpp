#include "Piece.h"

Piece::Piece(wxPanel* parent, wxBitmap image, wxString colourArg, wxString pieceArg) : wxStaticBitmap(parent, wxID_ANY, image)
{
  piece = pieceArg;
  colour = colourArg;
  SetCursor(wxCursor(wxCURSOR_HAND));
}

Piece::Piece(wxPanel* parent, wxBitmap image, wxString colourArg, wxString pieceArg, bool isCaptureArg) : wxStaticBitmap(parent, wxID_ANY, image)
{
  piece = pieceArg;
  colour = colourArg;
  isCapture = isCaptureArg;
}

wxString Piece::getPiece() { return piece; }
wxString Piece::getColour() { return colour; }
bool Piece::getIsCapture() { return isCapture; }

