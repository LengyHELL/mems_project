#include "functions.h"

void Menu::set_def(int x_pos, int y_pos, std::string p_title, std::vector<MenuPoint>* p_options, std::vector<ExtraLine> p_extra_lines) {
	x = x_pos;
	y = y_pos;

	title = p_title;

	t_color = 0x00000000;
	h_color = 0x00ff0000;

	options = *p_options;
	extra_lines = p_extra_lines;
	end_loop = false;

	movement = 0;
	value = 0;
	confirm = false;
	back = false;

	up_timer = 0;
	down_timer = 0;
	left_timer = 0;
	right_timer = 0;
	confirm_stall = true;
	back_stall = true;
	step_speed = 200;

	menu_pos = 0;

	std::string empty_spaces = "";
}

void Menu::set_main(Screen scr, Textures tex, Game game) {
	options.clear();
	extra_lines.clear();

	x = tex.font_width;
	y = tex.font_width;

	title = "Main menu";

	t_color = 0x00000000;
	h_color = 0x00ff0000;

	if (game.ongoing) { options.push_back(MenuPoint("Continue", false, true)); }
	options.push_back(MenuPoint("New game", false, true));
	//options.push_back(MenuPoint("Options", false, true));
	options.push_back(MenuPoint("Statistics", false, true));
	//options.push_back(MenuPoint("Highscores", false, true));
	//options.push_back(MenuPoint("Log Out", false, true));
	options.push_back(MenuPoint("Exit", false, true));

	return_on_esc = false;

	end_loop = false;

	movement = 0;
	value = 0;
	confirm = false;
	back = false;

	up_timer = 0;
	down_timer = 0;
	left_timer = 0;
	right_timer = 0;
	confirm_stall = true;
	back_stall = true;
	step_speed = 200;

	menu_pos = 0;

	std::string empty_spaces = "";
}

void Menu::set_stat(Screen scr, Textures tex, int stats[], int stats_size) {
	options.clear();
	extra_lines.clear();

	x = tex.font_width;
	y = tex.font_width;

	title = "Statistics";

	t_color = 0x00000000;
	h_color = 0x00ff0000;

	options.push_back(MenuPoint("Back", false, true));

	extra_lines.push_back(ExtraLine("Best score:", 0xff000000, true, stats[0], 15, false));
	extra_lines.push_back(ExtraLine("Time played:", 0x0000ff00, true, stats[1] / 60, 15, false, 0x00000000, " minutes"));
	extra_lines.push_back(ExtraLine("Games played:", 0x00000000, true, stats[2], 15, false));
	if (stats[3] > 0) { extra_lines.push_back(ExtraLine("Total yellows:", 0xdddd0000, true, stats[3], 15, true, 0x00000000)); }
	if (stats[4] > 0) { extra_lines.push_back(ExtraLine("Total blues:", 0x00dddd00, true, stats[4], 15, true, 0x00000000)); }
	if (stats[5] > 0) { extra_lines.push_back(ExtraLine("Total greens:", 0x00ff0000, true, stats[5], 15, true, 0x00000000)); }
	if (stats[6] > 0) { extra_lines.push_back(ExtraLine("Total purples:", 0xdd00dd00, true, stats[6], 15, true, 0x00000000)); }
	if (stats[7] > 0) { extra_lines.push_back(ExtraLine("Total oranges:", 0xffaa0000, true, stats[7], 15, true, 0x00000000)); }
	int test = 0;
	for (int i = 0; i < stats_size; i++) { test += stats[i]; }
	if (test == 0) { extra_lines.push_back(ExtraLine("We got a fresh man here", 0x00000000, false)); }
	extra_lines.push_back(ExtraLine());

	return_on_esc = true;

	end_loop = false;

	movement = 0;
	value = 0;
	confirm = false;
	back = false;

	up_timer = 0;
	down_timer = 0;
	left_timer = 0;
	right_timer = 0;
	confirm_stall = true;
	back_stall = true;
	step_speed = 200;

	menu_pos = 0;

	std::string empty_spaces = "";
}

