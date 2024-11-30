#include <string>

const char * CONFIG_TABLE = R"sql(
CREATE TABLE config (
    key TEXT NOT NULL PRIMARY KEY,
    value BLOB
);
)sql";

const char * OBJECT_XREF = R"sql(
CREATE TABLE object_xref (
    uid INTEGER PRIMARY KEY AUTOINCREMENT,
    obj_type TEXT
);
)sql";

const char * TRACK_INFO = R"sql(
CREATE TABLE trackinfo (
    uid INTEGER PRIMARY KEY,
    ttype INTEGER DEFAULT 0,
    name TEXT,
    mute INTEGER DEFAULT FALSE,
    solo INTEGER DEFAULT FALSE
);
)sql";


const char *MasterTrack1 = R"sql(
INSERT INTO object_xref (uid, obj_type) values (0, 'track');
)sql";

const char *MasterTrack2 = R"sql(
INSERT INTO trackinfo (uid, ttype, name) values (0, 0, 'MASTER');
)sql";

struct schema_step {
    std::string name;
    const char * sql;
};

schema_step STEPS[] = {
    {"create config table", CONFIG_TABLE},
    {"create object_xref table", OBJECT_XREF},
    {"create trackinfo table", TRACK_INFO},
    {"create master track pt1", MasterTrack1},
    {"create master track pt2", MasterTrack2},
};

//-----------------------------

const char * Version = R"sql(
INSERT INTO config (key, value) values ('VERSION', ?);
)sql";
