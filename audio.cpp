#include "audio.h"
#include "RtAudio.h"
RtAudio dac, adc;

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
