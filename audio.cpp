#include "audio.h"
#include "RtAudio.h"
RtAudio dac, adc;
std::string outError, inError;
bool outIsOpened = false, inIsOpened = false;
unsigned int sampleRate = 44100;
unsigned int bufferFrames = 256;
float * outBuffer, * inBuffer;

int audioOutputCallback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    static unsigned int i;
    float *buffer = (float *) outputBuffer;
    Q_UNUSED(inputBuffer);
    Q_UNUSED(userData);
    Q_UNUSED(streamTime);
    if (status) qDebug() << QObject::tr("Stream overflow detected in audio output stream!");
    for (i=0;i<nBufferFrames;i++)
    {
        *buffer++ = outBuffer[i];
    }
    return 0;
}

int audioInputCallback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    static unsigned int i;
    float *buffer = (float *) inputBuffer;
    Q_UNUSED(outputBuffer);
    Q_UNUSED(userData);
    Q_UNUSED(streamTime);
    if (status) qDebug() << QObject::tr("Stream overflow detected in audio input stream!");
    for (i=0;i<nBufferFrames;i++)
    {
        *buffer++ = inBuffer[i];
    }
    return 0;
}

unsigned int Audio::getAudioOutputCount()
{
    unsigned int num = 0;
    unsigned int deviceCount=dac.getDeviceCount();
    for (unsigned int i=0;i<deviceCount;i++)
    {
        if (dac.getDeviceInfo(i).outputChannels) num++;
    }
    return num;
}

unsigned int Audio::getAudioInputCount()
{
    unsigned int num = 0;
    unsigned int deviceCount=adc.getDeviceCount();
    for (unsigned int i=0;i<deviceCount;i++)
    {
        if(adc.getDeviceInfo(i).inputChannels) num++;
    }
    return num;
}

unsigned int Audio::getDefaultOutputDevice()
{
    return dac.getDefaultOutputDevice();
}

unsigned int Audio::getDefaultInputDevice()
{
    return adc.getDefaultInputDevice();
}

unsigned int Audio::getSampleRate()
{
    return sampleRate;
}

unsigned int Audio::getBufferFrames()
{
    return bufferFrames;
}

float * Audio::getOutputBuffer()
{
    return outBuffer;
}

float * Audio::getInputBuffer()
{
    return inBuffer;
}

bool Audio::openAudioOutputDevice(unsigned int device)
{
    RtAudio::StreamParameters p;
    double data[2];
    if (outIsOpened) return false;
    p.deviceId = device;
    p.firstChannel = 0;
    p.nChannels = 2;
    try
    {
        dac.openStream(&p, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, &audioOutputCallback, (void*)&data);
        dac.startStream();
    }
    catch (RtAudioError& e)
    {
        outError = e.getMessage();
        return false;
    }
    outBuffer=(float*)calloc(bufferFrames, sizeof(float));
    outIsOpened=true;
    return true;
}

bool Audio::openAudioInputDevice(unsigned int device)
{
    RtAudio::StreamParameters p;
    double data[2];
    if (inIsOpened) return false;
    p.deviceId = device;
    p.firstChannel = 0;
    p.nChannels = 2;
    try
    {
        adc.openStream(NULL, &p, RTAUDIO_FLOAT64, sampleRate, &bufferFrames, &audioInputCallback, (void*)&data);
        adc.startStream();
    }
    catch (RtAudioError& e)
    {
        inError = e.getMessage();
        return false;
    }
    inBuffer=(float*)calloc(bufferFrames, sizeof(float));
    inIsOpened=true;
    return true;
}

void Audio::setSampleRate(unsigned int samplerate)
{
    sampleRate = samplerate;
}

void Audio::setBufferFrames(unsigned int bufferframes)
{
    bufferFrames = bufferframes;
}

QString Audio::getOutError()
{
    return QString::fromStdString(outError);
}

QString Audio::getInError()
{
    return QString::fromStdString(inError);
}

QString Audio::getOutDeviceName(unsigned int device)
{
    if (dac.getDeviceCount()>device)
        return QString::fromStdString(dac.getDeviceInfo(device).name);
    return QObject::tr("Unknown audio output device");
}

QString Audio::getInDeviceName(unsigned int device)
{
    if (dac.getDeviceCount()>device)
        return QString::fromStdString(adc.getDeviceInfo(device).name);
    return QObject::tr("Unknown audio input device");
}