void Menu::set_pause(Screen scr, Textures tex) {
	options.clear();
	extra_lines.clear();

	x = tex.font_width;
	y = (scr.width / 2) - (2 * tex.font_height);

	title = "Game paused";

	t_color = 0x00000000;
	h_color = 0x00ff0000;

	options.push_back(MenuPoint("Resume", false, true));
	options.push_back(MenuPoint("Restart", false, true));
	options.push_back(MenuPoint("Exit to Main menu", false, true));

	return_on_esc = true;

	end_loop = false;

	movement = 0;
	value = 0;
	confirm = false;
	back = false;

	up_timer = 0;
	down_timer = 0;
	left_timer = 0;
	right_timer = 0;
	confirm_stall = true;
	back_stall = true;
	step_speed = 200;

	menu_pos = 0;

	std::string empty_spaces = "";
}

void Menu::set_sum(Screen scr, Textures tex, Game game) {
	options.clear();
	extra_lines.clear();

	x = tex.font_width;
	y = tex.font_width;

	title = "Game Over";

	t_color = 0x00000000;
	h_color = 0x00ff0000;

	options.push_back(MenuPoint("Restart", false, true));
	options.push_back(MenuPoint("Return to Main Menu", false, true));

	extra_lines.push_back(ExtraLine("Score:", 0xff000000, true, game.score, 11, false));
	extra_lines.push_back(ExtraLine("Game time:", 0x0000ff00, true, (game.length_timer / 1000) / 60, 11, false, 0x00000000, " minutes"));

	if (game.score >= 6000) { extra_lines.push_back(ExtraLine("Unbeliveable score", 0x00000000)); }
	else if (game.score >= 4000) { extra_lines.push_back(ExtraLine("Excellent score", 0x00000000)); }
	else if (game.score >= 2200) { extra_lines.push_back(ExtraLine("Fantastic score", 0x00000000)); }
	else if (game.score >= 2000) { extra_lines.push_back(ExtraLine("Amazing score", 0x00000000)); }
	else if (game.score >= 1800) { extra_lines.push_back(ExtraLine("Good score", 0x00000000)); }
	else { extra_lines.push_back(ExtraLine("Nice score", 0x00000000)); }

	if (game.yellow_got == 1) { extra_lines.push_back(ExtraLine("Yellow got", 0xdddd0000, false, 0, 0, true, 0x00000000)); }
	if (game.yellow_got >= 2) { extra_lines.push_back(ExtraLine(std::to_string(game.yellow_got) + " yellows got", 0xdddd0000, false, 0, 0, true, 0x00000000)); }

	if (game.blue_got == 1) { extra_lines.push_back(ExtraLine("Blue got", 0x00dddd00, false, 0, 0, true, 0x00000000)); }
	if (game.blue_got >= 2) { extra_lines.push_back(ExtraLine(std::to_string(game.blue_got) + " blues got", 0x00dddd00, false, 0, 0, true, 0x00000000)); }

	if (game.green_got == 1) { extra_lines.push_back(ExtraLine("Green got", 0x00ff0000, false, 0, 0, true, 0x00000000)); }
	if (game.green_got >= 2) { extra_lines.push_back(ExtraLine(std::to_string(game.green_got) + " greens got", 0x00ff0000, false, 0, 0, true, 0x00000000)); }

	if (game.purple_got == 1) { extra_lines.push_back(ExtraLine("Purple got", 0xdd00dd00, false, 0, 0, true, 0x00000000)); }
	if (game.purple_got >= 2) { extra_lines.push_back(ExtraLine(std::to_string(game.purple_got) + " purples got", 0xdd00dd00, false, 0, 0, true, 0x00000000)); }

	if (game.orange_got == 1) { extra_lines.push_back(ExtraLine("Orange got", 0xffaa0000, false, 0, 0, true, 0x00000000)); }
	if (game.orange_got >= 2) { extra_lines.push_back(ExtraLine(std::to_string(game.orange_got) + " oranges got", 0xffaa0000, false, 0, 0, true, 0x00000000)); }

	extra_lines.push_back(ExtraLine());

	return_on_esc = true;

	end_loop = false;

	movement = 0;
	value = 0;
	confirm = false;
	back = false;

	up_timer = 0;
	down_timer = 0;
	left_timer = 0;
	right_timer = 0;
	confirm_stall = true;
	back_stall = true;
	step_speed = 200;

	menu_pos = 0;

	std::string empty_spaces = "";
}

