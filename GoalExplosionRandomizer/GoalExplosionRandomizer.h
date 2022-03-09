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
	const char* getBMpath();
	
	bool getSelected(int var);
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;
	void setAllForN(int var);
	void clearAllForN(int var);

	bool Plugin_enabled = false;
	int lastSelected = 0;
	const char* items[106] = { "Abracadabra","Air Strike","Atomic Blip","Atomizer","Ball-Star","Ballistic","Batman 1989","Batman 2016","Beach Party","Big Splash","Buffy-Sugo","Butterflies","Carbonator","Chequered Flag","Chromatic Hollow","Classic","Cosmosis","DigiGlobe","Dueling Dragons","Dust Cloud","Electroshock","Fireworks","Floppy Fish","Force Razor I","Force Razor II","Grand Slam","Gravity Bomb","Hades Bomb","Hand Heart","Happy Holidays","Hellfire","HoloData","Hot Wheels","Juiced","Kablooey","Lantern Lift","League Legacy","Light Show","Meta-Blast","Meteor Storm","Mic Drop","Mister Monsoon","Neuro-Agitator","Night-Mare","Nomster","Overgrowth","Paper Dragon","Party Time","Phoenix Cannon","Planetary","Poly Pop","Poof","Popcorn","Quasar I","Quasar II","Quasar III","Rad Rock","Reaper","Righteous Gale","Riser","S5 - Bronze","S5 - Champion","S5 - Diamond","S5 - Gold","S5 - Grand Champion","S5 - Platinum","S5 - Silver","S5 - Supersonic Legend","Season 10 - Bronze","Season 10 - Champion","Season 10 - Diamond","Season 10 - Gold","Season 10 - Grand Champion","Season 10 - Platinum","Season 10 - Silver","Shade Raid","Shattered","Singularity","Solar Flare","Spatial Rift","Sphenergy","Standard Green","Standard Orange","Standard Pink","Standard Purple","Stay Puft","Striker Legend","Striker Pro","Striker","Sub-Zero","Supernova I","Supernova II","Supernova III","T. rex","TP","Tactical Nuke","Tentagoal","The Batman","The Dark Knight","Toon","Vampire Bat","Voxel","Wall Breaker I","Wall Breaker II","Wow!","Yeehaw" };
	const char* paints[14] = { "UNPAINTED","CRIMSON","LIME","BLACK","SKYBLUE","COBALT","BURNTSIENNA","FORESTGREEN","PURPLE","PINK","ORANGE","GREY","TITANIUMWHITE","SAFFRON" };
	uint16_t GoalIDs[106] = { 5104,5287,5826,2817,5955,2791,6805,2586,2922,3953,5378,2700,5659,5906,5851,1903,5419,5131,2044,4218,1904,1905,4523,3974,3975,4784,4549,4887,5262,2482,1908,4765,3324,2915,4328,3645,5061,4981,4522,4524,5257,5043,4118,6033,5237,4805,3703,2027,5975,5568,2349,3951,2329,3523,3524,3525,4873,2355,5036,4718,7429,7434,7433,7431,7435,7432,7430,7436,3952,3980,3979,3977,4158,3978,3976,7368,3763,3071,3453,5134,5708,1969,1970,1971,1972,4068,3020,3019,3018,1907,3129,3130,3131,2975,6470,4373,4823,7471,6743,2702,2023,4179,4377,4378,6922,6169 };

	int colorselection[106][14] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Abracadabra
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Air Strike
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Atomic Blip
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Atomizer
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Ball-Star
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Ballistic
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Batman 1989
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Batman 2016
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Beach Party
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Big Splash
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Buffy-Sugo
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Butterflies 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Carbonator
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Chequered Flag
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Chromatic Hollow
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Classic 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Cosmosis
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //DigiGlobe
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Dueling Dragons
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Dust Cloud
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Electroshock
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Fireworks
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Floppy Fish
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Force Razor I 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Force Razor II
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Grand Slam
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Gravity Bomb
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Hades Bomb
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Hand Heart
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Happy Holidays
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Hellfire
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //HoloData
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Hot Wheels
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Juiced
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Kablooey
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Lantern Lift
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //League Legacy
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Light Show
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Meta-Blast
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Meteor Storm
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Mic Drop
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Mister Monsoon
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Neuro-Agitator
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Night-Mare
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Nomster
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Overgrowth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Paper Dragon
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Party Time
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Phoenix Cannon
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Planetary
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Poly Pop
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Poof
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Popcorn
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Quasar I
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Quasar II
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Quasar III
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Rad Rock
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Reaper
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Righteous Gale
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Riser
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Bronze
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Champion
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Diamond
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Gold
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Grand Champion
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Platinum
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Silver
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //S5 - Supersonic Legend
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Bronze
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Champion
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Diamond
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Gold
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Grand Champion
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Platinum
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Silver
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Shade Raid
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Shattered
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Singularity
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Solar Flare
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Spatial Rift
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Sphenergy
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Green
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Orange
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Pink
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Purple
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Stay Puft
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Striker Legend
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Striker Pro
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Striker
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Sub-Zero
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Supernova I
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Supernova II
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Supernova III
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //T. rex
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //TP
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Tactical Nuke
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Tentagoal
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //The Batman
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //The Dark Knight
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Toon
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Vampire Bat
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Voxel
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Wall Breaker I
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Wall Breaker II
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Wow!
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //Yeehaw
	};
};