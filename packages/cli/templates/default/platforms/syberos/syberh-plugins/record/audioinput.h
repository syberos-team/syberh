#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H
#include <QAudioInput>
#include <QFile>
class AudioInput : public QObject
{
    Q_OBJECT
public:
    AudioInput(QObject *parent = 0);
    ~AudioInput();

    void setFilePath(const QString &filePath);
    QAudioInput* audio;
public Q_SLOTS:
    void record();
    int stop();
    void resume();
    void suspend();
public slots:
    void handleStateChanged(QAudio::State);
private:
    QFile file;
  
    QAudioFormat format;
    QAudioDeviceInfo info;

    // WAV header stuff

    struct chunk
    {
        char        id[4];
        quint32     size;
    };

    struct RIFFHeader
    {
        chunk       descriptor;
        char        type[4];
    };

    struct WAVEHeader
    {
        chunk       descriptor;
        quint16     audioFormat;        // PCM = 1
        quint16     numChannels;
        quint32     sampleRate;
        quint32     byteRate;
        quint16     blockAlign;
        quint16     bitsPerSample;
    };

    struct DATAHeader
    {
        chunk       descriptor;
//        quint8      data[];
    };

    struct CombinedHeader
    {
        RIFFHeader  riff;
        WAVEHeader  wave;
        DATAHeader  data;
    };

    CombinedHeader      header;

};

#endif // AUDIOINPUT_H
