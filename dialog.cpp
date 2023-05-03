#include "dialog.h"
#include "input_device.h"
#include "window_surface.h"
#include "user.h"

Dialog::Dialog(const char *str)
	: str_(str), space_(0), buttons_(0), activitiButton_(-1), isShow(false)
{
	buttonName_[0] = buttonName_[1] = buttonName_[2] = 0;
}

Dialog::Dialog(const Space *space)
	: str_(0), space_(space), buttons_(0), activitiButton_(-1), isShow(false)
{
	buttonName_[0] = buttonName_[1] = buttonName_[2] = 0;
}

void Dialog::SetRectangle(int x, int y, int width, int height)
{
	dialogFrame_.x = x;
	dialogFrame_.y = y;
	dialogFrame_.width = width;
	dialogFrame_.height = height;
}

void Dialog::SetButton(const char *str)
{
	buttons_ = 1;
	activitiButton_ = 0;
	buttonName_[0] = str;
	buttonFrame_[0].width = strlen(str) + 4;
	buttonFrame_[0].height = 3;
}

void Dialog::SetButton(const char *str1, const char *str2)
{
	buttons_ = 2;
	activitiButton_ = 0;

	buttonName_[0] = str1;
	buttonFrame_[0].width = strlen(str1) + 4;
	buttonFrame_[0].height = 3;

	buttonName_[1] = str2;
	buttonFrame_[1].width = strlen(str2) + 4;
	buttonFrame_[1].height = 3;
}

void Dialog::SetButton(const char *str1, const char *str2, const char *str3)
{
	buttons_ = 3;
	activitiButton_ = 0;

	buttonName_[0] = str1;
	buttonFrame_[0].width = strlen(str1) + 4;
	buttonFrame_[0].height = 3;

	buttonName_[1] = str2;
	buttonFrame_[1].width = strlen(str2) + 4;
	buttonFrame_[1].height = 3;

	buttonName_[2] = str3;
	buttonFrame_[2].width = strlen(str3) + 4;
	buttonFrame_[2].height = 3;
}

void Dialog::SetFocus(int i)
{
	WINSURF.DrawRectangle(buttonFrame_[activitiButton_].x, buttonFrame_[activitiButton_].y, buttonFrame_[activitiButton_].width, buttonFrame_[activitiButton_].height, LightGray);
	activitiButton_ = i;
	WINSURF.DrawRectangle(buttonFrame_[i].x, buttonFrame_[i].y, buttonFrame_[i].width, buttonFrame_[i].height, Red);
}

void Dialog::SetFocus(int x, int y)
{
	for (int i = buttons_ - 1; i >= 0; i--)
	{
		if(x >= buttonFrame_[i].x && x <= (buttonFrame_[i].x + buttonFrame_[i].width - 1) && 
			y >= buttonFrame_[i].y && y <= (buttonFrame_[i].y + buttonFrame_[i].height - 1))
		{
			if(i != activitiButton_)
				SetFocus(i);
			return;
		}
	}
}

// ¬озвращает 0 если координаты соответствуют кнопке диалога, от 100 до 139 если выбрано
// поле на игровой карте и -1 если попали в никуда.
int Dialog::GetItem(int x, int y)
{
	for (int i = buttons_ - 1; i >= 0; i--)
	{
		if(x >= buttonFrame_[i].x && x <= (buttonFrame_[i].x + buttonFrame_[i].width - 1) && 
			y >= buttonFrame_[i].y && y <= (buttonFrame_[i].y + buttonFrame_[i].height - 1))
			return 0;
	}
	if(x < 1 || y < 1 || x > 67 || y > 45 || x > 7 && x < 61 && y > 5 && y < 41)
		return -1;
	int line = (y - 1) / 4, column = (x - 1) / 6;
	if(line == 0)
		return 100 + column;
	else if(line == 10)
		return 130 - column;
	else if(column == 0)
		return 140 - line;
	else
		return 110 + line;
}

int Dialog::Show(int mode)
{
	if(!isShow) {
		isShow = true;
		int x_base = dialogFrame_.x + dialogFrame_.width - 1;
		int y_base = dialogFrame_.y + dialogFrame_.height;
		for (int i = buttons_ - 1; i >= 0; i--)
		{
			buttonFrame_[i].x = x_base - buttonFrame_[i].width - 1;
			buttonFrame_[i].y = y_base - buttonFrame_[i].height - 1;
			x_base = buttonFrame_[i].x;
		}

		WINSURF.DrawRectangle(dialogFrame_.x, dialogFrame_.y, dialogFrame_.width, dialogFrame_.height, LightGray);
		if (str_ != 0)
			WINSURF.DrawString(str_, dialogFrame_.x+3, dialogFrame_.y+2, LightGray);
		else
			WINSURF.DrawSpaceInfo(space_, dialogFrame_.x+5, dialogFrame_.y+2);
		for (int i = 0; i <= buttons_ - 1; i++)
		{
			WINSURF.DrawRectangle(buttonFrame_[i].x, buttonFrame_[i].y, buttonFrame_[i].width, buttonFrame_[i].height, i == activitiButton_ ? Red : LightGray);
			WINSURF.DrawString(buttonName_[i], buttonFrame_[i].x + 2, buttonFrame_[i].y + 1, LightGray);
		}
	}
	InputDevice input_device;
	InputDevice::EventInfo event_info;
	while (1)
	{
		input_device.GetEvent(event_info);
		if(event_info.type == InputDevice::Keyboard)
		{
			if(event_info.key == VK_LEFT)
			{
				int i = activitiButton_ - 1;
				if (i < 0) i = buttons_ - 1;
				SetFocus(i);
			}
			else if(event_info.key == VK_RIGHT)
			{
				int i = activitiButton_ + 1;
				if (i > buttons_ - 1) i = 0;
				SetFocus(i);
			}
			else if(event_info.key == VK_RETURN)
				break;
			else if(event_info.key == VK_ESCAPE)
				exit(0);
		}
		else if(event_info.type == InputDevice::Mouse && event_info.key == VK_LBUTTON)
		{
			int item = GetItem(event_info.coord.X, event_info.coord.Y);
			if(item == 0)
				break;
			else if (mode != 0 && item > 99) {
				Sleep(100);
				return item;
			}
		}
		else if(event_info.type == InputDevice::Mouse)
		{
			SetFocus(event_info.coord.X, event_info.coord.Y);
		}
	}

	return activitiButton_ + 1;
}

int Dialog::Show(const GameMap &map)
{
	int key = Show(1);
	while (key == 0 || key > 99)
	{
		if (key == 0)
			key = Show(1);
		if(key > 99) {
			Hide();
			Dialog d21(map.GetSpace(key - 100));
			d21.SetRectangle(10, 8, 49, 22);
			d21.SetButton("ѕродолжить");
			key = d21.Show(1);
			if (key == 1)
				key--;
		}
	}
	return key;
}

void Dialog::Hide()
{
	if(isShow == true) {
		WINSURF.ClearRectangle(dialogFrame_.x, dialogFrame_.y, dialogFrame_.width, dialogFrame_.height);
		isShow = false;
	}
}

Dialog::~Dialog()
{
	Hide();
}
