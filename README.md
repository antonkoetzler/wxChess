# wxChess
A chess application made with wxWidgets

# Compiling from source
## Linux
1. Compile wxWidgets from source (https://github.com/antonkoetzler/wxWidgets/blob/main/Installation/LinuxInstallation.pdf)
2. `https://github.com/antonkoetzler/wxChess.git`
3. `cd wxChess`
4. `sh build.sh`

## Windows
1. Compile wxWidgets from source (https://github.com/antonkoetzler/wxWidgets/blob/main/Installation/WindowsInstallation.pdf)
2. `https://github.com/antonkoetzler/wxChess.git`
3. `cd wxChess`
4. `cmake -G "MinGW Makefiles" -S ./ -B ./build`
5. `cd build`
6. `cp -r ../img ./img`
7. `mingw32-make`

# (Running pre-built binaries) dependancies for Arch Linux
`base-devel`, `cmake`, `gtk3`
  
