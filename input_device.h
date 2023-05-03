#ifndef INPUT_DEVICE_H_
#define INPUT_DEVICE_H_

#include <windows.h>

class InputDevice
{
private:
	HANDLE handle_;
	DWORD console_mode_;

public:
	enum InputDeviceType
	{
		Null,
		Mouse,
		Keyboard
	};
	struct EventInfo
	{
		InputDeviceType type;
		COORD coord;
		int key;
	};
	InputDevice();
	~InputDevice();

	bool GetEvent(EventInfo &info);
};

#endif