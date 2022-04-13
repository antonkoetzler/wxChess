#pragma once

#include <wx/wx.h>

class Piece : public wxStaticBitmap
{
 public:
  Piece(wxPanel*, wxBitmap, wxString, wxString);
  Piece(wxPanel*, wxBitmap, wxString, wxString, bool);

  wxString getPiece();
  wxString getColour();
  bool getIsCapture();

 private:
  wxString piece;
  wxString colour;
  bool isCapture = false;
};

