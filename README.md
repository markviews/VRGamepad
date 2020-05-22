#This project is Depreciated and no longer receving updates.




# VRGamepad
This program creates a virtual xbox360 controller from buttons pressed with Vive controllers, and is able to run while any other VR application is open.

## How to use:
1. [Downlad](https://github.com/markviews/VRGamepad/releases) and unzip
2. Configure config.txt if you want
3. Run VRGamepad.exe
4. Hold buttons to define right controller (default is trigger and trackpad press)

## How to setup to play local controller games with friends in VR:
1. Download and install [OVRDrop](https://store.steampowered.com/app/586210/OVRdrop/) ($15)
2. Download, install, sign up for [Parsec](https://parsecgaming.com/downloads) (install controller driver when prompted)
3. Download and extract [VRGamepad](https://github.com/markviews/VRGamepad/files/2762776/VRGamepad.1.0.zip)
4. Launch Parsec and connect to partner
5. Launch SteamVR with any game
6. Launch OVRDrop, select Parsec Window
7. Launch my app, define right controller by holding grip and trackpad

## Config
right_menu, right_grip, right_trackpad, right_trigger, left_menu, left_grip, left_trackpad, left_trigger, right_touch_up, right_touch_down, right_touch_right, right_touch_left, left_touch_up, left_touch_down, left_tocuh_right, left_touch_lef can be set to:
a, b, x, y, back, start, dpad_down, dpad_left, dpad_right, dpad_up, left_shoulder, left_thumb, right_shoulder, right_thumb

right_touch, left_touch can be set to:
thumb_left or thumb_right

def_right_1, def_right_2 can be set to:
menu, grip, tackpad, trigger

sound can be set to:
true, false

debug can be set to false, show(print button ids), buttons(disable virtual controller and print button ids)

## Build instructions:
1. Download and extract source code
2. Download and extract [OpenVR SDK](https://github.com/ValveSoftware/openvr) and [ViGEm](https://github.com/nefarius/ViGEm).
3. Open VRGamepad.sln with Visual Code Studio 2017
4. add openvr-master\headers and ViGEm to Configuration Properties > VC++ Directories > Include Directories
5. add openvr-master to C/C++ > General > Additional Include Directories
6. add openvr-master\lib\win32 to Linker > General > Additional Library Directories
7. Build

### Planned Features
- Oculous Support
- Video Demo
- Fix all bugs

### Bugs
- xbox "back" button opens annoying SteamVR popup (I don't recomend mapping it for now)
