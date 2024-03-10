#pragma once
#include "MainWindow.h"
#include "MicroRecording.h"


namespace NoiseImmunityAppClient
{
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Сводка для RecordToFileWindow
/// </summary>
public
ref class RecordToFileWindow : public System::Windows::Forms::Form
{
public:
    /// ## Конструктор с параметрами
    ///
    /// В данном конструкторе написана инициализация компонентов формы 
    /// и указатель на объект класса записи с микрофона
    ///
    /// @param [in] fileName Строка const char* содержащая имя файла, в который будет
    /// записываться разговор   
    RecordToFileWindow(const char* FileName)
    {
        FileRecording = new MicroRecording(FileName);
        InitializeComponent();        
    }

protected:
    /// ## Деструктор
    ///
    /// При уничтожении класса, удаляемкомпоненты формы и
    /// указатель на объект класса записи с микрофона
    ~RecordToFileWindow()
    {        
        delete FileRecording;
        if (components)
        {
            delete components;
        }
    }

private:
    System::Windows::Forms::FlowLayoutPanel ^ flowLayoutPanel1;

private:
    System::Windows::Forms::Label ^ RecordLabel;

private:
    System::Windows::Forms::Button ^ SpeakToMicro;

private:
    System::Windows::Forms::Button ^ StopSpeakToMicro;

private:
    System::Windows::Forms::Button ^ ReturnToMainWindow;

private:
    /// <summary>
    /// Обязательная переменная конструктора.
    /// </summary>
    System::ComponentModel::Container ^ components;

private:
    MicroRecording* FileRecording;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Требуемый метод для поддержки конструктора — не изменяйте
    /// содержимое этого метода с помощью редактора кода.
    /// </summary>
    void InitializeComponent(void)
    {
        this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
        this->RecordLabel = (gcnew System::Windows::Forms::Label());
        this->SpeakToMicro = (gcnew System::Windows::Forms::Button());
        this->StopSpeakToMicro = (gcnew System::Windows::Forms::Button());
        this->ReturnToMainWindow = (gcnew System::Windows::Forms::Button());
        this->flowLayoutPanel1->SuspendLayout();
        this->SuspendLayout();
        //
        // flowLayoutPanel1
        //
        this->flowLayoutPanel1->BackColor =
            System::Drawing::SystemColors::GradientInactiveCaption;
        this->flowLayoutPanel1->Controls->Add(this->RecordLabel);
        this->flowLayoutPanel1->Controls->Add(this->SpeakToMicro);
        this->flowLayoutPanel1->Controls->Add(this->StopSpeakToMicro);
        this->flowLayoutPanel1->Controls->Add(this->ReturnToMainWindow);
        this->flowLayoutPanel1->Location = System::Drawing::Point(117, 25);
        this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
        this->flowLayoutPanel1->Size = System::Drawing::Size(205, 305);
        this->flowLayoutPanel1->TabIndex = 0;
        //
        // RecordLabel
        //
        this->RecordLabel->AutoSize = true;
        this->RecordLabel->BackColor = System::Drawing::Color::White;
        this->RecordLabel->Font = (gcnew System::Drawing::Font(
            L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->RecordLabel->ForeColor = System::Drawing::Color::CornflowerBlue;
        this->RecordLabel->Location = System::Drawing::Point(3, 0);
        this->RecordLabel->Name = L"RecordLabel";
        this->RecordLabel->Size = System::Drawing::Size(152, 24);
        this->RecordLabel->TabIndex = 0;
        this->RecordLabel->Text = L"Recording to file";
        //
        // SpeakToMicro
        //
        this->SpeakToMicro->BackColor = System::Drawing::Color::Green;
        this->SpeakToMicro->Font = (gcnew System::Drawing::Font(
            L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->SpeakToMicro->ForeColor = System::Drawing::Color::White;
        this->SpeakToMicro->Location = System::Drawing::Point(3, 27);
        this->SpeakToMicro->Name = L"SpeakToMicro";
        this->SpeakToMicro->Size = System::Drawing::Size(199, 85);
        this->SpeakToMicro->TabIndex = 1;
        this->SpeakToMicro->Text = L"Record";
        this->SpeakToMicro->UseVisualStyleBackColor = false;
        this->SpeakToMicro->Click +=
            gcnew System::EventHandler(this, &RecordToFileWindow::SpeakToMicro_Click);
        //
        // StopSpeakToMicro
        //
        this->StopSpeakToMicro->BackColor = System::Drawing::Color::Orange;
        this->StopSpeakToMicro->Font = (gcnew System::Drawing::Font(
            L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->StopSpeakToMicro->ForeColor = System::Drawing::Color::White;
        this->StopSpeakToMicro->Location = System::Drawing::Point(3, 118);
        this->StopSpeakToMicro->Name = L"StopSpeakToMicro";
        this->StopSpeakToMicro->Size = System::Drawing::Size(199, 90);
        this->StopSpeakToMicro->TabIndex = 1;
        this->StopSpeakToMicro->Text = L"Stop";
        this->StopSpeakToMicro->UseVisualStyleBackColor = false;
        this->StopSpeakToMicro->Click +=
            gcnew System::EventHandler(this, &RecordToFileWindow::StopSpeakToMicro_Click);
        //
        // ReturnToMainWindow
        //
        this->ReturnToMainWindow->BackColor = System::Drawing::Color::Crimson;
        this->ReturnToMainWindow->Font = (gcnew System::Drawing::Font(
            L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
        this->ReturnToMainWindow->ForeColor = System::Drawing::Color::White;
        this->ReturnToMainWindow->Location = System::Drawing::Point(3, 214);
        this->ReturnToMainWindow->Name = L"ReturnToMainWindow";
        this->ReturnToMainWindow->Size = System::Drawing::Size(199, 91);
        this->ReturnToMainWindow->TabIndex = 1;
        this->ReturnToMainWindow->Text = L"Back";
        this->ReturnToMainWindow->UseVisualStyleBackColor = false;
        this->ReturnToMainWindow->Click += gcnew System::EventHandler(
            this, &RecordToFileWindow::ReturnToMainWindow_Click);
        //
        // RecordToFileWindow
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(435, 390);
        this->Controls->Add(this->flowLayoutPanel1);
        this->Name = L"RecordToFileWindow";
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
        this->Text = L"Record from micro to file";
        this->flowLayoutPanel1->ResumeLayout(false);
        this->flowLayoutPanel1->PerformLayout();
        this->ResumeLayout(false);
    }
#pragma endregion
    /// ## Метод записи
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void SpeakToMicro_Click(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод остановки записи
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void StopSpeakToMicro_Click(System::Object ^ sender, System::EventArgs ^ e);
    
    /// ## Метод возвращения к родительскому окну
    ///
    /// @param [in] sender System::Object^ предоставляет ссылку на объект, вызвавший
    /// событие
    /// @param [in] e System::EventArgs^ передает объект, относящийся к
    /// обрабатываемому событию
    private: System::Void ReturnToMainWindow_Click(System::Object ^ sender, System::EventArgs ^ e);
};
}  // namespace NoiseImmunityAppClient
