#pragma once

#include <wx/wx.h>
#include "Piece.h"

class Tile : public wxPanel
{
 public:
  Tile(wxFrame*);

  void addPiece(wxString, wxString);
  void addCapture(wxString, wxString = "");
  void resetTile();

  Piece* getPiece();

 private:
  wxBoxSizer* sizer; // Centers piece
  Piece* piece = nullptr;
};

