# kbDAW

Silly idea - vaporware.

A DAW where everything is doable from the keyboard. No mouse needed.

AngelScript will be used to allow the engine to be scriptable. Even
much of the stock behavior will be written in AngelScript.

Even the GUI will be written using AngelScript. (This sounds like a lot of
work to "port" wxWidgets to AngelScript).

The project file will be based on [simpleConfig](https://github.com/mhhollomon/simpleConfig)

## build
`cmake -S . -B build`
`cmake --build build`

`cmake --build build -v --clean-first -j 10 > cmake.txt 2>&1`

## Technologies

- [AngelScript](https://www.angelcode.com/angelscript/) for user scripting support
- [CPM](https://github.com/cpm-cmake/CPM.cmake/) for dependency management.
- [simpleConfig](https://github.com/mhhollomon/simpleConfig) for configuration file.
- [sqlite3](https://sqlite.org) for in-memory data storage.
- [sqlite_modern_cpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp) to make sqlite easier to deal with in C++.
- [WxWidgets](https://wxwidgets.org/) for the UI.
