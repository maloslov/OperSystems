#pragma once
#define _CRT_SECURE_NO_WARNINGS
//#include <winnt.h>
#include <iostream>
#include <Windows.h>
#include <shlwapi.h>
#include <tlhelp32.h>
#include <fstream>
#include <string>
#include <string>
//using namespace std;
#pragma comment(lib, "Shlwapi.lib")

namespace Forma {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
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
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				100)));
			this->tableLayoutPanel1->Controls->Add(this->button1, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(4, 4);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 86.37602F)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 13.62398F)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(441, 367);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(3, 320);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(435, 44);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Выполнить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				33.33333F)));
			this->tableLayoutPanel2->Controls->Add(this->textBox1, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->textBox2, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->textBox3, 2, 1);
			this->tableLayoutPanel2->Controls->Add(this->label1, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->label2, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->label3, 2, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 9.996785F)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 90.00321F)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(435, 311);
			this->tableLayoutPanel2->TabIndex = 1;
			// 
			// textBox1
			// 
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->BackColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(3, 34);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(138, 274);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->BackColor = System::Drawing::SystemColors::Window;
			this->textBox2->Location = System::Drawing::Point(147, 34);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox2->Size = System::Drawing::Size(138, 274);
			this->textBox2->TabIndex = 1;
			// 
			// textBox3
			// 
			this->textBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox3->BackColor = System::Drawing::SystemColors::Window;
			this->textBox3->Location = System::Drawing::Point(291, 34);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox3->Size = System::Drawing::Size(141, 274);
			this->textBox3->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Часть 1:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(147, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(50, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Часть 2:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(291, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Часть 3:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(457, 383);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		textBox1->Clear();
		textBox2->Clear();
		textBox3->Clear();
		doPart1(textBox1);
		doPart2(textBox2);
		doPart3(textBox3);
	}

	private: void doPart1(TextBox^ text) {

	}

	private: void doPart2(TextBox^ text) {

		DWORD pID = GetCurrentProcessId(); // Создаем для записи для идентификатора процесса
		HANDLE handle = GetCurrentProcess(); // Создаем для записи псевдодескриптора процесса
		HANDLE handleD, openProcess; // Создаем для записи дескриптора текущего процесса
		if (!DuplicateHandle(GetCurrentProcess(), handle, GetCurrentProcess(), &handleD, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
			//std::cout << "Failed to duplicate" << std::endl;
			MessageBox::Show("Duplication failed!", "Error");
		}

		//string *str;
		//str = &handle;
		
		text->Text = "\r\nID Процесса: " + pID 
			+ "\r\nПсевдодескриптор: " + (String)&handle;
		//std::cout << "Process Id: " << pID << "\nPseudo Descriptor: " << handle << std::endl;
		openProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, pID); // определяем копию дескриптора текущего процесса
		//std::cout << "Duplicate handle: " << handleD << "\nOpenProcess descriptor: " << openProcess << std::endl;
		text->Text += "\r\nДупликат HANDLE: " + ((char)handleD) 
			+ "\r\nДескриптор OpenProcess: " + ((char)openProcess);
		// закрываем дескрипторы
		CloseHandle(handleD);
		CloseHandle(openProcess);

	}

	private: void doPart3(TextBox^ text) {

	}
};
}
