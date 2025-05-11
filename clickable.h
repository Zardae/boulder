#pragma once
#include "surface.h"


namespace Boulder {

	class Clickable
	{
	public:
		Clickable();
		Clickable(bool penabled, int px, int py);
		bool IsEnabled();
		void SetEnabled( bool penabled );
		void ToggleEnabled();
		void OnClick();

	private:
		bool enabled;
		int posx;
		int posy;
	};

	class RectButton : Clickable
	{
	public:
		RectButton();
		RectButton(Sprite psprite, int pwidth, int pheight);
	private:
		int width;
		int height;
		// Sprite sprite;
	};
}