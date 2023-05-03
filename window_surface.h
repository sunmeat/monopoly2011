#ifndef WINDOW_SURFACE_H_
#define WINDOW_SURFACE_H_

#include "color.h"
struct Space;

#define WINSURF WindowSurface::instance()

class WindowSurface
{
public:
	// Создание объекта
	static const WindowSurface &instance();

	void DrawGameMap() const;
	void DrawSpaceInfo(const Space *space, int x, int y) const;
	void DrawString(const char *str, int x, int y, Color foreground) const;
	void DrawRectangle(int x, int y, int width, int height, Color foreground) const;
	void DrawSmilie(int gamer, int old_p, int new_p) const;
	void ClearSmilie(int gamer) const;
	void DrawUserName(int gamer, int x, int y) const;
	void RedrawSpace(int index, Color foreground) const;

	void ClearRectangle(int x, int y, int width, int height) const;

private:
	WindowSurface();
	WindowSurface(const WindowSurface &);
	WindowSurface &operator=(const WindowSurface &);

	void GotoXY(int x, int y) const;
	void WriteChar(char ch, int x, int y) const;
	void WriteChars(char ch, int x, int y, int len) const;

	HANDLE handle_;
};

#endif
