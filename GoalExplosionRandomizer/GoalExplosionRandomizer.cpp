#include "pch.h"
#include "GoalExplosionRandomizer.h"
#include "BMLoadout.h"
#include "bakkesmod\wrappers\cvarwrapper.h"
#include "bakkesmod\wrappers\GameWrapper.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
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

	cvarManager->registerNotifier("SelectOwned", [this](std::vector<std::string> args) {
		selectOwned();
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("SelectFavorites", [this](std::vector<std::string> args) {
		selectFavorites();
		}, "", PERMISSION_ALL);

	cvarManager->registerCvar("GoalExplosionRandomizer_enable", "0", "Enable Plugin", true, true, 0, true, 1)
		.addOnValueChanged([this](std::string oldValue, CVarWrapper cvar) {
			Plugin_enabled = cvar.getBoolValue();
		});

	gameWrapper->HookEventPost("Function TAGame.PRI_TA.ClientScoredGoal",
		[this](std::string eventName) {
			if (Plugin_enabled && checkempty()) {
				if (gameWrapper->IsInOnlineGame()) {
					getGoalExplosion();
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

	init();
}

void GoalExplosionRandomizer::onUnload() {}

void GoalExplosionRandomizer::init() {

	if (_mkdir(getSaveDir()) == 0)
		cvarManager->log("SavePath created");

	fillItemArray();
	sortItemsAlphabetically(0, items.size() - 1);
	writeUnpaintables();
	loadData();
}

void GoalExplosionRandomizer::setAllForN(uint64_t index) {

	for (uint64_t var = 0; var < IM_ARRAYSIZE(paints); var++) {
		if (selection[(index * IM_ARRAYSIZE(paints)) + var] != 2)
			selection[(index * IM_ARRAYSIZE(paints)) + var] = 1;
	}
	saveData();
}

void GoalExplosionRandomizer::clearAllForN(uint64_t index) {

	for (uint64_t var = 0; var < IM_ARRAYSIZE(paints); var++) {
		if (selection[(index * IM_ARRAYSIZE(paints)) + var] != 2)
			selection[(index * IM_ARRAYSIZE(paints)) + var] = 0;
	}
	saveData();
}

void GoalExplosionRandomizer::selectAll() {

	for (int var = 0; var < selection.size(); var++) {
		if (selection[var] != 2)
			selection[var] = 1;
	}
	saveData();
}

void GoalExplosionRandomizer::clearAll() {

	for (int var = 0; var < selection.size(); var++) {
		if (selection[var] != 2)
			selection[var] = 0;
	}
	saveData();
}

void GoalExplosionRandomizer::selectForXY(std::string Label, uint64_t PaintID) {

	for (uint64_t var = 0; var < items.size() ; var++) {

		if (items[var] == Label)
			selection[(var * IM_ARRAYSIZE(paints)) + PaintID] = 1;
	}

}

void GoalExplosionRandomizer::selectOwned() {

	auto iw = gw->GetItemsWrapper();
	if (iw.IsNull()) { return; }
	auto arr = iw.GetOwnedProducts();
	if (arr.IsNull()) { return; }

	bool isPainted = false;

	for (int var = 1; var < arr.Count(); var++) {

		auto product = arr.Get(var);
		if (!product.IsNull()) {

			auto productSlot = product.GetProduct();

			if (!productSlot.IsNull()) {

				if (productSlot.GetSlot().GetOnlineLabel().ToString() == "Goal Explosion") {

					auto attributes = product.GetAttributes();

					if (!attributes.IsNull()) {

						for (int svar = 0; svar < attributes.Count(); svar++) {

							auto attr = attributes.Get(svar);

							if (attr.GetAttributeType() == "ProductAttribute_Painted_TA") {
								selectForXY(product.GetLongLabel().ToString(), ProductAttribute_PaintedWrapper(attr.memory_address).GetPaintID());
								isPainted = true;
							} 
						}
					}

					if (isPainted == false)
						selectForXY(product.GetLongLabel().ToString(), 0);

					isPainted = false;
				}
			}
		}
	}
	saveData();
}

void GoalExplosionRandomizer::selectFavorites() {

/*	auto iw = gw->GetItemsWrapper();
	if (iw.IsNull()) { return; }
	auto arr = iw.GetOwnedProducts();
	if (arr.IsNull()) { return; }

	bool isPainted = false;

	for (int var = 1; i < arr.Count(); var++) {

		auto product = arr.Get(var);
		if (!product.IsNull()) {

			auto productSlot = product.GetProduct();

			if (!productSlot.IsNull()) {

				if (productSlot.GetSlot().GetOnlineLabel().ToString() == "Goal Explosion") {

					auto attributes = product.GetAttributes();

					if (!attributes.IsNull()) {

						for (int x = 0; svar < attributes.Count(); svar++) {

							auto attr = attributes.Get(svar);

							if (attr.GetAttributeType() == "ProductAttribute_Painted_TA" && product.IsFavorited()) {
								selectForXY(product.GetLongLabel().ToString(), ProductAttribute_PaintedWrapper(attr.memory_address).GetPaintID());
								isPainted = true;
							}
						}
					}

					if (isPainted == false && product.IsFavorited())
						selectForXY(product.GetLongLabel().ToString(), 0);

					isPainted = false;

				}
			}
		}
	}*/

}

bool GoalExplosionRandomizer::checkempty() {

	for (int var = 0; var < selection.size(); var++)
			if (selection[var] == 1)
				return true;
	return false;
}

void GoalExplosionRandomizer::getGoalExplosion() {

	while(true) {

		int var = rndm(0, selection.size());

		if (selection[var] == 1) {
			goal = GoalIDs[(int)(var / 14)];
			paint = var % 14;
			return;
		}
	}
}

int GoalExplosionRandomizer::rndm(int min, int max) {
	return (rand() % max + min);
}

std::string GoalExplosionRandomizer::getItemCode() {

	CVarWrapper code_cvar = cvarManager->getCvar("cl_itemmod_code");
	if (!code_cvar || code_cvar.getStringValue() == "") {
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
	file.open(getSaveFile(), std::ios::out);
	if (file.is_open())
		for (int var = 0; var < selection.size(); var++) {
				file << (int)selection[var];
				file << "\n";
		}
	file.close();
}

void GoalExplosionRandomizer::loadData() {

	int var = 0;

	std::fstream file;
	file.open(getSaveFile(), std::ios::in);

	if (!file.is_open()) return;

	std::string line;
	while(std::getline(file, line)) {
		
		if (line._Equal("0") && selection[var] != 2)
			selection[var] = 0;
		else if (line._Equal("1") && selection[var] != 2)
			selection[var] = 1;

		var++;
	}

	file.close();
}

const char* GoalExplosionRandomizer::getSaveDir() {

	auto BMpath = gameWrapper->GetDataFolder() / "GoalExplosionRandomizer";
	std::string BMpath_str = BMpath.string();
	return BMpath_str.c_str();
}

const char* GoalExplosionRandomizer::getSaveFile() {

	auto BMpath = gameWrapper->GetDataFolder() / "GoalExplosionRandomizer" / "GoalExplosionRandomizer.txt";
	std::string BMpath_str = BMpath.string();
	return BMpath_str.c_str();
}

void GoalExplosionRandomizer::fillItemArray() {

	auto iw = gw->GetItemsWrapper();
	if (iw.IsNull()) return;
	auto arr = iw.GetAllProducts();
	if (arr.IsNull()) return;

	items.clear();
	GoalIDs.clear();

	for (int var = 1; var <= arr.Count(); var++) {

		ProductWrapper product = iw.GetProduct(var);
		if (!product.IsNull()) {

			if (product.GetSlot().GetOnlineLabel().ToString() == "Goal Explosion") {

				std::string Label = product.GetLabel().ToString();
				items.push_back(Label);
				GoalIDs.push_back(var);
			}
		}
	}
}

void GoalExplosionRandomizer::sortItemsAlphabetically(int start, int end) {

	if (start >= end)
		return;

	int p = partition(start, end);
	sortItemsAlphabetically(start, p - 1);
	sortItemsAlphabetically(p + 1, end);

}

int GoalExplosionRandomizer::partition(int start, int end) {

	std::string pivot = items[start];

	int count = 0;
	for (int var = start + 1; var <= end; var++) {
		if (items[var] <= pivot)
			count++;
	}

	int pivotIndex = start + count;
	Swap(pivotIndex, start);

	int var = start, svar = end;

	while (var < pivotIndex && svar > pivotIndex) {

		while (items[var] <= pivot) {
			var++;
		}

		while (items[svar] > pivot) {
			svar--;
		}

		if (var < pivotIndex && svar > pivotIndex) {
			Swap(var++, svar--);
		}
	}

	return pivotIndex;
}

void GoalExplosionRandomizer::Swap(int var, int svar) {

	std::string temp = items[svar];
	items[svar] = items[var];
	items[var] = temp;

	uint16_t temp2 = GoalIDs[svar];
	GoalIDs[svar] = GoalIDs[var];
	GoalIDs[var] = temp2;

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

bool GoalExplosionRandomizer::isPaintable(int index) {

	auto iw = gw->GetItemsWrapper();
	if (iw.IsNull()) { return false; }
	auto arr = iw.GetAllProducts();
	if (arr.IsNull()) { return false; }

	ProductWrapper product = iw.GetProduct(GoalIDs[index]);
	if (!product.IsNull())
		if (product.IsPaintable())
			return true;

	return false;
}