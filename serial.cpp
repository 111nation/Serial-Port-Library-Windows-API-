#include <iostream>
#include "SerialPort.h"

int main () { 

	cout << "\n\n";
	
	try {
		SerialPort COM3("COM3");
		/*COM3.BaudRate(9600);
		COM3.TimeOut(50, 50);
		COM3.Write("Hello!");
		COM3.Clear();*/
		COM3.Close();
	} catch (int error) {

		switch (error) {
			case DISCONNECTED: 
				cout << "Disconnected Port\n";
				break;
			
			case COMM_ERROR:
				cout << "Failed to communicate\n";
				break;

			case READ_WRITE_ERROR: 
				cout << "Display/ Read Error\n";
				break;

			case CLEAR_ERROR:
				cout << "Could not clear buffer\n";
				break;
			
			case SETTING_ERROR:
				cout << "Could not set necissary settings\n";
				break;

			default:
				cout << "Unspecified Error\n";
				break;

		}

		cout << endl << GetLastError() << endl;

	}
	
	cout << endl;

	return 0;
}
