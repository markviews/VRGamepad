# VRGamepad
This program creates a virtual xbox360 controller from buttons pressed with VR controllers, and is able to run while any other VR application is open.

## How to use:
1. [Downlad](https://github.com/markviews/VRGamepad/files/2762776/VRGamepad.1.0.zip) and unzip
2. Configure config.txt if you want
3. Run VRGamepad.exe
4. Press buttons to define right controller (default is trigger and trackpad press)

## How to setup to play local controller games with friends in VR:
1. Download and install [OVRDrop](https://store.steampowered.com/app/586210/OVRdrop/) ($15)
2. Download, install, sign up for [Parsec](https://parsecgaming.com/downloads) (install controller driver when prompted)
3. Download and extract [VRGamepad](https://github.com/markviews/VRGamepad/files/2762776/VRGamepad.1.0.zip)
4. Launch Parsec and connect to partner
5. Launch SteamVR with any game
6. Launch OVRDrop, select Parsec Window
7. Launch my app, define right controller by holding grip and trackpad

## Build instructions:
1. Download and extract source code
2. Download and extract [OpenVR SDK](https://github.com/ValveSoftware/openvr) and [ViGEm](https://github.com/nefarius/ViGEm).
3. Open VRGamepad.sln
4. add openvr-master\headers and ViGEm to Configuration Properties > Include Directories
5. add openvr-master to C/C++ > General > Additional Include Directories
6. add openvr-master\lib\win32 to Linker > Gneral > Additional Library Directories
7. search for msvcprtd.lib in your Visual Studio folder, add its x86 directory to Linker > General > Additional Library Directories
 - Example directory: C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\lib\onecore\x86
8. Build

### Planned Features
- Oculous Support
- Video Demo
- Fix all bugs

### Bugs
- Buttons are setup for Vive, Probly won't work for any other VR controllers at the moment
- Trackpad dosn't send data to virtual controller if the controller was out of range of the lighthouses when this program was opened.
- xbox "back" button opens annoying SteamVR popup (I don't recomend mapping it for now)
