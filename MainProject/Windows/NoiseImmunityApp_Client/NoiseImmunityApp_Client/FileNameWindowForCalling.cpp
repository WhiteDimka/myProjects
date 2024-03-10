#include "FileNameWindowForCalling.h"

//переход на форму звонка
System::Void NoiseImmunityAppClient::FileNameWindowForCalling::OK_button_Click(
    System::Object ^ sender, System::EventArgs ^ e)
{
    String ^ filename = FileName->Text;
    // System::String -> const char*
    using namespace Runtime::InteropServices;
    const char* file = (const char*)(Marshal::StringToHGlobalAnsi(filename)).ToPointer();

    //тута переходим в другое окно для звонка
    CallWindow ^ callWindow =
        gcnew CallWindow((System::Windows::Forms::Form ^) this->Owner, IP,Port,
                         file);  //создаем новый экземпл¤р
    // callWindow->Owner = this;
    // callWindow->Show();                                          //открываем
    Close();
}

//показать подсказку на ввод имени файла
System::Void NoiseImmunityAppClient::FileNameWindowForCalling::FileName_Enter(
    System::Object ^ sender, System::EventArgs ^ e)
{
    if (FileName->Text == "Enter file name for recording...")
    {
        FileName->Text = "";
    }
}

//убрать подсказку на ввод имени файла
System::Void NoiseImmunityAppClient::FileNameWindowForCalling::FileName_Leave(
    System::Object ^ sender, System::EventArgs ^ e)
{
    if (FileName->Text == "")
    {
        FileName->Text = "Enter file name for recording...";
    }
}
