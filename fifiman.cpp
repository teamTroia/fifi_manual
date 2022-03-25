#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "mainFrame.h"
#include <sys/stat.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    mainFrame* frame = new mainFrame("Fifi Soccer Manual", wxPoint(300,300));
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp); 