#pragma hdrstop
#include "EventReceiver.h"

#include "LogScreen.h"

bool EventReceiver::OnEvent(irr::SEvent event)
{
 	if (event.EventType == irr::EET_LOG_TEXT_EVENT)
 	{
                FLogScreen->Memo1->Lines->Add(event.LogEvent.Text);
        }
        return false;
}