#include "FileNameForSendingWindow.h"

//отправка этого файла
System::Void NoiseImmunityAppClient::FileNameForSendingWindow::OK_Click(
    System::Object ^ sender, System::EventArgs ^ e)
{
    String ^ file = fileName->Text;
    using namespace Runtime::InteropServices;
    const char* FileName =
        (const char*)(Marshal::StringToHGlobalAnsi(file)).ToPointer();

    printf("%s\n", FileName);
    bool SendFileComplete = AudioClient->SendFile(FileName);

    //если отправка успешна пишем это
    if (SendFileComplete == true)
        MessageBox::Show("File send successfully!");
    else  //иначе пишем это
        MessageBox::Show("File send unsuccessfully(");
    AudioClient->DisconnectFromServer();
    this->Owner->Show();
    Close();  //закрыть окно
}

System::Void NoiseImmunityAppClient::FileNameForSendingWindow::file_enter(
    System::Object ^ sender, System::EventArgs ^ e)
{
    if (fileName->Text == "Enter file name...")
    {
        fileName->Text = "";
    }
}

System::Void NoiseImmunityAppClient::FileNameForSendingWindow::file_leave(
    System::Object ^ sender, System::EventArgs ^ e)
{
    if (fileName->Text == "")
    {
        fileName->Text = "Enter file name...";
    }
}
