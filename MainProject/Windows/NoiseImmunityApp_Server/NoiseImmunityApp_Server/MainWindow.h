#pragma once

#include "ParamsWindow.h"
#include <stdlib.h>
#include "..\..\ClientServer\Server.h"
#include "..\..\ClientServer\ClientServerConst.h"

namespace NoiseImmunityAppServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainWindow
	/// </summary>
	public ref class MainWindowServer : public System::Windows::Forms::Form
	{
	public:
		/// ## Конструктор по умолчанию
		/// 
		/// В данном конструкторе инициализируются все компоненты формы, 
		/// блокируется кнопка изменения парметров среды,
		/// инициализируется объект класса сервера
		MainWindowServer(void)
		{
			AudioServer = new Server();
			InitializeComponent();
			ChangeParams->Enabled = false; 
		}

	protected:
		/// ## Деструктор
		///
		/// В данном деструкторе освобождаются все компоненты формы
		~MainWindowServer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ ChangeParams;
	private: System::Windows::Forms::Button^ Exit;
	private: System::Windows::Forms::Button^ StartServer;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanelMain;
	private: System::Windows::Forms::Label^ ServerData;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutDataConnect;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ IP;
	private: System::Windows::Forms::TextBox^ Port;
	private:
		String^ ip = DEFAULT_SERVER_IP; //айпи по умолчанию
		Server* AudioServer;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора, не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ChangeParams = (gcnew System::Windows::Forms::Button());
			this->Exit = (gcnew System::Windows::Forms::Button());
			this->StartServer = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanelMain = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->ServerData = (gcnew System::Windows::Forms::Label());
			
			this->flowLayoutDataConnect = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->IP = (gcnew System::Windows::Forms::TextBox());
			this->Port = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanelMain->SuspendLayout();
			
			this->flowLayoutDataConnect->SuspendLayout();
			this->SuspendLayout();
			// 
			// ChangeParams
			// 
			this->ChangeParams->BackColor = System::Drawing::Color::CornflowerBlue;
			this->ChangeParams->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ChangeParams->ForeColor = System::Drawing::Color::White;
			this->ChangeParams->Location = System::Drawing::Point(66, 295);
			this->ChangeParams->Name = L"ChangeParams";
			this->ChangeParams->Size = System::Drawing::Size(208, 87);
			this->ChangeParams->TabIndex = 0;
			this->ChangeParams->Text = L"Settings";
			this->ChangeParams->UseVisualStyleBackColor = false;
			this->ChangeParams->Click += gcnew System::EventHandler(this, &MainWindowServer::ChangeParams_Click);
			// 
			// Exit
			// 
			this->Exit->BackColor = System::Drawing::Color::Red;
			this->Exit->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Exit->ForeColor = System::Drawing::Color::White;
			this->Exit->Location = System::Drawing::Point(66, 415);
			this->Exit->Name = L"Exit";
			this->Exit->Size = System::Drawing::Size(208, 87);
			this->Exit->TabIndex = 1;
			this->Exit->Text = L"Exit";
			this->Exit->UseVisualStyleBackColor = false;
			this->Exit->Click += gcnew System::EventHandler(this, &MainWindowServer::Exit_Click);
			// 
			// StartServer
			// 
			this->StartServer->BackColor = System::Drawing::Color::Green;
			this->StartServer->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->StartServer->ForeColor = System::Drawing::Color::White;
			this->StartServer->Location = System::Drawing::Point(66, 180);
			this->StartServer->Name = L"StartServer";
			this->StartServer->Size = System::Drawing::Size(208, 87);
			this->StartServer->TabIndex = 2;
			this->StartServer->Text = L"Start server";
			this->StartServer->UseVisualStyleBackColor = false;
			this->StartServer->Click += gcnew System::EventHandler(this, &MainWindowServer::StartServer_Click);
			// 
			// flowLayoutPanelMain
			// 
			this->flowLayoutPanelMain->BackColor = System::Drawing::SystemColors::Control;
			this->flowLayoutPanelMain->Controls->Add(this->ServerData);
	
			this->flowLayoutPanelMain->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
			this->flowLayoutPanelMain->Location = System::Drawing::Point(448, 39);
			this->flowLayoutPanelMain->Name = L"flowLayoutPanelMain";
			this->flowLayoutPanelMain->Size = System::Drawing::Size(407, 517);
			this->flowLayoutPanelMain->TabIndex = 3;
			// 
			// flowLayoutDataConnect
			// 
			this->flowLayoutDataConnect->Controls->Add(this->label1);
			this->flowLayoutDataConnect->Controls->Add(this->IP);
			this->flowLayoutDataConnect->Controls->Add(this->Port);
			this->flowLayoutDataConnect->Location = System::Drawing::Point(44, 39);
			this->flowLayoutDataConnect->Name = L"flowLayoutDataConnect";
			this->flowLayoutDataConnect->Size = System::Drawing::Size(264, 109);
			this->flowLayoutDataConnect->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->label1->Location = System::Drawing::Point(3, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(208, 31);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Data for connect";
			// 
			// IP
			// 
			this->IP->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->IP->Location = System::Drawing::Point(3, 34);
			this->IP->Multiline = true;
			this->IP->Name = L"IP";
			this->IP->Size = System::Drawing::Size(249, 33);
			this->IP->TabIndex = 1;
			this->IP->Text = L"Enter IP...";
			this->IP->Enter += gcnew System::EventHandler(this, &MainWindowServer::IP_enter);
			this->IP->Leave += gcnew System::EventHandler(this, &MainWindowServer::IP_leave);
			IP->Text = ip;//отображаем айпи по умолчанию
			// 
			// Port
			// 
			this->Port->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Port->Location = System::Drawing::Point(3, 73);
			this->Port->Multiline = true;
			this->Port->Name = L"Port";
			this->Port->Size = System::Drawing::Size(249, 33);
			this->Port->TabIndex = 2;
			this->Port->Text = L"Enter Port...";
			this->Port->Enter += gcnew System::EventHandler(this, &MainWindowServer::Port_enter);
			this->Port->Leave += gcnew System::EventHandler(this, &MainWindowServer::Port_leave);
			String^ port = System::Convert::ToString(DEFAULT_SERVER_PORT);  //айпи по умолчанию
			Port->Text = port;  //отображаем айпи по умолчанию
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(345, 555);
			this->Controls->Add(this->flowLayoutPanelMain);
			this->Controls->Add(this->StartServer);
			this->Controls->Add(this->Exit);
			this->Controls->Add(this->ChangeParams);
			this->Controls->Add(this->flowLayoutDataConnect);
			this->Name = L"MainWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main menu";
			this->flowLayoutPanelMain->ResumeLayout(false);
			this->flowLayoutPanelMain->PerformLayout();

			this->flowLayoutDataConnect->ResumeLayout(false);
			this->flowLayoutDataConnect->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	/// ## Метод, который открывает окно изменения параметров среды
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void ChangeParams_Click(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который завершает работу приложения сервера
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Exit_Click(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который начинает работу сервера
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void StartServer_Click(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который убирает подсказку с поля ввода айпи при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void IP_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода айпи при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void IP_leave(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который убирает подсказку с поля ввода порта при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Port_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода порта при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Port_leave(System::Object^ sender, System::EventArgs^ e);
};
}
