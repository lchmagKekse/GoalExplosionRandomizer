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
	const char* items[93] = { "Abracadabra","Air Strike","Atomic Blip","Atomizer","Ball-Star","Ballistic","Batman 1989","Batman 2016","Beach Party","Big Splash","Buffy-Sugo","Butterflies","Carbonator","Chequered Flag","Chromatic Hollow","Classic","Cosmosis","DigiGlobe","Dueling Dragons","Dust Cloud","Electroshock","Fireworks","Floppy Fish","Force Razor I","Force Razor II","Grand Slam","Gravity Bomb","Hades Bomb","Hand Heart","Happy Holidays","Hellfire","HoloData","Hot Wheels","Juiced","Kablooey","Lantern Lift","League Legacy","Light Show","Meta-Blast","Meteor Storm","Mic Drop","Mister Monsoon","Neuro-Agitator","Night-Mare","Overgrowth","Paper Dragon","Party Time","Phoenix Cannon","Planetary","Poly Pop","Poof","Popcorn","Quasar I","Quasar II","Quasar III","Rad Rock","Reaper","Righteous Gale","Riser","Season 10 - Bronze","Season 10 - Champion","Season 10 - Diamond","Season 10 - Gold","Season 10 - Grand Champion","Season 10 - Platinum","Season 10 - Silver","Shattered","Singularity","Solar Flare","Spatial Rift","Sphenergy","Standard Green","Standard Orange","Standard Pink","Standard Purple","Stay Puft","Striker Legend","Striker Pro","Striker","Sub-Zero","Supernova I","Supernova II","Supernova III","T. rex","Tactical Nuke","The Dark Knight","Toon","Vampire Bat","Voxel","Wall Breaker I","Wall Breaker II","Wow!","Yeehaw" };
	const char* paints[14] = { "UNPAINTED","CRIMSON","LIME","BLACK","SKYBLUE","COBALT","BURNTSIENNA","FORESTGREEN","PURPLE","PINK","ORANGE","GREY","TITANIUMWHITE","SAFFRON" };
	uint16_t GoalIDs[93] = { 5104,5287,5826,2817,5955,2791,6805,2586,2922,3953,5378,2700,5659,5906,5851,1903,5419,5131,2044,4218,1904,1905,4523,3974,3975,4784,4549,4887,5262,2482,1908,4765,3324,2915,4328,3645,5061,4981,4522,4524,5257,5043,4118,6033,4805,3703,2027,5975,5568,2349,3951,2329,3523,3524,3525,4873,2355,5036,4718,3952,3980,3979,3977,4158,3978,3976,3763,3071,3453,5134,5708,1969,1970,1971,1972,4068,3020,3019,3018,1907,3129,3130,3131,2975,4373,6743,2702,2023,4179,4377,4378,6922,6169 };

	int colorselection[93][14] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Abracadabra x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Air Strike x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Atomic Blip x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Atomizer x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Ball-Star x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Ballistic x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Batman 1989 x 
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Batman 2016 x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Beach Party x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Big Splash x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Buffy-Sugo x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Butterflies x 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Carbonator x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Chequered Flag x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Chromatic Hollow x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Classic x 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Cosmosis x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //DigiGlobe x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Dueling Dragons x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Dust Cloud x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Electroshock x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Fireworks x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Floppy Fish x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Force Razor I x 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Force Razor II x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Grand Slam x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Gravity Bomb x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Hades Bomb x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Hand Heart x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Happy Holidays x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Hellfire x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //HoloData x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Hot Wheels x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Juiced x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Kablooey x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Lantern Lift x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //League Legacy
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Light Show x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Meta-Blast x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Meteor Storm x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Mic Drop
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Mister Monsoon
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Neuro-Agitator
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Night-Mare x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Overgrowth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Paper Dragon
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Party Time
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Phoenix Cannon XXX
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Planetary x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Poly Pop
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Poof
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Popcorn
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Quasar I
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Quasar II
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Quasar III x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Rad Rock
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Reaper
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Righteous Gale x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Riser x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Bronze
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Champion
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Diamond
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Gold
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Grand Champion
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Platinum
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Season 10 - Silver x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Shattered
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Singularity
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Solar Flare x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Spatial Rift x
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Sphenergy x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Green
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Orange
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Pink
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Standard Purple
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Stay Puft x
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Striker Legend
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Striker Pro
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Striker
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Sub-Zero
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Supernova I
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Supernova II
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //Supernova III
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //T. rex
		0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, //Tactical Nuke
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