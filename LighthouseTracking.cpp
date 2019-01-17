#include "LighthouseTracking.h";

using namespace std;
void press(int controllerID, int buttonID, int eventID);
void touch(int controllerID, float x, float y);
void playSound(string type);

void setType(string t);

// Destructor
LighthouseTracking::~LighthouseTracking() {
	if (m_pHMD != NULL) {
		vr::VR_Shutdown();
		m_pHMD = NULL;
	}
}

// Constructor
LighthouseTracking::LighthouseTracking() {
	vr::EVRInitError eError = vr::VRInitError_None;
	m_pHMD = vr::VR_Init(&eError, vr::VRApplication_Background);

	if (eError != vr::VRInitError_None) {
		m_pHMD = NULL;
		char buf[1024];
		sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
		printf_s(buf);
		exit(EXIT_FAILURE);
	}
}

bool LighthouseTracking::RunProcedure(bool bWaitForEvents) {
	vr::VREvent_t event;
	while (m_pHMD->PollNextEvent(&event, sizeof(event))) {
		ProcessVREvent(event);
	}
	ParseTrackingFrame();
	return true;
}

int id1 = -2;
int id2 = -2;

bool LighthouseTracking::ProcessVREvent(const vr::VREvent_t & event) {
	if (event.eventType == 200 || event.eventType == 201 || event.eventType == 203) {
		press(event.trackedDeviceIndex, event.data.controller.button, event.eventType);
	}
	return true;
}

void LighthouseTracking::ParseTrackingFrame() {
	if (id1 != -2) {
		vr::TrackedDevicePose_t trackedDevicePose;
		vr::VRControllerState_t controllerState;
		vr::VRSystem()->GetControllerStateWithPose(vr::TrackingUniverseStanding, id1, &controllerState, sizeof(controllerState), &trackedDevicePose);
		touch(id1, controllerState.rAxis[0].x, controllerState.rAxis[0].y);
	}
	if (id2 != -2) {
		vr::TrackedDevicePose_t trackedDevicePose;
		vr::VRControllerState_t controllerState;
		vr::VRSystem()->GetControllerStateWithPose(vr::TrackingUniverseStanding, id2, &controllerState, sizeof(controllerState), &trackedDevicePose);
		touch(id2, controllerState.rAxis[0].x, controllerState.rAxis[0].y);
	}
}

void findControllers() {
	for (vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++) {

		vr::ETrackedDeviceClass trackedDeviceClass = vr::VRSystem()->GetTrackedDeviceClass(unDevice);
		switch (trackedDeviceClass) {
		case vr::ETrackedDeviceClass::TrackedDeviceClass_Controller:
			char manufacturer[1024];
			vr::VRSystem()->GetStringTrackedDeviceProperty(unDevice, vr::ETrackedDeviceProperty::Prop_ManufacturerName_String, manufacturer, sizeof(manufacturer));

			char modelnumber[1024];
			vr::VRSystem()->GetStringTrackedDeviceProperty(unDevice, vr::ETrackedDeviceProperty::Prop_ModelNumber_String, modelnumber, sizeof(modelnumber));

			if (strstr(modelnumber, "Vive. Controller MV"))
				setType("vive");

			if (!strstr(modelnumber, "XInput Controller")) {//Ignore the virtual controller we created
				printf("Controller found: |%s| |%s| ID: %d\n", manufacturer, modelnumber, unDevice);
				if (id1 == -2) id1 = unDevice;
				else id2 = unDevice;
			}

		}
	}
	if (id2 == -2) {
		printf("Failed to find two controllers...");
	}
}