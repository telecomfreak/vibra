#ifndef WAV_H
#define WAV_H

#include <string>
#include <vector>
#include <memory>
#include "byte_control.h"

using Sample = std::int16_t;
using Raw16bitPCM = std::vector<Sample>;

constexpr std::uint32_t LOW_QUALITY_SAMPLE_RATE = 16000;
constexpr std::uint32_t LOW_QUALITY_SAMPLE_WIDTH = 16;
class Wav
{
public:
    Wav(const std::string& wav_file_path);
    Wav(const char* raw_wav, std::uint32_t raw_wav_size);
    Wav(const char* raw_pcm, std::uint32_t raw_pcm_size, std::uint32_t sample_rate, std::uint32_t sample_width, std::uint32_t channel_count);
    ~Wav();

    inline std::uint32_t GetAudioFormat() { return mAudioFormat; }
    inline std::uint32_t GetChannel() { return mChannel; }
    inline std::uint32_t GetSampleRate() { return mSampleRate; }
    inline std::uint32_t GetBitPerSample() { return mBitPerSample; }
    inline std::uint32_t GetDataSize() { return mDataSize; }
    inline std::uint32_t GetFileSize() { return mFileSize; }
    inline std::shared_ptr<std::uint8_t> GetData() const { return mData; }
    void GetLowQualityPCM(Raw16bitPCM* raw_pcm) const;

private:
    void readWavFile(const std::string& wav_file_path);
    void readWavBuffer(std::istream& stream);

    inline Sample stereoToMonoSample(std::uint32_t width, const void* data, std::uint32_t index) const;
    inline Sample monoToMonoSample(std::uint32_t width, const void* data, std::uint32_t index) const;
    inline Sample getMonoSample(std::uint32_t width, const void* data, std::uint32_t index) const;


private:
    std::string mWavFilePath;
    std::uint32_t mAudioFormat;
    std::uint32_t mChannel;
    std::uint32_t mSampleRate;
    std::uint32_t mBitPerSample;
    std::uint32_t mDataSize;
    std::uint32_t mFileSize;
    std::shared_ptr<std::uint8_t> mData;
};

#endif // WAV_H