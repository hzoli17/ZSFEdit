#ifndef AUDIO_H
#define AUDIO_H
#include <cstdlib>
#include <string>
#include <QString>
#include <QDebug>
#include <QObject>
namespace Audio
{
    // Get
    unsigned int getAudioOutputCount();
    unsigned int getAudioInputCount();
    unsigned int getDefaultOutputDevice();
    unsigned int getDefaultInputDevice();
    unsigned int getSampleRate();
    unsigned int getBufferFrames();
    float * getOutputBuffer();
    float * getInputBuffer();
    QString getOutError();
    QString getInError();
    QString getOutDeviceName(unsigned int device);
    QString getInDeviceName(unsigned int device);
    // Set
    bool openAudioOutputDevice(unsigned int device);
    bool openAudioInputDevice(unsigned int device);
    void setSampleRate(unsigned int samplerate = 44100);
    void setBufferFrames(unsigned int bufferframes = 256);
}
#endif // AUDIO_H
