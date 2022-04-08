#pragma once

#include <wx/wx.h>

class Piece : public wxStaticBitmap
{
 public:
  Piece(wxPanel*, wxBitmap, wxString);

 private:
  wxString colour;
};

