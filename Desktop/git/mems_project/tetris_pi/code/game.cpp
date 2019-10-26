#include "functions.h"

void Game::set_normal(int smooth_option, bool s_fps) {
	srand(time(NULL));

	pause = false;
	end = false;
	ongoing = true;

	show_fps = s_fps;

	if (smooth_option == 0) { base_smoothing = 16; }
	if (smooth_option == 1) { base_smoothing = 4; }
	if (smooth_option == 2) { base_smoothing = 2; }
	if (smooth_option == 3) { base_smoothing = 1; }

	h_smoothing = base_smoothing;
	v_smoothing = base_smoothing;

	horizontal_mov = 0;
	vertical_mov = 0;

	passivise = false;

	game_w = 10;
	game_h = 20;
	game_h += 5;
	game_buffer.clear();
	for (int i = 0; i < game_w; i++) {
		std::vector<int> tempvec(game_h, 0);
		game_buffer.push_back(tempvec);
	}

	yellow_got = 0;
	blue_got = 0;
	green_got = 0;
	purple_got = 0;
	orange_got = 0;

	current_block.set_block(4, 3, -1, -1, true, rand() % 4);
	next_block.set_block(4, 3, -1, -1, true, rand() % 4);

	if (current_block.type == 1) { yellow_got++; }
	if (current_block.type == 2) { blue_got++; }
	if (current_block.type == 3) { green_got++; }
	if (current_block.type == 4) { purple_got++; }
	if (current_block.type == 5) { orange_got++; }

	rotate_stall = false;

	vertical_timer = 0;
	left_timer = 0;
	right_timer = 0;
	left_timer_in = 0;
	right_timer_in = 0;

	horizontal_speed = 200;
	vertical_speed = 500;
	down_speed = 100;
	in_delay = 150;

	score = 0;
	stage = 1;
	prev_stage;
	stage_size = 100;

	enable_esc = false;

	length_timer = 0;

	act_fps = 0;
	act_fps_count = 0;
	act_fps_timer = 0;

	sm_v_counter = 0;
	sm_h_counter = 0;
	sm_v_mov = 0;
	sm_h_mov = 0;

	act_fps_count = 0;
}

