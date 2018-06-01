#include "mainWindow.h"
#include "Mixer.h"
#include "Serial.h"
#include "App.h"

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
	/*Serial s("COM3");
	char buffer[10];
	while (1) {
		strcpy(buffer, "empt");
		s.readSerial(buffer, 4);
		buffer[4] = '\0';
		if (!strcmp(buffer, "tmut")) {
			if (m.GetMuteMasterVolume() == true)
				m.SetMuteMasterVolume(false);
			else if (m.GetMuteMasterVolume() == false)
				m.SetMuteMasterVolume(true);
		}
	}*/
	double vol = 0.25;
	//m.SetMasterVolume(vol, true);
	TCHAR processName[MAX_PATH] = TEXT("Steam.exe");

	std::cout << m.SetMuteApplication(processName,1);

	Application::Run(%form);
}

