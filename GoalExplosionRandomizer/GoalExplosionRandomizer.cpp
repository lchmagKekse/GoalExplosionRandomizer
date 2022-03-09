#include "pch.h"
#include "GoalExplosionRandomizer.h"
#include "BMLoadout.h"
#include "bakkesmod\wrappers\cvarwrapper.h"
#include "bakkesmod\wrappers\GameWrapper.h"
#include <iostream>
#include <fstream>
#include <string>

BAKKESMOD_PLUGIN(GoalExplosionRandomizer, "GoalExplosionRandomizer", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
std::shared_ptr<GameWrapper> gw;

uint16_t goal;
uint8_t paint;
std::string itemmod_code;


void GoalExplosionRandomizer::onLoad() {

	_globalCvarManager = cvarManager;

	cvarManager->registerNotifier("ClearAll", [this](std::vector<std::string> args) {
		clearAll();
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("SelectAll", [this](std::vector<std::string> args) {
		selectAll();
		}, "", PERMISSION_ALL);

	cvarManager->registerCvar("GoalExplosionRandomizer_enable", "0", "Enable Plugin", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
		Plugin_enabled = cvar.getBoolValue();
			});

	gameWrapper->HookEventPost("Function TAGame.PRI_TA.ClientScoredGoal",
		[this](std::string eventName) {
			if (Plugin_enabled && checkempty()) {
				if (gameWrapper->IsInOnlineGame()) {
					setRandomGoalExplosionFromSelected();
					setGoalExplosion(goal, 0);
				}
			}			
		});

	gameWrapper->HookEventPost("Function ReplayDirector_TA.Playing.EndState",
		[this](std::string eventName) {
			if (Plugin_enabled && checkempty()) {
				if (gameWrapper->IsInOnlineGame()) {
					if (paint == 0)
						paint = 19;
					setGoalExplosion(goal, paint);
				}
			}
		});

	fillVector();
	sortVector();
	writeUnpaintables();
	loadData();
}

void GoalExplosionRandomizer::onUnload() {}

void GoalExplosionRandomizer::setAllForN(int var) {

	for (int x = 0; x < IM_ARRAYSIZE(paints); x++) {
		if (colorselection[var][x] != 2)
			colorselection[var][x] = 1;
	}
	saveData();
}

void GoalExplosionRandomizer::clearAllForN(int var) {

	for (int x = 0; x < IM_ARRAYSIZE(paints); x++) {
		if (colorselection[var][x] != 2)
			colorselection[var][x] = 0;
	}
	saveData();
}

void GoalExplosionRandomizer::selectAll() {

	for (int i = 0; i < items.size(); i++) {
		for (int x = 0; x < IM_ARRAYSIZE(paints); x++) {
			if (colorselection[i][x] != 2)
				colorselection[i][x] = 1;
		}
	}
	saveData();
}

bool GoalExplosionRandomizer::checkempty() {

	for (int i = 0; i < items.size(); i++) {
		for (int x = 0; x < IM_ARRAYSIZE(paints); x++) {

			if (colorselection[i][x] == 1)
			{
				return true;
			}
		}
	}
	return false;
}

void GoalExplosionRandomizer::setRandomGoalExplosionFromSelected() {

	int var, svar;

	for (bool hasIDs = false; !hasIDs;) {
		var = rndm(0, items.size());
		svar = rndm(0, IM_ARRAYSIZE(paints));

		if (colorselection[var][svar] == 1) {
			goal = GoalIDs[var];
			paint = svar;
			hasIDs = true;
		}
	}
}

int GoalExplosionRandomizer::rndm(int min, int max) {
	return (rand() % max + min);
}

std::string GoalExplosionRandomizer::getItemCode() {

	CVarWrapper code_cvar = cvarManager->getCvar("cl_itemmod_code");
	if (!code_cvar) {
		return "AwIgA1yAAAA=";
	}
	return code_cvar.getStringValue();
}

void GoalExplosionRandomizer::setGoalExplosion(uint16_t goalID, uint8_t paintID) {

	BMLoadout customLoadout = load(getItemCode());

	customLoadout.body.blue_loadout[SLOT_GOALEXPLOSION] = { SLOT_GOALEXPLOSION, goalID, paintID };
	customLoadout.body.orange_loadout[SLOT_GOALEXPLOSION] = { SLOT_GOALEXPLOSION, goalID, paintID };

	std::string loadoutString = save(customLoadout);
	cvarManager->executeCommand("cl_itemmod_enabled 1; cl_itemmod_code \"" + loadoutString + "\"");
}

void GoalExplosionRandomizer::saveData() {

	std::fstream file;
	file.open(getBMpath(), std::ios::out);
	if (file.is_open())
		for (int i = 0; i < items.size(); i++) {
			for (int x = 0; x < IM_ARRAYSIZE(paints); x++) {
				file << colorselection[i][x];
				file << "\n";
			}
		}
	file.close();
}

void GoalExplosionRandomizer::loadData() {
	int var = 0, svar = 0;
	std::fstream file;
	file.open(getBMpath(), std::ios::in);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			if (svar >= IM_ARRAYSIZE(paints)) {
				svar = 0;
				var++;
			}

			if (line._Equal("0") && colorselection[var][svar] != 2)
				colorselection[var][svar] = 0;
			else if (line._Equal("1") && colorselection[var][svar] != 2)
				colorselection[var][svar] = 1;
			svar++;
		}
	}
	file.close();
}

