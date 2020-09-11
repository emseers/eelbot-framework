# Eelbot Framework

Eelbot Framework is a discord bot framework that is designed for writing extensible bots.

## Building

Eelbot Framework requires C++ 17 and CMake 3.15 or higher to build. Due to it's reliance on [cpprestsdk](https://github.com/microsoft/cpprestsdk), it also needs `libboost` and `libssl`.

Install the required libraries (use the equivalent packages with your distribution's package manager):
```
sudo apt install libboost-atomic-dev libboost-thread-dev libboost-system-dev libboost-date-time-dev libboost-regex-dev libboost-filesystem-dev libboost-random-dev libboost-chrono-dev libboost-serialization-dev libwebsocketpp-dev openssl libssl-dev
```

On Windows, install the required libraries with `vcpkg`:
```
vcpkg install --triplet x64-windows zlib openssl boost-system boost-date-time boost-regex boost-interprocess websocketpp brotli
```

**Note:** At this time, a Windows build has not been tested.

### Cmake

Eelbot Framework can be embedded directly into an existing CMake project by using either [`add_subdirectory`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html) or (since CMake 3.11) [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html).

**Note:** Eelbot Framework embeds the following libraries using `add_subdirectory`:
* [cpprestsdk](https://github.com/microsoft/cpprestsdk)
* [fmt](https://github.com/fmtlib/fmt)
* [nlohmann/json](https://github.com/nlohmann/json)

If you would like to embed any of these libraries in your top level project that also embeds Eelbot Framework, you will need to embed that library before embedding Eelbot Framework to avoid any duplicate target errors (since Eelbot Framework checks if these have been embedded before trying to embed them).

## Usage

Coming soon...
