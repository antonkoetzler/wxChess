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
  else if (colourArg == "Black")
  {
    if (pieceArg == "Pawn")        image.LoadFile("../img/blackPawn.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("../img/blackKnight.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("../img/blackBishop.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("../img/blackRook.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("../img/blackQueen.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King") image.LoadFile("../img/blackKing.png", wxBITMAP_TYPE_PNG);
  }

  if (!image.IsOk()) Close();
  if (sizer != nullptr)
  {
    sizer->Clear(false);
    delete piece; piece = nullptr;
  } else sizer = new wxBoxSizer(wxHORIZONTAL);
  piece = new Piece(this, image, colourArg, pieceArg);
  sizer->Add(piece, 1, wxSHAPED | wxALIGN_CENTRE);

  SetSizer(sizer);
  Refresh();
}

void Tile::addMove(wxString pieceArg, wxString colourArg)
{
  wxBitmap image;
  // Avoids iCCP PNG warning (dirty fix)
  wxLogNull warningAvoider;

  if (pieceArg == "Tile") image.LoadFile("../img/openTile.png", wxBITMAP_TYPE_PNG);

  if (colourArg == "White")
  {
    if (pieceArg == "Pawn") image.LoadFile("../img/whitePawnCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("../img/whiteKnightCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("../img/whiteBishopCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook") image.LoadFile("../img/whiteRookCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen") image.LoadFile("../img/whiteQueenCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King") image.LoadFile("../img/whiteKingCapture.png", wxBITMAP_TYPE_PNG);
  } else if (colourArg == "Black")
  {
    if (pieceArg == "Pawn") image.LoadFile("../img/blackPawnCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("../img/blackKnightCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("../img/blackBishopCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook") image.LoadFile("../img/blackRookCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen") image.LoadFile("../img/blackQueenCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King") image.LoadFile("../img/blackKingCapture.png", wxBITMAP_TYPE_PNG);
  }

  if (!image.IsOk()) Close();
  if (sizer != nullptr)
  {
    sizer->Clear(false);
    if (piece != nullptr) { delete piece; piece = nullptr; }
  } else sizer = new wxBoxSizer(wxHORIZONTAL);
  piece = new Piece(this, image, colourArg, pieceArg,  true);
  sizer->Add(piece, 1, wxSHAPED | wxALIGN_CENTRE);

  SetSizer(sizer);
  Refresh();
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

void Tile::resetTile()
{
  wxString pieceName = piece->getPiece();
  wxString pieceColour = piece->getColour();

  if (pieceName != "Tile")
  {
    addPiece(pieceColour, pieceName);
  } else
  {
    sizer->Clear(false);
    delete sizer; sizer = nullptr;
    delete piece; piece = nullptr;
    SetSizer(nullptr);
    Refresh();
  }
}

