#include "Tile.h"

Tile::Tile(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(80, 80)) {}

void Tile::addPiece(wxString colourArg, wxString pieceArg)
{
  // Loading bitmap to pass to piece variable
  wxBitmap image;

  if (colourArg == "White")
  {
    if (pieceArg == "Pawn")        image.LoadFile("../img/whitePawn.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("../img/whiteKnight.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("../img/whiteBishop.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("../img/whiteRook.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("../img/whiteQueen.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King") image.LoadFile("../img/whiteKing.png", wxBITMAP_TYPE_PNG);
  }
  else
  {
    if (pieceArg == "Pawn")        image.LoadFile("../img/blackPawn.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("../img/blackKnight.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("../img/blackBishop.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("../img/blackRook.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("../img/blackQueen.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King") image.LoadFile("../img/blackKing.png", wxBITMAP_TYPE_PNG);
  }

  if (image.IsOk())
  {
    piece = new Piece(this, image, colourArg, pieceArg);
    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(piece, 1, wxSHAPED | wxALIGN_CENTRE);
    SetSizer(sizer);
  }
}

Piece* Tile::getPiece() { return piece; }

void Tile::movePiece()
{
  if (sizer != nullptr && piece != nullptr)
  {
    // Remove piece from sizer without deleting piece
    sizer->Clear(false);
    delete sizer; sizer = nullptr;
    // Move Piece*
    piece->Move(10, 10);
  }
}

