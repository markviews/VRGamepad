#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include "Windows.h"
#include "LighthouseTracking.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ViGEmClient.h"
#include<fstream>
#include <string.h>
#include <vector>
using namespace std;

enum _XUSB_BUTTON right_menu;
enum _XUSB_BUTTON right_grip;
enum _XUSB_BUTTON right_trackpad;
enum _XUSB_BUTTON right_trigger;
enum _XUSB_BUTTON left_menu;
enum _XUSB_BUTTON left_grip;
enum _XUSB_BUTTON left_trackpad;
enum _XUSB_BUTTON left_trigger;
enum _XUSB_BUTTON right_touch_up;
enum _XUSB_BUTTON right_touch_down;
enum _XUSB_BUTTON right_touch_right;
enum _XUSB_BUTTON right_touch_left;
enum _XUSB_BUTTON left_touch_up;
enum _XUSB_BUTTON left_touch_down;
enum _XUSB_BUTTON left_touch_right;
enum _XUSB_BUTTON left_touch_left;
string left_touch;
string right_touch;
int def_right_1;
int def_right_2;

USHORT hold_buttons = 0;
USHORT touch_buttons = 0;

XUSB_REPORT report;
auto driver = vigem_alloc();
auto x360 = vigem_target_x360_alloc();

bool debug;
bool sound;
string type = "";

void findControllers();

void setType(string t) {
	if (type == "") {
		type = t;
		printf("Headset type: %s\n", t);
	}
}

int getID(string st) {
	if (st == "menu") return 1;
	else if (st == "grip") return 2;
	else if (st == "trackpad") return 32;
	else if (st == "trigger") return 33;
	return 0;
}

enum _XUSB_BUTTON gettype(string st) {
	if (st == "a") return XUSB_GAMEPAD_A;
	else if (st == "b") return XUSB_GAMEPAD_B;
	else if (st == "back") return XUSB_GAMEPAD_BACK;
	else if (st == "dpad_down") return XUSB_GAMEPAD_DPAD_DOWN;
	else if (st == "dpad_left") return XUSB_GAMEPAD_DPAD_LEFT;
	else if (st == "dpad_right") return XUSB_GAMEPAD_DPAD_RIGHT;
	else if (st == "dpad_up") return XUSB_GAMEPAD_DPAD_UP;
	else if (st == "xbox") return XUSB_GAMEPAD_GUIDE;
	else if (st == "left_shoulder") return XUSB_GAMEPAD_LEFT_SHOULDER;
	else if (st == "left_thumb") return XUSB_GAMEPAD_LEFT_THUMB;
	else if (st == "right_shoulder") return XUSB_GAMEPAD_RIGHT_SHOULDER;
	else if (st == "right_thumb") return XUSB_GAMEPAD_RIGHT_THUMB;
	else if (st == "start") return XUSB_GAMEPAD_START;
	else if (st == "x") return XUSB_GAMEPAD_X;
	else if (st == "y") return XUSB_GAMEPAD_Y;
	return XUSB_GAMEPAD_GUIDE;
}

void loadConfig() {
	ifstream infile("config.txt");
	string line;
	while (std::getline(infile, line)) {
		string thing = line.substr(0, line.find("="));
		line.erase(0, line.find("=") + 1);
		if (thing == "right_menu") right_menu = gettype(line);
		else if (thing == "right_grip") right_grip = gettype(line);
		else if (thing == "right_trackpad") right_trackpad = gettype(line);
		else if (thing == "right_trigger") right_trigger = gettype(line);
		else if (thing == "left_menu") left_menu = gettype(line);
		else if (thing == "left_grip") left_grip = gettype(line);
		else if (thing == "left_trackpad") left_trackpad = gettype(line);
		else if (thing == "left_trigger") left_trigger = gettype(line);
		else if (thing == "right_touch_up") right_touch_up = gettype(line);
		else if (thing == "right_touch_down") right_touch_down = gettype(line);
		else if (thing == "right_touch_right") right_touch_right = gettype(line);
		else if (thing == "right_touch_left") right_touch_left = gettype(line);
		else if (thing == "right_touch") right_touch = line;
		else if (thing == "left_touch_up") left_touch_up = gettype(line);
		else if (thing == "left_touch_down") left_touch_down = gettype(line);
		else if (thing == "left_touch_right") left_touch_right = gettype(line);
		else if (thing == "left_touch_left") left_touch_left = gettype(line);
		else if (thing == "left_touch") left_touch = line;
		else if (thing == "def_right_1") def_right_1 = getID(line);
		else if (thing == "def_right_2") def_right_2 = getID(line);
		else if (thing == "sound") { if (line == "true") sound = true; else sound = false; }
		else if (thing == "debug") { if (line == "true") debug = true; else debug = false; }
	}
	printf("Config loaded\n");
}