void Game::update(const Uint8* state, int test_delay) {
	vertical_timer += test_delay;
	left_timer += test_delay;
	right_timer += test_delay;
	length_timer += test_delay;

	act_fps_timer += test_delay;
	if (act_fps_timer >= 1000) { act_fps = act_fps_count; act_fps_count = 0; act_fps_timer = 0; }

	if (state[SDL_SCANCODE_RETURN] && enable_esc) {
		bool temp_stall = true;
		enable_esc = false;
		pause = true;
	}
	if (!state[SDL_SCANCODE_RETURN]) { enable_esc = true; }

	if (state[SDL_SCANCODE_UP] && !rotate_stall) {
		rotate_stall = true;

		Block temp_block = current_block;
		bool do_change = true;

		if (temp_block.type == 4) { temp_block.set_block(-2, -2, -1, -2, true, rand() % 4); }
		else { temp_block.set_block(-2, -2, -2, -2, true, 1); }
		// turns
		// 1	- anti clockwise
		// -1	- clockwise

		for (int i = 0; (i < 8) && do_change; i += 2) {
			int temp_x = temp_block.center_x + temp_block.parts[i];
			int temp_y = temp_block.center_y + temp_block.parts[i + 1];
			if ((temp_x >= 0) && (temp_x < game_w) && (temp_y >= 0) && (temp_y < game_h)) {
				if (game_buffer[temp_x][temp_y] == 2) { do_change = false; }
			}
			else { do_change = false; }
		}

		if (do_change) { current_block = temp_block; }
	}
	else if (!state[SDL_SCANCODE_UP]) { rotate_stall = false; }

	if (state[SDL_SCANCODE_DOWN]) {
		act_vertical_speed = down_speed;
	}
	if (!state[SDL_SCANCODE_DOWN]) {
		act_vertical_speed = vertical_speed;
	}

	if (!state[SDL_SCANCODE_RIGHT] || !state[SDL_SCANCODE_LEFT]) {
		if (state[SDL_SCANCODE_LEFT]) {
			if (((left_timer_in == 0) || (left_timer_in >= in_delay)) && (left_timer >= horizontal_speed)) {
				horizontal_mov = -1;
				if (left_timer >= horizontal_speed) { left_timer = 0; }
			}
			left_timer_in += test_delay;
		}
		else if (!state[SDL_SCANCODE_LEFT]) { left_timer = horizontal_speed; left_timer_in = 0; }

		if (state[SDL_SCANCODE_RIGHT]) {
			if (((right_timer_in == 0) || (right_timer_in >= in_delay)) && (right_timer >= horizontal_speed)) {
				horizontal_mov = 1;
				if (right_timer >= horizontal_speed) { right_timer = 0; }
			}
			right_timer_in += test_delay;
		}
		else if (!state[SDL_SCANCODE_RIGHT]) { right_timer = horizontal_speed; right_timer_in = 0; }
	}

	if (vertical_timer >= act_vertical_speed) {
		vertical_timer = 0;
		vertical_mov = 1;
	}

	if (horizontal_mov != 0) {
		Block temp_block = current_block;
		temp_block.set_block(temp_block.center_x + horizontal_mov, -2);
		bool do_change = true;

		for (int i = 0; (i < 8) && do_change; i += 2) {
			int temp_x = temp_block.center_x + temp_block.parts[i];
			int temp_y = temp_block.center_y + temp_block.parts[i + 1];
			if ((temp_x >= 0) && (temp_x < game_w)) {
				if (game_buffer[temp_x][temp_y] == 2) { do_change = false; }
			}
			else { do_change = false; }
		}

		if (do_change) {
			current_block = temp_block;
			if (sm_h_counter != 0) {
				h_smoothing++;
				if (h_smoothing > 16) { h_smoothing = 16; }
			}
			else {
				h_smoothing--;
				if (h_smoothing < base_smoothing) { h_smoothing = base_smoothing; }
			}
			sm_h_counter = 16;
			sm_h_mov = horizontal_mov;
		}
		horizontal_mov = 0;
	}

	if (vertical_mov != 0) {
		Block temp_block = current_block;
		temp_block.set_block(-2, temp_block.center_y + vertical_mov);
		bool do_change = true;

		for (int i = 0; (i < 8) && do_change; i += 2) {
			int temp_x = temp_block.center_x + temp_block.parts[i];
			int temp_y = temp_block.center_y + temp_block.parts[i + 1];
			if ((temp_y >= 0) && (temp_y < game_h)) {
				if (game_buffer[temp_x][temp_y] == 2) { do_change = false; }
			}
			else { do_change = false; }
		}

		if (do_change) {
			current_block = temp_block;
			if (sm_v_counter != 0) {
				v_smoothing++;
				if (v_smoothing > 16) { v_smoothing = 16; }
			}
			else {
				v_smoothing--;
				if (v_smoothing < base_smoothing) { v_smoothing = base_smoothing; }
			}
			sm_v_counter = 16;
			sm_v_mov = vertical_mov;
			score += 1;
		}
		else {
			passivise = true;
		}
		vertical_mov = 0;
	}

	if (passivise) {
		passivise = false;

		if (current_block.type == 1) { score += 50; }
		if (current_block.type == 2) { score += 100; }
		if (current_block.type == 3) { score += 200; }
		if (current_block.type == 4) { score += 50; }
		if (current_block.type == 5) {
			score += 50;
			int extra_score = 5;

			bool o_up = false;
			bool o_down = false;
			bool o_left = false;
			bool o_right = false;

			if ((current_block.parts[0] == 0) && (current_block.parts[1] == -1)) { o_up = true; o_left = true; o_right = true; }
			if ((current_block.parts[0] == -1) && (current_block.parts[1] == 0)) { o_up = true; o_down = true; o_left = true; }
			if ((current_block.parts[0] == 0) && (current_block.parts[1] == 1)) { o_down = true; o_left = true; o_right = true; }
			if ((current_block.parts[0] == 1) && (current_block.parts[1] == 0)) { o_up = true; o_down = true; o_right = true; }
			if (o_left && o_right) {
				if (o_up) {
					for (int i = current_block.center_y; i >= 0; i--) {
						if (game_buffer[current_block.center_x][i] == 2) {
							score += extra_score;
						}
						game_buffer[current_block.center_x][i] = 0;
					}
				}
				else if (o_down) {
					for (int i = current_block.center_y; i < game_h; i++) {
						if (game_buffer[current_block.center_x][i] == 2) {
							score += extra_score;
						}
						game_buffer[current_block.center_x][i] = 0;
					}
				}
				for (int i = current_block.center_y; i >= 0; i--) {
					if (i > 0) {
						for (int j = 0; j < game_w; j++) {
							if ((i == current_block.center_y) && (game_buffer[j][i] == 2)) {
								score += extra_score;
							}
							game_buffer[j][i] = game_buffer[j][i - 1];
						}
					}
					else {
						for (int j = 0; j < game_w; j++) {
							game_buffer[j][i] = 0;
						}
					}
				}
			}
			else if (o_up && o_down) {
				if (o_left) {
					for (int i = current_block.center_x; i >= 0; i--) {
						if (game_buffer[i][current_block.center_y] == 2) {
							score += extra_score;
						}
						game_buffer[i][current_block.center_y] = 0;
					}
				}
				else if (o_right) {
					for (int i = current_block.center_x; i < game_w; i++) {
						if (game_buffer[i][current_block.center_y] == 2) {
							score += extra_score;
						}
						game_buffer[i][current_block.center_y] = 0;
					}
				}
				for (int i = 0; i < game_h; i++) {
					if (game_buffer[current_block.center_x][i] == 2) {
						score += extra_score;
					}
					game_buffer[current_block.center_x][i] = 0;
				}
			}
		}

		if (current_block.type != 5) {
			for (int i = 0; i < 8; i += 2) {
				game_buffer[current_block.center_x + current_block.parts[i]][current_block.center_y + current_block.parts[i + 1]] = 2;
			}
		}

		bool rerun = true;
		while (rerun) {
			rerun = false;
			int i = 0;
			while (!rerun && (i < game_h)) {
				int j = 0;
				while (!rerun && (j < game_w)) {
					if (game_buffer[j][i] != 2) { j = game_w; }
					else {
						if (j == (game_w - 1)) {
							for (int k = i; k >= 0; k--) {
								if (k > 0) {
									for (int l = 0; l < game_w; l++) {
										game_buffer[l][k] = game_buffer[l][k - 1];
									}
								}
								else {
									for (int l = 0; l < game_w; l++) {
										game_buffer[l][k] = 0;
									}
								}
							}
							rerun = true;
							score += 10;
						}
					}
					j++;
				}
				i++;
			}
		}
		for (int i = 0; i < game_w; i++) {
			if (game_buffer[i][4] == 2) {
				end = true;
				ongoing = false;
			}
		}

		current_block = next_block;
		next_block.set_block(4, 3, -1, -1, true, rand() % 4);

		if (current_block.type == 1) { yellow_got++; }
		if (current_block.type == 2) { blue_got++; }
		if (current_block.type == 3) { green_got++; }
		if (current_block.type == 4) { purple_got++; }
		if (current_block.type == 5) { orange_got++; }
	}

	prev_stage = stage;
	stage = score / stage_size;

	if (prev_stage != stage) {
		if (down_speed > 10) { down_speed -= 5; }
		if (vertical_speed > 50) { vertical_speed -= 25; }
		if (horizontal_speed > 20) { horizontal_speed -= 10; }
	}
}

