#pragma once
#include "MainWindow.h"
#include "..\..\ClientServer\Client.h"

namespace NoiseImmunityAppClient
{
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Сводка для CallWindow
/// </summary>
public
ref class CallWindow : public System::Windows::Forms::Form
{
public:
    /// ## Конструктор с параметрами
    ///
    /// В данном конструкторе написана инициализация компонентов формы
    ///
    /// @param [in] Ip Строка const char* содержащая айпи, с которым установлено
    /// подключение
    /// @param [in] Port unsigned int содержащий порт, с которым установлено подключение
    CallWindow(System::Windows::Forms::Form ^ Owner, const char* IP, unsigned short Port)
    {
        InitializeComponent();
        this->Show();
        this->Owner = Owner;
        AudioClient = new Client();
        if (!AudioClient->ConnectToServer(IP, Port))
        {
            this->Owner->Show();
            Close();
        }     
       
    }

    /// ## Конструктор с параметрами
    ///
    /// В данном конструкторе написана инициализация компонентов формы
    ///
    /// @param [in] Ip Строка const char* содержащая айпи, с которым установлено
    /// подключение
    /// @param [in] Port unsigned int содержащий порт, с которым установлено подключение
    /// @param [in] FileName Строка const char* содержащая имя файла, в который
    /// записывается разговор
    CallWindow(System::Windows::Forms::Form ^ Owner, const char* IP, unsigned short Port,
               const char* RecordingFileName)
    {
        InitializeComponent();
        this->Show();
        this->Owner = Owner;
        AudioClient = new Client();
        if (!AudioClient->ConnectToServer(IP, Port, RecordingFileName))
        {
            this->Owner->Show();
            Close();
        }
    }
protected:
    /// ## Деструктор
    ///
    /// При уничтожении класса, удаляем компоненты формы
    ~CallWindow()
    {
        AudioClient->DisconnectFromServer();
        if (components)
        {
            delete components;
        }
    }

private:
    System::Windows::Forms::Button ^ SpeakButton;

private:
    System::Windows::Forms::Button ^ EndCall;

    Button ^ PressedButton;
    bool IsMicroOn;
    Client* AudioClient;

private:
    /// <summary>
    /// Обязательная переменная конструктора.
    /// </summary>
    System::ComponentModel::Container ^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Требуемый метод для поддержки конструктора не изменяйте
    /// содержимое этого метода с помощью редактора кода.
    /// </summary>
    void InitializeComponent(void)
    {
        this->SpeakButton = (gcnew System::Windows::Forms::Button());
        this->EndCall = (gcnew System::Windows::Forms::Button());
        this->SuspendLayout();
        //
        // SpeakButton
        //
        this->SpeakButton->BackColor = System::Drawing::Color::ForestGreen;
        this->SpeakButton->Font = (gcnew System::Drawing::Font(
            L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->SpeakButton->ForeColor = System::Drawing::Color::White;
        this->SpeakButton->Location = System::Drawing::Point(97, 51);
        this->SpeakButton->Name = L"SpeakButton";
        this->SpeakButton->Size = System::Drawing::Size(181, 71);
        this->SpeakButton->TabIndex = 0;
        this->SpeakButton->Text = L"Micro is on";
        this->SpeakButton->UseVisualStyleBackColor = false;
        this->SpeakButton->Click +=
            gcnew System::EventHandler(this, &CallWindow::SpeakButton_Click);
        //
        // EndCall
        //
        this->EndCall->BackColor = System::Drawing::Color::Red;
        this->EndCall->Font = (gcnew System::Drawing::Font(
            L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->EndCall->ForeColor = System::Drawing::Color::White;
        this->EndCall->Location = System::Drawing::Point(97, 128);
        this->EndCall->Name = L"EndCall";
        this->EndCall->Size = System::Drawing::Size(181, 73);
        this->EndCall->TabIndex = 2;
        this->EndCall->Text = L"End call";
        this->EndCall->UseVisualStyleBackColor = false;
        this->EndCall->Click +=
            gcnew System::EventHandler(this, &CallWindow::EndCall_Click);
        //
        // CallWindow
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(375, 251);
        this->Controls->Add(this->EndCall);
        this->Controls->Add(this->SpeakButton);
        this->Name = L"CallWindow";
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        this->Text = L"Calling";
        this->ResumeLayout(false);
    }
#pragma endregion
    /// ## Метод, который откл кнопку разговора
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void SpeakButton_Click(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод, который завершает звонок
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private:System::Void EndCall_Click(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод, который вкл кнопку разговора
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    void PressedButton_click(Object ^ sender, EventArgs ^ e);
};
}  // namespace NoiseImmunityAppClient

