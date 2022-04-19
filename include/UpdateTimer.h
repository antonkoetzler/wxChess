// A class to update Scoreboard::playerOne & Scoreboard::playerTwo timers
#pragma once

#include <wx/wx.h>

class UpdateTimer : public wxTimer
{
 public:
  UpdateTimer(wxStaticText*);
  void Notify() wxOVERRIDE;

 private:
  wxStaticText* time;
};

