#include "mainWindow.h"
#include "Mixer.h"
#include "Serial.h"
#include "App.h"
#include "atlconv.h"
#include <string>
#include <iostream>


using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	soundmixer::mainWindow form;
	
	std::cout << "Digite a porta serial(COM1, COM2..)" << endl;
	std::cin >> COMPort;

	serialCon = new Serial(COMPort);
	Mixer m;
	while (1) {
		/*strcpy(buffer, "empt");
		serialCon->readSerial(buffer, 4);
		buffer[4] = '\0';
		if (!strcmp(buffer, "tmut")) {
			if (m.GetMuteMaster() == true)
				m.SetMuteMaster(false);
			else if (m.GetMuteMaster() == false)
				m.SetMuteMaster(true);
		}

		if (!strcmp(buffer, "svap")) {
			serialCon->readSerial(buffer, 20);
			_tcscpy(processName, (TCHAR*)buffer);
			serialCon->readSerial(buffer, 1);
			float v = buffer[0];
			m.SetApplicationVolume(processName, v);
		}

		if (!strcmp(buffer, "tmap")) {
			serialCon->readSerial(buffer, 20);
			_tcscpy(processName, (TCHAR*)buffer);
			serialCon->readSerial(buffer, 1);
			float v = buffer[0];

			if (m.GetMuteApplication(processName) == true)
				m.SetMuteApplication(processName, false);
			else if (m.GetMuteApplication(processName) == false)
				m.SetMuteApplication(processName, true);
		}*/
		serialCon->readSerial(buffer, 3);
		double vol = atoi(buffer)/100.0;
		std::cout << "Volume: " << m.SetMasterVolume(vol, true) << endl;
		
	}
	//
	//std::cout << m.SetMuteApplication(processName,true);
	

	//Application::Run(%form);
}

void soundmixer::mainWindow::setComPort(std::string inputPort)
{
	strcpy(COMPort, inputPort.c_str());
}