void GoalExplosionRandomizer::clearAll() {

	for (int i = 0; i < items.size(); i++) {
		for (int x = 0; x < IM_ARRAYSIZE(paints); x++) {
			if(colorselection[i][x] != 2)
				colorselection[i][x] = 0;
		}
	}
	saveData();
}

const char* GoalExplosionRandomizer::getBMpath() {

	auto BMpath = gameWrapper->GetDataFolder() / "GoalExplosionRandomizer.txt";
	std::string BMpath_str = BMpath.string();
	return BMpath_str.c_str();
}

void GoalExplosionRandomizer::fillVector() {

	auto iw = gw->GetItemsWrapper();
	if (iw.IsNull()) { return; }
	auto arr = iw.GetAllProducts();
	if (arr.IsNull()) { return; }

	items.clear();
	GoalIDs.clear();

	for (int i = 1; i <= arr.Count(); i++) {

		ProductWrapper product = iw.GetProduct(i);
		if (!product.IsNull()) {

			if (product.GetSlot().GetOnlineLabel().ToString() == "Goal Explosion") {

				std::string svar = product.GetLabel().ToString();
				items.push_back(svar);
				GoalIDs.push_back(i);
			}
		}
	}
}

void GoalExplosionRandomizer::sortVector() {

	for (int var = 0; var < items.size(); var++) {
		for (int svar = 0; svar < (items.size() - 1 - var); svar++) {

			if (strcmp(items[svar].c_str(), items[svar + 1].c_str()) > 0) {

				std::string temp = items[svar];
				items.erase(items.begin() + svar);
				items.insert(items.begin() + svar + 1, temp);

				uint16_t temp2 = GoalIDs[svar];
				GoalIDs.erase(GoalIDs.begin() + svar);
				GoalIDs.insert(GoalIDs.begin() + svar + 1, temp2);

			}
		}
	}
}

void GoalExplosionRandomizer::writeUnpaintables() {

	for (int var = 0; var < items.size(); var++) {

		if (isPaintable(var))
			for (int svar = 0; svar < IM_ARRAYSIZE(paints); svar++) {			
				selection.push_back(0);
			}
		else {
			selection.push_back(0);
			for (int svar = 0; svar < (IM_ARRAYSIZE(paints) - 1); svar++) {
				selection.push_back(2);
			}
		}
	}
}

bool GoalExplosionRandomizer::isPaintable(int var) {

	auto iw = gw->GetItemsWrapper();
	if (iw.IsNull()) { return false; }
	auto arr = iw.GetAllProducts();
	if (arr.IsNull()) { return false; }

	ProductWrapper product = iw.GetProduct(GoalIDs[var]);
	if (!product.IsNull())
		if (product.IsPaintable())
			return true;

	return false;
}