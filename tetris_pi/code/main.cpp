#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <string>
#include "functions.h"

int main(int argc, char* args[]) {
	int stat_array[8];
	int stat_array_size = 8;

	Screen d_screen;

	Textures d_textures;
	d_textures.def_cube_size = 16;

	d_textures.font_array = new std::string[123];
	std::ifstream load_file;
	std::ofstream save_file;
	std::string arow;
	int aline = 1;

	int quit;

	load_file.open("fonts.dat");
	if (load_file.is_open()) {
		quit = 0;
		while (std::getline(load_file, arow)) {
			if (aline < 123) { d_textures.font_array[aline] = arow; }
			else if (aline == 123) { d_textures.font_width = std::stoi(arow); }
			else if (aline == 124) { d_textures.font_height = std::stoi(arow); }
			else if (aline == 125) { d_textures.def_cube = arow; }
			else if (aline == 126) { d_textures.plain_cube = arow; }
			aline++;
		}
	}
	else {
		quit = 1;
	}
	load_file.close();

	aline = 0;
	d_screen.width = 480;
	d_screen.height = 480;
	d_textures.cube_size = 24;
	int smooth_option = 0;
	int show_fps = 0;
	int auto_login = 0;

	int fix_screen_width = 320;
	int fix_screen_height = 480;

	load_file.open("config.dat");
	if (load_file.is_open()) {
		while (std::getline(load_file, arow)) {
			if (aline == 0) { d_screen.width = std::stoi(arow); }
			if (aline == 1) { d_screen.height = std::stoi(arow); }
			if (aline == 2) { d_textures.cube_size = std::stoi(arow); }
			if (aline == 3) { smooth_option = std::stoi(arow); }
			if (aline == 4) { show_fps = std::stoi(arow); }
			if (aline == 5) { fix_screen_width = std::stoi(arow); }
			if (aline == 6) { fix_screen_height = std::stoi(arow); }
			if (aline == 7) { d_textures.def_cube_type = std::stoi(arow); }
			aline++;
		}
		load_file.close();
	}
	//width
	//height
	//cube size
	//smoothing
	//show fps
	//default cube texture

	SDL_Rect fix_screen;
	fix_screen.x = 0;
	fix_screen.y = 0;
	fix_screen.w = d_screen.width;
	fix_screen.h = d_screen.height;

	d_screen.pixel_buffer = new uint32_t[fix_screen_width * fix_screen_height];
  SDL_Window* window = NULL;
  SDL_Renderer *renderer;
	SDL_Texture *screen;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(fix_screen_width, fix_screen_height, SDL_WINDOW_SHOWN, &window, &renderer);
	screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, fix_screen_width, fix_screen_height);

	int test_delay = 0;
	Uint32 test_tick = 0;
	SDL_Event event;
	const Uint8* state;

	int game_state = 1;
	int sub_state;

	int target_fps = 1000;

	Game d_game;
	Menu d_menu;

	//load stats here
	aline = 0;
	load_file.open("save.dat");
	if (load_file.is_open()) {
		while (std::getline(load_file, arow)) {
			stat_array[aline] = std::stoi(arow);
			aline++;
		}
		load_file.close();
	}
	else {
		for (int i = 0; i < 8; i++) {
			stat_array[i] = 0;
		}
	}

	sub_state = 0;
	clear_pixels(d_screen, 0xd3d3d300);
	d_game.ongoing = false;
	d_menu.set_main(d_screen, d_textures, d_game);

	SDL_ShowCursor(SDL_DISABLE);

	while (quit == 0) {
		test_tick = SDL_GetTicks();
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) { quit = 1; }
		SDL_PumpEvents();
		state = SDL_GetKeyboardState(NULL);

		if (game_state == 0) {
			d_game.update(state, test_delay);
			d_game.render(d_screen, d_textures);

			if (d_game.end) {
				d_game.end = false;

				/*
				d_game.yellow_got += 1;
				d_game.blue_got += 1;
				d_game.green_got += 1;
				d_game.orange_got += 1;
				d_game.purple_got += 1;
				*/

				if (d_game.score > stat_array[0]) { stat_array[0] = d_game.score; }
				stat_array[1] += d_game.length_timer / 1000;
				stat_array[2]++;
				stat_array[3] += d_game.yellow_got;
				stat_array[4] += d_game.blue_got;
				stat_array[5] += d_game.green_got;
				stat_array[6] += d_game.purple_got;
				stat_array[7] += d_game.orange_got;

				game_state = 1;
				sub_state = 4;
				clear_pixels(d_screen, 0xd3d3d300);
				d_menu.set_sum(d_screen, d_textures, d_game);
			}
			else if (d_game.pause) {
				d_game.pause = false;
				game_state = 1;
				sub_state = 3;
				shade_pixels(d_screen);
				int temp_h_value = 20 * d_textures.cube_size;
				int i_start = (temp_h_value / 2) - (d_textures.font_height * 3);
				int i_end = (temp_h_value / 2) + (d_textures.font_height * 3);
				for (int i = i_start; i <= i_end; i++) {
					for (int j = 0; j < d_screen.width; j++) {
						if ((i < i_start + (d_textures.font_height / 16)) || (i > i_end - (d_textures.font_height / 16))) {
							draw_pixel(d_screen, j, i, 0x00000000);
						}
						else {
							draw_pixel(d_screen, j, i, 0xd3d3d300);
						}
					}
				}
				d_menu.set_pause(d_screen, d_textures);
			}
		}
		else if (game_state == 1) {
			d_menu.update(state, test_delay);

			if (sub_state == 0) {
				if (d_menu.end_loop) {
					if (d_game.ongoing) { d_menu.ret_value--; }
					int test = 0;
					switch (d_menu.ret_value) {
					case -1:
						game_state = 0;
						break;
					case 0:
						game_state = 0;
						d_game.set_normal(smooth_option, show_fps);
						break;
					case 1:
						sub_state = 2;
						clear_pixels(d_screen, 0xd3d3d300);
						d_menu.set_stat(d_screen, d_textures, stat_array, stat_array_size);
						break;
					case 2:
						quit = 1;
						break;
					}
				}
			}
			else if (sub_state == 2) {
				if (d_menu.end_loop) {
					switch (d_menu.ret_value) {
					case 0: case 1:
						sub_state = 0;
						clear_pixels(d_screen, 0xd3d3d300);
						d_menu.set_main(d_screen, d_textures, d_game);
						break;
					}
				}
			}
			else if (sub_state == 3) {
				if (d_menu.end_loop) {
					switch (d_menu.ret_value) {
					case 0: case 3:
						game_state = 0;
						break;
					case 1:
						game_state = 0;
						d_game.set_normal(smooth_option, show_fps);
						break;
					case 2:
						sub_state = 0;
						clear_pixels(d_screen, 0xd3d3d300);
						d_menu.set_main(d_screen, d_textures, d_game);
						break;
					}
				}
			}
			else if (sub_state == 4) {
				if (d_menu.end_loop) {
					switch (d_menu.ret_value) {
					case 0:
						game_state = 0;
						d_game.set_normal(smooth_option, show_fps);
						break;
					case 1: case 2:
						sub_state = 0;
						clear_pixels(d_screen, 0xd3d3d300);
						d_menu.set_main(d_screen, d_textures, d_game);
						break;
					}
				}
			}

			d_menu.render(d_screen, d_textures);
		}

		SDL_UpdateTexture(screen, &fix_screen, d_screen.pixel_buffer, d_screen.width * sizeof(uint32_t));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, screen, NULL, NULL);
		SDL_RenderPresent(renderer);

		test_delay = SDL_GetTicks() - test_tick;
		if (test_delay < (1000 / target_fps)) { SDL_Delay((1000 / target_fps) - test_delay); }
		test_delay = SDL_GetTicks() - test_tick;
	}

	save_file.open("save.dat");
	if (save_file.is_open()) {
		for (int i = 0; i < stat_array_size; ++i) {
			save_file << stat_array[i];
			if (i != (stat_array_size - 1)) {
				save_file << '\n';
			}
		}
		save_file.close();
	}

	delete[] d_screen.pixel_buffer;
	delete[] d_textures.font_array;
	SDL_DestroyTexture(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}