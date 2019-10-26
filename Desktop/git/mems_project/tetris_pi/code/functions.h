#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <time.h>

struct Screen {
	int width;
	int height;
	uint32_t* pixel_buffer;
};

struct Textures {
	std::string* font_array;
	int font_width;
	int font_height;

	std::string def_cube;
	std::string plain_cube;
	int cube_size;
	int def_cube_size;
	int def_cube_type;
};

struct MenuPoint {
	MenuPoint(std::string p_name = "", bool p_has_value = false, bool p_selectable = false, int p_space = 0, bool p_is_special = false, int p_min_value = 0, int p_max_value = 0, int p_value = 0, int p_value_m = 0, int p_special_id = 0) {
		name = p_name;
		has_value = p_has_value;
		min_value = p_min_value;
		max_value = p_max_value;
		value = p_value;
		value_m = p_value_m;
		selectable = p_selectable;
		is_special = p_is_special;
		special_id = p_special_id;
		space = p_space;
	}
	std::string name;
	bool has_value;
	int min_value;
	int max_value;
	int value;
	int value_m;
	bool selectable;
	bool is_special;
	int special_id;
	int space;
	std::string textvalue;
	int written;
	bool hidetext;
};

struct ExtraLine {
	ExtraLine(std::string p_line = "", uint32_t p_f_color = 0x00000000, bool p_has_value = false, int p_value = 0, int p_space = 0, bool p_has_bg = false, uint32_t p_bg_color = 0x00000000, std::string p_special = "") {
		line = p_line;
		f_color = p_f_color;
		has_bg = p_has_bg;
		bg_color = p_bg_color;
		space = p_space;
		has_value = p_has_value;
		value = p_value;
		special = p_special;
	}
	bool has_value;
	int value;
	std::string line;
	uint32_t f_color;
	bool has_bg;
	uint32_t bg_color;
	int space;
	std::string special;
};

struct Block {
	//variables
	int center_x;
	int center_y;
	int rotation = 0;
	int shape;
	int type;

	uint32_t color;
	int parts[8];

	//functions

	void set_block(int p_center_x = -2, int p_center_y = -2, int p_shape = -2, int p_type = -2, bool p_do_rotation = false, int p_rotation_mod = 0);
};

class Game {
private:
	int horizontal_mov;
	int vertical_mov;

	bool passivise;

	int game_w;
	int game_h;
	std::vector<std::vector<int>> game_buffer;
	/*
	void - 0
	passive - 2
	*/

	Block current_block;
	Block next_block;

	bool rotate_stall;

	int vertical_timer;
	int left_timer;
	int right_timer;
	int left_timer_in;
	int right_timer_in;

	int horizontal_speed;
	int vertical_speed;
	int down_speed;
	int in_delay;
	int act_vertical_speed;

	int stage;
	int prev_stage;
	int stage_size;

	bool enable_esc;

	int act_fps;
	int act_fps_count;
	int act_fps_timer;

	int sm_v_counter = 0;
	int sm_h_counter = 0;
	int sm_v_mov = 0;
	int sm_h_mov = 0;

public:
	int score;
	int length_timer;
	int yellow_got;
	int blue_got;
	int green_got;
	int purple_got;
	int orange_got;

	bool pause;
	bool end;
	bool ongoing = false;

	int base_smoothing;
	int h_smoothing;
	int v_smoothing;
	int show_fps;

	void set_normal(int smooth_option, bool s_fps);
	void update(const Uint8* state, int test_delay);
	void render(Screen scr, Textures tex);
};

class Menu {
private:
	int x;
	int y;
	std::string title;
	uint32_t t_color;
	uint32_t h_color;

	int movement;
	int value;
	bool confirm;
	bool back;

	int up_timer;
	int down_timer;
	int left_timer;
	int right_timer;
	bool confirm_stall;
	bool back_stall;
	bool key_stall[54];
	bool bs_stall;
	int step_speed;

	int test_delay;
	Uint32 test_tick;

	int menu_pos;

	std::string empty_spaces;

	bool return_on_esc;

public:
	std::vector<MenuPoint> options;
	std::vector<ExtraLine> extra_lines;
	bool end_loop;
	int ret_value;

	void set_def(int x_pos, int y_pos, std::string p_title, std::vector<MenuPoint>* p_options, std::vector<ExtraLine> p_extra_lines);
	void set_main(Screen scr, Textures tex, Game game);
	void set_opt(Screen scr, Textures tex, int smooth, bool fps, bool auto_login);
	void set_stat(Screen scr, Textures tex, int stats[], int stats_size);
	void set_pause(Screen scr, Textures tex);
	void set_sum(Screen scr, Textures tex, Game game);
	void set_welc(Screen scr, Textures tex);
	void set_login(Screen scr, Textures tex);
	void set_register(Screen scr, Textures tex);
	void set_cantsave(Screen scr, Textures tex);
	void set_highscore(Screen scr, Textures tex);

	void update(const Uint8* state, int test_delay);
	void render(Screen scr, Textures tex);
};

void clear_pixels(Screen scr, uint32_t colour);
void shade_pixels(Screen scr);
int draw_pixel(Screen scr, int x, int y, uint32_t colour);
void draw_cube(Screen scr, Textures tex, int type, int x_pos, int y_pos, uint32_t color);
void draw_cube_s(Screen scr, Textures tex, int type, int x, int y, uint32_t color);
void draw_text(Screen scr, Textures tex, int x, int y, std::string text, uint32_t f_color, bool is_bg, uint32_t bg_color = 0x00000000);
std::string clear_spaces(std::string str);