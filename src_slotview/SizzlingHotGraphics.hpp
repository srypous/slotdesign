#include "Win32Graphics.hpp"

#ifndef SIZZLINGHOTGRAPHICS_HPP
#define SIZZLINGHOTGRAPHICS_HPP

class SizzlingHotGraphics : public Win32Graphics
{
public:
	SizzlingHotGraphics(int width, int height)
		: Win32Graphics(width, height)
	{}

	void paint(HDC hdc)
	{
		if (!this->wasInitialized)
			return;

		Gdiplus::Graphics graphics(hdc);
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

		// Draw the frame around
		int padding = 15;
		graphics.DrawRectangle(this->penFrame, this->offsetX - padding, this->offsetY - padding
								, 2 * padding + Settings::reelCount * this->symbolW
								, 2 * padding + Settings::rowCount * this->symbolH);

		// Draw symbols
		if (WinGlobal::game->isWindowReady())
		{
			for (int i = 0; i<Settings::reelCount; i++)
				for (int j=0; j<Settings::rowCount; j++)
				{
					int symbolID = WinGlobal::game->getWindow().getSymbol(i, j);
					assert((symbolID >= 0) && (symbolID < Settings::symbolCount));
					DrawState(hdc, NULL, NULL, LPARAM(this->bmpSymbol[symbolID]), 0
						,this->offsetX + i * this->symbolW, this->offsetY + j * this->symbolH
						, 0, 0, DST_BITMAP);
			}
		}

		// Draw the grid
		for (int j=0; j<=Settings::rowCount; j++)
		{
			graphics.DrawLine(this->penGrid
				, this->offsetX, this->offsetY + j * this->symbolH
				, this->offsetX + Settings::reelCount * this->symbolW, this->offsetY + j * this->symbolH);
		}
		for (int i = 0; i<=Settings::reelCount; i++)
		{
				graphics.DrawLine(this->penGrid
				, this->offsetX + i * this->symbolW, this->offsetY 
				, this->offsetX + i * this->symbolW, this->offsetY + Settings::rowCount * this->symbolH);
		}

		// Draw higlights
		int margin = 4;
		for (int i = 0; i<Settings::reelCount; i++)
			for (int j=0; j<Settings::rowCount; j++)
			{
				if (WinGlobal::game->highlighted(i, j))
					graphics.DrawRectangle(this->penHighlight
					, this->offsetX + i * this->symbolW + margin
					, this->offsetY + j * this->symbolH + margin
					, this->symbolW - 2*margin
					, this->symbolH - 2*margin);
			}

		// Draw number values
		wchar_t txtWin[50];
		swprintf(txtWin, L"Kredit: %d", WinGlobal::game->getCredit());
		TextOut(hdc, this->offsetX, 350, txtWin, wcslen(txtWin));
		swprintf(txtWin, L"V�hra: %d", WinGlobal::game->getLastWinAmount());
		TextOut(hdc, this->width - 1.5*this->offsetX, 350, txtWin, wcslen(txtWin));
	}
};


#endif