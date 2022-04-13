#pragma once

#include <wx/wx.h>

class Piece : public wxStaticBitmap
{
 public:
  Piece(wxPanel*, wxBitmap, wxString, wxString);

 private:
  wxString piece;
  wxString colour;
};

