#pragma once
#include "RecordToFileWindow.h"
#include "FileNameWindowForCalling.h"
#include "CallingSendingWindow.h"
#include "../../ClientServer/ClientServerConst.h"

namespace NoiseImmunityAppClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;

	/// <summary>
	/// Сводка для MainWindow
	/// </summary>
	public ref class MainWindowClient : public System::Windows::Forms::Form
	{
	public:
        /// ## Конструктор по умолчанию
        ///
        /// В данном конструкторе написана инициалиация компонентов формы
		MainWindowClient(void)
		{
			InitializeComponent();
		}

	protected:
        /// ## Деструктор
        ///
        /// При уничтожении класса, удаляем компоненты формы
		~MainWindowClient()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ Play;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::TextBox^ FileName;
	private: System::Windows::Forms::Button^ WriteToFileFromMicro;
	private: System::Windows::Forms::Button^ Exit;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::Label^ WithWhoToCall;
	private: System::Windows::Forms::TextBox^ IP;
	private: System::Windows::Forms::TextBox^ Port;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
    private: System::Windows::Forms::Button ^ ConnectServer;
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
            this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
            this->Play = (gcnew System::Windows::Forms::Button());
            this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->FileName = (gcnew System::Windows::Forms::TextBox());
            this->WriteToFileFromMicro = (gcnew System::Windows::Forms::Button());
            this->Exit = (gcnew System::Windows::Forms::Button());
            this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->WithWhoToCall = (gcnew System::Windows::Forms::Label());
            this->IP = (gcnew System::Windows::Forms::TextBox());
            this->Port = (gcnew System::Windows::Forms::TextBox());
            this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->ConnectServer = (gcnew System::Windows::Forms::Button());
            this->flowLayoutPanel1->SuspendLayout();
            this->flowLayoutPanel2->SuspendLayout();
            this->flowLayoutPanel3->SuspendLayout();
            this->SuspendLayout();
            //
            // Play
            //
            this->Play->BackColor = System::Drawing::Color::Green;
            this->Play->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->Play->ForeColor = System::Drawing::SystemColors::ButtonFace;
            this->Play->Location = System::Drawing::Point(3, 59);
            this->Play->Name = L"Play";
            this->Play->Size = System::Drawing::Size(169, 67);
            this->Play->TabIndex = 0;
            this->Play->Text = L"Play";
            this->Play->UseVisualStyleBackColor = false;
            this->Play->Click +=
                gcnew System::EventHandler(this, &MainWindowClient::Play_Click);
            //
            // flowLayoutPanel1
            //
            this->flowLayoutPanel1->BackColor =
                System::Drawing::SystemColors::GradientInactiveCaption;
            this->flowLayoutPanel1->BorderStyle =
                System::Windows::Forms::BorderStyle::FixedSingle;
            this->flowLayoutPanel1->Controls->Add(this->FileName);
            this->flowLayoutPanel1->Controls->Add(this->Play);
            this->flowLayoutPanel1->Controls->Add(this->WriteToFileFromMicro);
            this->flowLayoutPanel1->Location = System::Drawing::Point(120, 287);
            this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
            this->flowLayoutPanel1->Size = System::Drawing::Size(352, 130);
            this->flowLayoutPanel1->TabIndex = 2;
            //
            // FileName
            //
            this->FileName->BackColor = System::Drawing::SystemColors::Window;
            this->FileName->Font = (gcnew System::Drawing::Font(
                L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->FileName->ForeColor = System::Drawing::SystemColors::ControlText;
            this->FileName->Location = System::Drawing::Point(3, 3);
            this->FileName->Multiline = true;
            this->FileName->Name = L"FileName";
            this->FileName->Size = System::Drawing::Size(344, 50);
            this->FileName->TabIndex = 3;
            this->FileName->Text = L"Enter file name...";
            this->FileName->Enter +=
                gcnew System::EventHandler(this, &MainWindowClient::FileName_Enter);
            this->FileName->Leave +=
                gcnew System::EventHandler(this, &MainWindowClient::FileName_Leave);
            //
            // WriteToFileFromMicro
            //
            this->WriteToFileFromMicro->BackColor =
                System::Drawing::Color::CornflowerBlue;
            this->WriteToFileFromMicro->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->WriteToFileFromMicro->ForeColor = System::Drawing::Color::White;
            this->WriteToFileFromMicro->Location = System::Drawing::Point(178, 59);
            this->WriteToFileFromMicro->Name = L"WriteToFileFromMicro";
            this->WriteToFileFromMicro->Size = System::Drawing::Size(169, 67);
            this->WriteToFileFromMicro->TabIndex = 7;
            this->WriteToFileFromMicro->Text = L"Recording with micro to file";
            this->WriteToFileFromMicro->UseVisualStyleBackColor = false;
            this->WriteToFileFromMicro->Click +=
                gcnew System::EventHandler(this, &MainWindowClient::WriteToFileFromMicro_Click);
            //
            // Exit
            //
            this->Exit->BackColor = System::Drawing::Color::Crimson;
            this->Exit->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->Exit->ForeColor = System::Drawing::Color::White;
            this->Exit->Location = System::Drawing::Point(412, 515);
            this->Exit->Name = L"Exit";
            this->Exit->Size = System::Drawing::Size(169, 67);
            this->Exit->TabIndex = 8;
            this->Exit->Text = L"Exit";
            this->Exit->UseVisualStyleBackColor = false;
            this->Exit->Click +=
                gcnew System::EventHandler(this, &MainWindowClient::Exit_Click);
            //
            // flowLayoutPanel2
            //
            this->flowLayoutPanel2->BackColor =
                System::Drawing::SystemColors::GradientInactiveCaption;
            this->flowLayoutPanel2->BorderStyle =
                System::Windows::Forms::BorderStyle::FixedSingle;
            this->flowLayoutPanel2->Controls->Add(this->WithWhoToCall);
            this->flowLayoutPanel2->Controls->Add(this->IP);
            this->flowLayoutPanel2->Controls->Add(this->Port);
            this->flowLayoutPanel2->Location = System::Drawing::Point(3, 3);
            this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
            this->flowLayoutPanel2->Size = System::Drawing::Size(552, 174);
            this->flowLayoutPanel2->TabIndex = 3;
            //
            // WithWhoToCall
            //
            this->WithWhoToCall->AutoEllipsis = true;
            this->WithWhoToCall->AutoSize = true;
            this->WithWhoToCall->Font = (gcnew System::Drawing::Font(
                L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->WithWhoToCall->ForeColor = System::Drawing::Color::CornflowerBlue;
            this->WithWhoToCall->Location = System::Drawing::Point(3, 0);
            this->WithWhoToCall->Name = L"WithWhoToCall";
            this->WithWhoToCall->Size = System::Drawing::Size(313, 32);
            this->WithWhoToCall->TabIndex = 4;
            this->WithWhoToCall->Text = L"Data for calling/sending";
            //
            // IP
            //
            this->IP->Font = (gcnew System::Drawing::Font(
                L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->IP->Location = System::Drawing::Point(3, 35);
            this->IP->Multiline = true;
            this->IP->Name = L"IP";
            this->IP->Size = System::Drawing::Size(539, 59);
            this->IP->TabIndex = 0;
            this->IP->Text = L"Enter IP ...";
            this->IP->Enter += gcnew System::EventHandler(this, &MainWindowClient::IP_enter);
            this->IP->Leave += gcnew System::EventHandler(this, &MainWindowClient::IP_leave);
            String ^ ip = DEFAULT_SERVER_IP;  //айпи по умолчанию
            IP->Text = ip;  //отображаем айпи по умолчанию
            //
            // Port
            //
            this->Port->Font = (gcnew System::Drawing::Font(
                L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->Port->Location = System::Drawing::Point(3, 100);
            this->Port->Multiline = true;
            this->Port->Name = L"Port";
            this->Port->Size = System::Drawing::Size(539, 59);
            this->Port->TabIndex = 1;
            this->Port->Text = L"Enter Port ...";
            this->Port->Enter +=
                gcnew System::EventHandler(this, &MainWindowClient::Port_enter);
            this->Port->Leave +=
                gcnew System::EventHandler(this, &MainWindowClient::Port_leave);
            String ^ port = System::Convert::ToString(DEFAULT_SERVER_PORT);  //айпи по умолчанию
            Port->Text = port;  //отображаем айпи по умолчанию
            //
            // flowLayoutPanel3
            //
            this->flowLayoutPanel3->Anchor =
                static_cast<System::Windows::Forms::AnchorStyles>(
                    (System::Windows::Forms::AnchorStyles::Top |
                     System::Windows::Forms::AnchorStyles::Bottom));
            this->flowLayoutPanel3->BackColor =
                System::Drawing::SystemColors::GradientInactiveCaption;
            this->flowLayoutPanel3->BorderStyle =
                System::Windows::Forms::BorderStyle::FixedSingle;
            this->flowLayoutPanel3->Controls->Add(this->flowLayoutPanel2);
            this->flowLayoutPanel3->Controls->Add(this->ConnectServer);
            this->flowLayoutPanel3->Location = System::Drawing::Point(16, 12);
            this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
            this->flowLayoutPanel3->Size = System::Drawing::Size(565, 259);
            this->flowLayoutPanel3->TabIndex = 5;
            //
            // ConnectServer
            //
            this->ConnectServer->BackColor = System::Drawing::Color::CornflowerBlue;
            this->ConnectServer->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->ConnectServer->ForeColor = System::Drawing::Color::White;
            this->ConnectServer->Location = System::Drawing::Point(178, 183);
            this->ConnectServer->Name = L"ConnectServer";
            this->ConnectServer->Size = System::Drawing::Size(169, 67);
            this->ConnectServer->TabIndex = 5;
            this->ConnectServer->Text = L"Connect to server";
            this->ConnectServer->UseVisualStyleBackColor = false;
            this->ConnectServer->Click +=
                gcnew System::EventHandler(this, &MainWindowClient::ConnectServer_Click);
            //
            // MainWindow
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->ClientSize = System::Drawing::Size(593, 594);
            this->Controls->Add(this->Exit);
            this->Controls->Add(this->flowLayoutPanel3);
            this->Controls->Add(this->flowLayoutPanel1);
            this->Name = L"MainWindow";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Menu";
            this->flowLayoutPanel1->ResumeLayout(false);
            this->flowLayoutPanel1->PerformLayout();
            this->flowLayoutPanel2->ResumeLayout(false);
            this->flowLayoutPanel2->PerformLayout();
            this->flowLayoutPanel3->ResumeLayout(false);
            this->ResumeLayout(false);
        }

#pragma endregion
    /// ## Метод воспроизведения файла
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void Play_Click(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод удаления подсказки на ввод имени файла
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void FileName_Enter(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод возвращения подсказки на ввод имени файла
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void FileName_Leave(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод удаления подсказки на ввод айпи
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void IP_enter(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод возвращения подсказки на ввод айпи
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void IP_leave(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод удаления подсказки на ввод порта
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void Port_enter(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод возвращения подсказки на ввод порта
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void Port_leave(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод записи с микрофона в файл
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void WriteToFileFromMicro_Click(System::Object^ sender, System::EventArgs^ e);
	
    /// ## Метод выхода из приложения клиента
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void Exit_Click(System::Object^ sender, System::EventArgs^ e);
	
    /// Метод ## подключения к серверу
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private:System::Void ConnectServer_Click(System::Object ^ sender, System::EventArgs ^ e);
    };
    }
