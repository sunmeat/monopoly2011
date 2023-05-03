#include "window_surface.h"

#include <string.h>
#include <iostream>

#include "user.h"
#include "space.h"

const char middlRight = '\271', vertical = '\272', rUpCorner = '\273', rDownCorner = '\274',
	lDownCorner = '\310', lUpCorner = '\311', middlDown = '\312', middlUp = '\313',
	middlLeft = '\314', horizontal = '\315', cross = '\316';

WindowSurface::WindowSurface()
	: handle_(GetStdHandle(STD_OUTPUT_HANDLE))
{
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false };
	SetConsoleCursorInfo(handle_, &cci);
}

// Создание объекта
const WindowSurface &WindowSurface::instance()
{
	static const WindowSurface single_instance;
	return single_instance;
}

void WindowSurface::GotoXY(int x, int y) const
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(handle_, coord);
}

void WindowSurface::WriteChar(char ch, int x, int y) const
{
	GotoXY(x, y);
	std::cout << ch;
}

void WindowSurface::WriteChars(char ch, int x, int y, int len) const
{
	GotoXY(x, y);
	for (int i = 0; i < len; i++)
		std::cout << ch;
}

void WindowSurface::DrawRectangle(int x, int y, int width, int height, Color foreground) const
{
	SetConsoleTextAttribute(handle_, (WORD)(foreground));

	WriteChar(lUpCorner, x, y);
	WriteChars(horizontal, x + 1, y, width - 2);
	WriteChar(rUpCorner, x + width - 1, y);

	for(int i = 1; i <= height - 2; i++)
	{
		WriteChar(vertical, x, y + i);
		WriteChar(vertical, x + width - 1, y + i);
	}

	WriteChar(lDownCorner, x, y + height - 1);
	WriteChars(horizontal, x + 1, y + height - 1, width - 2);
	WriteChar(rDownCorner, x + width - 1, y + height - 1);

	SetConsoleTextAttribute(handle_, (WORD)(LightGray));
}

void WindowSurface::ClearRectangle(int x, int y, int width, int height) const
{
		for(int i = 0; i < height; i++)
			WINSURF.WriteChars(' ', x, y + i, width);
}

