#include "MainWindow.h"
#include "..\..\ClientServer\AudioRecording\AudioRecorder.h"
#include "..\..\ClientServer\Client.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute] 
int main(array<String ^> ^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    NoiseImmunityAppClient::MainWindowClient form;
    Application::Run(% form);
}

System::Void NoiseImmunityAppClient::MainWindowClient::Play_Click(System::Object^ sender, System::EventArgs^ e)
{
    //Обработка имени файла, введенного пользователем
    String ^ file_name = FileName->Text;
	using namespace Runtime::InteropServices;
    const char* FileName =
        (const char*)(Marshal::StringToHGlobalAnsi(file_name)).ToPointer();
    AudioRecorder().PlayAudio(FileName);

}

//Убираем подсказку с поля ввода имени файла
System::Void NoiseImmunityAppClient::MainWindowClient::FileName_Enter(System::Object^ sender, System::EventArgs^ e)
{
	if (FileName->Text == "Enter file name...") {
		FileName->Text = "";
	}
}

//Возвращаем подсказку с поля ввода имени файла
System::Void NoiseImmunityAppClient::MainWindowClient::FileName_Leave(System::Object^ sender, System::EventArgs^ e)
{
	if (FileName->Text == "") {
		FileName->Text = "Enter file name...";
	}
}

//подсказка на ввод IP
System::Void NoiseImmunityAppClient::MainWindowClient::IP_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (IP->Text == "Enter IP ...") {
		IP->Text = "";
	}
}

//возврат подсказки на ввод IP
System::Void NoiseImmunityAppClient::MainWindowClient::IP_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (IP->Text == "") {
		IP->Text = "Enter IP ...";
	}
}

//подсказка на ввод Port
System::Void NoiseImmunityAppClient::MainWindowClient::Port_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (Port->Text == "Enter Port ...") {
		Port->Text = "";
	}
}

//возврат подсказки на ввод Port
System::Void NoiseImmunityAppClient::MainWindowClient::Port_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (Port->Text == "") {
		Port->Text = "Enter Port ...";
	}
}

//запись с микрофона в файл
System::Void NoiseImmunityAppClient::MainWindowClient::WriteToFileFromMicro_Click(System::Object^ sender, System::EventArgs^ e)
{

	//Обработка имени файла, введенного пользователем
	String^ file_name = FileName->Text;
    using namespace Runtime::InteropServices;
    const char* FileName = (const char*)(Marshal::StringToHGlobalAnsi(file_name)).ToPointer();

	//тута переходим в другое окно для записи
    RecordToFileWindow^ recordWindow = gcnew RecordToFileWindow(FileName); //создаем новый экземпляр
    recordWindow->Owner = this;
	recordWindow->Show(); //открываем
	MainWindowClient::Hide(); //скрываем главное меню
}

//выход из программы
System::Void NoiseImmunityAppClient::MainWindowClient::Exit_Click(System::Object^ sender, System::EventArgs^ e)
{
	exit(0);
}

//приконнектиться к серверу
System::Void NoiseImmunityAppClient::MainWindowClient::ConnectServer_Click(
    System::Object ^ sender, System::EventArgs ^ e)
{
	//Обработка IP/PORT, введенных пользователем
	String^ ip = IP->Text;
	String^ port = Port->Text;
	using namespace Runtime::InteropServices;
	const char* IP = (const char*)(Marshal::StringToHGlobalAnsi(ip)).ToPointer();
	using namespace Runtime::InteropServices;
    unsigned int Port = Int32::Parse(port);

	Client* AudioClient = new Client();

        //если успешно приконнектились то открываем форму звонка/отправки файла
        CallingSendingWindow ^ Window =
        gcnew CallingSendingWindow(this, IP, Port);  //создаем новый экземпляр
        MainWindowClient::Hide();
 
}
