#include "CallingSendingWindow.h"

System::Void NoiseImmunityAppClient::CallingSendingWindow::Call_Click(
    System::Object ^ sender, System::EventArgs ^ e)
{  
    this->Hide();
    if (MessageBox::Show("Record calling to the file?", "Recording",
                         MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
        System::Windows::Forms::DialogResult::Yes)
    {
        //код записи

        //тута переходим в другое окно дл¤ ввода имени файла
        FileNameWindowForCalling ^ fileNameWindow =
            gcnew FileNameWindowForCalling(this, IP,Port);  //создаем новый экземпл¤р
        //fileNameWindow->Owner = this;
        //fileNameWindow->Show();  //открываем 
    }
    else
    {
        MessageBox::Show("Recording isn't start");
        //тута переходим в другое окно дл¤ звонка
        CallWindow ^ cllWindow =
            gcnew CallWindow(this, IP, Port);  //создаем новый экземпл¤р
        //cllWindow->Owner = this;
        //cllWindow->Show();  //открываем  
    }
}

//отправка файла
System::Void NoiseImmunityAppClient::CallingSendingWindow::SendFile_Click(
    System::Object ^ sender, System::EventArgs ^ e)
{
    Client* AudioClient=new Client();
    if (AudioClient->ConnectToServer(IP, Port))
    {
        //тута пишем отправку
        //тута переходим в другое окно дл¤ ввода имени файла
        FileNameForSendingWindow ^ fileWindow =
            gcnew FileNameForSendingWindow(AudioClient);  //создаем новый экземпл¤р
        fileWindow->Owner = this;
        fileWindow->Show();  //открываем
        this->Hide(); 
    }

}

//вернутьс¤
System::Void NoiseImmunityAppClient::CallingSendingWindow::Back_Click(System::Object ^ sender, System::EventArgs ^ e)
{
    this->Owner->Show();
    Close();  //закрыть окно
}