void WindowSurface::DrawSpaceInfo(const Space *space, int x, int y) const
{
	char buf[256];
	if (space->type == Space::Start) {
		DrawString("СТАРТ", x, y, LightRed);
	}
	else if (space->type == Space::Chance) {
		DrawString("Шанс", x, y, LightRed);
	}
	else if (space->type == Space::PublicTreasury) {
		DrawString("Общественная казна", x, y, LightRed);
	}
	else if (space->type == Space::FreeParking) {
		DrawString("Беспплатная стоянка", x, y, LightRed);
	}
	else if (space->type == Space::GoToJail) {
		DrawString("Отправляйся в тюрьму!", x, y, LightRed);
	}
	else if (space->type == Space::Jail) {
		DrawString("Тюрьма", x, y, LightRed);
	}
	else if (space->type == Space::Site) {
		DrawString(space->site.street, x, y, LightRed);
		DrawString("Владелец участка", x, y + 3, LightGray);
		DrawString("Стоимость участка", x, y + 5, LightGray);
		DrawString("Рента без строений", x, y + 6, LightGray);
		DrawString("      с 1 домом", x, y + 7, LightGray);
		DrawString("      с 2 домами", x, y + 8, LightGray);
		DrawString("      с 3 домами", x, y + 9, LightGray);
		DrawString("      с 4 домами", x, y + 10, LightGray);
		DrawString("      с отелем", x, y + 11, LightGray);
		DrawString("Стоимость постройки", x, y + 12, LightGray);
		DrawString("Уровень застройки", x, y + 13, LightGray);

		DrawUserName(space->site.owner, x + 27, y + 3);
		sprintf(buf, "%i$", space->site.cost);
		DrawString(buf, x + 27, y + 5, LightGray);
		sprintf(buf, "%i$", space->site.rent0);
		DrawString(buf, x + 27, y + 6, LightGray);
		sprintf(buf, "%i$", space->site.rent1);
		DrawString(buf, x + 27, y + 7, LightGray);
		sprintf(buf, "%i$", space->site.rent2);
		DrawString(buf, x + 27, y + 8, LightGray);
		sprintf(buf, "%i$", space->site.rent3);
		DrawString(buf, x + 27, y + 9, LightGray);
		sprintf(buf, "%i$", space->site.rent4);
		DrawString(buf, x + 27, y + 10, LightGray);
		sprintf(buf, "%i$", space->site.rent5);
		DrawString(buf, x + 27, y + 11, LightGray);
		sprintf(buf, "%i$", space->site.cost_building);
		DrawString(buf, x + 27, y + 12, LightGray);
		sprintf(buf, "%i", space->site.buildings);
		DrawString(buf, x + 27, y + 13, LightGray);
	}
	else if (space->type == Space::Communication) {
		DrawString(space->communication.name, x, y, LightRed);
		DrawString("Владелец предприятия", x, y + 3, LightGray);
		DrawString("Стоимость предприятия", x, y + 5, LightGray);
		DrawString("Рента", x, y + 6, LightGray);

		DrawUserName(space->communication.owner, x + 27, y + 3);
		sprintf(buf, "%i$", space->communication.cost);
		DrawString(buf, x + 27, y + 5, LightGray);
		sprintf(buf, "*%i$", space->communication.rent);
		DrawString(buf, x + 27, y + 6, LightGray);
	}
	else if (space->type == Space::Service) {
		DrawString(space->service.name, x, y, LightRed);
		DrawString("Владелец предприятия", x, y + 3, LightGray);
		DrawString("Стоимость предприятия", x, y + 5, LightGray);
		DrawString("Рента", x, y + 6, LightGray);

		DrawUserName(space->service.owner, x + 27, y + 3);
		sprintf(buf, "%i$", space->service.cost);
		DrawString(buf, x + 27, y + 5, LightGray);
		sprintf(buf, "%i$", space->service.rent);
		DrawString(buf, x + 27, y + 6, LightGray);
	}
	else if (space->type == Space::Taxation) {
		DrawString(space->taxation.name, x, y, LightRed);
		DrawString("Рента", x, y + 5, LightGray);

		sprintf(buf, "%i$", space->taxation.rent);
		DrawString(buf, x + 27, y + 5, LightGray);
	}
}

void WindowSurface::DrawString(const char *str, int x, int y, Color foreground) const
{
	char *buf = new char[strlen(str) + 1];
	CharToOemA(str, buf);

	char *token;
	token = strtok(buf, "\n");
	if(token) 
	{
		SetConsoleTextAttribute(handle_, foreground);
		GotoXY(x, y);
		std::cout << token;
	}
	else
	{
		return;
	}
	while((token = strtok(0, "\n")))
	{
		y++;
		GotoXY(x, y);
		std::cout << token;
	}
	SetConsoleTextAttribute(handle_, LightGray);
}

