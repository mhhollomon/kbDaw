
#include "Model.hpp"

struct UUIDFactory {
    long get_uuid() { return 1L; }
};

class RTModel {

    std::map<long, TrackInfo> tracks_;
    std::vector<TrackBundleInfo> track_order_;

    UUIDFactory uuid_factory;

    std::mutex mutex_;


public:
    RTModel() {}

};
