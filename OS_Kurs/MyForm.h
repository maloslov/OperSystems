#pragma once
#include <winsock.h>

#define MAX_CLIENTS 10
#define MAX_BUFFER 1024
#define REQUESTDATA "Запрос данных"
#define REQUESTSHUTDOWN "Завершение работы"

namespace Forma {

	enum State { Empty, Server1, Server2, Shut, Client };

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace std;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	protected:
		State state = State::Empty;
		static String^ message = "";
		Socket^ socket; 
		IPAddress^ ipAddr;
		IPEndPoint^ ipEndPoint;
		List<Thread^>^ t = gcnew List<Thread^>();
		List<Socket^>^ clients = gcnew List<Socket^>();
		Mutex^ mutex = gcnew Mutex();
	private: System::Windows::Forms::Button^ Clear1;
	private: System::Windows::Forms::TextBox^ portBox;
	protected:
	private: System::Windows::Forms::Button^ Clear2;


	protected:
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
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ shutdown1;
	private: System::Windows::Forms::Button^ setup1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ serverLog;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ disconBtn;
	private: System::Windows::Forms::Button^ connectBtn;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::ComboBox^ serverBox;
	private: System::Windows::Forms::ComboBox^ commandBox;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ sendBtn;
	private: System::Windows::Forms::TextBox^ clientLog;
	private: System::ComponentModel::IContainer^ components;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		/// 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->serverBox = (gcnew System::Windows::Forms::ComboBox());
			this->commandBox = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->Clear1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->serverLog = (gcnew System::Windows::Forms::TextBox());
			this->shutdown1 = (gcnew System::Windows::Forms::Button());
			this->setup1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->portBox = (gcnew System::Windows::Forms::TextBox());
			this->Clear2 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->sendBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->clientLog = (gcnew System::Windows::Forms::TextBox());
			this->disconBtn = (gcnew System::Windows::Forms::Button());
			this->connectBtn = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// serverBox
			// 
			this->serverBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->serverBox->BackColor = System::Drawing::SystemColors::Window;
			this->serverBox->ForeColor = System::Drawing::SystemColors::InfoText;
			this->serverBox->FormattingEnabled = true;
			this->serverBox->Location = System::Drawing::Point(3, 23);
			this->serverBox->Name = L"serverBox";
			this->serverBox->Size = System::Drawing::Size(121, 21);
			this->serverBox->Sorted = true;
			this->serverBox->TabIndex = 0;
			this->toolTip1->SetToolTip(this->serverBox, L"Выберите подключенный сервер для отправки запроса.\r\nЕсли поле пустое, то клиент о"
				L"тправит запрос всем подключениям.");
			this->serverBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::comboBox1_KeyPress);
			// 
			// commandBox
			// 
			this->commandBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->commandBox->BackColor = System::Drawing::SystemColors::Window;
			this->commandBox->ForeColor = System::Drawing::SystemColors::InfoText;
			this->commandBox->FormattingEnabled = true;
			this->commandBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Завершение работы", L"Запрос данных" });
			this->commandBox->Location = System::Drawing::Point(130, 23);
			this->commandBox->Name = L"commandBox";
			this->commandBox->Size = System::Drawing::Size(172, 21);
			this->commandBox->Sorted = true;
			this->commandBox->TabIndex = 1;
			this->commandBox->Text = L"Запрос данных";
			this->toolTip1->SetToolTip(this->commandBox, L"Выберите команду для запроса у сервера");
			this->commandBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::comboBox1_KeyPress);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Процесс 1", L"Процесс 2" });
			this->comboBox1->Location = System::Drawing::Point(48, 7);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(99, 21);
			this->comboBox1->TabIndex = 1;
			this->comboBox1->Text = L"Процесс 1";
			this->toolTip1->SetToolTip(this->comboBox1, L"Процесс 1 собирает информацию:\r\n- имя компьютера\r\n- имя пользователя\r\n- версия ОС"
				L" \r\nПроцесс 2 собирает информацию:\r\n- процент физической памяти\r\n- процент виртуа"
				L"льной памяти");
			this->comboBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::comboBox1_KeyPress);
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(2, 4);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(533, 417);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->Clear1);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Controls->Add(this->shutdown1);
			this->tabPage1->Controls->Add(this->setup1);
			this->tabPage1->Controls->Add(this->comboBox1);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(525, 391);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Сервер";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// Clear1
			// 
			this->Clear1->Location = System::Drawing::Point(446, 7);
			this->Clear1->Name = L"Clear1";
			this->Clear1->Size = System::Drawing::Size(75, 21);
			this->Clear1->TabIndex = 5;
			this->Clear1->Text = L"Очистить";
			this->Clear1->UseVisualStyleBackColor = true;
			this->Clear1->Click += gcnew System::EventHandler(this, &MyForm::Clear1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->serverLog);
			this->groupBox1->Location = System::Drawing::Point(3, 35);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(519, 353);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Лог сервера";
			// 
			// serverLog
			// 
			this->serverLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->serverLog->Location = System::Drawing::Point(7, 20);
			this->serverLog->Multiline = true;
			this->serverLog->Name = L"serverLog";
			this->serverLog->ReadOnly = true;
			this->serverLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->serverLog->Size = System::Drawing::Size(506, 327);
			this->serverLog->TabIndex = 0;
			// 
			// shutdown1
			// 
			this->shutdown1->Enabled = false;
			this->shutdown1->Location = System::Drawing::Point(305, 7);
			this->shutdown1->Name = L"shutdown1";
			this->shutdown1->Size = System::Drawing::Size(134, 21);
			this->shutdown1->TabIndex = 3;
			this->shutdown1->Text = L"Выключение сервера";
			this->shutdown1->UseVisualStyleBackColor = true;
			this->shutdown1->Click += gcnew System::EventHandler(this, &MyForm::shutdown1_Click);
			// 
			// setup1
			// 
			this->setup1->Location = System::Drawing::Point(153, 7);
			this->setup1->Name = L"setup1";
			this->setup1->Size = System::Drawing::Size(146, 21);
			this->setup1->TabIndex = 2;
			this->setup1->Text = L"Запуск сервера";
			this->setup1->UseVisualStyleBackColor = true;
			this->setup1->Click += gcnew System::EventHandler(this, &MyForm::setup1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Тип:";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->portBox);
			this->tabPage2->Controls->Add(this->Clear2);
			this->tabPage2->Controls->Add(this->groupBox4);
			this->tabPage2->Controls->Add(this->groupBox2);
			this->tabPage2->Controls->Add(this->disconBtn);
			this->tabPage2->Controls->Add(this->connectBtn);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(525, 391);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Клиент";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// portBox
			// 
			this->portBox->Location = System::Drawing::Point(48, 8);
			this->portBox->MaxLength = 6;
			this->portBox->Name = L"portBox";
			this->portBox->Size = System::Drawing::Size(76, 20);
			this->portBox->TabIndex = 1;
			this->portBox->Text = L"11000";
			// 
			// Clear2
			// 
			this->Clear2->Location = System::Drawing::Point(445, 7);
			this->Clear2->Name = L"Clear2";
			this->Clear2->Size = System::Drawing::Size(75, 20);
			this->Clear2->TabIndex = 7;
			this->Clear2->Text = L"Очистить";
			this->Clear2->UseVisualStyleBackColor = true;
			this->Clear2->Click += gcnew System::EventHandler(this, &MyForm::Clear2_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox4->Controls->Add(this->tableLayoutPanel1);
			this->groupBox4->Location = System::Drawing::Point(5, 299);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(517, 86);
			this->groupBox4->TabIndex = 5;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Команда серверу";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 3;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				25)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				40)));
			this->tableLayoutPanel1->Controls->Add(this->label4, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->serverBox, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->commandBox, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->label5, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->sendBtn, 2, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(3, 19);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 43)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(511, 61);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(80, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Порт сервера:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(130, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(99, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Команда серверу:";
			// 
			// sendBtn
			// 
			this->sendBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->sendBtn->BackColor = System::Drawing::Color::Transparent;
			this->sendBtn->Location = System::Drawing::Point(308, 23);
			this->sendBtn->Name = L"sendBtn";
			this->sendBtn->Size = System::Drawing::Size(200, 37);
			this->sendBtn->TabIndex = 2;
			this->sendBtn->Text = L"Отправить запрос";
			this->sendBtn->UseVisualStyleBackColor = false;
			this->sendBtn->Click += gcnew System::EventHandler(this, &MyForm::sendBtn_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->clientLog);
			this->groupBox2->Location = System::Drawing::Point(7, 36);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(512, 257);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Лог клиента";
			// 
			// clientLog
			// 
			this->clientLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->clientLog->Location = System::Drawing::Point(6, 19);
			this->clientLog->Multiline = true;
			this->clientLog->Name = L"clientLog";
			this->clientLog->ReadOnly = true;
			this->clientLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->clientLog->Size = System::Drawing::Size(499, 231);
			this->clientLog->TabIndex = 0;
			// 
			// disconBtn
			// 
			this->disconBtn->Enabled = false;
			this->disconBtn->Location = System::Drawing::Point(298, 7);
			this->disconBtn->Name = L"disconBtn";
			this->disconBtn->Size = System::Drawing::Size(144, 20);
			this->disconBtn->TabIndex = 3;
			this->disconBtn->Text = L"Отключиться от сервера";
			this->disconBtn->UseVisualStyleBackColor = true;
			this->disconBtn->Click += gcnew System::EventHandler(this, &MyForm::disconBtn_Click);
			// 
			// connectBtn
			// 
			this->connectBtn->Location = System::Drawing::Point(130, 7);
			this->connectBtn->Name = L"connectBtn";
			this->connectBtn->Size = System::Drawing::Size(162, 20);
			this->connectBtn->TabIndex = 2;
			this->connectBtn->Text = L"Подключиться к серверу";
			this->connectBtn->UseVisualStyleBackColor = true;
			this->connectBtn->Click += gcnew System::EventHandler(this, &MyForm::connectBtn_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Порт:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(538, 427);
			this->Controls->Add(this->tabControl1);
			this->Name = L"MyForm";
			this->Text = L"ОС Курсовая работа \"Межпроцессорное взаимодействие\"";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void comboBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		e->Handled = true;
	}



#pragma region Server

	private: System::Void serverEntry(int port)
	{
		//инициализация сокета
		ipAddr = Dns::GetHostEntry("localhost")->AddressList[0]; 
		ipEndPoint = gcnew IPEndPoint(ipAddr, port);
		socket = gcnew Socket(ipAddr->AddressFamily, 
			SocketType::Stream, ProtocolType::Tcp);

		try
		{
			socket->Bind(ipEndPoint);
			socket->Listen(MAX_CLIENTS);
			
			serverLog->AppendText(DateTime::Now + " - " +
				"Сервер " + socket->LocalEndPoint->ToString()->Split(':')[3] +
				" начинает работу как " + comboBox1->Text + "\r\n");

			comboBox1->Enabled = false;
			if (comboBox1->Text->Equals("Процесс 1"))
				state = State::Server1;
			else state = State::Server2;

				//запуск потоков для подключения
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					t->Add(gcnew Thread(gcnew Threading::ThreadStart(this, &MyForm::Getmsg)));
					t[i]->Name = "Поток " + i;
					clients->Add(socket);
					t[i]->Start();
				}

			timer1->Start();
		}
		catch (SocketException^ e)
		{
			if (e->SocketErrorCode == SocketError::AddressAlreadyInUse)
				serverEntry(port + 1);
		}
	}

	private: void Getmsg()
	{
		int n = 
			Convert::ToInt32(Thread::CurrentThread->Name->Split(' ')[1]);
		try
		{
			//создание сокета для соединения с клиентом
			Socket^ client = socket->Accept();

			mutex->WaitOne();
			clients[n] = client;
			message += (DateTime::Now + " - " +
				Thread::CurrentThread->Name +
				" принял соединение от " +
				client->RemoteEndPoint->ToString()->Split(':')[3] + "\r\n");
			mutex->ReleaseMutex();

			Begin:
			String^ request = "";
			// Мы дождались клиента, пытающегося с нами соединиться
			cli::array<unsigned char>^ bytes = 
				gcnew cli::array<unsigned char>(MAX_BUFFER);
			//Получаем байты и декодируем их
			int bytesRec = client->Receive(bytes);
			System::Text::UTF8Encoding^ encoder = gcnew System::Text::UTF8Encoding;
			request += encoder->GetString(bytes, 0, bytesRec);

			// Показываем данные
			mutex->WaitOne();
			message += (DateTime::Now + " - " +
				Thread::CurrentThread->Name +
				" получил запрос от " +
				client->RemoteEndPoint->ToString()->Split(':')[3] + ": " +
				request + "\r\n");
			mutex->ReleaseMutex();

			// Отправляем ответ клиенту
			String^ response = "";
			int sh = 0; //переменная для завершения подключения или сервера
			
			if (request->Contains(REQUESTDATA)) {
				if (state == State::Server1)
					response += GetData1();
				else response += GetData2();
				sh = 1;
			}
			else if (request->Contains(REQUESTSHUTDOWN)) {
				response += "Сервер " + ipEndPoint->Port +
					" завершил работу\r\n";
				sh = 2;
			}
			else  response += "Неверный запрос!";

			cli::array<unsigned char>^ msg = 
				System::Text::Encoding::UTF8->GetBytes(response);
			client->Send(msg);
			if(sh != 2)
				goto Begin;

			mutex->WaitOne();
			message += (DateTime::Now + " - " +
				Thread::CurrentThread->Name +
				" завершил соединение с клиентом " +
				client->RemoteEndPoint->ToString()->Split(':')[3] + "\r\n");
			if(sh==2) state = State::Shut;
			mutex->ReleaseMutex();
		}
		catch (SocketException^ se)
		{
			if (se->SocketErrorCode == 
				SocketError::ConnectionReset
				|| se->SocketErrorCode == 
				SocketError::ConnectionAborted)
			{
				mutex->WaitOne();
				message += DateTime::Now + " - " +
					Thread::CurrentThread->Name +
					" соединение разорвано\r\n";
				mutex->ReleaseMutex();
				return;
			} 

		}
		catch (ThreadInterruptedException^){}
		if (shutdown1->Enabled)
		{
			mutex->WaitOne();
			clients[n]->Shutdown(SocketShutdown::Both);
			clients[n]->Close();
			mutex->ReleaseMutex();
		}
	}


	private: System::Void setup1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (comboBox1->Text == "")
			return;
		setup1->Enabled = false;
		connectBtn->Enabled = false;
		disconBtn->Enabled = false;
		shutdown1->Enabled = true;
		comboBox1->Enabled = false;
		sendBtn->Enabled = false;
		serverEntry(11000);
	}

	private: System::Void shutdown1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		sendBtn->Enabled = true;
		setup1->Enabled = true;
		connectBtn->Enabled = true;
		disconBtn->Enabled = true;
		shutdown1->Enabled = false;
		comboBox1->Enabled = true; 
	}
		   //получение данных для процесса 1
		   String^ GetData1() {
			   return ("Machine name: " +
				   Environment::MachineName + " | " +
				   "User name: "+Environment::UserName + " | " +
				   "OS version: " + Environment::OSVersion + " | " +
				   "Is OS x64: " + Environment::Is64BitOperatingSystem);
		   }
		   //прлучение данных для процесса 2
		   String^ GetData2() {
			   MEMORYSTATUSEX M;
			   M.dwLength = sizeof(M);
			   GlobalMemoryStatusEx(&M);
			   String^ str = "Physmem total= " +
				   Convert::ToInt64(M.ullTotalPhys/1024L)
				   +" kBytes | Virtmem total= "+
				   Convert::ToInt64(M.ullTotalVirtual/1024L)
				   +" kBytes";
			   Diagnostics::Process^ p = 
				   Diagnostics::Process::GetCurrentProcess();
			   p->Refresh();
			   double p1 = (static_cast<double>(p->WorkingSet64)
				   / static_cast<double>(M.ullTotalPhys) * 100);
			   double p2 = (static_cast<double>(p->VirtualMemorySize64) 
				   / static_cast<double>(M.ullTotalVirtual) * 100);
			   str += " | Physmem current= " + (p->WorkingSet64/1024L)
				   + " kBytes | Virtmem curent= " + 
				   (p->VirtualMemorySize64/1024L)
				   + " kBytes | Physmem percent= " + p1 +
				   "% | Virtmem percent= " + p2 + "%";
			   return str;
		   }
#pragma endregion

#pragma region Client

	private: System::Void connectBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (state != State::Client)
			clients = gcnew List<Socket^>();
		state = State::Client;
		setup1->Enabled = false;
		sendBtn->Enabled = true;
		disconBtn->Enabled = true;
		int port;
		try {
			port = Convert::ToInt32(portBox->Text);
		}
		catch (FormatException^)
		{
			MessageBox::Show("Неверный формат!",
				"Внимание",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}
		//проверка порта
		ipAddr = Dns::GetHostEntry("localhost")->AddressList[0];
		ipEndPoint = gcnew IPEndPoint(ipAddr, port);
		if (serverBox->Items->Contains(ipEndPoint->Port.ToString()))
		{
			MessageBox::Show("Соединение с этим сервером уже установлено!", 
				"Внимание", MessageBoxButtons::OK, 
				MessageBoxIcon::Information);
			return;
		}

		//создание сокета
		IPEndPoint^ ep = ipEndPoint;
		Socket^ s = gcnew Socket(ep->AddressFamily, 
			SocketType::Stream, ProtocolType::Tcp);

		String^ str;
		try
		{
			//соединение с сервером
			s->Connect(ep);
			str = s->RemoteEndPoint->ToString()->Split(':')[3];
		}
		catch (SocketException^ se)
		{
			if (se->SocketErrorCode == SocketError::ConnectionRefused)
				clientLog->AppendText(DateTime::Now + " - Cервер " 
					+ ep->Port + " отказал в соединении\r\n");
			return;
		}
		serverBox->Items->Add(str);
		clients->Add(s);
		serverBox->Text = str;
		clientLog->AppendText(DateTime::Now + 
			" - Клиент подключился к серверу с портом " + str + "\r\n");
	}

	private: System::Void disconBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		state = State::Empty;
		sendBtn->Enabled = false;
		disconBtn->Enabled = false;
		setup1->Enabled = true;
		serverBox->Items->Clear();
		serverBox->Text = "";
		t->Clear();
		for (int i = 0; i < clients->Count; i++) {
			clients[i]->Shutdown(SocketShutdown::Both);
			clients[i]->Close();
		}
		clients->Clear();
		serverBox->Items->Clear();
	}

	private: System::Void sendBtn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (serverBox->Text == "" || commandBox->Text == "")
			return;
		if (!serverBox->Items->Contains(serverBox->Text))
			return;

		message = serverBox->Text;
		socket = clients->Find(gcnew Predicate<Socket^>(FindPredicate));

		//кодирование сообщения
		System::Text::UTF8Encoding^ encoder = 
			gcnew System::Text::UTF8Encoding;
		cli::array<unsigned char>^ bytes = 
			encoder->GetBytes(commandBox->Text);
		try {
			//попытка отправления
			socket->Send(bytes);
			
			bytes =
				gcnew cli::array<unsigned char>(MAX_BUFFER);
			message = "";
			//прием сообщения и декодирование
			int bytesrec = socket->Receive(bytes);
			socket->Blocking = true;
			message += encoder->GetString(bytes, 0, bytesrec);
			clientLog->AppendText(DateTime::Now + 
				" - Ответ сервера: \r\n" + message + "\r\n");
			message = "";
			if (commandBox->Text->Equals("Завершение работы")) {
				serverBox->Items->Remove(socket->RemoteEndPoint->ToString()->Split(':')[3]);
				clients->Remove(socket);
				socket->Shutdown(SocketShutdown::Both);
				socket->Close();
			}
		}
		catch (SocketException^ se) {
			if(se->SocketErrorCode == SocketError::ConnectionAborted 
				|| se->SocketErrorCode == SocketError::ConnectionReset)
			clientLog->AppendText(DateTime::Now + " - Сервер "
				+ socket->RemoteEndPoint->ToString()->Split(':')[3]
				+ " недоступен\r\n");
			serverBox->Items->Remove(socket->RemoteEndPoint->ToString()->Split(':')[3]);
			clients->Remove(socket);
			socket->Shutdown(SocketShutdown::Both);
			socket->Close();
		}
	}
		   private: static bool FindPredicate(Socket^ o) {
			   return (o->RemoteEndPoint->ToString()->Split(':')[3]->Equals(message));
		   }
