#pragma once
#include <Windows.h>
#include <WinBase.h>


namespace Forma {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(2, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(278, 69);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(2, 79);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(278, 179);
			this->textBox1->TabIndex = 1;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//part 1
		textBox1->AppendText("\r\nPC name: " + getPCName() +"\r\nUsername: " + getUsername() + "\r\n");
		//part 2 

		OperatingSystem^ os = Environment::OSVersion;
		textBox1->AppendText("\r\nOS version: " + os->ToString() 
			+"\r\n");
		//part 3
		textBox1->AppendText("Directories: \r\n" +
			getSysDir() + "\r\n" + getWinDir() + "\r\n" + getTPath());
		//part 4
		MOUSEKEYS mouse;
		mouse.cbSize = sizeof(MOUSEKEYS);
		SystemParametersInfoA(SPI_GETMOUSEKEYS, sizeof(MOUSEKEYS), &mouse, 0);
		int fh; 
		ACCESSTIMEOUT fw;
		fw.cbSize = sizeof(ACCESSTIMEOUT);
		SystemParametersInfoA(SPI_GETSCREENSAVETIMEOUT , 0, &fh, 0);
		SystemParametersInfoA(SPI_GETACCESSTIMEOUT, sizeof(ACCESSTIMEOUT), &fw, 0);
		textBox1->AppendText("\r\nParams:\r\nMouse maxspeed: "
			+ mouse.iMaxSpeed
			+"\r\nScreenSaveTimeout: "+fh+"\r\nACCESS TIMEOUT: "+fw.iTimeOutMSec);
		//part 5
		long color = getColor(COLOR_WINDOWTEXT);
		textBox1->AppendText("\r\nColor: " + 
		GetRValue(color)+"|"+ GetGValue(color)+"|"+GetBValue(color));
		char clr[3];
		Random^ rnd = gcnew Random();
		for (int i = 0; i < 3; i++)
			clr[i] = rnd->Next(255);

		setColor(COLOR_WINDOWTEXT, RGB(clr[0], clr[1], clr[2]));
		//part 6
		textBox1->AppendText("\r\nTime: " + getTime() + "\r\n");
		textBox1->AppendText("GetMessageTime: " + GetMessageTime() + "\r\n");
		//part 7
		textBox1->AppendText("Current directory: " + getDir() + "\r\n");
		textBox1->AppendText("Battery Life percent: " + getBLP() + "\r\n");
		textBox1->AppendText("Maximum processor count: " + getCount() + "\r\n");
		textBox1->AppendText("Number of event log records: " + getLogNumbers() + "\r\n");

	}
		   String^ getLogNumbers() {
			   HANDLE log;
			   DWORD word;
			   GetNumberOfEventLogRecords(log,&word);
			   long res = word;
			   return res.ToString();
		   }
		   String^ getCount() {
			   long res = GetMaximumProcessorCount(0);
			   String^ str = res.ToString();
			   return str;
		   }

		   String^ getBLP() {
			   SYSTEM_POWER_STATUS sps;
			   GetSystemPowerStatus(&sps);
			   String^ str = Convert::ToString(sps.BatteryLifePercent);
			   return str;
		   }

		   String^ getDir() {
			   char path[50];
			   DWORD size = sizeof(path);
			   GetCurrentDirectoryA(size, path);
			   String^ str;
			   for (int i = 0; i < sizeof(path); i++) {
				   if (path[i] == '\0')
					   break;
				   str += Convert::ToChar(path[i]);
			   }
			   return str;
		   }
		   String^ getTime() {
			   SYSTEMTIME st;
			   GetSystemTime(&st);
			   return (String^)(st.wDay + "/" + st.wMonth + "/" + st.wYear
				   + "\r\n\t" + st.wHour + ":" + st.wMinute + ":" + st.wSecond);
		   }

		   long getColor(int index) {
			   DWORD res = 
			   GetSysColor(index);
			   return res;
			}
		   void setColor(int index, long color) {
			   DWORD set = color;
			   
			   SetSysColors(1,&index,&set);
		   }
		   
	String^ getPCName() {
		char name[20];
		DWORD nSize = sizeof(name);
		GetComputerNameA(name, &nSize);
		String^ str;
		for (int i = 0; i < nSize; i++) {
			str += Convert::ToChar(name[i]);
		}
		return str;
	}
	String^ getUsername() {
		char name[20];
		DWORD nSize = sizeof(name);
		GetUserNameA((char*)name, &nSize);
		String^ str;
		for (int i = 0; i < nSize; i++) {
			str += Convert::ToChar(name[i]);
		}
		return str;
	}

	/*
	OSVERSIONINFOW getVOS() {
		OSVERSIONINFOW osvi;
		//VerifyVersionInfo();
		//memset(&osvi, 0, sizeof(OSVERSIONINFOW));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
		//GetVersionExW(&osvi);
		return osvi;
	}
	*/

	String^ getSysDir() {
		char path[50];
		int size = sizeof(path);
		GetSystemDirectoryA(path, size);
		String^ str;
		for (int i = 0; i < sizeof(path); i++) {
			if (path[i] == '\0')
				break;
			str += Convert::ToChar(path[i]);
		}
		return str;
	}
	String^ getWinDir() {
		char path[50];
		int size = sizeof(path);
		GetWindowsDirectoryA(path, size);
		String^ str;
		for (int i = 0; i < size; i++) {
			if (path[i] == '\0')
				break;
			str += Convert::ToChar(path[i]);
		}
		return str;
	}
	String^ getTPath() {
		char path[50];
		int size = sizeof(path);
		GetTempPathA(size, path);
		String^ str;
		for (int i = 0; i < sizeof(path); i++) {
			if (path[i] == '\0')
				break;
			str += Convert::ToChar(path[i]);
		}
		return str;
	}

	String^ getMetric(int index) {
		return Convert::ToString(GetSystemMetrics(index));
	}
	};
}
