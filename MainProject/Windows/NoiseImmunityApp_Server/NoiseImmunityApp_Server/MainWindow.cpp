#include "MainWindow.h"
#include <clocale>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	NoiseImmunityAppServer::MainWindowServer form;
	Application::Run(% form);
}

//изменение параметров среды
System::Void NoiseImmunityAppServer::MainWindowServer::ChangeParams_Click(System::Object^ sender, System::EventArgs^ e)
{
	ParamsWindow^ prm = gcnew ParamsWindow(AudioServer); 
	prm->Owner = this;
	prm->Show(); 
	this->Hide();
}

//выход
System::Void NoiseImmunityAppServer::MainWindowServer::Exit_Click(System::Object^ sender, System::EventArgs^ e)
{
	AudioServer->EndServer();
	exit(0);
}

//cтарт сервера
System::Void NoiseImmunityAppServer::MainWindowServer::StartServer_Click(System::Object^ sender, System::EventArgs^ e)
{
	//код запуска сервака

	//Обработка IP/PORT, введенных пользователем
	String^ ip = IP->Text;
	String^ port = Port->Text;

	using namespace Runtime::InteropServices;
	const char* IP = (const char*)(Marshal::StringToHGlobalAnsi(ip)).ToPointer();
	unsigned int Port = Int32::Parse(port);

	if (AudioServer->StartServer(IP, Port)) {
		/// Разблокировка кнопок
		ChangeParams->Enabled = true;
		MessageBox::Show("Server was started.");
	}
	else 
	{
		MessageBox::Show("Server was NOT started!!!");
	}


}

//подсказка на ввод IP
System::Void NoiseImmunityAppServer::MainWindowServer::IP_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (IP->Text == "Enter IP...") {
		IP->Text = "";
	}
}

//возврат подсказки на ввод IP
System::Void NoiseImmunityAppServer::MainWindowServer::IP_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (IP->Text == "") {
		IP->Text = "Enter IP...";
	}
}

//подсказка на ввод Port
System::Void NoiseImmunityAppServer::MainWindowServer::Port_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (Port->Text == "Enter Port...") {
		Port->Text = "";
	}
}

//возврат подсказки на ввод Port
System::Void NoiseImmunityAppServer::MainWindowServer::Port_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (Port->Text == "") {
		Port->Text = "Enter Port...";
	}
}
