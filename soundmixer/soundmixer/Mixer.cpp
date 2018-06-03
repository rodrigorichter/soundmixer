#include "Mixer.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
Mixer::Mixer() {

}

double Mixer::SetMasterVolume(double nVolume, bool bScalar) { // volume value from 0.0 to 1.0
	HRESULT hr = NULL;
	bool decibels = false;
	bool scalar = false;
	double newVolume = nVolume;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	// -------------------------
	float currentVolume = 0;
	endpointVolume->GetMasterVolumeLevel(&currentVolume);
	// printf("Current volume in dB is: %f\n", currentVolume);

	hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	//CString strCur=L"";
	//strCur.Format(L"%f",currentVolume);
	//AfxMessageBox(strCur);

	// printf("Current volume as a scalar is: %f\n", currentVolume);
	if (bScalar == false) {
		hr = endpointVolume->SetMasterVolumeLevel((float)newVolume, NULL);
		endpointVolume->GetMasterVolumeLevel(&currentVolume);
	}
	else if (bScalar == true) {
		hr = endpointVolume->SetMasterVolumeLevelScalar((float)newVolume, NULL);
		endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	}

	endpointVolume->Release();
	CoUninitialize();

	if (currentVolume == newVolume)
		return currentVolume;
	else
		return newVolume;
}

double Mixer::SetMuteMaster(bool bMute) {
	HRESULT hr = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	hr = endpointVolume->SetMute(bMute, NULL);

	endpointVolume->Release();
	CoUninitialize();
	return 0;
}

bool Mixer::GetMuteMaster() {
	HRESULT hr = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;
	BOOL bMute;
	hr = endpointVolume->GetMute(&bMute);

	endpointVolume->Release();
	CoUninitialize();
	return bMute;
}

double Mixer::GetMasterVolume(bool bScalar) { // volume value from 0.0 to 1.0
	HRESULT hr = NULL;
	bool decibels = false;
	bool scalar = false;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	IMMDeviceEnumerator *deviceEnumerator = NULL;
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
	IMMDevice *defaultDevice = NULL;

	hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
	deviceEnumerator->Release();
	deviceEnumerator = NULL;

	IAudioEndpointVolume *endpointVolume = NULL;
	hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume),
		CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
	defaultDevice->Release();
	defaultDevice = NULL;

	// -------------------------
	float currentVolume = 0;

	if (bScalar == false) {
		endpointVolume->GetMasterVolumeLevel(&currentVolume);
	}
	else if (bScalar == true) {
		endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
	}

	endpointVolume->Release();
	CoUninitialize();

	return currentVolume;
}

float Mixer::GetApplicationVolume(TCHAR *app) {
	static PROPERTYKEY key;

	GUID IDevice_FriendlyName = { 0xa45c254e, 0xdf1c, 0x4efd,{ 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } };
	key.pid = 14;
	key.fmtid = IDevice_FriendlyName;

	HRESULT hr = NULL;
	
	
	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioSessionControl* pSessionControl = NULL;
	IAudioSessionControl2* pSessionControl2 = NULL;
	IAudioSessionManager* pSessionManager = NULL;
	IAudioSessionManager2* pSessionManager2 = NULL;
	IAudioSessionEnumerator* pEnum = NULL;
	ISimpleAudioVolume* pVolume = NULL;

	LPWSTR sessionDisplayName = NULL;
	DWORD procId = NULL;
	IPropertyStore *pProps = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	
	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&pEnumerator);
	
	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager2);
	hr = pDevice->Activate(__uuidof(IAudioSessionManager), CLSCTX_ALL, NULL, (void**)&pSessionManager);

	hr = pSessionManager2->GetSessionEnumerator(&pEnum);

	int count;
	hr = pEnum->GetCount(&count);
	for (ULONG i = 0; i < count; i++) { // traverse through all open audio sessions
		// get audio session
		hr = pEnum->GetSession(i, &pSessionControl);
		hr = pSessionControl->QueryInterface(&pSessionControl2);

		// get process id of this session
		hr = pSessionControl2->GetProcessId(&procId);

		// find process name using its id
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, procId);
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
			}
		}
		
		
		//cout << "Session " << i << ": id:" << procId;
		_tprintf(TEXT(" name: %s\n"), szProcessName);

		CloseHandle(hProcess);

		if (_tcscmp(app, szProcessName) == 0) {
			pSessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pVolume);
			float v;
			pVolume->GetMasterVolume(&v);
			pVolume->Release();
			CoUninitialize();
			return v;
		}
	}

	return 0;
}

