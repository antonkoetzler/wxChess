#include "Piece.h"

Piece::Piece(wxPanel* parent, wxBitmap bitmap, wxString colourArg) : wxStaticBitmap(parent, wxID_ANY, bitmap) { colour = colourArg; }

