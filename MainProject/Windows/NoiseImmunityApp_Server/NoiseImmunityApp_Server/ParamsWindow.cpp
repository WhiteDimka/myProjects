#include "ParamsWindow.h"

System::String^ NoiseImmunityAppServer::ParamsWindow::ConvertToNumberString(String^ StringFromTextBox)
{
	std::string NumberString= msclr::interop::marshal_as<std::string>(StringFromTextBox);

	std::size_t found = NumberString.find_first_not_of("0123456789");

	if (found != std::string::npos)
	{
		return "0";
	}
	return StringFromTextBox;
}

//разблокирует кнопку Apply при изменении textbox
System::Void NoiseImmunityAppServer::ParamsWindow::Min_Latency_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	Apply->Enabled = true;
}

//разблокирует кнопку Apply при изменении textbox
System::Void NoiseImmunityAppServer::ParamsWindow::MaxLatency_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	Apply->Enabled = true;
}

//разблокирует кнопку Apply при изменении textbox
System::Void NoiseImmunityAppServer::ParamsWindow::PacketLossProbability_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	Apply->Enabled = true;
}

//разблокирует кнопку Apply при изменении textbox
System::Void NoiseImmunityAppServer::ParamsWindow::PacketMixingProbability_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	Apply->Enabled = true;
}

//разблокирует кнопку Apply при изменении textbox
System::Void NoiseImmunityAppServer::ParamsWindow::NoiseRate_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	Apply->Enabled = true;
}

//разблокирует кнопку Apply при изменении textbox
System::Void NoiseImmunityAppServer::ParamsWindow::NoiseIntensivity_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	Apply->Enabled = true;
}

//вернуться в главное меню
System::Void NoiseImmunityAppServer::ParamsWindow::ReturnToMain_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->AudioServer != nullptr)
	{
		this->AudioServer->DisableInterference();
	}
	Owner->Show();
	this->Hide();
}

//чекбокс latency
System::Void NoiseImmunityAppServer::ParamsWindow::checkBoxLatency_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxLatency->Checked)
	{
		Apply->Enabled = true;
		Min_Latency->Visible = true;
		MaxLatency->Visible = true;
	}
	else
	{
		Apply->Enabled = false;
		Min_Latency->Visible = false;
		MaxLatency->Visible = false;
	}

}

//чекбокс loss
System::Void NoiseImmunityAppServer::ParamsWindow::checkBoxLoss_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxLoss->Checked)
	{
		Apply->Enabled = true;
		PacketLossProbability->Visible = true;
	}
	else
	{
		Apply->Enabled = false;
		PacketLossProbability->Visible = false;
	}
}

//чекбокс mixing
System::Void NoiseImmunityAppServer::ParamsWindow::checkBoxMixing_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxMixing->Checked)
	{
		Apply->Enabled = true;
		PacketMixingProbability->Visible = true;
	}
	else
	{
		Apply->Enabled = false;
		PacketMixingProbability->Visible = false;
	}
}

//чекбокс Jitter
System::Void NoiseImmunityAppServer::ParamsWindow::checkBoxInterference_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (checkBoxInterference->Checked)
	{
		Apply->Enabled = true;
		NoiseRate->Visible = true;
		NoiseIntensivity->Visible = true;
	}
	else
	{
		Apply->Enabled = false;
		NoiseRate->Visible = false;
		NoiseIntensivity->Visible = false;
	}
}

//подсказка на ввод NoiseIntensivity
System::Void NoiseImmunityAppServer::ParamsWindow::NoiseIntensivity_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (NoiseIntensivity->Text == "Enter noise intensivity [0;280]...") {
		NoiseIntensivity->Text = "";
	}
}

//возврат подсказки на ввод NoiseIntensivity
System::Void NoiseImmunityAppServer::ParamsWindow::NoiseIntensivity_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (NoiseIntensivity->Text == "") {
		NoiseIntensivity->Text = "Enter noise intensivity [0;280]...";
	}
}

//подсказка на ввод NoiseRate
System::Void NoiseImmunityAppServer::ParamsWindow::NoiseRate_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (NoiseRate->Text == "Enter noise rate [0;100]...") {
		NoiseRate->Text = "";
	}
}

//возврат подсказки на ввод NoiseRate
System::Void NoiseImmunityAppServer::ParamsWindow::NoiseRate_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (NoiseRate->Text == "") {
		NoiseRate->Text = "Enter noise rate [0;100]...";
	}
}

//подсказка на ввод Min_Latency
System::Void NoiseImmunityAppServer::ParamsWindow::Min_Latency_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (Min_Latency->Text == "Enter min latency (mc/pac)...") {
		Min_Latency->Text = "";
	}
}

//возврат подсказки на ввод Min_Latency
System::Void NoiseImmunityAppServer::ParamsWindow::Min_Latency_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (Min_Latency->Text == "") {
		Min_Latency->Text = "Enter min latency (mc/pac)...";
	}
}

