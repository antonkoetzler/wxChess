#pragma once

#include <wx/wx.h>

class Piece : public wxStaticBitmap
{
 public:
  Piece(wxPanel*, wxBitmap, wxString, wxString);

  // Getters
  wxString getPiece();
  wxString getColour();

 private:
  wxString colour;
  wxString piece;
};