void Menu::update(const Uint8* state, int test_delay) {
	uint32_t t_color = 0x00000000;
	uint32_t h_color = 0x00ff0000;

	up_timer += test_delay;
	down_timer += test_delay;
	left_timer += test_delay;
	right_timer += test_delay;

	if (state[SDL_SCANCODE_UP] && (up_timer >= step_speed)) { up_timer = 0; movement = -1; }
	else if (!state[SDL_SCANCODE_UP]) { up_timer = step_speed; }

	if (state[SDL_SCANCODE_DOWN] && (down_timer >= step_speed)) { down_timer = 0; movement = 1; }
	else if (!state[SDL_SCANCODE_DOWN]) { down_timer = step_speed; }

	if (state[SDL_SCANCODE_LEFT] && (left_timer >= step_speed)) { left_timer = 0; value = -1; }
	else if (!state[SDL_SCANCODE_LEFT]) { left_timer = step_speed; }

	if (state[SDL_SCANCODE_RIGHT] && (right_timer >= step_speed)) { right_timer = 0; value = 1; }
	else if (!state[SDL_SCANCODE_RIGHT]) { right_timer = step_speed; }

	if (state[SDL_SCANCODE_RETURN] && !confirm_stall && options[menu_pos].selectable) { end_loop = true; ret_value = menu_pos; confirm_stall = true; }
	else if (!state[SDL_SCANCODE_RETURN]) { confirm_stall = false; }

	if (state[SDL_SCANCODE_ESCAPE] && !back_stall && return_on_esc) { end_loop = true; ret_value = options.size(); back_stall = true; }
	else if (!state[SDL_SCANCODE_ESCAPE]) { back_stall = false; }

	menu_pos += movement;
	if (menu_pos < 0) { menu_pos = 0; }
	if (menu_pos >= options.size()) { menu_pos = options.size() - 1; }
	movement = 0;

	if (options[menu_pos].has_value) {
		options[menu_pos].value += value * options[menu_pos].value_m;
		if (options[menu_pos].value < options[menu_pos].min_value) { options[menu_pos].value = options[menu_pos].min_value; }
		if (options[menu_pos].value > options[menu_pos].max_value) { options[menu_pos].value = options[menu_pos].max_value; }
		value = 0;

		if (options[menu_pos].is_special) {
			if (options[menu_pos].special_id == 3) {
				if (options[menu_pos].value > options[menu_pos].written) {
					options[menu_pos].value = options[menu_pos].written;
				}
				for (int i = 4; i <= 53; i++) {
					if (i == 39) { i = 53; }
					if (state[i]) {
						if ((options[menu_pos].written < options[menu_pos].max_value) && !key_stall[i]) {
							key_stall[i] = true;
							int modify = 0;
							if (true) {
								if (i == 28) { modify = 1; }
								if (i == 29) { modify = -1; }
							}
							int act_char = 0;
							if (i < 30) {
								if (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT]) {
									act_char = i + modify + 61;
								}
								else {
									act_char = i + modify + 93;
								}
							}
							else if (i < 39) {
								act_char = i + 19;
							}
							else if (i == 53) {
								act_char = i - 5;
							}
							for (int j = options[menu_pos].textvalue.length() - 1; j >= options[menu_pos].value; j--) {
								if (j == options[menu_pos].value) {
									options[menu_pos].textvalue[j] = char(act_char);
								}
								else {
									options[menu_pos].textvalue[j] = options[menu_pos].textvalue[j - 1];
								}
							}
							options[menu_pos].written++;
							options[menu_pos].value++;
						}
					}
					else { key_stall[i] = false; }

					if (state[SDL_SCANCODE_BACKSPACE] && !bs_stall) {
						bs_stall = true;
						if (options[menu_pos].written > options[menu_pos].min_value) {
							options[menu_pos].written--;
							options[menu_pos].value--;
							for (int j = options[menu_pos].value; j < options[menu_pos].textvalue.length(); j++) {
								if (j == options[menu_pos].textvalue.length() - 1) {
									options[menu_pos].textvalue[j] = ' ';
								}
								else {
									options[menu_pos].textvalue[j] = options[menu_pos].textvalue[j + 1];
								}
							}
						}
					}
					else if (!state[SDL_SCANCODE_BACKSPACE]) { bs_stall = false; }
				}
			}
		}
	}
}

