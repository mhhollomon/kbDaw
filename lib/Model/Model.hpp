#pragma once

#include <string>
#include <map>
#include <vector>

#include <mutex>
#include <stdexcept>


enum class TrackType {
    Normal,
    Folder,
    Group
};

struct TrackInfo {

    long uuid_;
    TrackType ttype_ = TrackType::Normal;
    std::string name_;
    bool mute_ = false;
    bool solo_ = false;

    TrackInfo(long uuid, std::string name = "") : uuid_(uuid), name_(name) {}
    TrackInfo(long uuid, TrackType ttype) : 
            uuid_(uuid), ttype_(ttype) {}

};

struct TrackBundleInfo {
    long uuid_;
    long parent_;

    TrackBundleInfo(long uuid, long parent = -1) : 
            uuid_(uuid), parent_(parent) {}
};
