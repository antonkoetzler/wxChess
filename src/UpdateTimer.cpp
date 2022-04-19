#include "UpdateTimer.h"

UpdateTimer::UpdateTimer(wxStaticText* playerTime)
{
  time = playerTime;
  Start(1000);
}

void UpdateTimer::Notify()
{
  int leftHand = wxAtoi(time->GetLabel()[0]);         // i.e. [1]:00
  wxString leftHandOutput = time->GetLabel()[0];      // What we will feed into UpdateTimer::time
  int rightHand = wxAtoi(time->GetLabel().substr(2)); // i.e. 1:[00]
  wxString rightHandOutput;                           // What we will feed into UpdateTimer::time

  // An end condition
  if (leftHand == 0 && rightHand == 0) exit(0);
  else if (rightHand != 0)
  {
    rightHand -= 1;
    if (rightHand < 10) rightHandOutput = "0" + wxString::Format(wxT("%d"), (int)rightHand);
    else                rightHandOutput = wxString::Format(wxT("%d"), (int)rightHand);
  }
  else
  {
    rightHandOutput = "59";
    leftHand -= 1;
    leftHandOutput = wxString::Format(wxT("%d"), (int)leftHand);
  }

  time->SetLabel(leftHandOutput + ":" + rightHandOutput);
}