#pragma endregion

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		switch (state)
		{
		case State::Shut:
			serverLog->AppendText(message);
			setup1->Enabled = true;
			connectBtn->Enabled = true;
			disconBtn->Enabled = true;
			shutdown1->Enabled = false;
			comboBox1->Enabled = true;
		case State::Server1:
		case State::Server2:
		{
			if (!shutdown1->Enabled)
			{
				//завершение потоков
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					t[i]->Interrupt();
				}
				serverLog->Text += DateTime::Now + " - " +
					"Сервер " + ipEndPoint->Port +
					" завершил работу\r\n";
				message = "";
				t->Clear();
				clients->Clear();
				socket->Close();
				timer1->Stop();
				state = State::Empty;
			}
			else
			{
				serverLog->Text += message;
				message = "";
				//возобновление завершенных потоков
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (!t[i]->IsAlive)
					{
						t[i] = gcnew Thread(gcnew ThreadStart(this, &MyForm::Getmsg));
						t[i]->Name = "Поток " + i;
						t[i]->Start();
						message += (DateTime::Now + " - " +
							t[i]->Name +
							" отключается и ожидает соединение\r\n");
					}
				}
			}
			break;
		case State::Client:
			for (int i = 0; i < clients->Count; i++) {
				if (!clients[i]->Connected)
					clients[i]->Close();				
			}
			break;
		}
		}
	}

	private: System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		switch (state) {
		case State::Server1:
		case State::Server2: {
			shutdown1_Click(sender, e);
			timer1_Tick(sender, e);
			break;
		}
		case State::Client: {
			disconBtn_Click(sender, e);
			timer1_Tick(sender, e);
			break;
		}
		}
	}
private: System::Void Clear1_Click(System::Object^ sender, System::EventArgs^ e) {
	serverLog->Clear();
}
private: System::Void Clear2_Click(System::Object^ sender, System::EventArgs^ e) {
	clientLog->Clear();
}
};
}
