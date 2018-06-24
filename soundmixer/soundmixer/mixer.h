#pragma once
#include <windows.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <string>
#include <Audiopolicy.h>
#include <comdef.h>
#include <comip.h>
#include <tchar.h>
#include <psapi.h>
#include <vector>


using namespace std;
ref class Mixer

{
	public:
		Mixer();
		double SetMasterVolume(double nVolume, bool bScalar);
		double SetMuteMaster(bool bMute);
		bool GetMuteMaster();
		double GetMasterVolume(bool bScalar);

		float GetApplicationVolume(TCHAR *app);
		int SetApplicationVolume(TCHAR *app, float v);
		BOOL GetMuteApplication(TCHAR *app);
		int SetMuteApplication(TCHAR *app, BOOL pbMute);
		vector<string> GetOpenApplicationsList();
	};

