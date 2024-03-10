#pragma once

#include "MainWindow.h"
#include "../../ClientServer/Server.h"
#include <msclr\marshal_cppstd.h>

namespace NoiseImmunityAppServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для ParamsWindow
	/// </summary>
	public ref class ParamsWindow : public System::Windows::Forms::Form
	{
	public:
		/// ## Конструктор по умолчанию
		/// 
		/// В данном конструкторе инициализируются все компоненты формы
		ParamsWindow(Server* AudioServer)
		{
			this->AudioServer = AudioServer;	
			this->AudioServer->DisableInterference();
			InitializeComponent();
			Apply->Enabled = false;
		}


	protected:
		/// ## Деструктор
		///
		/// В данном деструкторе освобождаются все компоненты формы
		~ParamsWindow()
		{
			if (components)
			{
				delete components;
			}
		}
		
	private: System::Windows::Forms::Button^ ReturnToMain;
	private: System::Windows::Forms::CheckBox^ checkBoxLatency;
	private: System::Windows::Forms::CheckBox^ checkBoxLoss;
	private: System::Windows::Forms::CheckBox^ checkBoxMixing;
	private: System::Windows::Forms::CheckBox^ checkBoxInterference;
	private: System::Windows::Forms::TextBox^ Min_Latency;
	private: System::Windows::Forms::TextBox^ MaxLatency;
	private: System::Windows::Forms::TextBox^ PacketLossProbability;
	private: System::Windows::Forms::TextBox^ PacketMixingProbability;
	private: System::Windows::Forms::TextBox^ NoiseIntensivity;
	private: System::Windows::Forms::TextBox^ NoiseRate;
	private: System::Windows::Forms::Label^ label_ChooseParam;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^ Apply;
	private: Server* AudioServer;
	private: System::String^ ConvertToNumberString(String^ StringFromTextBox);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора, не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ReturnToMain = (gcnew System::Windows::Forms::Button());
			this->checkBoxLatency = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxLoss = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxMixing = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxInterference = (gcnew System::Windows::Forms::CheckBox());
			this->label_ChooseParam = (gcnew System::Windows::Forms::Label());
			this->Apply = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// ReturnToMain
			// 
			this->ReturnToMain->BackColor = System::Drawing::Color::Red;
			this->ReturnToMain->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ReturnToMain->ForeColor = System::Drawing::Color::White;
			this->ReturnToMain->Location = System::Drawing::Point(797, 517);
			this->ReturnToMain->Name = L"ReturnToMain";
			this->ReturnToMain->Size = System::Drawing::Size(169, 67);
			this->ReturnToMain->TabIndex = 0;
			this->ReturnToMain->Text = L"Back";
			this->ReturnToMain->UseVisualStyleBackColor = false;
			this->ReturnToMain->Click += gcnew System::EventHandler(this, &ParamsWindow::ReturnToMain_Click);
			// 
			// checkBoxLatency
			// 
			this->checkBoxLatency->AutoSize = true;
			this->checkBoxLatency->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBoxLatency->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->checkBoxLatency->Location = System::Drawing::Point(88, 168);
			this->checkBoxLatency->Name = L"checkBoxLatency";
			this->checkBoxLatency->Size = System::Drawing::Size(111, 31);
			this->checkBoxLatency->TabIndex = 1;
			this->checkBoxLatency->Text = L"Latency";
			this->checkBoxLatency->UseVisualStyleBackColor = true;
			this->checkBoxLatency->CheckedChanged += gcnew System::EventHandler(this, &ParamsWindow::checkBoxLatency_CheckedChanged);
			// 
			// checkBoxLoss
			// 
			this->checkBoxLoss->AutoSize = true;
			this->checkBoxLoss->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkBoxLoss->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->checkBoxLoss->Location = System::Drawing::Point(88, 259);
			this->checkBoxLoss->Name = L"checkBoxLoss";
			this->checkBoxLoss->Size = System::Drawing::Size(78, 31);
			this->checkBoxLoss->TabIndex = 2;
			this->checkBoxLoss->Text = L"Loss";
			this->checkBoxLoss->UseVisualStyleBackColor = true;
			this->checkBoxLoss->CheckedChanged += gcnew System::EventHandler(this, &ParamsWindow::checkBoxLoss_CheckedChanged);
			// 
			// checkBoxMixing
			// 
			this->checkBoxMixing->AutoSize = true;
			this->checkBoxMixing->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBoxMixing->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->checkBoxMixing->Location = System::Drawing::Point(88, 355);
			this->checkBoxMixing->Name = L"checkBoxMixing";
			this->checkBoxMixing->Size = System::Drawing::Size(105, 31);
			this->checkBoxMixing->TabIndex = 3;
			this->checkBoxMixing->Text = L"Mixing";
			this->checkBoxMixing->UseVisualStyleBackColor = true;
			this->checkBoxMixing->CheckedChanged += gcnew System::EventHandler(this, &ParamsWindow::checkBoxMixing_CheckedChanged);
			// 
			// checkBoxInterference
			// 
			this->checkBoxInterference->AutoSize = true;
			this->checkBoxInterference->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->checkBoxInterference->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->checkBoxInterference->Location = System::Drawing::Point(88, 448);
			this->checkBoxInterference->Name = L"checkBoxInterference";
			this->checkBoxInterference->Size = System::Drawing::Size(85, 31);
			this->checkBoxInterference->TabIndex = 4;
			this->checkBoxInterference->Text = L"Interference";
			this->checkBoxInterference->UseVisualStyleBackColor = true;
			this->checkBoxInterference->CheckedChanged += gcnew System::EventHandler(this, &ParamsWindow::checkBoxInterference_CheckedChanged);
			// 
			// label_ChooseParam
			// 
			this->label_ChooseParam->AutoSize = true;
			this->label_ChooseParam->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 13.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label_ChooseParam->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->label_ChooseParam->Location = System::Drawing::Point(82, 67);
			this->label_ChooseParam->Name = L"label_ChooseParam";
			this->label_ChooseParam->Size = System::Drawing::Size(236, 31);
			this->label_ChooseParam->TabIndex = 10;
			this->label_ChooseParam->Text = L"Choose parameters";
			// 
			// Apply
			// 
			this->Apply->BackColor = System::Drawing::Color::Green;
			this->Apply->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Apply->ForeColor = System::Drawing::Color::White;
			this->Apply->Location = System::Drawing::Point(583, 517);
			this->Apply->Name = L"Apply";
			this->Apply->Size = System::Drawing::Size(169, 67);
			this->Apply->TabIndex = 11;
			this->Apply->Text = L"Apply";
			this->Apply->UseVisualStyleBackColor = false;
			this->Apply->Click += gcnew System::EventHandler(this, &ParamsWindow::Apply_Click);
			// 
			// ParamsWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1022, 639);
			this->Controls->Add(this->Apply);
			this->Controls->Add(this->label_ChooseParam);
			this->Controls->Add(this->checkBoxInterference);
			this->Controls->Add(this->checkBoxMixing);
			this->Controls->Add(this->checkBoxLoss);
			this->Controls->Add(this->checkBoxLatency);
			this->Controls->Add(this->ReturnToMain);
			this->Name = L"ParamsWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Settings";
			this->ResumeLayout(false);
			this->PerformLayout();

			//создаем мин и макс latency
			this->Min_Latency = (gcnew System::Windows::Forms::TextBox());
			this->MaxLatency = (gcnew System::Windows::Forms::TextBox());
			// Min_Latency
			this->Min_Latency->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Min_Latency->Location = System::Drawing::Point(210, 135);
			this->Min_Latency->Multiline = true;
			this->Min_Latency->Name = L"Min_Latency";
			this->Min_Latency->Size = System::Drawing::Size(240, 25);
			this->Min_Latency->TabIndex = 5;
			this->Min_Latency->Text = L"Enter min latency (mc/pac)...";
			this->Min_Latency->Enter += gcnew System::EventHandler(this, &ParamsWindow::Min_Latency_enter);
			this->Min_Latency->Leave += gcnew System::EventHandler(this, &ParamsWindow::Min_Latency_leave);
			// MaxLatency
			this->MaxLatency->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MaxLatency->Location = System::Drawing::Point(480, 135);
			this->MaxLatency->Multiline = true;
			this->MaxLatency->Name = L"MaxLatency";
			this->MaxLatency->Size = System::Drawing::Size(240, 25);
			this->MaxLatency->TabIndex = 6;
			this->MaxLatency->Text = L"Enter max latency (mc/pac)...";
			this->MaxLatency->Enter += gcnew System::EventHandler(this, &ParamsWindow::MaxLatency_enter);
			this->MaxLatency->Leave += gcnew System::EventHandler(this, &ParamsWindow::MaxLatency_leave);
			this->MaxLatency->TextChanged += gcnew System::EventHandler(this, &ParamsWindow::MaxLatency_TextChanged);
			this->Min_Latency->TextChanged += gcnew System::EventHandler(this, &ParamsWindow::Min_Latency_TextChanged);
			//добавляем на форму
			this->Controls->Add(this->MaxLatency);
			this->Controls->Add(this->Min_Latency);
			Min_Latency->Visible = false;
			MaxLatency->Visible = false;

			//Loss
			this->PacketLossProbability = (gcnew System::Windows::Forms::TextBox());
			this->PacketLossProbability->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PacketLossProbability->Location = System::Drawing::Point(210, 210);
			this->PacketLossProbability->Multiline = true;
			this->PacketLossProbability->Name = L"PacketLossProbability";
			this->PacketLossProbability->Size = System::Drawing::Size(240, 25);
			this->PacketLossProbability->TabIndex = 7;
			this->PacketLossProbability->Text = L"Enter loss rate [0;100]...";
			this->PacketLossProbability->Enter += gcnew System::EventHandler(this, &ParamsWindow::PacketLossProbability_enter);
			this->PacketLossProbability->Leave += gcnew System::EventHandler(this, &ParamsWindow::PacketLossProbability_leave);
			this->PacketLossProbability->TextChanged += gcnew System::EventHandler(this, &ParamsWindow::PacketLossProbability_TextChanged);
			this->Controls->Add(this->PacketLossProbability);
			PacketLossProbability->Visible = false;

			//Mixing
			this->PacketMixingProbability = (gcnew System::Windows::Forms::TextBox());
			this->PacketMixingProbability->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PacketMixingProbability->Location = System::Drawing::Point(210, 287);
			this->PacketMixingProbability->Multiline = true;
			this->PacketMixingProbability->Name = L"PacketMixingProbability";
			this->PacketMixingProbability->Size = System::Drawing::Size(240, 25);
			this->PacketMixingProbability->TabIndex = 8;
			this->PacketMixingProbability->Text = L"Enter mixing rate [0;100]...";
			this->PacketMixingProbability->Enter += gcnew System::EventHandler(this, &ParamsWindow::PacketMixingProbability_enter);
			this->PacketMixingProbability->Leave += gcnew System::EventHandler(this, &ParamsWindow::PacketMixingProbability_leave);
			this->PacketMixingProbability->TextChanged += gcnew System::EventHandler(this, &ParamsWindow::PacketMixingProbability_TextChanged);
			this->Controls->Add(this->PacketMixingProbability);
			PacketMixingProbability->Visible = false;

			//NoiseRate
			this->NoiseRate = (gcnew System::Windows::Forms::TextBox());
			this->NoiseRate->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NoiseRate->Location = System::Drawing::Point(210, 365);
			this->NoiseRate->Multiline = true;
			this->NoiseRate->Name = L"NoiseRate";
			this->NoiseRate->Size = System::Drawing::Size(240, 25);
			this->NoiseRate->TabIndex = 8;
			this->NoiseRate->Text = L"Enter noise rate [0;100]...";
			this->NoiseRate->Enter += gcnew System::EventHandler(this, &ParamsWindow::NoiseRate_enter);
			this->NoiseRate->Leave += gcnew System::EventHandler(this, &ParamsWindow::NoiseRate_leave);
			this->NoiseRate->TextChanged += gcnew System::EventHandler(this, &ParamsWindow::NoiseRate_TextChanged);
			this->Controls->Add(this->NoiseRate);

			//NoiseIntensivity
			this->NoiseIntensivity = (gcnew System::Windows::Forms::TextBox());
			this->NoiseIntensivity->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NoiseIntensivity->Location = System::Drawing::Point(480, 365);
			this->NoiseIntensivity->Multiline = true;
			this->NoiseIntensivity->Name = L"NoiseIntensivity";
			this->NoiseIntensivity->Size = System::Drawing::Size(240, 25);
			this->NoiseIntensivity->TabIndex = 8;
			this->NoiseIntensivity->Text = L"Enter noise intensivity [0;280]...";
			this->NoiseIntensivity->Enter += gcnew System::EventHandler(this, &ParamsWindow::NoiseIntensivity_enter);
			this->NoiseIntensivity->Leave += gcnew System::EventHandler(this, &ParamsWindow::NoiseIntensivity_leave);
			this->NoiseIntensivity->TextChanged += gcnew System::EventHandler(this, &ParamsWindow::NoiseIntensivity_TextChanged);
			this->Controls->Add(this->NoiseIntensivity);
			NoiseRate->Visible = false;
			NoiseIntensivity->Visible = false;
		}
