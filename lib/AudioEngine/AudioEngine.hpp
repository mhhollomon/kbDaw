#pragma once

#include "Model/RTModel.hpp"

#include <mutex>

class AudioEngine {

    RTModel model_;

    bool please_stop_ = false;

    std::mutex mutex_;
    std::condition_variable cv_;

public :
    AudioEngine() = default;

    RTModel &get_model() {
        return model_;
    }

    std::thread *run() {
        return new std::thread(&AudioEngine::entry, this);
    }

    void entry();

    void stop();


};