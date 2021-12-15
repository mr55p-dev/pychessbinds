# libpychess
---

`C++` bindings for my own Python implementation of Chess.
This will be implemented alongside the (currently private) Python application to enhance the speed of game generation.

This project is managed with CMake, project files are built "out of source". To generate a working
configuration of the libpychess library (which can be imported as a regular Python package) follow
the steps below.

To install the binary:
- Clone this repository with `git clone --recursive https://github.com/mr55p-dev/pychessbinds.git`
- Create a `build` directory inside the repository (`mkdir build` and `cd ./build`)
- Run `cmake ..` to build the project files. The default configuration is release mode, but this can be overridden by running `cmake -DCMAKE_BUILD_TYPE=Debug ..`
- Build the library target with `make`
- The library file now exists in the `build` directory

---

- You can also use CMake to generate XCode or VisualStudio solutions 
- First delete the `build` directory and its contents
- Use `cmake -G <generator> ..` (see `cmake --help` for the allowed generators).
- This will generate projects with `Debug` and `Release` configurations.

Feel free to PR with any suggestions.