#pragma endregion
	/// ## Метод, который разблокирует кнопку Apply при изменении textbox
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Min_Latency_TextChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который разблокирует кнопку Apply при изменении textbox
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void MaxLatency_TextChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который разблокирует кнопку Apply при изменении textbox
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void PacketLossProbability_TextChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который разблокирует кнопку Apply при изменении textbox
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void PacketMixingProbability_TextChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который разблокирует кнопку Apply при изменении textbox
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void NoiseRate_TextChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который разблокирует кнопку Apply при изменении textbox
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void NoiseIntensivity_TextChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает на главное окно
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void ReturnToMain_Click(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который определяет изменение состояние
	/// чекбокса задержки, регулирует видимость полей
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void checkBoxLatency_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который определяет изменение состояние
	/// чекбокса потерь, регулирует видимость полей
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void checkBoxLoss_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который определяет изменение состояние
	/// чекбокса перемешивания пакетов, регулирует видимость полей
	/// 
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void checkBoxMixing_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который определяет изменение состояние
	/// чекбокса джиттера, регулирует видимость полей/// 
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void checkBoxInterference_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который убирает подсказку с поля ввода при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void NoiseIntensivity_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void NoiseIntensivity_leave(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который убирает подсказку с поля ввода при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void NoiseRate_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void NoiseRate_leave(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который убирает подсказку с поля ввода минимальной задержки при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Min_Latency_enter(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который возвращает подсказку на поле ввода минимальной задержки при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Min_Latency_leave(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который убирает подсказку с поля ввода максимальной задержки при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void MaxLatency_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода максимальной задержки при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void MaxLatency_leave(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который убирает подсказку с поля ввода вероятности потери пакетов при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void PacketLossProbability_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода вероятности потери пакетов при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void PacketLossProbability_leave(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который убирает подсказку с поля ввода вероятности перемешивания пакетов при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void PacketMixingProbability_enter(System::Object^ sender, System::EventArgs^ e);

	/// ## Метод, который возвращает подсказку на поле ввода вероятности перемешивания пакетов при клике по нему
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void PacketMixingProbability_leave(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который устанавливает изменения параметров среды
	///
	/// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к обрабатываемому событию
	private: System::Void Apply_Click(System::Object^ sender, System::EventArgs^ e);

};
}
