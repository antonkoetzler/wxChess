#include "Tile.h"

Tile::Tile(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(80, 80))
{
  sizer = new wxBoxSizer(wxHORIZONTAL);
  SetSizer(sizer);
}

void Tile::addPiece(wxString colourArg, wxString pieceArg)
{
  wxBitmap image;

  if (colourArg == "White")
  {
    if (pieceArg == "Pawn") image.LoadFile("./img/whitePawn.png");
    else if (pieceArg == "Knight") image.LoadFile("./img/whiteKnight.png");
    else if (pieceArg == "Bishop") image.LoadFile("./img/whiteBishop.png");
    else if (pieceArg == "Rook") image.LoadFile("./img/whiteRook.png");
    else if (pieceArg == "Queen") image.LoadFile("./img/whiteQueen.png");
    else if (pieceArg == "King") image.LoadFile("./img/whiteKing.png");
  }
  else if (colourArg == "Black")
  {
    if (pieceArg == "Pawn") image.LoadFile("./img/blackPawn.png");
    else if (pieceArg == "Knight") image.LoadFile("./img/blackKnight.png");
    else if (pieceArg == "Bishop") image.LoadFile("./img/blackBishop.png");
    else if (pieceArg == "Rook") image.LoadFile("./img/blackRook.png");
    else if (pieceArg == "Queen") image.LoadFile("./img/blackQueen.png");
    else if (pieceArg == "King") image.LoadFile("./img/blackKing.png");
  }

  if (!image.IsOk()) Close();

  if (piece != nullptr)
  {
    sizer->Clear(true);
    piece = nullptr;
  }

  piece = new Piece(this, image, colourArg, pieceArg);
  sizer->Add(piece, 0, wxALIGN_CENTRE);
  Refresh();
}

