#include "CallWindow.h"
#include "MainWindow.h"

//нажать на кнопку говорить
System::Void NoiseImmunityAppClient::CallWindow::SpeakButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	IsMicroOn = true;
	if (AudioClient->SetMute(!IsMicroOn)) 
	{
		SpeakButton->Visible = false; //скрыть кнопку говорить

		//и тут крч создаем новую кнопку "не говорть"
		PressedButton = gcnew Button();
		PressedButton->BackColor = System::Drawing::Color::DarkOrange;
		PressedButton->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		PressedButton->ForeColor = System::Drawing::Color::White;
		PressedButton->Location = System::Drawing::Point(73, 41);
		PressedButton->Name = L"DontSpeakButton";
		PressedButton->Size = System::Drawing::Size(135, 58);
		PressedButton->TabIndex = 0;
		PressedButton->Text = L"Micro is off";
		PressedButton->UseVisualStyleBackColor = false;
		PressedButton->Click += gcnew System::EventHandler(this, &CallWindow::PressedButton_click);
		this->Controls->Add(PressedButton);
	}
	else
	{
		IsMicroOn = false;
	}

}

//завершить звонок
System::Void NoiseImmunityAppClient::CallWindow::EndCall_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Owner->Show();
	Close(); //закрыть окно
}

//нажать на кнопку не говорить
void NoiseImmunityAppClient::CallWindow::PressedButton_click(Object^ sender, EventArgs^ e)
{
	this->PressedButton->Visible = false; //скрыть кнопку "не говорить"
	this->SpeakButton->Visible = true;	  //показать кнопку "говорить"

	IsMicroOn = false;
	/// Возможно нужен if(AudioClient->SetMute(!IsMicroOn)){}
	AudioClient->SetMute(!IsMicroOn);
}