int Mixer::SetApplicationVolume(TCHAR *app, float v) {
	static PROPERTYKEY key;

	GUID IDevice_FriendlyName = { 0xa45c254e, 0xdf1c, 0x4efd,{ 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } };
	key.pid = 14;
	key.fmtid = IDevice_FriendlyName;

	HRESULT hr = NULL;


	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioSessionControl* pSessionControl = NULL;
	IAudioSessionControl2* pSessionControl2 = NULL;
	IAudioSessionManager* pSessionManager = NULL;
	IAudioSessionManager2* pSessionManager2 = NULL;
	IAudioSessionEnumerator* pEnum = NULL;
	ISimpleAudioVolume* pVolume = NULL;

	LPWSTR sessionDisplayName = NULL;
	DWORD procId = NULL;
	IPropertyStore *pProps = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&pEnumerator);

	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager2);
	hr = pDevice->Activate(__uuidof(IAudioSessionManager), CLSCTX_ALL, NULL, (void**)&pSessionManager);

	hr = pSessionManager2->GetSessionEnumerator(&pEnum);

	int count;
	hr = pEnum->GetCount(&count);
	for (ULONG i = 0; i < count; i++) { // traverse through all open audio sessions
										// get audio session
		hr = pEnum->GetSession(i, &pSessionControl);
		hr = pSessionControl->QueryInterface(&pSessionControl2);

		// get process id of this session
		hr = pSessionControl2->GetProcessId(&procId);

		// find process name using its id
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, procId);
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
			}
		}

		CloseHandle(hProcess);

		if (_tcscmp(app, szProcessName) == 0) {
			pSessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pVolume);
			pVolume->SetMasterVolume(v,NULL);
			pVolume->Release();
			CoUninitialize();
			return 0;
		}
	}

	return 0;
}

BOOL Mixer::GetMuteApplication(TCHAR *app) {
	static PROPERTYKEY key;

	GUID IDevice_FriendlyName = { 0xa45c254e, 0xdf1c, 0x4efd,{ 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } };
	key.pid = 14;
	key.fmtid = IDevice_FriendlyName;

	HRESULT hr = NULL;


	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioSessionControl* pSessionControl = NULL;
	IAudioSessionControl2* pSessionControl2 = NULL;
	IAudioSessionManager* pSessionManager = NULL;
	IAudioSessionManager2* pSessionManager2 = NULL;
	IAudioSessionEnumerator* pEnum = NULL;
	ISimpleAudioVolume* pVolume = NULL;

	LPWSTR sessionDisplayName = NULL;
	DWORD procId = NULL;
	IPropertyStore *pProps = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&pEnumerator);

	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager2);
	hr = pDevice->Activate(__uuidof(IAudioSessionManager), CLSCTX_ALL, NULL, (void**)&pSessionManager);

	hr = pSessionManager2->GetSessionEnumerator(&pEnum);

	int count;
	hr = pEnum->GetCount(&count);
	for (ULONG i = 0; i < count; i++) { // traverse through all open audio sessions
										// get audio session
		hr = pEnum->GetSession(i, &pSessionControl);
		hr = pSessionControl->QueryInterface(&pSessionControl2);

		// get process id of this session
		hr = pSessionControl2->GetProcessId(&procId);

		// find process name using its id
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, procId);
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
			}
		}


		//cout << "Session " << i << ": id:" << procId;
		_tprintf(TEXT(" name: %s\n"), szProcessName);

		CloseHandle(hProcess);

		if (_tcscmp(app, szProcessName) == 0) {
			pSessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pVolume);
			BOOL pbMute;
			pVolume->GetMute(&pbMute);

			pVolume->Release();
			CoUninitialize();
			return pbMute;
		}
	}

	return -1;
}

int Mixer::SetMuteApplication(TCHAR *app, BOOL pbMute) {
	static PROPERTYKEY key;

	GUID IDevice_FriendlyName = { 0xa45c254e, 0xdf1c, 0x4efd,{ 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0 } };
	key.pid = 14;
	key.fmtid = IDevice_FriendlyName;

	HRESULT hr = NULL;


	IMMDeviceEnumerator* pEnumerator = NULL;
	IMMDevice* pDevice = NULL;
	IAudioSessionControl* pSessionControl = NULL;
	IAudioSessionControl2* pSessionControl2 = NULL;
	IAudioSessionManager* pSessionManager = NULL;
	IAudioSessionManager2* pSessionManager2 = NULL;
	IAudioSessionEnumerator* pEnum = NULL;
	ISimpleAudioVolume* pVolume = NULL;

	LPWSTR sessionDisplayName = NULL;
	DWORD procId = NULL;
	IPropertyStore *pProps = NULL;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator), (LPVOID *)&pEnumerator);

	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	hr = pDevice->Activate(__uuidof(IAudioSessionManager2), CLSCTX_ALL, NULL, (void**)&pSessionManager2);
	hr = pDevice->Activate(__uuidof(IAudioSessionManager), CLSCTX_ALL, NULL, (void**)&pSessionManager);

	hr = pSessionManager2->GetSessionEnumerator(&pEnum);

	int count;
	hr = pEnum->GetCount(&count);
	for (ULONG i = 0; i < count; i++) { // traverse through all open audio sessions
										// get audio session
		hr = pEnum->GetSession(i, &pSessionControl);
		hr = pSessionControl->QueryInterface(&pSessionControl2);

		// get process id of this session
		hr = pSessionControl2->GetProcessId(&procId);

		// find process name using its id
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
			PROCESS_VM_READ,
			FALSE, procId);
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
			}
		}

		CloseHandle(hProcess);

		if (_tcscmp(app, szProcessName) == 0) {
			pSessionControl->QueryInterface(__uuidof(ISimpleAudioVolume), (void**)&pVolume);
			pVolume->SetMute(pbMute, NULL);
			pVolume->Release();
			CoUninitialize();
			return 0;
		}
	}

	return -1;
}