#pragma once

#include "../../ClientServer/AudioRecording/AudioRecorder.h"
#include <thread>
#include <iostream>

class MicroRecording
{
public:
    MicroRecording(const char* FileName);
    ~MicroRecording();
    void PauseRecording();
    void ResumeRecording();

private:
    bool IsRecordingNow;
    bool IsRecordingEnd;
    bool IsRecording;
    AudioRecorder Microphone;

    void Recording();
};