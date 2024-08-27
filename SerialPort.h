#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
	
// Constants stating I/O mode of port
#define READ GENERIC_READ
#define WRITE GENERIC_WRITE

// ==============
//	ERROR CODES
// ==============
#define DISCONNECTED 1
#define COMM_ERROR 2
#define SETTING_ERROR 3
#define TIMEOUT_ERROR 4
#define READ_WRITE_ERROR 5
#define CLEAR_ERROR 6


using namespace std;

class SerialPort {
	private:
	HANDLE hPort;
	DCB dcbSettings = {0};
	COMMTIMEOUTS timeout ={0};

	public:
	SerialPort(string sPort);
 
	void BaudRate(int BaudRate);
	void TimeOut(int WAIT_BYTES_READ, int WAIT_READ, int WAIT_MULTIPLIER_READ, 
			int WAIT_WRITE, int WAIT_BYTES_WRITE); 
	void TimeOut(int WAIT_READ, int WAIT_WRITE);
	
	// Read and Writing
	string Read();
	void Write(const string& message);

	void Close();
	void Clear();
};

SerialPort::SerialPort(string sPort) { 
	// Creates the handle which references the port
	wstring wPort(sPort.begin(), sPort.end()); // Converts the begining and end of the normal string to a wide string called 'wPort'
	
	hPort = CreateFileW(wPort.c_str(), READ | WRITE, 0, NULL, OPEN_EXISTING, 0, NULL); 
	// Error when trying to reference port
	if (hPort == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) { // Port wasn't connected
			throw DISCONNECTED;
		} else {	// Port connected but error communicating
			throw COMM_ERROR;
		}
		
	}
}

void SerialPort::BaudRate (int BaudRate) {
	dcbSettings = {0};
	dcbSettings.DCBlength = sizeof(dcbSettings);	// Initializes it so settings are empty

	// Gets existing settings of the ComPort
	if (!GetCommState(hPort, &dcbSettings)){ 
		// Unable to fetch port settings
		throw SETTING_ERROR;
	}

	// Changes the existing ports settings
	dcbSettings.BaudRate = BaudRate;
	dcbSettings.ByteSize = 8;
	dcbSettings.StopBits = ONESTOPBIT;
	dcbSettings.Parity = NOPARITY;
	
	// Attempt to commit changes to actual port
	if (!SetCommState(hPort, &dcbSettings)){
		// Error setting settings
		throw SETTING_ERROR;
	}
}


void SerialPort::TimeOut(int WAIT_BYTES_READ, int WAIT_READ, int WAIT_MULTIPLIER_READ, 
			int WAIT_WRITE, int WAIT_BYTES_WRITE){
	// Sets time out settings
	timeout = {0};
	timeout.ReadIntervalTimeout = WAIT_BYTES_READ;
	timeout.ReadTotalTimeoutConstant = WAIT_READ;
	timeout.ReadTotalTimeoutMultiplier = WAIT_MULTIPLIER_READ;
	timeout.WriteTotalTimeoutConstant = WAIT_WRITE;
	timeout.WriteTotalTimeoutMultiplier = WAIT_BYTES_WRITE;

	// Attempts to set them
	if (!SetCommTimeouts(hPort, &timeout)) {
		// Error: Could'nt set timeout
		throw TIMEOUT_ERROR;
	}
} 

void SerialPort::TimeOut(int WAIT_READ, int WAIT_WRITE) { 

	// Sets time out settings
	timeout = {0};
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = WAIT_READ;
	timeout.ReadTotalTimeoutMultiplier = 10;
	timeout.WriteTotalTimeoutConstant = WAIT_WRITE;
	timeout.WriteTotalTimeoutMultiplier = 5;

	// Attempts to set them
	if (!SetCommTimeouts(hPort, &timeout)) {
		// Error: Could'nt set timeout
		throw TIMEOUT_ERROR;
	} 
	
}

string SerialPort::Read() {
	char dataIn[1024] = {0};
	DWORD bytesRead = 0; 

	// Attempts to read data in serial port
	if (!ReadFile(hPort, dataIn, sizeof(dataIn)-1, &bytesRead, NULL)) {
		// Error: Data hasnt been read
		throw READ_WRITE_ERROR;
	} else {
		dataIn[bytesRead] = '\0';	// Ensures string is closed at end
		return std::string(dataIn);
	}
}

void SerialPort::Write(const string& message) {
	const char* dataIn = message.c_str();
	DWORD bytesWritten = 0; 

	// Attempts to write data in serial port
	if (!WriteFile(hPort, dataIn, message.size(), &bytesWritten, NULL)) {
		// Error: Data hasnt been written
		throw READ_WRITE_ERROR;
	}
}

void SerialPort::Close() { 
	CloseHandle(hPort);
}


void SerialPort::Clear() {
	 if (!PurgeComm(hPort, PURGE_RXCLEAR | PURGE_TXCLEAR)) {
		throw CLEAR_ERROR;
	 }
}
