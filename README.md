# Serial-Port-Library-Windows-API-

### Serial Port Library

Btw its my first time using github

This library was intended for me to simplify the Serial Port API from <windows.h>
I do not want to remember the long code, so I 'dumbed' it down so that I can easily reuse it in projects.

But there are errors which I do not know how to fix. If you are able to, may you please help me?

## How library Works

### Basic commands 

constructor **SerialPort(Communication Port)** -- Instantiates port


**BaudRate(BAUD)** -- Sets baud rate of port, other settings of port is predetermined (makes it simpler for me to work with Arduino)

**TimeOut( ... )** -- Specifies the timeout settings (How long must program wait for the data)


**Read()** -- Reading buffer

**Write()** -- Writing to buffer

**Close()** -- Closes serial port

**Clear()** -- Clears buffer

### Error Messages

**DISCONNECTED** -- Port disconnected

**COMM_ERROR** -- Port connected but failed to communicate with program

**SETTING_ERROR** -- Error setting up settings on port (BaudRate)

**TIMEOUT_ERROR** -- Error setting timeout settings

**READ_WRITE_ERROR** -- Error when trying to read/write from port

**CLEAR_ERROR** -- Error when attempting to clear


# Errors I keep getting

When the program sends the message, I have to plug in and plug in my Arduino to receive the message in the serial monitor, not immediately.
I also keep getting COMM_ERROR