void Menu::render(Screen scr, Textures tex) {
	draw_text(scr, tex, x, y, title, t_color, false);
	int lines_out = 0;
	int temp_val1 = x + tex.font_width;
	if (extra_lines.size() > 0) {
		for (; lines_out < extra_lines.size(); lines_out++) {
			empty_spaces = "";
			if (extra_lines[lines_out].has_value) {
				int temp_it = extra_lines[lines_out].space - extra_lines[lines_out].line.length();
				for (int j = 0; j < temp_it; j++) { empty_spaces = empty_spaces + " "; }
			}
			int temp_val2 = y + ((lines_out + 1) * ((tex.font_height) + (2 * (tex.font_height / 12))));
			if (extra_lines[lines_out].has_value) {
				draw_text(scr, tex, temp_val1, temp_val2, extra_lines[lines_out].line + empty_spaces + std::to_string(extra_lines[lines_out].value) + extra_lines[lines_out].special, extra_lines[lines_out].f_color, extra_lines[lines_out].has_bg, extra_lines[lines_out].bg_color);
			}
			else {
				draw_text(scr, tex, temp_val1, temp_val2, extra_lines[lines_out].line, extra_lines[lines_out].f_color, extra_lines[lines_out].has_bg, extra_lines[lines_out].bg_color);
			}
		}
	}
	for (int i = 0; i < options.size(); i++, lines_out++) {
		empty_spaces = "";
		if (options[i].has_value) {
			int temp_it = options[i].space - options[i].name.length();
			for (int j = 0; j < temp_it; j++) { empty_spaces = empty_spaces + " "; }
		}

		int temp_val2 = y + ((lines_out + 1) * ((tex.font_height) + (2 * (tex.font_height / 12))));
		if (options[i].is_special) {
			std::string value_to_text;
			int temp_val3 = 0;
			switch (options[i].special_id) {
			case 0:
				if (i == menu_pos) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + std::to_string(options[i].value) + 'X' + std::to_string(options[i].value), t_color, true, h_color); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + std::to_string(options[i].value) + 'X' + std::to_string(options[i].value), t_color, true, 0xd3d3d300); }
				break;
			case 1:
				if (options[i].value == 0) { value_to_text = "Off   "; }
				if (options[i].value == 1) { value_to_text = "Low   "; }
				if (options[i].value == 2) { value_to_text = "Medium"; }
				if (options[i].value == 3) { value_to_text = "High  "; }
				if (i == menu_pos) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + value_to_text, t_color, true, h_color); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + value_to_text, t_color, true, 0xd3d3d300); }
				break;
			case 2:
				if (options[i].value == 0) { value_to_text = "Off"; }
				if (options[i].value == 1) { value_to_text = "On "; }
				if (i == menu_pos) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + value_to_text, t_color, true, h_color); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + value_to_text, t_color, true, 0xd3d3d300); }
				break;
			case 3:
				if (i == menu_pos) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces, t_color, true, h_color); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces, t_color, true, 0xd3d3d300); }
				temp_val3 = temp_val1 + ((options[i].name.length() + empty_spaces.length()) * ((tex.font_width / 4) + tex.font_width));
				value_to_text = options[i].textvalue;
				if (options[i].hidetext) {
					for (int j = 0; j < value_to_text.length(); j++) {
						if (value_to_text[j] != ' ') {
							value_to_text[j] = ':';
						}
					}
				}
				draw_text(scr, tex, temp_val3, temp_val2, value_to_text + ' ', 0x00ff0000, true, 0x00000000);
				if (i == menu_pos) {
					temp_val3 = temp_val1 + ((options[i].name.length() + empty_spaces.length() + options[i].value) * ((tex.font_width / 4) + tex.font_width));
					for (int j = 0; j < tex.font_height; j++) {
						for (int k = 0; k < tex.font_width / 4; k++)
							draw_pixel(scr, temp_val3 + k, temp_val2 + j, 0xff000000);
					}
				}
				break;
			case 4:
				if (i == menu_pos) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name, t_color, true, h_color); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name, t_color, true, 0xd3d3d300); }
				break;
			}
		}
		else {
			if (i == menu_pos) {
				if (options[i].has_value) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + std::to_string(options[i].value), t_color, true, h_color); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name, t_color, true, h_color); }
			}
			else {
				if (options[i].has_value) { draw_text(scr, tex, temp_val1, temp_val2, options[i].name + empty_spaces + std::to_string(options[i].value), t_color, true, 0xd3d3d300); }
				else { draw_text(scr, tex, temp_val1, temp_val2, options[i].name, t_color, true, 0xd3d3d300); }
			}
		}
	}
}