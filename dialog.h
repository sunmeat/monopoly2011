#ifndef DIALOG_H_
#define DIALOG_H_

#include "game_map.h"

struct Space;

class Dialog
{
private:
	struct Rect
	{
		Rect()
			: x(0), y(0), width(0), height(0) { }
		int x;
		int y;
		int width;
		int height;
	};

	Dialog();
	void SetFocus(int i);
	void SetFocus(int x, int y);
	int GetItem(int x, int y);

	const char *str_;
	const Space *space_;
	int buttons_;
	int activitiButton_;
	Rect dialogFrame_;
	Rect buttonFrame_[3];
	const char *buttonName_[3];
	bool isShow;

public:
	Dialog(const char *str);
	Dialog(const Space *space);
	~Dialog();
	
	void SetButton(const char *str);
	void SetButton(const char *str1, const char *str2);
	void SetButton(const char *str1, const char *str2, const char *str3);
	void SetRectangle(int x, int y, int width, int height);
	void Hide();
	// Показать диалог. Если mode = 0 поля игровой карты не выбираются.
	int Show(int mode);
	// Показать комбинированный диалог, в который включены диалоги информации о полях игровой карты.
	int Show(const GameMap &map);
};

#endif
