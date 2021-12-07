# PyChessBinds
---

Soon to be called libpychess. `C++` bindings for my own Python implementation of Chess.
This will be implemented alongside the (currently private) Python application to enhance the speed of game generation.

To install the binary:
- Create a `build` directory (`mkdir build` and `cd ./build`)
- Run `cmake ..`
- Build the project with `make`
- Run the binary with `./pychessbinds`
- Clean the build directory with `make clean`
- You can also use CMake to generate XCode or VisualStudio solutions 
- First delete the `build` directory and its contents
- Use `cmake -G <generator> ..` (see `cmake --help` for the allowed generators).

Feel free to PR with any suggestions.
