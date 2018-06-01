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
	Mixer m;
	/*char input[10] = "";
	cout << "qual a com port? Escrever COM1, COM2, etc...: ";
	cin >> input;
	Serial s(input);*/
	char buffer[20];
	TCHAR processName[MAX_PATH] = TEXT("Empty.exe");
	while (0) {
		/*strcpy(buffer, "empt");
		s.readSerial(buffer, 4);
		buffer[4] = '\0';
		if (!strcmp(buffer, "tmut")) {
			if (m.GetMuteMaster() == true)
				m.SetMuteMaster(false);
			else if (m.GetMuteMaster() == false)
				m.SetMuteMaster(true);
		}

		if (!strcmp(buffer, "svap")) {
			s.readSerial(buffer, 20);
			_tcscpy(processName, (TCHAR*)buffer);
			s.readSerial(buffer, 1);
			float v = buffer[0];
			 m.SetApplicationVolume(processName, v);
		}

		if (!strcmp(buffer, "tmap")) {
			s.readSerial(buffer, 20);
			_tcscpy(processName, (TCHAR*)buffer);
			s.readSerial(buffer, 1);
			float v = buffer[0];
			
			if (m.GetMuteApplication(processName) == true)
				m.SetMuteApplication(processName, false);
			else if (m.GetMuteApplication(processName) == false)
				m.SetMuteApplication(processName, true);
		}*/
	}
	double vol = 0.25;
	//m.SetMasterVolume(vol, true);
	std::cout << m.SetMuteApplication(processName,true);

	Application::Run(%form);
}

void soundmixer::mainWindow::setComPort(std::string inputPort)
{
	strcpy(COMPort, inputPort.c_str());
}
