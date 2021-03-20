# Eelbot Framework

Eelbot Framework is a discord bot framework that is designed for writing extensible bots.

## Building

### Prerequisites

Eelbot Framework requires C++ 17 and CMake 3.15 or higher to build. It also requires `openssl`.

### CMake

Eelbot Framework can be embedded directly into an existing CMake project by using either [`add_subdirectory`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html) or [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html).

**Note:** Eelbot Framework embeds the following libraries using `add_subdirectory`:
* [cpr](https://github.com/whoshuu/cpr)
* [fmt](https://github.com/fmtlib/fmt)
* [nlohmann/json](https://github.com/nlohmann/json)
* [Catch2](https://github.com/catchorg/Catch2) (For tests only)

If you would like to embed any of these libraries in your top level project that also embeds Eelbot Framework, you will need to embed that library before embedding Eelbot Framework to avoid any duplicate target errors (since Eelbot Framework checks if these have been embedded before trying to embed them).

**Note:** Eelbot Framework also embeds [zlib](https://github.com/madler/zlib) using `add_subdirectory`. However, due to limitations with its CMakeLists.txt (see [here](https://github.com/madler/zlib/issues/133) and [here](https://github.com/madler/zlib/issues/218.)), if you would like to use the `zlib` or `zlibstatic` targets in your top level project that also embeds Eelbot Framework, you will need to embed Eelbot Framework and just use the `zlib` or `zlibstatic` target (Eelbot Framework will make these targets available to use). The include files for these targets will be defined in the CMake variable `EF_ZLIB_INCLUDE_DIRS`.

**Note:** Eelbot Framework also embeds the following header only libraries without using `add_subdirectory`:
* [asio](https://github.com/chriskohlhoff/asio)
* [websocketpp](https://github.com/zaphoyd/websocketpp)

You should be able to embed these in your top level project that also embeds Eelbot Framework in any order without any problems.

## Usage

Coming soon...
