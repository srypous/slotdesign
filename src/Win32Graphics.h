// link the Gdiplus library
#pragma comment(lib,"gdiplus.lib")
#include <windows.h>
#include <GdiPlus.h>
#include "WinGlobal.h"
#include "resource.h"
#include "Settings.h"
#include "Game.h"
#include "Reel.h"

#ifndef WIN32GRAPHICS_HPP
#define WIN32GRAPHICS_HPP

class Win32Graphics
{
protected:
	const int symbolCount;
	const int reelCount;
	const int rowCount;
	int width, height;
	int offsetX, offsetY;
	int symbolW, symbolH;
	bool wasInitialized;
	HBITMAP* bmpSymbol;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::Pen* penGrid;
	Gdiplus::Pen* penFrame;
	Gdiplus::Pen* penFrameWin;
	Gdiplus::Pen* penHighlight;
public:
	Win32Graphics(int width, int height);
	~Win32Graphics();
	void init();
public:
	virtual void paint(HDC hdc);
	void paintBasic(HDC hdc);
private:
	virtual void loadSymbols()
	{}
};

class ValueWidget
{
public:
	typedef enum
	{
		FormatInt,
		FormatDouble
	} ValueFormat;

	ValueWidget(std::wstring caption, int xpos, int ypos, int width, int height);
	void setValue(int value);
	void setValue(double value);
	void setFormat(ValueFormat format);
	void paint(Gdiplus::Graphics& graphics);

private:
	int xpos, ypos, width, height;
	std::wstring caption;
	int valueInt;
	double valueDouble;
	ValueFormat format;
};

#endif