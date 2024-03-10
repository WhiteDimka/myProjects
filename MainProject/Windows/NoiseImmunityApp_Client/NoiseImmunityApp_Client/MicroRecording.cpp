#include "MicroRecording.h"

MicroRecording::MicroRecording(const char*FileName)
{
    IsRecordingNow = false;    
    Microphone.StartPlayingAndRecordingToFile(FileName);
    IsRecording = true;   
    IsRecordingEnd = false;
    new std::thread(&MicroRecording::Recording, this);
}

MicroRecording::~MicroRecording()
{
    IsRecordingNow = false;
    IsRecording = false;
    while (!IsRecordingEnd)
    {
    }
    Microphone.StopRecording();
    std::cout << "File Recording end.\n";
}

void MicroRecording::PauseRecording()
{
    IsRecordingNow = false;
}

void MicroRecording::ResumeRecording()
{
    IsRecordingNow = true;
}

void MicroRecording::Recording()
{
    int Size;
    while (IsRecording)
    {
        while (IsRecordingNow)
        {
            Microphone.RecordOnePart(Size);
            if (Size < 0)
            {
                std::cout << "Recording Error!\n";
                return;
            }
        }
    }
    IsRecordingEnd = true;
}
