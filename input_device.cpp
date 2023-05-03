#include "input_device.h"

InputDevice::InputDevice()
	: handle_(GetStdHandle(STD_INPUT_HANDLE))
{
	GetConsoleMode(handle_, &console_mode_);
	SetConsoleMode(handle_, ENABLE_MOUSE_INPUT);
}

InputDevice::~InputDevice()
{
	SetConsoleMode(handle_, console_mode_);
	handle_ = 0;
}

bool InputDevice::GetEvent(EventInfo &info)
{
	INPUT_RECORD all_events[2];
	DWORD read_event;
	info.type = Null;

	ReadConsoleInput(handle_, all_events, 2, &read_event);
	for(DWORD i = 0; i < read_event; i++)
	{
		if(all_events[i].EventType == KEY_EVENT && all_events[i].Event.KeyEvent.bKeyDown &&
			(all_events[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE ||
			 all_events[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN ||
			 all_events[i].Event.KeyEvent.wVirtualKeyCode == VK_LEFT ||
			 all_events[i].Event.KeyEvent.wVirtualKeyCode == VK_RIGHT))
		{
			info.type = Keyboard;
			info.key = all_events[i].Event.KeyEvent.wVirtualKeyCode;
		}

		if(all_events[i].EventType == MOUSE_EVENT)
		{
			info.type = Mouse;
			info.coord.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			info.coord.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;
			if(all_events[i].Event.MouseEvent.dwButtonState == VK_LBUTTON )
				info.key = VK_LBUTTON;
			else
				info.key = 0;
		}
	}
	return true;
}