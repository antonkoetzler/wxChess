#pragma once

#include <wx/wx.h>

class Piece : public wxStaticBitmap
{
 public:
  Piece(wxPanel*, wxBitmap, wxString, wxString);
  Piece(wxPanel*, wxBitmap, wxString, wxString, bool);

  // Getters
  wxString getPiece();
  wxString getColour();
  bool getIsCaptureIcon();

 private:
  wxString colour;
  wxString piece;
  bool isCaptureIcon = false;
};

