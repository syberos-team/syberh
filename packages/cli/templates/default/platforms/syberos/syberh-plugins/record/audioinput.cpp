#include "audioinput.h"
#include <QDebug>

#define _CHANNEL_COUNT 1 
#define _SAMPLE_RATE 8000 
#define _SAMPLE_BITS 16

AudioInput::AudioInput(QObject *parent)
{
    // Set up the desired format, for example:

    format.setSampleRate(_SAMPLE_RATE);
    format.setChannelCount(_CHANNEL_COUNT);
    format.setSampleSize(_SAMPLE_BITS);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        format = info.nearestFormat(format);
    }
    format.setCodec(info.supportedCodecs().at(0));
    audio = new QAudioInput(format, this);
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

}
AudioInput::~AudioInput(){
    delete audio;
}

void AudioInput::setFilePath(const QString &filePath)
{
    file.setFileName(filePath);
}

void AudioInput::record(){
    if(file.open( QIODevice::WriteOnly | QIODevice::Truncate )) {
        memset(&header,0,sizeof(CombinedHeader));
        memcpy(header.riff.descriptor.id,"RIFF",4);
        header.riff.descriptor.size = 0xFFFFFFFF; // This should be updated on stop(), filesize-8
        memcpy(header.riff.type,"WAVE",4);
        memcpy(header.wave.descriptor.id,"fmt ",4);
        header.wave.descriptor.size = 16;
        header.wave.audioFormat = 1; // for PCM data
        header.wave.numChannels = _CHANNEL_COUNT;
        header.wave.sampleRate = _SAMPLE_RATE;
        header.wave.byteRate = _SAMPLE_RATE * _CHANNEL_COUNT * _SAMPLE_BITS / 8;
        header.wave.blockAlign = _CHANNEL_COUNT * _SAMPLE_BITS / 8;
        header.wave.bitsPerSample = _SAMPLE_BITS;
        memcpy(header.data.descriptor.id,"data",4);
        header.data.descriptor.size = 0xFFFFFFFF; // This should be updated on stop(),samples*channels*sampleSize/8
        file.write((char*)&header,sizeof(CombinedHeader));

        audio->start(qobject_cast<QIODevice*>(&file));
    } else {
        delete audio;
        audio = 0;
    }
}
int AudioInput::stop(){
     int duration =static_cast<int>(audio->processedUSecs());
    audio->stop();
    file.close();
    qint32 fileSize = file.size();
    file.open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    file.read((char*)&header,sizeof(CombinedHeader));
    header.riff.descriptor.size = fileSize - 8; // The RIFF chunk size is the file size minus
    // the first two RIFF fields (8 bytes)
    header.data.descriptor.size = fileSize - 44; // dataSize = fileSize - headerSize (44 bytes)
    file.seek(0);
    file.write((char*)&header,sizeof(CombinedHeader));
    file.close();
    delete audio;
    audio = 0;

    return duration;
}


void AudioInput::suspend(){
     qWarning() <<Q_FUNC_INFO<< "suspend:";
    audio->suspend();
}
void AudioInput::resume(){
    qWarning() <<Q_FUNC_INFO<< "resume:";
    audio->resume();
}


void AudioInput::handleStateChanged(QAudio::State newState)
{
     qWarning() <<Q_FUNC_INFO<< "handleStateChanged:"<<newState;
    switch (newState) {
        case QAudio::StoppedState:
            if (audio->error() != QAudio::NoError) {
                // Error handling
            } else {
                // Finished recording
            }
            break;

        case QAudio::ActiveState:
            // Started recording - read from IO device
            break;

        default:
            // ... other cases as appropriate
            break;
    }
}

