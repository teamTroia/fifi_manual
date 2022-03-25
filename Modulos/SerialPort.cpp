// Arquivo .cpp da comunica��o serial
#include "SerialPort.h"

SerialPort::SerialPort(std::string port_name) {
    std::string cmd = "stty 115200 -F ";
    cmd += port_name;
    cmd += " raw -echo";
    system(cmd.c_str());
    port = open(port_name.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    flags = fcntl(port, F_GETFL, 0);
    fcntl(port, F_SETFL, flags | O_NONBLOCK);
}

SerialPort::~SerialPort(){
    close(port);
}

bool SerialPort::writeSerialPort(char* buffer, unsigned int buf_size) {
    if(isConnected()){
        write(port, buffer, buf_size);
        return true;
    }
    return false;
    
}

char* SerialPort::readSerialPort(unsigned int buf_size){
    if(isConnected()){
        char* buff = new char[10];
        int s = read(port, buff, 10);
        if(s > 0)
            return buff;
        else 
            return NULL;
    }
    return NULL;
}

bool SerialPort::isConnected()
{
    return port != NULL;
}
