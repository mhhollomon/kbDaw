#pragma once

#include "Model.hpp"
#include "sqlite3.h"

#include <string>

class FullModel {
    bool open_ = false;
    bool modified_ = false;
    std::shared_ptr<sqlite3> db_conn_ = nullptr;

    static constexpr int VERSION = 0;
    static const std::string DB_URI;

    bool build_skeleton();

public :
    bool is_open() const { return open_; }
    bool is_modified() const { return modified_; }

    void open_model(const std::string &file_name);
    bool close_model(bool force = false);

    std::vector<TrackBundleInfo> get_track_list();
    TrackInfo get_track_info(long uuid);

};