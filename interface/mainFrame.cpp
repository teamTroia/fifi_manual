#include <mainFrame.h>
#include <iostream>

wxBEGIN_EVENT_TABLE(mainFrame, wxFrame)
EVT_BUTTON(ID_BEGIN, mainFrame::btnIniciarClick)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(myPanel, wxPanel)
EVT_KEY_DOWN(myPanel::keyDown)
EVT_KEY_UP(myPanel::keyUp)
wxEND_EVENT_TABLE()

void myPanel::keyDown(wxKeyEvent &evt){
    if(evt.GetUnicodeKey() == wxChar('w') or evt.GetUnicodeKey() == wxChar('W'))
        parent->w = true;
    if(evt.GetUnicodeKey() == wxChar('a') or evt.GetUnicodeKey() == wxChar('A'))
        parent->a = true;
    if(evt.GetUnicodeKey() == wxChar('s') or evt.GetUnicodeKey() == wxChar('S'))
        parent->s = true;
    if(evt.GetUnicodeKey() == wxChar('d') or evt.GetUnicodeKey() == wxChar('D'))
        parent->d = true;
}

void myPanel::keyUp(wxKeyEvent &evt){
    if(evt.GetUnicodeKey() == wxChar('w') or evt.GetUnicodeKey() == wxChar('W'))
        parent->w = false;
    if(evt.GetUnicodeKey() == wxChar('a') or evt.GetUnicodeKey() == wxChar('A'))
        parent->a = false;
    if(evt.GetUnicodeKey() == wxChar('s') or evt.GetUnicodeKey() == wxChar('S'))
        parent->s = false;
    if(evt.GetUnicodeKey() == wxChar('d') or evt.GetUnicodeKey() == wxChar('D'))
        parent->d = false;
}

void mainFrame::btnIniciarClick(wxCommandEvent &evt){
    idRobot = choiceRobot->GetSelection();
    std::string IP = editPort->GetValue().ToStdString();
    if(IP[0] == '/'){
        std::cout << "im a server\n";
        com->setPort(IP);
        if(true/*com->connect()*/){
            //com->setEnabled(true);
            if(sock->connect("192.168.0.100") == true){
                sock->bind_sock(); 
                isClient = false;
                timer->Start();
            } else {
                wxMessageBox("Falha ao conectar à porta", "ERRO");
            } 
        }
    } else {
        std::cout << "im a cliet\n";
        if(sock->connect(IP) == true){
            isClient = true;
            timer->Start();
        } else {
            wxMessageBox("Falha ao conectar à porta", "ERRO");
        }
    }
}

mainFrame::mainFrame(const wxString& title, const wxPoint& pos) : wxFrame(NULL, wxID_ANY, title, pos, wxDefaultSize){
    setting = new settingGlobal;
    com = new Comunication(setting);
    timer = new loopTimer(this);
    sock = new Socket();
    isClient = false;
    wheel = new std::pair<int,int>[3];
    for(int i=0; i<3; i++){
        wheel[i].first = 0;
        wheel[i].second = 0;
    }
    w = false;
    a = false;
    s = false;
    d = false;
    panel = new myPanel(this, wxID_ANY, "");
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    editPort = new wxTextCtrl(this, ID_PORT, "/dev/ttyUSB0", wxDefaultPosition, wxSize(150,30));
    wxArrayString ch = wxArrayString();
    ch.Add("0");
    ch.Add("1");
    ch.Add("2");
    choiceRobot = new wxChoice(this, ID_ROBOT, wxDefaultPosition, wxSize(150,30), ch);
    choiceRobot->Select(0);
    btnIniciar = new wxButton(this, ID_BEGIN, "INICIAR", wxDefaultPosition, wxSize(150,30));
    sizer->Add(editPort, 0, wxALL, 10);
    sizer->Add(choiceRobot, 0, wxALL, 10);
    sizer->Add(btnIniciar, 0, wxALL, 10);
    sizer->Add(panel, 0, wxALL, 10);
    SetSizerAndFit(sizer);
}

void loopTimer::Start(){
	wxTimer::Start(16);
}

loopTimer::loopTimer(mainFrame* parent){
    this->parent = parent;
}

void parse_message(char* message, std::pair<int, int>* wheels){
    int id;
    int i = 1;
    if(message[0] == '|'){
        std::cout << message << "\n";
        for(int j=0; j<3;j++){
            std::string aux = "";
            while(message[i] != '|'){
                aux += message[i];
                i++;
            }
            i++;
            if(j == 0){
                id = atoi(aux.c_str());
            }else if(j == 1){
                wheels[id].first = atoi(aux.c_str());
            }else {
                wheels[id].second = atoi(aux.c_str());
            }
        }
    }
}

void loopTimer::Notify(){
	bool all = parent->w or parent->s or parent->d or parent->a;
    if(parent->w and parent->a){
        parent->wheel[parent->idRobot].first = 25;
        parent->wheel[parent->idRobot].second = 50;
    }else if(parent->w and parent->d){
        parent->wheel[parent->idRobot].first = 50;
        parent->wheel[parent->idRobot].second = 25;
    }else if(parent->w) {
        parent->wheel[parent->idRobot].first = 50;
        parent->wheel[parent->idRobot].second = 50;
    } else if(parent->s and parent->a){
        parent->wheel[parent->idRobot].first = -25;
        parent->wheel[parent->idRobot].second = -50;
    }else if(parent->s and parent->d){
        parent->wheel[parent->idRobot].first = -50;
        parent->wheel[parent->idRobot].second = -25;
    }else if(parent->s) {
        parent->wheel[parent->idRobot].first = -50;
        parent->wheel[parent->idRobot].second = -50;
    }else if(parent->d){
        parent->wheel[parent->idRobot].first = 25;
        parent->wheel[parent->idRobot].second = -25;
    }else if(parent->a){
        parent->wheel[parent->idRobot].first = -25;
        parent->wheel[parent->idRobot].second = 25;
    }

    if(parent->isClient){
        std::string pacote = "|";
        pacote += std::to_string(parent->idRobot);
        pacote += "|";
        pacote += std::to_string(parent->wheel[parent->idRobot].first);
        pacote += "|";
        pacote += std::to_string(parent->wheel[parent->idRobot].second);
        pacote += "|";
        parent->sock->send((char*)pacote.c_str());
    } else {
        char* message = parent->sock->receive();
        parse_message(message, parent->wheel);
        //parent->com->sendPackage(parent->wheel);
    }
}

myPanel::myPanel(mainFrame* parent, wxWindowID winid, wxString label) : wxPanel((wxWindow*)parent, wxID_ANY, wxDefaultPosition,wxSize(150,150)){
    this->parent = parent;
}