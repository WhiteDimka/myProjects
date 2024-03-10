#pragma once
#include "CallWindow.h"
#include "FileNameForSendingWindow.h"
#include "..\..\ClientServer\Client.h"

namespace NoiseImmunityAppClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для CallingSendingWindow
	/// </summary>
	public ref class CallingSendingWindow : public System::Windows::Forms::Form
	{
	public:
        /// ## Конструктор с параметрами
        ///
        /// В данном конструкторе написано указание на компоненты формы
        ///
        /// @param [in] Ip Строка const char* содержащая айпи, с которым установлено
        /// подключение
        /// @param [in] Port unsigned int содержащий порт, с которым установлено
        /// подключение
        CallingSendingWindow(System::Windows::Forms::Form ^ Owner, const char* IP,
                             unsigned short Port)
        {
            this->IP = IP;
            this->Port = Port;
            this->Show();
            this->Owner = Owner;
            InitializeComponent();
        }

	protected:
        /// ## Деструктор
        ///
        /// При уничтожении класса, удаляем компоненты формы
		~CallingSendingWindow()
		{
			if (components)
			{
				delete components;
			}
		}

    private:
        System::Windows::Forms::Button ^ Call;
    private:
        System::Windows::Forms::Button ^ SendFile;
    private:
        System::Windows::Forms::Button ^ Back;

    private:
        const char* IP;
        unsigned short Port;
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
            this->Call = (gcnew System::Windows::Forms::Button());
            this->SendFile = (gcnew System::Windows::Forms::Button());
            this->Back = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            //
            // Call
            //
            this->Call->BackColor = System::Drawing::Color::CornflowerBlue;
            this->Call->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->Call->ForeColor = System::Drawing::Color::White;
            this->Call->Location = System::Drawing::Point(121, 90);
            this->Call->Name = L"Call";
            this->Call->Size = System::Drawing::Size(169, 67);
            this->Call->TabIndex = 0;
            this->Call->Text = L"Call";
            this->Call->UseVisualStyleBackColor = false;
            this->Call->Click +=
                gcnew System::EventHandler(this, &CallingSendingWindow::Call_Click);
            //
            // SendFile
            //
            this->SendFile->BackColor = System::Drawing::Color::CornflowerBlue;
            this->SendFile->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->SendFile->ForeColor = System::Drawing::Color::White;
            this->SendFile->Location = System::Drawing::Point(121, 182);
            this->SendFile->Name = L"SendFile";
            this->SendFile->Size = System::Drawing::Size(169, 67);
            this->SendFile->TabIndex = 1;
            this->SendFile->Text = L"Send file";
            this->SendFile->UseVisualStyleBackColor = false;
            this->SendFile->Click +=
                gcnew System::EventHandler(this, &CallingSendingWindow::SendFile_Click);
            //
            // Back
            //
            this->Back->BackColor = System::Drawing::Color::Red;
            this->Back->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->Back->ForeColor = System::Drawing::Color::White;
            this->Back->Location = System::Drawing::Point(121, 277);
            this->Back->Name = L"Back";
            this->Back->Size = System::Drawing::Size(169, 67);
            this->Back->TabIndex = 2;
            this->Back->Text = L"Back";
            this->Back->UseVisualStyleBackColor = false;
            this->Back->Click +=
                gcnew System::EventHandler(this, &CallingSendingWindow::Back_Click);
            //
            // CallingSendingWindow
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(418, 399);
            this->Controls->Add(this->Back);
            this->Controls->Add(this->SendFile);
            this->Controls->Add(this->Call);
            this->Name = L"CallingSendingWindow";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Calling / sending window";
            this->ResumeLayout(false);
        }
#pragma endregion
    /// ## Метод, который переходит на форму для звонка
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void Call_Click(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод, который переходит на форму для ввода имени файла для отправки
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void SendFile_Click(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод, который возвращает на родительскую форму
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private:System::Void Back_Click(System::Object ^ sender, System::EventArgs ^ e);
    };
    }
