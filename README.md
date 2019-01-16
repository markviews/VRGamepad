# VRGamepad
This program creates a virtual xbox360 controller from buttons pressed with VR controllers, and is able to run while any other VR application is open.

## How do I run it?
1. [Downlad](https://github.com/markviews/VRGamepad/files/2762776/VRGamepad.1.0.zip) and unzip
2. Configure config.txt if you want
3. Run VRGamepad.exe

## How to setup to play local controller games with friends in VR:
1. Download and install [OVRDrop](https://store.steampowered.com/app/586210/OVRdrop/) ($15)
2. Download, install, sign up for [Parsec](https://parsecgaming.com/downloads) (install controller driver when prompted)
3. Download and extract [VRGamepad](https://github.com/markviews/VRGamepad/files/2762776/VRGamepad.1.0.zip)
4. Launch Parsec and connect to partner
5. Launch SteamVR with any game
6. Launch OVRDrop, select Parsec Window
7. Launch my app, define right controller by holding grip and trackpad

### Planned Features
- Oculous Support
- Video Demo
- Fix all bugs

### Bugs
- Buttons are setup for Vive, Probly won't work for any other VR controllers at the moment
- Trackpad dosn't send data to virtual controller if the controller was out of range of the lighthouses when this program was opened.
- xbox "back" button opens annoying SteamVR popup (I don't recomend mapping it for now)
