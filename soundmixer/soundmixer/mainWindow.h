#pragma once
#include "Mixer.h"
#include "Serial.h"
#include "App.h"
#include "atlconv.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <CoreWindow.h>


char COMPort[32];
Serial *serialCon;
TCHAR processName[MAX_PATH] = TEXT("Empty.exe");
char buffer[20];
vector<string> appList;
TCHAR selectedApp[MAX_PATH] = TEXT("Empty.exe");
int ticksElapsed = 0;
double oldVol = 0.99;

namespace soundmixer {

	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for mainWindow
	/// </summary>
	public ref class mainWindow : public System::Windows::Forms::Form
	{
	public:
		mainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		void setComPort(std::string inputPort);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox2;

	private: System::Windows::Forms::ListBox^  listBox1;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::Windows::Forms::Label^  label6;
	private: System::ComponentModel::IContainer^  components;



	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 144);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Application";
			this->label1->Click += gcnew System::EventHandler(this, &mainWindow::label1_Click);
			// 
			// button1
			// 
			this->button1->Enabled = false;
			this->button1->Location = System::Drawing::Point(12, 313);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Refresh List";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &mainWindow::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 81);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"COM Port";
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6" });
			this->comboBox2->Location = System::Drawing::Point(12, 97);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 6;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &mainWindow::comboBox2_SelectedIndexChanged);
			// 
			// listBox1
			// 
			this->listBox1->Enabled = false;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"noapplication" });
			this->listBox1->Location = System::Drawing::Point(12, 160);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(154, 147);
			this->listBox1->TabIndex = 8;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &mainWindow::listBox1_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(172, 160);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(22, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"X%\r\n";
			this->label3->Click += gcnew System::EventHandler(this, &mainWindow::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(172, 144);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 13);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Volume";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 121);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(135, 13);
			this->label5->TabIndex = 12;
			this->label5->Text = L"No port has been selected.";
			this->label5->Click += gcnew System::EventHandler(this, &mainWindow::label5_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &mainWindow::timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Tick += gcnew System::EventHandler(this, &mainWindow::timer2_Tick);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 9);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(239, 39);
			this->label6->TabIndex = 13;
			this->label6->Text = L"1. Plug in your soundmixer device.\r\n2. Select the COM Port that  your device is \r"
				L"\nplugged in. You can check it in Device Manager.";
			// 
			// mainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(264, 348);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"mainWindow";
			this->Text = L"Soundmixer";
			this->Load += gcnew System::EventHandler(this, &mainWindow::mainWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		ref class ManagedGlobals abstract sealed {
		public:
			static Mixer m;;
		};
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		appList = ManagedGlobals::m.GetOpenApplicationsList();
		listBox1->Items->Clear();
		for (int i = 0; i < appList.size();i++)
		{
			String^ strAux = gcnew String(appList[i].c_str());
			listBox1->Items->Add(strAux);
		}
	

		
	}
	private: System::Void comboBox2_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		
			Object^ selectedItem = comboBox2->SelectedItem;
			System::String^ s = selectedItem->ToString();
			setComPort(msclr::interop::marshal_as<std::string>(s));
			serialCon = new Serial(COMPort);

			if (serialCon->isConnected()) {
				label5->Text = "Device is connected successfully.";
				listBox1->Enabled = true;
				button1->Enabled = true;

				appList = ManagedGlobals::m.GetOpenApplicationsList();
				listBox1->Items->Clear();
				for (int i = 0; i < appList.size(); i++)
				{
					String^ strAux = gcnew String(appList[i].c_str());
					listBox1->Items->Add(strAux);
				}
			}
			else if (!serialCon->isConnected()) {
				label5->Text = "Error. Device is not connected to this COM Port.";
			}
			timer1->Start();
			timer2->Start();
			ticksElapsed = 0;
	}

	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		int ind = listBox1->SelectedIndex;
		strcpy(selectedApp,TEXT((TCHAR*)Marshal::StringToHGlobalAnsi(listBox1->Items[ind]->ToString()).ToPointer()));
		
	}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void mainWindow_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

		
	cout << serialCon->readSerial(buffer, 4) << endl;

	if (ticksElapsed > 10) {
		double vol = atoi(buffer) / 100.0;
		if (oldVol == vol) {
			std::cout << "Arduino sent: " << oldVol * 100 << endl;
		}
		else if (abs(vol - oldVol) < (0.2)) {
			std::cout << "Volume: " << abs(vol - oldVol) << endl;
			ManagedGlobals::m.SetApplicationVolume(selectedApp, vol);
		}
		oldVol = vol;
	}
	ticksElapsed++;
}
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
	String^ newtext;
	for (int i = 0; i < appList.size(); i++) {
		float v = ManagedGlobals::m.GetApplicationVolume(TEXT((TCHAR*)appList[i].c_str()));
		v = v * 100;

		newtext += gcnew String(to_string((int)v).c_str());
		newtext += "%\n";
	}
	label3->Text = newtext;
}
};
}
