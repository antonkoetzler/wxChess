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

void Tile::addCapture(wxString colourArg, wxString pieceArg)
{
  wxBitmap image;

  if (colourArg == "Open")         image.LoadFile("./img/openTile.png");
  else if (colourArg == "White")
  {
    if (pieceArg == "Pawn")        image.LoadFile("./img/whitePawnCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("./img/whiteKnightCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("./img/whiteBishopCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("./img/whiteRookCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("./img/whiteQueenCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King")   image.LoadFile("./img/whiteKingCapture.png", wxBITMAP_TYPE_PNG);
  }
  else
  {
    if (pieceArg == "Pawn")        image.LoadFile("./img/blackPawnCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Knight") image.LoadFile("./img/blackKnightCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Bishop") image.LoadFile("./img/blackBishopCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Rook")   image.LoadFile("./img/blackRookCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "Queen")  image.LoadFile("./img/blackQueenCapture.png", wxBITMAP_TYPE_PNG);
    else if (pieceArg == "King")   image.LoadFile("./img/blackKingCapture.png", wxBITMAP_TYPE_PNG);
  }

  if (!image.IsOk()) Close();

  wxString pieceName = wxEmptyString;
  wxString pieceColour = wxEmptyString;
  if (piece != nullptr)
  {
    pieceName = piece->getPiece();
    pieceColour = piece->getColour();
    sizer->Clear(true);
    piece = nullptr;
  }

  piece = new Piece(this, image, pieceColour, pieceName, true);
  sizer->Add(piece, 0, wxALIGN_CENTRE);
  Refresh();
}

void Tile::resetTile()
{
  // Capture icon that's not a chess piece
  wxString pieceColour = piece->getColour();
  wxString pieceName = piece->getPiece();

  sizer->Clear(true);
  piece = nullptr;

  // pieceName == wxEmptyString indicates that it's openTile.png
  if (pieceName != "") addPiece(pieceColour, pieceName);
  else Refresh();
}

Piece* Tile::getPiece() { return piece; }

