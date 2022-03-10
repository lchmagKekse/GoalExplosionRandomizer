#include "pch.h"
#include "GoalExplosionRandomizer.h"
#include "imgui/imgui.h"

std::string GoalExplosionRandomizer::GetPluginName() {
	return "Goal Explosion Randomizer";
}

void GoalExplosionRandomizer::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void GoalExplosionRandomizer::RenderSettings() {

	CVarWrapper enableCvar = cvarManager->getCvar("GoalExplosionRandomizer_enable");

	if (!enableCvar) {
		return;
	}

	bool enabled = enableCvar.getBoolValue();

	if (ImGui::Checkbox("Enable plugin", &enabled)) {
		enableCvar.setValue(enabled);
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Toggle Goal Explosion Randomizer");
	}

	ImGui::Text("\nSelect Goal Explosions:");
	if (ImGui::ListBoxHeader("Shift to clear all paints\nCtrl to select all paints"))
	{
		for (int var = 0; var < items.size(); var++)
		{
			if (ImGui::Selectable(items[var].c_str(), getSelected(var))) {
				lastSelected = var;
				if (ImGui::GetIO().KeyCtrl)
					setAllForN(lastSelected);
				if (ImGui::GetIO().KeyShift)
					clearAllForN(lastSelected);
			}				
		}
		ImGui::ListBoxFooter();
	}

	std::string a = "\nSelect Colors for ";
	std::string b = items[lastSelected];
	std::string c = a + b;

	ImGui::Text(c.c_str());
	if (ImGui::ListBoxHeader(" "))
	{
		for (int var = 0; selection[(lastSelected * IM_ARRAYSIZE(paints)) + var] != 2 && var < IM_ARRAYSIZE(paints); var++)
		{
			if (ImGui::Selectable(paints[var], selection[(lastSelected * IM_ARRAYSIZE(paints)) + var]))
			{
				if (selection[(lastSelected * IM_ARRAYSIZE(paints)) + var] != 2)
					selection[(lastSelected * IM_ARRAYSIZE(paints)) + var] ^= 1;
				saveData();
			}
		}
		ImGui::ListBoxFooter();
	}

	ImGui::Text("");
	if (ImGui::Button("Clear all")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("ClearAll"); });
	}

	ImGui::SameLine();
	if (ImGui::Button("Select all")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("SelectAll"); });
	}

	ImGui::Text("Made by LchmagKekse");
}

bool GoalExplosionRandomizer::getSelected(int var) {

	bool isenabled = false;

	for (int svar = 0; svar < IM_ARRAYSIZE(paints) && !isenabled; svar++) {
		if (selection[(var * IM_ARRAYSIZE(paints)) + svar] == 1)
			isenabled = true;
	}
	return isenabled;
}