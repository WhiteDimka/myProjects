#pragma once
#include "CallWindow.h"
#include "FileNameWindowForCalling.h"
#include "MainWindow.h"
#include "../../ClientServer/Client.h"

namespace NoiseImmunityAppClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class FileNameWindowForCalling : public System::Windows::Forms::Form
	{
	public:
		/*
		FileNameWindowForCalling(void)
		{
			InitializeComponent();
		}
		*/
        /*
		FileNameWindowForCalling(MainWindow^ DefaultBackWinsow,const char* IP, unsigned int Port)
		{
			this->DefaultBackWinsow = DefaultBackWinsow;
			this->IP = IP;
			this->Port = Port;
			InitializeComponent();
		}
		*/


        /// ## Конструктор с параметрами
        ///
        /// В данном конструкторе написана инициализация компонентов формы
        ///
        /// @param [in] Ip Строка const char* содержащая айпи, с которым установлено
        /// подключение
        /// @param [in] Port unsigned int содержащий порт, с которым установлено
        /// подключение  
        FileNameWindowForCalling(System::Windows::Forms::Form ^ Owner, const char* IP,
                                 unsigned short Port)
        {
            this->IP = IP;
            this->Port = Port;
            InitializeComponent();
            this->Owner = Owner;
            this->Show();
        }

	protected:
        /// ## Деструктор
        ///
        /// При уничтожении класса, удаляем компоненты формы
		~FileNameWindowForCalling()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ FileName;
	private: System::Windows::Forms::Button^ OK_button;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
	private:
        System::Object ^ Owner;
        const char* IP;
        unsigned short Port;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора и не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->FileName = (gcnew System::Windows::Forms::TextBox());
			this->OK_button = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// FileName
			// 
			this->FileName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FileName->Location = System::Drawing::Point(3, 3);
			this->FileName->Multiline = true;
			this->FileName->Name = L"FileName";
			this->FileName->Size = System::Drawing::Size(204, 54);
			this->FileName->TabIndex = 0;
			this->FileName->Text = L"Enter file name for recording...";
			this->FileName->Enter += gcnew System::EventHandler(this, &FileNameWindowForCalling::FileName_Enter);
			this->FileName->Leave += gcnew System::EventHandler(this, &FileNameWindowForCalling::FileName_Leave);
			// 
			// OK_button
			// 
			this->OK_button->BackColor = System::Drawing::Color::Green;
			this->OK_button->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OK_button->ForeColor = System::Drawing::Color::White;
			this->OK_button->Location = System::Drawing::Point(107, 138);
			this->OK_button->Name = L"OK_button";
			this->OK_button->Size = System::Drawing::Size(116, 57);
			this->OK_button->TabIndex = 1;
			this->OK_button->Text = L"OK";
			this->OK_button->UseVisualStyleBackColor = false;
			this->OK_button->Click += gcnew System::EventHandler(this, &FileNameWindowForCalling::OK_button_Click);
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->FileName);
			this->flowLayoutPanel1->Location = System::Drawing::Point(107, 75);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(210, 61);
			this->flowLayoutPanel1->TabIndex = 2;
			// 
			// FileNameWindowForCalling
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(415, 276);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->OK_button);
			this->Name = L"FileNameWindowForCalling";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"File name window";
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
    /// ## Метод, который переходит на форму звонка
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void OK_button_Click(System::Object^ sender, System::EventArgs^ e);
	
	/// ## Метод, который убирает подсказку для ввода имени файла при клике
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
	/// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void FileName_Enter(System::Object^ sender, System::EventArgs^ e);
        
	/// ## Метод, который возвращает подсказку для ввода имени фалй при клике
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
	private: System::Void FileName_Leave(System::Object^ sender, System::EventArgs^ e);
	};
}
