
#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

class SerialPort
{
private:
    int port;
    int flags;
public:
    SerialPort(std::string port_name);
    ~SerialPort();

    char* readSerialPort(unsigned int buf_size);
    bool writeSerialPort(char* buffer, unsigned int buff_size);
    bool isConnected();
};

#endif  // SERIALPORT_H