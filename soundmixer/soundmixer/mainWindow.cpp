#include "mainWindow.h"
#include "Mixer.h"
#include "Serial.h"
#include "App.h"
#include "atlconv.h"
#include <string>
#include <ctime>
#include <stdlib.h>
#include <iostream>


using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	soundmixer::mainWindow form;
	
	//std::cout << "Digite a porta serial(COM1, COM2..)" << endl;
	//std::cin >> COMPort;

	serialCon = new Serial(COMPort);
	Mixer m;

	std::clock_t start;
	start = std::clock();
	float currTime = 0;
	//std::cout << "Starting.." << endl;
	double oldVol = 0.99;
	while (0) {
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
		currTime = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
		serialCon->readSerial(buffer, 3);
		if (currTime > 1000) {
			double vol = atoi(buffer) / 100.0;
			if (oldVol == vol) {
				std::cout << "oi: " << oldVol * 100 << endl;
			}
			else if (abs(vol - oldVol) < (0.2)) {
				std::cout << "Volume: " << abs(vol - oldVol) << endl;
				m.SetMasterVolume(vol, true);
			}
			oldVol = vol;
		}
		
	}
	//
	//std::cout << m.SetMuteApplication(processName,true);
	

	Application::Run(%form);
}

void soundmixer::mainWindow::setComPort(std::string inputPort)
{
	strcpy(COMPort, inputPort.c_str());
}
