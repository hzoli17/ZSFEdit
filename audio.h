#ifndef AUDIO_H
#define AUDIO_H
namespace Audio
{
    // Get
    unsigned int getAudioOutputCount();
    unsigned int getAudioInputCount();
    unsigned int getDefaultOutputDevice();
    unsigned int getDefaultInputDevice();
}
#endif // AUDIO_H
