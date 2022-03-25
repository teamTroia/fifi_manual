#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "Comunication.h"
#include "Socket.h"

enum {
    ID_PORT = wxID_HIGHEST + 1,
    ID_BEGIN, 
    ID_ROBOT
};

class mainFrame;
class loopTimer : public wxTimer {
	mainFrame* parent;
public:
	loopTimer(mainFrame* parent);
	void Notify();
	void Start();

};

class myPanel : public wxPanel{
    private:
        mainFrame* parent;
    public:
        myPanel(mainFrame* parent, wxWindowID winid, wxString label);
        void keyDown(wxKeyEvent& evt);
        void keyUp(wxKeyEvent& evt);
        wxDECLARE_EVENT_TABLE();
};

class mainFrame : public wxFrame {
    friend class loopTimer;
    friend class myPanel;
    private:
        settingGlobal* setting;
        wxTextCtrl* editPort;
        wxChoice* choiceRobot;
        wxButton* btnIniciar;
        loopTimer* timer;
        Comunication* com;
        myPanel* panel;
        bool isClient;
        Socket* sock;
        bool w,a,s,d;
        int idRobot;
        std::pair<int, int>* wheel;
    public:
        mainFrame(const wxString& title, const wxPoint& pos);
        void btnIniciarClick(wxCommandEvent& evt);
        wxDECLARE_EVENT_TABLE();
};
