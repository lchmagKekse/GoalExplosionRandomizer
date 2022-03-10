#pragma once
#include "imgui/imgui.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class GoalExplosionRandomizer: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow
{
	virtual void onLoad();
	virtual void onUnload();

	int rndm(int min, int max);
	void setGoalExplosion(uint16_t goalID, uint8_t paintID);
	std::string getItemCode();
	void setRandomGoalExplosionFromSelected();
	bool checkempty();
	void saveData();
	void loadData();
	void clearAll();
	void selectAll();
	void selectOwned();
	const char* getSelectionSavePath();
	void selectForXY(std::string var, int svar);
	void fillVector();
	void sortVector();
	void writeUnpaintables();
	bool isPaintable(int);
	
	bool getSelected(int var);
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;
	void setAllForN(int var);
	void clearAllForN(int var);

	bool Plugin_enabled = false;
	int lastSelected = 0;
	std::vector<std::string> items;
	std::vector<std::uint16_t> GoalIDs;
	std::vector<std::uint8_t> selection;
	const char* paints[14] = { "UNPAINTED","CRIMSON","LIME","BLACK","SKYBLUE","COBALT","BURNTSIENNA","FORESTGREEN","PURPLE","PINK","ORANGE","GREY","TITANIUMWHITE","SAFFRON" };

};