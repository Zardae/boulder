#include "clickable.h"

namespace Boulder
{
	Clickable::Clickable()
	{
		posx = 0;
		posy = 0;
		enabled = false;
	}

	Clickable::Clickable(bool penabled, int px, int py)
	{
		enabled = penabled;
		posx = px;
		posy = py;
	}

	bool Clickable::IsEnabled()
	{
		return enabled;
	}

	void Clickable::SetEnabled(bool penabled)
	{
		enabled = penabled;
	}

	void Clickable::ToggleEnabled()
	{
		enabled = !enabled;
	}


	RectButton::RectButton()
	{
		width = 0;
		height = 0;
	}
};