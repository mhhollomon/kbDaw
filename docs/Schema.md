# SQLite table schema

## CONFIG
```sql
CREATE TABLE config (
    key TEXT NOT NULL PRIMARY KEY,
    value BLOB
)
```

A simple key/value store for configuration items that don't need anything fancier.

*Note* not making this `WITHOUT ROWID` as at least one value could be potentially
long.

### Known Keys

#### VERSION
The value is an integer that represents the version of the config data. Currently,
this is 0.

#### trackorder

The value is a json(?) string that is a dictonary where the keys are
the trackid and the value is the order as an array.

In the below, track `4` is a group and `5` is a child of the group.

```json
{
    "3" : [ 1 ],
    "4"  : [ 2 ],
    "5"  : [ 2, 1 ]
}
```

## TRACKINFO
```sql
CREATE TABLE trackinfo (
    uid INTEGER PRIMARY KEY,
    ttype INTEGER DEFAULT 0,
    name TEXT,
    mute INTEGER DEFAULT FALSE,
    solo INTEGER DEFAULT FALSE
)
```

### uid
The unique identifier for the track.

### ttype
The track type
-  0 = Normal
-  1 = Group
-  2 = Folder

### name
The name of the track

### mute
a Boolean indicating if the track is currently muted or not.

Per Sqlite,
- 0 = False
- 1 = True

### solo
a Boolean indication if the track is currently soloed or not.

Per Sqlite,
- 0 = False
- 1 = True

## OBJECT_XREF

```sql
CREATE TABLE object_xref (
    uid INTEGER PRIMARY KEY AUTOINCREMENT,
    obj_type TEXT
)
```

This is used as a number fountain to form the unqiue ids
for various objects.

### uid
The unique id that sqlite assigns.

### obj_type
The object type. One of
- "track"