void Game::render(Screen scr, Textures tex) {
	act_fps_count++;

	clear_pixels(scr, 0xD3D3D300);

	//current_block start

	for (int i = 0; i < 8; i += 2) {
		draw_cube_s(scr, tex, tex.def_cube_type, ((current_block.center_x + current_block.parts[i]) * tex.cube_size) - (sm_h_counter * sm_h_mov), ((current_block.center_y + current_block.parts[i + 1] - 5) * tex.cube_size) - (sm_v_counter * sm_v_mov), current_block.color);
	}

	sm_v_counter -= v_smoothing;
	sm_h_counter -= h_smoothing;
	if (sm_v_counter < 0) { sm_v_counter = 0; }
	if (sm_h_counter < 0) { sm_h_counter = 0; }

	//current_block end

	for (int i = 0; i < game_w; i++) {
		for (int j = 0; j < game_h - 5; j++) {
			if (game_buffer[i][j + 5] == 2) { draw_cube(scr, tex, 1, i, j, 0x00000000); }
		}
	}
	for (int i = scr.width / 2; i < scr.width; i++) {
		for (int j = 0; j < scr.height; j++) {
			if (i < (scr.width / 2) + (tex.cube_size / 12)) { draw_pixel(scr, i, j, 0x00000000); }
			else { draw_pixel(scr, i, j, 0xC0C0C000); }
		}
	}
	for (int i = 12; i < 18; i++) {
		for (int j = 3; j < 7; j++) {
			draw_cube(scr, tex, 1, i, j, 0x00000000);
		}
	}
	for (int i = 0; i < scr.width; ++i) {
		for (int j = scr.width; j < scr.height; ++j) {
			if ((j < scr.width + (tex.cube_size / 12)) && (i < (scr.width / 2) + (tex.cube_size / 12))) { draw_pixel(scr, i, j, 0x00000000); }
			else { draw_pixel(scr, i, j, 0xC0C0C000); }
		}
	}

	Block temp_out_block = next_block;
	temp_out_block.set_block(-2, -2, -2, -2, true, -1 * temp_out_block.rotation);
	for (int i = 0; i < 8; i += 2) {
		draw_cube(scr, tex, tex.def_cube_type, temp_out_block.parts[i] + 14, temp_out_block.parts[i + 1] + 5, 0x80808000);
	}
	draw_text(scr, tex, (scr.width / 2) + (tex.cube_size * 2), tex.cube_size * 1.5, "Next:", 0x00000000, false);
	draw_text(scr, tex, (scr.width / 2) + (tex.cube_size * 0.5), tex.cube_size * 8, "Score: " + std::to_string(score), 0x00000000, false);
	draw_text(scr, tex, (scr.width / 2) + (tex.cube_size * 0.5), tex.cube_size * 9.5, "Stage: " + std::to_string(stage), 0x00000000, false);
	if (stage >= 15) {
		draw_text(scr, tex, (scr.width / 2) + (tex.cube_size * 0.5), tex.cube_size * 11, "Oh BOY!", 0x00000000, false);
	}
	if (show_fps == 1) {
		draw_text(scr, tex, (scr.width / 2) + (tex.cube_size * 0.5), tex.cube_size * 12.5, "FPS: " + std::to_string(act_fps), 0x00000000, false);
	}
}