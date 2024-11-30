#include "AudioEngine.hpp"


void AudioEngine::stop() {
    {
        std::unique_lock<std::mutex> lock(mutex_);
        please_stop_ = true;
    }
    cv_.notify_all();
}

void AudioEngine::entry() {
    // Nothing to do but hang around for now.
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this]{ return please_stop_; });
}

