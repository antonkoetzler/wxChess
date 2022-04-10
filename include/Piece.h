#pragma once

#include <wx/wx.h>

class Piece : public wxStaticBitmap
{
 public:
  Piece(wxPanel*, wxBitmap, wxString, wxString);

  // When clicked, this shows where a piece can move
  void leftDown(wxMouseEvent&);

 private:
  DECLARE_EVENT_TABLE();
  wxString colour;
  wxString piece;
};