void WindowSurface::DrawGameMap() const
{
	SetConsoleTextAttribute(handle_, Green);

	int x = 1, y = 1;
	// Верхняя строка
	WriteChar(lUpCorner, x, y);
	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(middlUp, x, y);

	for(int i = 1; i < 10; i++)
	{
		x += 1;
		WriteChars(horizontal, x, y, 5);
		x += 5;
		WriteChar(middlUp, x, y);
	}

	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(rUpCorner, x, y);
	x = 1;

	// Ячейки
	for(int i = 1; i < 4; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			WriteChar(vertical, x, y + i);
			x += 6;
		}
		x = 1;
	}

	// Нижняя строка первого ряда
	y += 4;
	WriteChar(middlLeft, x, y);
	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(cross, x, y);

	for(int i = 1; i < 10; i++)
	{
		x += 1;
		WriteChars(horizontal, x, y, 5);
		x += 5;
		WriteChar(middlDown, x, y);
	}

	WriteChar(cross, x, y);
	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(middlRight, x, y);
	x = 1; y++;

	// Средние ячейки

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			WriteChar(vertical, x, y);
			x += 6;
			WriteChar(vertical, x, y);
			x += 54;
			WriteChar(vertical, x, y);
			x += 6;
			WriteChar(vertical, x, y);
			x = 1; y++;
		}
		WriteChar(middlLeft, x, y);
		x += 1;
		WriteChars(horizontal, x, y, 5);
		x += 5;
		WriteChar(middlRight, x, y);
		x += 54;
		WriteChar(middlLeft, x, y);
		x += 1;
		WriteChars(horizontal, x, y, 5);
		x += 5;
		WriteChar(middlRight, x, y);
		x = 1; y++;
	}

	y--;
	// Нижние ячейки
	WriteChar(middlLeft, x, y);
	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(cross, x, y);

	for(int i = 1; i < 10; i++)
	{
		x += 1;
		WriteChars(horizontal, x, y, 5);
		x += 5;
		WriteChar(middlUp, x, y);
	}

	WriteChar(cross, x, y);
	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(middlRight, x, y);
	x = 1;

	for(int i = 1; i < 4; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			WriteChar(vertical, x, y + i);
			x += 6;
		}
		x = 1;
	}
	y += 4;

	// Самая нижняя строка
	WriteChar(lDownCorner, x, y);
	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(middlDown, x, y);

	for(int i = 1; i < 10; i++)
	{
		x += 1;
		WriteChars(horizontal, x, y, 5);
		x += 5;
		WriteChar(middlDown, x, y);
	}

	x += 1;
	WriteChars(horizontal, x, y, 5);
	x += 5;
	WriteChar(rDownCorner, x, y);
	DrawString("СТАРТ\n  \32", 2, 3, LightGreen);
	DrawString(" -1-", 8, 3, LightGray);
	DrawString(" $$$", 14, 3, White);
	DrawString(" -1-", 20, 3, LightGray);
	DrawString(" -$", 26, 3, White);
	DrawString("  A", 32, 3, LightGray);
	DrawString(" -2-", 38, 3, LightGray);
	DrawString(" <?>", 44, 3, LightGreen);
	DrawString(" -2-", 50, 3, LightGray);
	DrawString(" -2-", 56, 3, LightGray);
	DrawString(" ###", 62, 3, Yellow);
	DrawString(" -3-", 62, 7, LightGray);
	DrawString(" (@)", 62, 11, LightGray);
	DrawString(" -3-", 62, 15, LightGray);
	DrawString(" -3-", 62, 19, LightGray);
	DrawString(" ЖД", 62, 23, LightGray);
	DrawString(" -4-", 62, 27, LightGray);
	DrawString(" $$$", 62, 31, White);
	DrawString(" -4-", 62, 35, LightGray);
	DrawString(" -4-", 62, 39, LightGray);
	DrawString(" Б\14С\n ^ ^", 62, 43, Yellow);
	DrawString(" -5-", 56, 43, LightGray);
	DrawString(" <?>", 50, 43, LightGreen);
	DrawString(" -5-", 44, 43, LightGray);
	DrawString(" -5-", 38, 43, LightGray);
	DrawString("  A", 32, 43, LightGray);
	DrawString(" -6-", 26, 43, LightGray);
	DrawString(" -6-", 20, 43, LightGray);
	DrawString(" (@)", 14, 43, LightGray);
	DrawString(" -6-", 8, 43, LightGray);
	DrawString(" \30\30\30", 2, 43, Yellow);
	DrawString(" -7-", 2, 39, LightGray);
	DrawString(" -7-", 2, 35, LightGray);
	DrawString(" $$$", 2, 31, White);
	DrawString(" -7-", 2, 27, LightGray);
	DrawString(" ЖД", 2, 23, LightGray);
	DrawString(" <?>", 2, 19, LightGreen);
	DrawString(" -8-", 2, 15, LightGray);
	DrawString(" -$", 2, 11, White);
	DrawString(" -8-", 2, 7, LightGray);

	SetConsoleTextAttribute(handle_, LightGray);
}

void WindowSurface::DrawSmilie(int gamer, int old_p, int new_p) const
{
	int x, y, x0, y0;

	switch (USERS.GetUser(gamer)->GetColor())
	{
	case LightRed: x0 = 2; y0 = 2; break;
	case LightGreen: x0 = 2; y0 = 4; break;
	case Cyan: x0 = 6; y0 = 2; break;
	case Yellow: x0 = 6; y0 = 4;
	}

	if (old_p <= 10) {
		x = old_p * 6;
		y = 0;
	}
	else if (old_p <=20) {
		x = 60;
		y = (old_p - 10) * 4;
	}
	else if (old_p <=30) {
		x = (30 - old_p) * 6;
		y = 40;
	}
	else if (old_p <=40) {
		x = 0;
		y = (40 -old_p) * 4;
	}

	WriteChar(' ', x + x0, y + y0);

	if (new_p <= 10) {
		x = new_p * 6;
		y = 0;
	}
	else if (new_p <=20) {
		x = 60;
		y = (new_p - 10) * 4;
	}
	else if (new_p <=30) {
		x = (30 - new_p) * 6;
		y = 40;
	}
	else if (new_p <=40) {
		x = 0;
		y = (40 -new_p) * 4;
	}

	SetConsoleTextAttribute(handle_, USERS.GetUser(gamer)->GetColor());
	WriteChar(1, x + x0, y + y0);

	SetConsoleTextAttribute(handle_, LightGray);
}

