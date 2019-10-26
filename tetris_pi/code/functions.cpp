#include "functions.h"

void clear_pixels(Screen scr, uint32_t colour) {
	int buffer_size = scr.width * scr.height;

	for (int i = 0; i < buffer_size; i++) {
		scr.pixel_buffer[i] = colour;
	}
}

void shade_pixels(Screen scr) {
	int buffer_size = scr.width * scr.height;

	for (int i = 0; i < buffer_size; i++) {
		int temp_c[3];
		uint32_t temp_color = scr.pixel_buffer[i];
		temp_c[0] = temp_color / 0x01000000;
		temp_color -= 0x01000000 * Uint32(temp_c[0]);
		temp_c[1] = temp_color / 0x00010000;
		temp_color -= 0x00010000 * Uint32(temp_c[1]);
		temp_c[2] = temp_color / 0x00000100;

		for (int k = 0; k < 3; k++) {
			temp_c[k] -= 50;
			if (temp_c[k] < 0) { temp_c[k] = 0; }
		}

		scr.pixel_buffer[i] = (0x01000000 * Uint32(temp_c[0])) + (0x00010000 * Uint32(temp_c[1])) + (0x00000100 * Uint32(temp_c[2]));
	}
}

int draw_pixel(Screen scr, int x, int y, uint32_t colour) {
	if ((x < 0) || (y < 0) || (x >= scr.width) || (y >= scr.height)) {
		return 1;
	}

	scr.pixel_buffer[(y * scr.width) + x] = colour;
	return 0;
}

void draw_cube(Screen scr, Textures tex, int type, int x_pos, int y_pos, uint32_t color) {
	int x = x_pos * tex.cube_size;
	int y = y_pos * tex.cube_size;
	double cube_scale = double(tex.def_cube_size) / double(tex.cube_size);

	for (int i = 0; i < tex.cube_size; i++) {
		for (int j = 0; j < tex.cube_size; j++) {
			if (type == 0) {
				if (tex.def_cube[int(i * cube_scale) * tex.def_cube_size + int(j * cube_scale)] == '1') {
					int temp_c[3];
					uint32_t temp_color = color;
					temp_c[0] = temp_color / 0x01000000;
					temp_color -= 0x01000000 * Uint32(temp_c[0]);
					temp_c[1] = temp_color / 0x00010000;
					temp_color -= 0x00010000 * Uint32(temp_c[1]);
					temp_c[2] = temp_color / 0x00000100;

					for (int k = 0; k < 3; k++) {
						temp_c[k] -= 50;
						if (temp_c[k] < 0) { temp_c[k] = 0; }
					}

					temp_color = (0x01000000 * Uint32(temp_c[0])) + (0x00010000 * Uint32(temp_c[1])) + (0x00000100 * Uint32(temp_c[2]));
					draw_pixel(scr, x + j, y + i, temp_color);
				}
				else {
					draw_pixel(scr, x + j, y + i, color);
				}
			}
			else if (type == 1) {
				draw_pixel(scr, x + j, y + i, color);
			}
		}
	}
}

void draw_cube_s(Screen scr, Textures tex, int type, int x, int y, uint32_t color) {
	double cube_scale = double(tex.def_cube_size) / double(tex.cube_size);

	for (int i = 0; i < tex.cube_size; i++) {
		for (int j = 0; j < tex.cube_size; j++) {
			if (type == 0) {
				if (tex.def_cube[int(i * cube_scale) * tex.def_cube_size + int(j * cube_scale)] == '1') {
					int temp_c[3];
					uint32_t temp_color = color;
					temp_c[0] = temp_color / 0x01000000;
					temp_color -= 0x01000000 * Uint32(temp_c[0]);
					temp_c[1] = temp_color / 0x00010000;
					temp_color -= 0x00010000 * Uint32(temp_c[1]);
					temp_c[2] = temp_color / 0x00000100;

					for (int k = 0; k < 3; k++) {
						temp_c[k] -= 50;
						if (temp_c[k] < 0) { temp_c[k] = 0; }
					}

					temp_color = (0x01000000 * Uint32(temp_c[0])) + (0x00010000 * Uint32(temp_c[1])) + (0x00000100 * Uint32(temp_c[2]));
					draw_pixel(scr, x + j, y + i, temp_color);
				}
				else {
					draw_pixel(scr, x + j, y + i, color);
				}
			}
			else if (type == 1) {
				draw_pixel(scr, x + j, y + i, color);
			}
		}
	}
}

void draw_text(Screen scr, Textures tex, int x, int y, std::string text, uint32_t f_color, bool is_bg, uint32_t bg_color) {
	if (is_bg) {
		for (int i = y - 1; i < y + tex.font_height + 1; i++) {
			for (int j = x - 1; j < x + (text.length() * tex.font_width) + ((text.length() - 1) * (tex.font_width / 4)) + 1; j++) {
				draw_pixel(scr, j, i, bg_color);
			}
		}
	}
	for (int i = 0; i < text.length(); i++) {
		int temp = int(text[i]);
		int t_x = x + (i * ((tex.font_width / 4) + tex.font_width));
		int t_y = y;
		for (int i = 0; i < tex.font_width; i++) {
			for (int j = 0; j < tex.font_height; j++) {
				if (tex.font_array[temp] != "") {
					if (tex.font_array[temp][(j * tex.font_width) + i] == '1') { draw_pixel(scr, t_x + i, t_y + j, f_color); }
				}
			}
		}
	}
}

std::string clear_spaces(std::string str) {
	std::string ret_str = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') { ret_str += str[i]; }
	}
	return ret_str;
}