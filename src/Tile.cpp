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
    if (pieceArg == "Pawn")        image.LoadFile("./img/whitePawn.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("./img/whiteKnight.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("./img/whiteBishop.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("./img/whiteRook.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("./img/whiteQueen.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King")   image.LoadFile("./img/whiteKing.png", wxBITMAP_TYPE_PNG);
  }
  else if (colourArg == "Black")
  {
    if (pieceArg == "Pawn")        image.LoadFile("./img/blackPawn.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("./img/blackKnight.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("./img/blackBishop.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("./img/blackRook.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("./img/blackQueen.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King")   image.LoadFile("./img/blackKing.png", wxBITMAP_TYPE_PNG);
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

