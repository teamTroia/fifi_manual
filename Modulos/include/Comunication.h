#include "SerialPort.h"
#include <string>
#include <vector>
#include "FFtypes.h"

class Comunication {
private:
	settingGlobal* configGlobal;
	SerialPort* arduino;
	std::string port;
	bool enabled;
public:
	Comunication(settingGlobal* configGlobal);
	void setPort(std::string port);
	bool connect();
	bool disconnect();
	char* read(char* buffer, int buffer_size);
	bool write(char* buffer, int buffer_size);
	void setEnabled(bool val);
	void sendPackage(std::pair<int, int> wheels[]);
	std::pair<int, float> readBateries();
	
	template<typename T>
	T listComPorts() {
		T lista = T();
		std::string port;
		int fd;
		for(int i = 0; i < 5; ++i)
		{
			port = "/dev/ttyUSB"+std::to_string(i);
			fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
			if(fd != -1)
				lista.Add(port);

			port = "/dev/ttyACM"+std::to_string(i);
			fd = open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
			if(fd != -1)
				lista.Add(port);
		}
		if(lista.IsEmpty()){
			lista.Add(" ");
		}
		return lista;
	}
	
};
