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
	void init();

	int rndm(int min, int max);
	void setGoalExplosion(uint16_t goalID, uint8_t paintID);
	std::string getItemCode();
	void getGoalExplosion();
	bool checkempty();
	void saveData();
	void loadData();
	void clearAll();
	void selectAll();
	void selectOwned();
	void selectFavorites();
	const char* getSaveDir();
	const char* getSaveFile();
	void selectForXY(std::string Label, uint64_t PaintID);
	void fillItemArray();
	void sortItemsAlphabetically(int start, int end);
	int partition(int start, int end);
	void Swap(int var, int svar);
	void writeUnpaintables();
	bool isPaintable(int index);
	
	bool getSelected(uint64_t index);
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;
	void setAllForN(uint64_t index);
	void clearAllForN(uint64_t index);

	bool Plugin_enabled = false;
	uint64_t lastSelected = 0;
	std::vector<std::string> items;
	std::vector<std::uint16_t> GoalIDs;
	std::vector<std::uint8_t> selection;
	const char* paints[14] = { "UNPAINTED","CRIMSON","LIME","BLACK","SKYBLUE","COBALT","BURNTSIENNA","FORESTGREEN","PURPLE","PINK","ORANGE","GREY","TITANIUMWHITE","SAFFRON" };

};