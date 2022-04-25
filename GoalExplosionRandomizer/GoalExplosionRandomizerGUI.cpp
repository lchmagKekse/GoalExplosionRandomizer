#include "pch.h"
#include "GoalExplosionRandomizer.h"

std::string GoalExplosionRandomizer::GetPluginName() {
	return "Goal Explosion Randomizer";
}

void GoalExplosionRandomizer::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void GoalExplosionRandomizer::RenderSettings() {

	CVarWrapper enableCvar = cvarManager->getCvar("GoalExplosionRandomizer_enable");
	if (!enableCvar) return;
	bool enabled = enableCvar.getBoolValue();
	if (ImGui::Checkbox("Enable plugin", &enabled))
		enableCvar.setValue(enabled);

	ImGui::Text("\nSelect Goal Explosions:");
	if (ImGui::ListBoxHeader(""))
	{
		for (int var = 0; var < items.size(); var++)
		{
			if (ImGui::Selectable(items[var].c_str(), getSelected(var))) {
				lastSelected = var;
				if (ImGui::GetIO().KeyShift)
					setAllForN(lastSelected);
				if (ImGui::GetIO().KeyCtrl)
					clearAllForN(lastSelected);
			}
		}
		ImGui::ListBoxFooter();
	}
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.4f, 1.0f), "Shift\nCtrl");
	ImGui::SameLine(0,0);
	ImGui::Text(" to select all paints\n to clear all paints");

	ImGui::NewLine();
	ImGui::Text("Select Colors for ");
	ImGui::SameLine(0,0);
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.4f, 1.0f), items[lastSelected].c_str());

	if (ImGui::ListBoxHeader(" "))
	{
		for (uint64_t var = 0; selection[(lastSelected * IM_ARRAYSIZE(paints)) + var] != 2 && var < IM_ARRAYSIZE(paints); var++)
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

	ImGui::NewLine();
	if (ImGui::Button("Clear all")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("ClearAll"); });
	}

	ImGui::SameLine();
	if (ImGui::Button("Select all")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("SelectAll"); });
	}

	ImGui::SameLine();
	if (ImGui::Button("Select owned")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("SelectOwned"); });
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Selects all owned Goal Explosions");
	}

	ImGui::SameLine();
	if (ImGui::Button("Select favorites")) {
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("SelectFavorites"); });
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Selects all Goal Explosions marked as Favorite");
	}

	ImGui::SameLine();
	CVarWrapper repetition = cvarManager->getCvar("NoRepetition");
	if (!repetition) return;
	bool repetitionEnabled = repetition.getBoolValue();
	if (ImGui::Checkbox("No repetition", &repetitionEnabled))
		repetition.setValue(repetitionEnabled);
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Disables that the same Goal Explosion gets played twice in a row");

	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.4f, 0.5f), "Made by LchmagKekse");
}

