#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "Engine.h"
#include "ConfigUtilities.h"
#include "ItemEsp.h"

void DrawItemEsp()
{
	if (!Configs.Items.Enabled)
		return;
	if (!EngineInstance)
		return;

	auto items  = EngineInstance->GetItems();
	auto cam    = EngineInstance->GetCameraCache();
	Vector3 campos(cam.POV.Location.X, cam.POV.Location.Y, cam.POV.Location.Z);

	for (auto& item : items) {
		Vector3 pos(item.position.X, item.position.Y, item.position.Z);
		if (pos.IsZero())
			continue;

		float dist = Vector3::Distance(campos, pos) / 100.f;
		if (dist < 0.f || dist > static_cast<float>(Configs.Items.MaxDistance))
			continue;

		Vector2 screen = Camera::WorldToScreen(cam.POV, pos);
		if (screen.IsZero())
			continue;

		std::wstring label = L"Loot [" + std::to_wstring(static_cast<int>(dist)) + L"m]";
		DrawText(static_cast<int>(screen.x), static_cast<int>(screen.y),
		         label, "Verdana", Configs.Items.FontSize,
		         MyColour(Configs.Items.Colour), CentreCentre);
	}
}
