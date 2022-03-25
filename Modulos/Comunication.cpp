#include "Comunication.h"
#include <wx/wx.h>
using namespace std;
Comunication::Comunication(settingGlobal* configGlobal) {
    this->configGlobal = configGlobal;
	port = "COM0";
    enabled = false;
}

void Comunication::setPort(std::string port) {
    this->port = port;
}

bool Comunication::connect() {
    arduino = new SerialPort(port.c_str());
    if (arduino->isConnected())
        return true;
    else
        delete arduino;
    return false;
}

bool Comunication::disconnect() {
    delete arduino;
    return false;
}

char* Comunication::read(char* buffer, int buffer_size) {
    if (arduino != nullptr && arduino->isConnected())
        return arduino->readSerialPort(buffer_size);
    else
        throw "Impossivel se conectar com o dispositivo";
}

bool Comunication::write(char* buffer, int buffer_size) {
    if (enabled) {
        if (arduino != nullptr && arduino->isConnected())
            return arduino->writeSerialPort(buffer, buffer_size);
        else
            throw "Impossivel se conectar com o dispositivo";
    }
}

std::pair<int, float> Comunication::readBateries() {
    char* incomingData = arduino->readSerialPort(MAX_DATA_LENGTH);
    std::pair<int, float> bat;
    bat.first = -1;

    for(int i=0; incomingData[i] != 'B' and i < MAX_DATA_LENGTH; i++){
        if (incomingData[0] == 'B' && incomingData[1] == 'A' && incomingData[2] == 'T') {
            int id = incomingData[4] - 48;
            float batValue = (incomingData[8] - 48) + (incomingData[10] - 48) / 10.0 + (incomingData[11] - 48) / 100.0;
            bat.first = id;
            bat.second = batValue;        
        }
    }
    
    delete incomingData;
    return bat;
}


void Comunication::setEnabled(bool val) {
    enabled = val;
}

void Comunication::sendPackage(std::pair<int, int> wheels[]) {
    char pacote[13];
    pacote[0] = 'F';
    pacote[1] = 'D';
    pacote[2] = 6 + 48;
    for (int i = 0; i < 3; i++) {
        pacote[2 * i + 3] = wheels[i].first + 48 + 100;
        pacote[2 * i + 4] = wheels[i].second + 48 + 100;
    }
    pacote[9] = 'I';
    pacote[10] = 10;
    pacote[11] = 10;
    pacote[12] = 0;
    try {
        write(pacote, 13);
    }
    catch (std::exception e) {
        std::cerr << e.what();
    }
}