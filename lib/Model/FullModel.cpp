#include "sqlite_modern_cpp.h"

#include "FullModel.hpp"

#include "wx/log.h"

#include <stdexcept>


#include "SchemaCreation.cpp"

#define GET_DB() sqlite::database db(db_conn_)

const std::string FullModel::DB_URI = "file:fullmodel?mode=memory&cache=shared";
//const std::string FullModel::DB_URI = ":memory:";

bool FullModel::close_model(bool force) {
    if (! is_open()) {
        return true;
    }

    if (is_modified() && ! force) {
        return false;
    }

    db_conn_.reset();
    open_ = false;
    modified_ = false;

    return true;
}

void FullModel::open_model(const std::string & filename) {

    wxLogMessage("Attempting to open project file [%s]", filename);
    wxLogMessage("SQLite3 version == %s", sqlite3_libversion());

    if (is_open()) {
        throw new std::runtime_error("Model is already open");
    }

    try {
        sqlite::database db(FullModel::DB_URI);

        db_conn_ = db.connection();
        open_ = true;
        modified_ = false;

    } catch(sqlite::sqlite_exception& e) {
        wxLogMessage("Unable to open model db - (%d) %s", e.get_code(), e.what());
        throw e;
    }


    open_ = build_skeleton();
    if (! open_) {
        close_model(true);
    }

}

bool FullModel::build_skeleton() {

    GET_DB();

    char *errmsg = nullptr;


    try {
        for (const auto &entry : STEPS ) {
            wxLogMessage("Running %s", entry.name);
            db << entry.sql;
        }

        // Set Version
        wxLogMessage("Set Version %d", FullModel::VERSION);
        db << Version << FullModel::VERSION;

    } catch (sqlite::sqlite_exception & e) {
        wxLogMessage("Schema creation failed - %s : %s", e.what(), e.get_sql());
        return false;
    }

    return true;

}

std::vector<TrackBundleInfo> FullModel::get_track_list() {

    GET_DB();

    auto retval = std::vector<TrackBundleInfo>{};

    try {

     for(auto &&row : db << "select uid from trackinfo;") {
        long uid;
        row >> uid;
        retval.emplace_back(TrackBundleInfo{uid, 0});
      }

    } catch(sqlite::sqlite_exception & e) { 
        wxLogMessage("get_track_list failed - %s : %s", e.what(), e.get_sql());
    }
 

    wxLogMessage("get_track_list - returning %llu tracks", retval.size());

    return retval;
}

TrackInfo FullModel::get_track_info(long uuid) {

    GET_DB();

    TrackInfo retval = TrackInfo(-1);

    db << "select * from trackinfo where uid = ?" << uuid
    >> [&](long uid, int ttype, std::string name, int mute, int solo) {
        retval = TrackInfo(uid, TrackType(ttype));
        retval.name_ = name;
        retval.mute_ = bool(mute);
        retval.solo_ = bool(solo);
    };

    return retval;


}

