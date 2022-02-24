#pragma once

#include "helper_classes.h"

#include <stdint.h>
#include <map>

#define CURRENT_LOADOUT_VERSION 2


	/*
	Slots supported by BakkesMod
*/
	enum EQUIPSLOT {
		SLOT_BODY = 0, //Body won't be applied when loading in BakkesMod, user must have it equipped
		SLOT_SKIN = 1,
		SLOT_WHEELS = 2,
		SLOT_BOOST = 3,
		SLOT_ANTENNA = 4,
		SLOT_HAT = 5,

		SLOT_PAINTFINISH = 7,
		SLOT_PAINTFINISH_SECONDARY = 12,

		SLOT_ENGINE_AUDIO = 13,
		SLOT_SUPERSONIC_TRAIL = 14,
		SLOT_GOALEXPLOSION = 15,
		SLOT_PLAYERANTHEM = 18,
	};

	enum ITEMPAINT {
		PAINT_NONE = 0,
		PAINT_CRIMSON = 1,
		PAINT_LIME = 2,
		PAINT_BLACK = 3,
		PAINT_SKYBLUE = 4,
		PAINT_COBALT = 5,
		PAINT_BURNTSIENNA = 6,
		PAINT_FORESTGREEN = 7,
		PAINT_PURPLE = 8,
		PAINT_PINK = 9,
		PAINT_ORANGE = 10,
		PAINT_GREY = 11,
		PAINT_TITANIUMWHITE = 12,
		PAINT_SAFFRON = 13,
		PAINT_GOLD = 14,
		PAINT_ROSEGOLD = 15,
		PAINT_WHITEGOLD = 16,
		PAINT_ONYX = 17,
		PAINT_PLATINUM = 18
	};

	struct Header
	{
		uint8_t version = 0;
		uint16_t code_size = 0;
		uint8_t crc = 0;
	};

	struct Item
	{
		uint8_t slot_index = 0;
		uint16_t product_id = 0;
		uint8_t paint_index = 0;
	};

	struct RGB
	{
		uint8_t r = 0;
		uint8_t g = 0;
		uint8_t b = 0;

		void randomize() {
			r = std::rand() % 256;
			g = std::rand() % 256;
			b = std::rand() % 256;
		}
	};

	struct OverrideColor
	{
		bool should_override = false;
		RGB primary_colors;
		RGB secondary_colors;
	};

	struct Body
	{
		bool blue_is_orange = true;
		std::map<uint8_t, Item> blue_loadout;
		uint8_t blue_wheel_team_id;
		OverrideColor blueColor;
		std::map<uint8_t, Item> orange_loadout;
		OverrideColor orangeColor;
		uint8_t orange_wheel_team_id;
	};

	struct BMLoadout
	{
		Header header;
		Body body;
	};

	void write_loadout(BitBinaryWriter<unsigned char>& writer, std::map<uint8_t, Item> loadout);
	void write_color(BitBinaryWriter<unsigned char>& writer, RGB color);
	std::string save(BMLoadout loadout);
	BMLoadout load(std::string loadoutString);
	std::map<uint8_t, Item> read_items_from_buffer(BitBinaryReader<unsigned char>& reader);
	RGB read_colors_from_buffer(BitBinaryReader<unsigned char>& reader);
	void print_loadout(BMLoadout loadout);