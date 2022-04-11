// Child wxPanel class that acts as a tile on the chess board
// This class also holds an wxStaticBitmap of the chess piece it represents
#pragma once

#include <wx/wx.h>
#include "Piece.h"

class Tile : public wxPanel
{
 public:
  Tile(wxFrame*);

  void addPiece(wxString, wxString = "");
  Piece* getPiece();
  void movePiece(); // Disconnects the sizer to move Piece*

 private:
  wxBoxSizer* sizer = nullptr; // Keeps Piece* centered
  Piece* piece = nullptr;
};