void initialize_xbox() {
	printf("Creating Virtual Controller\n");
	VIGEM_ERROR err = vigem_connect(driver);
	if (err == VIGEM_ERROR_NONE) {
		std::cout << " => connected successfully" << std::endl;
	}
	else {
		std::cout << "connection error: " << err << std::endl;
		vigem_free(driver);
		exit(1);
	}
	x360 = vigem_target_x360_alloc();
	vigem_target_add(driver, x360);
	XUSB_REPORT_INIT(&report);
	printf("Virtual Controller Created!\n");
}

void playSound(string type) {
	if (sound) {
		if (type == "enabled") PlaySound(TEXT("enabled.wav"), NULL, SND_FILENAME);
		else if (type == "disabled") PlaySound(TEXT("disabled.wav"), NULL, SND_FILENAME);
		else if (type == "right_set") PlaySound(TEXT("right_set.wav"), NULL, SND_FILENAME);
		else if (type == "error") PlaySound(TEXT("error.wav"), NULL, SND_FILENAME);
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	loadConfig();
	initialize_xbox();
	LighthouseTracking *lighthouseTracking = new LighthouseTracking();
	if (lighthouseTracking) {
		printf("Light house tracking\n");
		findControllers();
		Sleep(2000);
		while (lighthouseTracking->RunProcedure(true)) {
			//printf(".");
			touch_buttons = 0;
			Sleep(1);
		}
		delete lighthouseTracking;
	}
	return EXIT_SUCCESS;
}

int first = -2;
int seccond = -2;
int rightController = -2;
bool enabled = true;

void setRight(int controllerID) {
	if (rightController == controllerID) {
		if (enabled) {
			playSound("disabled");
			enabled = false;
		}
		else {
			playSound("enabled");
			enabled = true;
		}
	}
	else {
		playSound("right_set");
		rightController = controllerID;
		printf("Set right controller to controllerID: %d\n", controllerID);
	}
}

void press(int controllerID, int buttonID, int eventID) {
	if (debug)
		printf("ControllerID: %d ButtonID: %d EventID: %d\n", controllerID, buttonID, eventID);

	if (buttonID == def_right_1) {//Squeese
		if (eventID == 200) {
			first = controllerID;
			if (seccond == controllerID) {
				setRight(controllerID);
			}
		}
		else first = -2;
	}

	if (buttonID == def_right_2) {//Trackpad press
		if (eventID == 200) {
			seccond = controllerID;
			if (first == controllerID) {
				setRight(controllerID);
			}
		}
		else seccond = -2;
	}

	if (enabled)
		if (controllerID == rightController) {//right controller

			if (buttonID == 1 && right_menu != XUSB_GAMEPAD_GUIDE) //Menu
				if (eventID == 200) hold_buttons = hold_buttons | right_menu;
				else hold_buttons = hold_buttons & ~right_menu;

			if (buttonID == 2 && right_grip != XUSB_GAMEPAD_GUIDE) //Grip
				if (eventID == 200) hold_buttons = hold_buttons | right_grip;
				else hold_buttons = hold_buttons & ~right_grip;

			if (buttonID == 32 && right_trackpad != XUSB_GAMEPAD_GUIDE) //Trackpad press
				if (eventID == 200) hold_buttons = hold_buttons | right_trackpad;
				else hold_buttons = hold_buttons & ~right_trackpad;

			if (buttonID == 33 && right_trigger != XUSB_GAMEPAD_GUIDE) //Trigger
				if (eventID == 200) hold_buttons = hold_buttons | right_trigger;
				else if (eventID == 203) hold_buttons = hold_buttons & ~right_trigger;

		}
		else {//left controller

			if (buttonID == 1 && left_menu != XUSB_GAMEPAD_GUIDE) //Menu
				if (eventID == 200) hold_buttons = hold_buttons | left_menu;
				else hold_buttons = hold_buttons & ~left_menu;

			if (buttonID == 2 && left_grip != XUSB_GAMEPAD_GUIDE) //Grip
				if (eventID == 200) hold_buttons = hold_buttons | left_grip;
				else hold_buttons = hold_buttons & ~left_grip;

			if (buttonID == 32 && left_trackpad != XUSB_GAMEPAD_GUIDE) //Trackpad press
				if (eventID == 200) hold_buttons = hold_buttons | left_trackpad;
				else hold_buttons = hold_buttons & ~left_trackpad;

			if (buttonID == 33 && left_trigger != XUSB_GAMEPAD_GUIDE) //Trigger
				if (eventID == 200) hold_buttons = hold_buttons | left_trigger;
				else if (eventID == 203) hold_buttons = hold_buttons & ~left_trigger;
		}

	report.wButtons = hold_buttons | touch_buttons;
	vigem_target_x360_update(driver, x360, report);
}

void touch(int controllerID, float x, float y) {
	if (debug && (x != 0 || y != 0))
		printf("ControllerID %d touched at: %.2f, %.2f\n", controllerID, x, y);

	if (enabled)
		if (controllerID == rightController) {//right controller
			if (x != 0 || y != 0) {
				if (abs(x) < abs(y)) {
					if (y > 0) {
						if (right_touch_up != XUSB_GAMEPAD_GUIDE)
							touch_buttons = touch_buttons | right_touch_up;
					}
					else {
						if (right_touch_down != XUSB_GAMEPAD_GUIDE)
							touch_buttons = touch_buttons | right_touch_down;
					}
				}
				else if (x > 0) {
					if (right_touch_right != XUSB_GAMEPAD_GUIDE)
						touch_buttons = touch_buttons | right_touch_right;
				}
				else {
					if (right_touch_left != XUSB_GAMEPAD_GUIDE)
						touch_buttons = touch_buttons | right_touch_left;
				}
			}

			if (x != 0 || y != 0) {
				if (right_touch == "thumb_left") {
					report.sThumbLX = x * 32700.67;
					report.sThumbLY = y * 32700.67;
				}
				else if (right_touch == "thumb_right") {
					report.sThumbRX = x * 32700.67;
					report.sThumbRY = y * 32700.67;
				}
			}
			else {
				//let go of controlls when not pressing any
				report.sThumbLX = 0;
				report.sThumbLY = 0;
				report.sThumbRX = 0;
				report.sThumbRY = 0;
			}

		}
		else {//left controller

			if (abs(x) < abs(y)) {
				if (y > 0) {
					if (left_touch_up != XUSB_GAMEPAD_GUIDE)
						touch_buttons = touch_buttons | left_touch_up;
				}
				else {
					if (left_touch_down != XUSB_GAMEPAD_GUIDE)
						touch_buttons = touch_buttons | left_touch_down;
				}
			}
			else if (x > 0) {
				if (left_touch_right != XUSB_GAMEPAD_GUIDE)
					touch_buttons = touch_buttons | left_touch_right;
			}
			else {
				if (left_touch_left != XUSB_GAMEPAD_GUIDE)
					touch_buttons = touch_buttons | left_touch_left;
			}


			if (x != 0 || y != 0) {
				if (left_touch == "thumb_left") {
					report.sThumbLX = x * 32700.67;
					report.sThumbLY = y * 32700.67;
				}
				else if (left_touch == "thumb_right") {
					report.sThumbRX = x * 32700.67;
					report.sThumbRY = y * 32700.67;
				}
			}
			else {
				//let go of controlls when not pressing any
				report.sThumbLX = 0;
				report.sThumbLY = 0;
				report.sThumbRX = 0;
				report.sThumbRY = 0;
			}
		}

	report.wButtons = hold_buttons | touch_buttons;
	vigem_target_x360_update(driver, x360, report);

}