void WindowSurface::ClearSmilie(int gamer) const
{
	int x, y, x0, y0;
	switch (USERS.GetUser(gamer)->GetColor())
	{
	case LightRed: x0 = 2; y0 = 2; break;
	case LightGreen: x0 = 2; y0 = 4; break;
	case Cyan: x0 = 6; y0 = 2; break;
	case Yellow: x0 = 6; y0 = 4;
	}
	int pos = USERS.GetUser(gamer)->GetPosition();
	if (pos <= 10) {
		x = pos * 6;
		y = 0;
	}
	else if (pos <=20) {
		x = 60;
		y = (pos - 10) * 4;
	}
	else if (pos <=30) {
		x = (30 - pos) * 6;
		y = 40;
	}
	else if (pos <=40) {
		x = 0;
		y = (40 -pos) * 4;
	}

	WriteChar(' ', x + x0, y + y0);
}

void WindowSurface::DrawUserName(int gamer, int x, int y) const
{	
	Color foreground = gamer == -1 ? LightGray : USERS.GetUser(gamer)->GetColor();
	DrawString(gamer == -1 ? "-" : USERS.GetUser(gamer)->GetName(), x, y, foreground);
}

void WindowSurface::RedrawSpace(int index, Color foreground) const
{
	switch (index)
	{
	case 1:
		DrawString(" -1-", 8, 3, foreground);
		break;
	case 3:
		DrawString(" -1-", 20, 3, foreground);
		break;
	case 5:
		DrawString("  A", 32, 3, foreground);
		break;
	case 6:
		DrawString(" -2-", 38, 3, foreground);
		break;
	case 8:
		DrawString(" -2-", 50, 3, foreground);
		break;
	case 9:
		DrawString(" -2-", 56, 3, foreground);
		break;
	case 11:
		DrawString(" -3-", 62, 7, foreground);
		break;
	case 12:
		DrawString(" (@)", 62, 11, foreground);
		break;
	case 13:
		DrawString(" -3-", 62, 15, foreground);
		break;
	case 14:
		DrawString(" -3-", 62, 19, foreground);
		break;
	case 15:
		DrawString(" ЖД", 62, 23, foreground);
		break;
	case 16:
		DrawString(" -4-", 62, 27, foreground);
		break;
	case 18:
		DrawString(" -4-", 62, 35, foreground);
		break;
	case 19:
		DrawString(" -4-", 62, 39, foreground);
		break;
	case 21:
		DrawString(" -5-", 56, 43, foreground);
		break;
	case 23:
		DrawString(" -5-", 44, 43, foreground);
		break;
	case 24:
		DrawString(" -5-", 38, 43, foreground);
		break;
	case 25:
		DrawString("  A", 32, 43, foreground);
		break;
	case 26:
		DrawString(" -6-", 26, 43, foreground);
		break;
	case 27:
		DrawString(" -6-", 20, 43, foreground);
		break;
	case 28:
		DrawString(" (@)", 14, 43, foreground);
		break;
	case 29:
		DrawString(" -6-", 8, 43, foreground);
		break;
	case 31:
		DrawString(" -7-", 2, 39, foreground);
		break;
	case 32:
		DrawString(" -7-", 2, 35, foreground);
		break;
	case 34:
		DrawString(" -7-", 2, 27, foreground);
		break;
	case 35:
		DrawString(" ЖД", 2, 23, foreground);
		break;
	case 37:
		DrawString(" -8-", 2, 15, foreground);
		break;
	case 39:
		DrawString(" -8-", 2, 7, foreground);
	}

	SetConsoleTextAttribute(handle_, LightGray);
}
