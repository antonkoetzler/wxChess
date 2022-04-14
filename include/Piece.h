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
  void setEnPassant(bool);
  bool getEnPassant();

 private:
  wxString piece;
  wxString colour;
  bool isCapture = false;
  bool enPassant = false; // Determines if a pawn if en passantable
};

