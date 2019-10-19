#include "functions.h"

void Block::set_block(int p_center_x, int p_center_y, int p_shape, int p_type, bool p_do_rotation, int p_rotation_mod) {
	// -2 none -1 random for p_shape and p_type
	// -2 no movement for center_x and center_y

	if (p_center_x >= -1) { center_x = p_center_x; }
	if (p_center_y >= -1) { center_y = p_center_y; }

	if (p_shape >= -1) {
		if (p_shape == -1) { shape = rand() % 7; }
		else { shape = p_shape; }
		int blocks[7][8] = {
			{ -1, 0, 0, 0, 1, 0, 2, 0 },
			{ -1, -1, -1, 0, 0, 0, 1, 0 },
			{ 1, -1, -1, 0, 0, 0, 1, 0 },
			{ 0, -1, 1, -1, 0, 0, 1, 0 },
			{ 0, -1, 1, -1, -1, 0, 0, 0 },
			{ 0, -1, -1, 0, 0, 0, 1, 0 },
			{ -1, -1, 0, -1, 0, 0, 1, 0 }
		};
		for (int i = 0; i < 8; i++) { parts[i] = blocks[shape][i]; }
	}

	if (p_type >= -1) {
		if (p_type == -1) {
			bool yellow = false;	//1
			bool blue = false;		//2
			bool green = false;		//3
			bool purple = false;	//4
			bool orange = false;	//5

			int yellow_chance = 100;
			int blue_chance = 1000;
			int purple_chance = 200;
			int orange_chance = 250;//250

			if ((rand() % yellow_chance) == (rand() % yellow_chance)) { yellow = true; }
			if ((rand() % blue_chance) == (rand() % blue_chance)) { blue = true; }
			if ((rand() % purple_chance) == (rand() % purple_chance)) { purple = true; }
			if ((rand() % orange_chance) == (rand() % orange_chance)) { orange = true; }

			if (shape != 5) { orange = false; }

			if (yellow && blue) { type = 3; color = 0x00ff0000; }
			else if (yellow) { type = 1; color = 0xdddd0000; }
			else if (blue) { type = 2; color = 0x00dddd00; }
			else if (orange) { type = 5; color = 0xffaa0000; }
			else if (purple) { type = 4; color = 0xdd00dd00; }
			else { type = 0; color = 0xff000000; }
		}
		else {
			type = p_type;
			if (type == 0) { color = 0xff000000; }
			if (type == 1) { color = 0xdddd0000; }
			if (type == 2) { color = 0x00dddd00; }
			if (type == 3) { color = 0x00ff0000; }
			if (type == 4) { color = 0xdd00dd00; }
			if (type == 5) {
				if (shape == 5) { color = 0xffaa0000; }
				else { type = 0; color = 0xff000000; }
			}
		}
	}

	if (p_do_rotation) {
		rotation += p_rotation_mod;
		if (rotation < 0) { rotation += 4; }
		else if (rotation > 3) { rotation -= 4; }
		int blocks[7][8] = {
			{ -1, 0, 0, 0, 1, 0, 2, 0 },	//i - 0
			{ -1, -1, -1, 0, 0, 0, 1, 0 },	//j - 1
			{ 1, -1, -1, 0, 0, 0, 1, 0 },	//l - 2
			{ 0, -1, 1, -1, 0, 0, 1, 0 },	//o - 3
			{ 0, -1, 1, -1, -1, 0, 0, 0 },	//s - 4
			{ 0, -1, -1, 0, 0, 0, 1, 0 },	//t - 5
			{ -1, -1, 0, -1, 0, 0, 1, 0 }	//z - 6
		};
		if ((shape == 0) || (shape == 4) || (shape == 6)) {
			switch (rotation) {
			case 0: case 2:
				for (int i = 0; i < 8; i++) {
					parts[i] = blocks[shape][i];
				}
				break;
			case 1: case 3:
				for (int i = 0; i < 8; i += 2) {
					parts[i] = blocks[shape][i + 1];
					parts[i + 1] = -1 * blocks[shape][i];
				}
				break;
			}
		}
		else if ((shape == 1) || (shape == 2) || (shape == 5)) {
			switch (rotation) {
			case 0:
				for (int i = 0; i < 8; i++) {
					parts[i] = blocks[shape][i];
				}
				break;
			case 1:
				for (int i = 0; i < 8; i += 2) {
					parts[i] = blocks[shape][i + 1];
					parts[i + 1] = -1 * blocks[shape][i];
				}
				break;
			case 2:
				for (int i = 0; i < 8; i++) {
					parts[i] = -1 * blocks[shape][i];
				}
				break;
			case 3:
				for (int i = 0; i < 8; i += 2) {
					parts[i] = -1 * blocks[shape][i + 1];
					parts[i + 1] = blocks[shape][i];
				}
				break;
			}
		}
	}
}