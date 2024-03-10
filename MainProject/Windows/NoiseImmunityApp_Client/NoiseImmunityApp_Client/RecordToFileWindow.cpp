#include "RecordToFileWindow.h"

//начать запись
System::Void NoiseImmunityAppClient::RecordToFileWindow::SpeakToMicro_Click(System::Object^ sender, System::EventArgs^ e)
{
    SpeakToMicro->Enabled = false;     //блок кнопки говорить
    StopSpeakToMicro->Enabled = true;  //включение кнопки стоп
    FileRecording->ResumeRecording();
    

}

//остановить запись
System::Void NoiseImmunityAppClient::RecordToFileWindow::StopSpeakToMicro_Click(System::Object^ sender, System::EventArgs^ e)
{
	SpeakToMicro->Enabled = true; //включение кнопки говорить
	StopSpeakToMicro->Enabled = false; //блок кнопки стоп
    FileRecording->PauseRecording();
}

//вернутьс¤ в главное меню
System::Void NoiseImmunityAppClient::RecordToFileWindow::ReturnToMainWindow_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->Owner->Show();  //открываем
	//тута переходим в другое окно 
	Close();

}
