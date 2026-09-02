#pragma once
#include "Pch.h"
#include "PlayerConfig.h"
#include "Overlay.h"

struct ItemEspConfig {
	bool Enabled    = true;
	int  MaxDistance = 500;
	int  FontSize    = 10;
	D2D1::ColorF Colour = D2D1::ColorF(1.f, 0.86f, 0.f, 1.f); // gold
};

class ConfigInstances
{
public:
	PlayerConfig Survivor = PlayerConfig(LIT("Survivor"));
	PlayerConfig Killer = PlayerConfig(LIT("Killer"));
	OverlayConfig Overlay = OverlayConfig(LIT("Overlay"));
	ItemEspConfig Items;
	json ToJson()
	{
		json jsoned;
		jsoned.merge_patch(Survivor.ToJson());
		jsoned.merge_patch(Overlay.ToJson());
		jsoned.merge_patch(Killer.ToJson());
		return jsoned;
	}

	void FromJson(json jsoned)
	{
		Survivor.FromJson(jsoned);
		Overlay.FromJson(jsoned);
		Killer.FromJson(jsoned);
	}
};