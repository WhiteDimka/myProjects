#pragma once
#include "..\..\ClientServer\Client.h"

namespace NoiseImmunityAppClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для FileNameForSendingWindow
	/// </summary>
	public ref class FileNameForSendingWindow : public System::Windows::Forms::Form
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
        FileNameForSendingWindow(Client * AudioClient)
		{
            this->AudioClient = AudioClient;
			InitializeComponent();            
		}

	protected:
        /// ## Деструктор
        ///
        /// При уничтожении класса, удаляем компоненты формы
		~FileNameForSendingWindow()
		{
			if (components)
			{
                AudioClient->DisconnectFromServer();
				delete components;
			}
		}

    private:
        System::Windows::Forms::TextBox ^ fileName;

    private:
        System::Windows::Forms::Button ^ OK;

    private:
        Client* AudioClient;

    private:
        System::Windows::Forms::FlowLayoutPanel ^ flowLayoutPanel1;

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
            this->fileName = (gcnew System::Windows::Forms::TextBox());
            this->OK = (gcnew System::Windows::Forms::Button());
            this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->flowLayoutPanel1->SuspendLayout();
            this->SuspendLayout();
            //
            // fileName
            //
            this->fileName->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Regular,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->fileName->Location = System::Drawing::Point(3, 3);
            this->fileName->Multiline = true;
            this->fileName->Name = L"fileName";
            this->fileName->Size = System::Drawing::Size(166, 42);
            this->fileName->TabIndex = 0;
            this->fileName->Text = L"Enter file name...";
            this->fileName->Enter +=
                gcnew System::EventHandler(this, &FileNameForSendingWindow::file_enter);
            this->fileName->Leave +=
                gcnew System::EventHandler(this, &FileNameForSendingWindow::file_leave);
            //
            // OK
            //
            this->OK->BackColor = System::Drawing::Color::Green;
            this->OK->Font = (gcnew System::Drawing::Font(
                L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
                System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->OK->ForeColor = System::Drawing::Color::White;
            this->OK->Location = System::Drawing::Point(141, 189);
            this->OK->Name = L"OK";
            this->OK->Size = System::Drawing::Size(169, 67);
            this->OK->TabIndex = 1;
            this->OK->Text = L"OK";
            this->OK->UseVisualStyleBackColor = false;
            this->OK->Click +=
                gcnew System::EventHandler(this, &FileNameForSendingWindow::OK_Click);
            //
            // flowLayoutPanel1
            //
            this->flowLayoutPanel1->Controls->Add(this->fileName);
            this->flowLayoutPanel1->Location = System::Drawing::Point(141, 83);
            this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
            this->flowLayoutPanel1->Size = System::Drawing::Size(173, 67);
            this->flowLayoutPanel1->TabIndex = 2;
            //
            // FileNameForSendingWindow
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(451, 363);
            this->Controls->Add(this->flowLayoutPanel1);
            this->Controls->Add(this->OK);
            this->Name = L"FileNameForSendingWindow";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"File name for sending wndow";
            this->flowLayoutPanel1->ResumeLayout(false);
            this->flowLayoutPanel1->PerformLayout();
            this->ResumeLayout(false);
        }
#pragma endregion
    private:
    /// ## Метод, который определяет в какое окно нужно вернуться
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    System::Void OK_Click(System::Object ^ sender, System::EventArgs ^ e);

    /// ## Метод, который убирает подсказку для ввода имени файла при клике
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void file_enter(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод, который возвращает подсказку для ввода имени фалй при клике
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void file_leave(System::Object ^ sender, System::EventArgs ^ e);
    };
    }