//подсказка на ввод MaxLatency
System::Void NoiseImmunityAppServer::ParamsWindow::MaxLatency_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (MaxLatency->Text == "Enter max latency (mc/pac)...") {
		MaxLatency->Text = "";
	}
}

//возврат подсказки на ввод MaxLatency
System::Void NoiseImmunityAppServer::ParamsWindow::MaxLatency_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (MaxLatency->Text == "") {
		MaxLatency->Text = "Enter max latency (mc/pac)...";
	}
}

//подсказка на ввод PacketLossProbability
System::Void NoiseImmunityAppServer::ParamsWindow::PacketLossProbability_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (PacketLossProbability->Text == "Enter loss rate [0;100]...") {
		PacketLossProbability->Text = "";
	}
}

//возврат подсказки на ввод PacketLossProbability
System::Void NoiseImmunityAppServer::ParamsWindow::PacketLossProbability_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (PacketLossProbability->Text == "") {
		PacketLossProbability->Text = "Enter loss rate [0;100]...";
	}
}

//подсказка на ввод Packet Mixing Probability
System::Void NoiseImmunityAppServer::ParamsWindow::PacketMixingProbability_enter(System::Object^ sender, System::EventArgs^ e)
{
	if (PacketMixingProbability->Text == "Enter mixing rate [0;100]...") {
		PacketMixingProbability->Text = "";
	}
}

//возврат подсказки на ввод Packet Mixing Probability
System::Void NoiseImmunityAppServer::ParamsWindow::PacketMixingProbability_leave(System::Object^ sender, System::EventArgs^ e)
{
	if (PacketMixingProbability->Text == "") {
		PacketMixingProbability->Text = "Enter mixing rate [0;100]...";
	}
}

//переменные среды
System::Void NoiseImmunityAppServer::ParamsWindow::Apply_Click(System::Object^ sender, System::EventArgs^ e)
{
	if ((checkBoxLatency->Checked) && (Min_Latency->Text != "Enter min latency...") && (MaxLatency->Text != "Enter max latency..."))
	{
		//Latency
		String^ minLatency = ConvertToNumberString(Min_Latency->Text);
		String^ maxLatency = ConvertToNumberString(MaxLatency->Text);
		int minlatency = Int32::Parse(minLatency);
		int maxlatency = Int32::Parse(maxLatency);

		AudioServer->set_min_latency(minlatency);
		AudioServer->set_max_latency(maxlatency);
		AudioServer->set_latency_flag(true);
	}

	if ((checkBoxLoss->Checked) && (PacketLossProbability->Text != "Enter loss rate..."))
	{
		//Loss
		String^ packetLossProbability = ConvertToNumberString(PacketLossProbability->Text);
		int packetlossprobability = Int32::Parse(packetLossProbability);
		if (packetlossprobability >= 0 && packetlossprobability <= 100) {
			// 0-100
			AudioServer->set_loss_rate(packetlossprobability);
			AudioServer->set_loss_flag(true);
		}
		else {
			MessageBox::Show("Loss rate wasn't set, because it's not from 0 to 100!");
			AudioServer->set_loss_flag(false);
		}
	}

	if ((checkBoxMixing->Checked) && (PacketMixingProbability->Text != "Enter mixing rate..."))
	{
		//Mixing
		String^ packetMixingProbability = ConvertToNumberString(PacketMixingProbability->Text);
		int packetmixingProbability = Int32::Parse(packetMixingProbability);
		if (packetmixingProbability >= 0 && packetmixingProbability <= 100) {
			// 0-100
			AudioServer->set_mixing_rate(packetmixingProbability);
			AudioServer->set_mixing_flag(true);
		}
		else {
			MessageBox::Show("Mixing rate wasn't set, because it's not from 0 to 100!");
			AudioServer->set_mixing_flag(false);
		}
	}

	if ((checkBoxInterference->Checked) && (NoiseRate->Text != "Enter noise rate...") && (NoiseIntensivity->Text != "Enter noise intensivity..."))
	{
		//Interference
		String^ noiseRate = ConvertToNumberString(NoiseRate->Text);
		int noiserate = Int32::Parse(noiseRate);
		if (noiserate >= 0 && noiserate <= 100) {
			// 0-100
			AudioServer->set_noise_rate(noiserate);

			String^ noiseIntensivity = ConvertToNumberString(NoiseIntensivity->Text);
			int noiseintensivity = Int32::Parse(noiseIntensivity);
			if (noiseintensivity >= 0 && noiseintensivity <= 280) {
				// 0-280
				AudioServer->set_noise_intensivity(noiseintensivity);
				AudioServer->set_noise_flag(true);
			}
			else
			{
				MessageBox::Show("Noise intensivity wasn't set, because it's not from 0 to 280!");
				AudioServer->set_noise_flag(false);
			}
		}
		else
		{
			MessageBox::Show("Noise rate wasn't set, because it's not from 0 to 100!");
			AudioServer->set_noise_flag(false);
		}


	}
	Apply->Enabled = false;
}

