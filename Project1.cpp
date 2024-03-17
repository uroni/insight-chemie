//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("LoadingScreen.cpp", FLoadingScreen);
USEFORM("MainScreen.cpp", FMainScreen);
USEFORM("DrawFrame.cpp", FDrawFrame); /* TFrame: File Type */
USEFORM("SimParams.cpp", FSimParams);
USEFORM("LogScreen.cpp", FLogScreen);
USEFORM("AboutBox.cpp", FAboutBox);
USEFORM("PresentationScreen.cpp", FPresentationScreen);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Insight Chemie";
                 Application->CreateForm(__classid(TFLoadingScreen), &FLoadingScreen);
                 Application->CreateForm(__classid(TFSimParams), &FSimParams);
                 Application->CreateForm(__classid(TFLogScreen), &FLogScreen);
                 Application->CreateForm(__classid(TFAboutBox), &FAboutBox);
                 Application->CreateForm(__classid(TFPresentationScreen), &FPresentationScreen);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
