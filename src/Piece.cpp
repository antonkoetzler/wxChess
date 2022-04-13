#include "Piece.h"

Piece::Piece(wxPanel* parent, wxBitmap image, wxString pieceArg, wxString colourArg) : wxStaticBitmap(parent, wxID_ANY, image)
{
  piece = pieceArg;
  colour = colourArg;
}

