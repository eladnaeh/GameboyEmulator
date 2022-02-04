#include <stdio.h>

#include "interrupt.h"
#include "memory.h"
#include "keys.h"
#include "cpu.h"
#include "gpu.h"

/*DEFINES*/
unsigned long long cycles_per_frame = (CLOCK_SPEED / FRAME_RATE);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int modes);

/*FUNCTIONS*/

/*Registers*/
unsigned char get_lcd_status_register() {
	unsigned char lcd_status;
	readByte(LCD_STATUS_ADDRESS, &lcd_status);
	return lcd_status;
}

unsigned char get_lcd_control_register() {
	unsigned char lcd_control;
	readByte(LCD_CONTROL_MEMORY_ADDRESS, &lcd_control);
	return lcd_control;
}

unsigned char get_ly_register() {
	unsigned char ly;
	readByte(LCD_Y_COORDINATE_ADDRESS, &ly);
	return ly;
}

unsigned char get_scroll_y_register() {
	unsigned char scroll_y;
	readByte(SCROLL_Y_REGISTER_ADDRESS, &scroll_y);
	return scroll_y;
}

unsigned char get_scroll_x_register() {
	unsigned char scroll_x;
	readByte(SCROLL_X_REGISTER_ADDRESS, &scroll_x);
	return scroll_x;
}

unsigned char get_window_y_register() {
	unsigned char window_y;
	readByte(WINDOW_Y_REGISTER_ADDRESS, &window_y);
	return window_y;
}

unsigned char get_window_x_register() {
	unsigned char window_x;
	readByte(WINDOW_X_REGISTER_ADDRESS, &window_x);
	return window_x;
}

void set_ly_register(unsigned char value) {
	writeByte(LCD_Y_COORDINATE_ADDRESS, &value);
}

/*GPU*/
void initialize_gpu() {
	gpu.frames = 0;
	gpu.cycles_for_scanline = 0;
}

void initialize_glfw() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int initialize_glad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed To Initialize GLAD\n");
		return -1;
	}

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int modes) {
	/*Handle keyboard clicks*/
	/*Check Action Types*/
	if (action != GLFW_PRESS && action != GLFW_RELEASE) {
		return;
	}

	if (action == GLFW_RELEASE) {
		handle_release();
		return;
	}

	/*Making an interrupt request*/
	set_interrupt_flag(JOYPAD);

	/*Down*/
	if (action == GLFW_KEY_DOWN) {
		set_direction_buttons();
		set_key_pressed(DOWN_START);
		return;
	}

	/*Up*/
	if (action == GLFW_KEY_UP) {
		set_direction_buttons();
		set_key_pressed(UP_SELECT);
		return;
	}

	/*Left*/
	if (action == GLFW_KEY_LEFT) {
		set_direction_buttons();
		set_key_pressed(LEFT_B);
		return;
	}

	/*Right*/
	if (action == GLFW_KEY_RIGHT) {
		set_direction_buttons();
		set_key_pressed(RIGHT_A);
		return;
	}

	/*Start*/
	if (action == GLFW_KEY_ENTER) {
		set_action_buttons();
		set_key_pressed(DOWN_START);
		return;
	}

	/*Select*/
	if (action == GLFW_KEY_SPACE) {
		set_action_buttons();
		set_key_pressed(UP_SELECT);
		return;
	}

	/*B*/
	if (action == GLFW_KEY_B) {
		set_action_buttons();
		set_key_pressed(LEFT_B);
		return;
	}

	/*A*/
	if (action == GLFW_KEY_A) {
		set_action_buttons();
		set_key_pressed(RIGHT_A);
		return;
	}
}

void clear_background(GLFWwindow* window) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}

/*Main functionality*/
GLFWwindow* create_window(int width, int height, char* name) {
	GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (window == NULL) {
		printf("Failed To Create GLFW Window\n");
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	
	/*Add a resize callback*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*Add a keyboard handler callback*/
	glfwSetKeyCallback(window, keyboard_callback);

	return window;
}

unsigned int create_vertex_shader() {
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	/*Check if shader compiled successfully*/
	int success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		printf("Error - Shader - Vertex - Compilation Error - %s\n", infoLog);
	}

	return vertex_shader;
}

unsigned int create_fragment_shader() {
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	/*Check if shader compiled successfully*/
	int success;
	char infoLog[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		printf("Error - Shader - Fragment - Compilation Error - %s\n", infoLog);
	}

	return fragment_shader;
}

unsigned int link_shaders(unsigned int vertex_shader, unsigned int fragment_shader) {
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	/*Checking for linking errors*/
	int success;
	char infoLog[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		printf("Error - Shader - Program - Linking Error - %s\n", infoLog);
	}

	/*Deleting the shaders after linking*/
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}

void initialize_buffers() {
	/*Initializing the position vbo*/
	glGenBuffers(1, &position_vbo);

	/*Initializing the color vbo*/
	glGenBuffers(1, &color_vbo);

	/*Initializing the vao*/
	glGenVertexArrays(1, &vao);

	/*Generate the position vertices*/
	/*Every pixel is defined by 2 triangles - meaning we need 6 points - and every point is defined by x and y (z is unimportant) - meaning 6 * 2 = 12*/
	unsigned char x = 0;
	unsigned char y = 0;
	unsigned char normalize_x = 2 / WINDOW_WIDTH;
	unsigned char normalize_y = 2 / WINDOW_HEIGHT;
	
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT * 12; i += 12) {
		position_vertices[i] = OPENGL_NDC_X_START + (x * normalize_x);
		position_vertices[i + 1] = OPENGL_NDC_Y_START - (y * normalize_y);
		position_vertices[i + 2] = OPENGL_NDC_X_START + (x * normalize_x) + normalize_x;
		position_vertices[i + 3] = OPENGL_NDC_Y_START - (y * normalize_y);
		position_vertices[i + 4] = OPENGL_NDC_X_START + (x * normalize_x);
		position_vertices[i + 5] = OPENGL_NDC_Y_START - (y * normalize_y) - normalize_y;
		position_vertices[i + 6] = OPENGL_NDC_X_START + (x * normalize_x) + normalize_x;
		position_vertices[i + 7] = OPENGL_NDC_Y_START - (y * normalize_y);
		position_vertices[i + 8] = OPENGL_NDC_X_START + (x * normalize_x);
		position_vertices[i + 9] = OPENGL_NDC_Y_START - (y * normalize_y) - normalize_y;
		position_vertices[i + 10] = OPENGL_NDC_X_START + (x * normalize_x) + normalize_x;
		position_vertices[i + 11] = OPENGL_NDC_Y_START - (y * normalize_y) - normalize_y;

		x += 1;

		if (x == WINDOW_WIDTH) {
			y += 1;
			x = 0;
		}
	}

	/*Bind the position_vbo*/
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position_vertices), position_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*Adding the vertex buffers to the vertex array*/
	/*VBO bind*/
	glBindBuffer(GL_ARRAY_BUFFER, position_vbo);
	/*VAO bind*/
	glBindVertexArray(vao);
	
	/*position vbo*/
	/*set the index in the vertex attributes*/
	glEnableVertexAttribArray(0);
	/*set the vertex attribute pointer*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*2, NULL);

	/*color vbo*/
	/*set the index in the vertex attributes*/
	glEnableVertexAttribArray(1);
	/*set the vertex attribute pointer*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, NULL);

	/*VAO unbind*/
	glBindVertexArray(0);
	/*VBO unbind*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void draw_pixels() {
	unsigned char x = 0;
	unsigned char y = 0;
	float normalize_color = 255.0f;
	
	/*Creating the color_vertices to render*/
	/*Like before, 6 points are need to draw a pixel - every point has an rgb color - 6 * 3 = 18*/
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT * 18; i += 18) {
		color_vertices[i] = pixels[x][y].r / normalize_color;
		color_vertices[i + 1] = pixels[x][y].g / normalize_color;
		color_vertices[i + 2] = pixels[x][y].b / normalize_color;
		color_vertices[i + 3] = pixels[x][y].r / normalize_color;
		color_vertices[i + 4] = pixels[x][y].g / normalize_color;
		color_vertices[i + 5] = pixels[x][y].b / normalize_color;
		color_vertices[i + 6] = pixels[x][y].r / normalize_color;
		color_vertices[i + 7] = pixels[x][y].g / normalize_color;
		color_vertices[i + 8] = pixels[x][y].b / normalize_color;
		color_vertices[i + 9] = pixels[x][y].r / normalize_color;
		color_vertices[i + 10] = pixels[x][y].g / normalize_color;
		color_vertices[i + 11] = pixels[x][y].b / normalize_color;
		color_vertices[i + 12] = pixels[x][y].r / normalize_color;
		color_vertices[i + 13] = pixels[x][y].g / normalize_color;
		color_vertices[i + 14] = pixels[x][y].b / normalize_color;
		color_vertices[i + 15] = pixels[x][y].r / normalize_color;
		color_vertices[i + 16] = pixels[x][y].g / normalize_color;
		color_vertices[i + 17] = pixels[x][y].b / normalize_color;

		x += 1;

		if (x == WINDOW_WIDTH) {
			y += 1;
			x = 0;
		}
	}

	/*Bind the position_vbo*/
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_vertices), color_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*bind vao*/
	glBindVertexArray(vao);
	/*draw arrays*/
	glDrawArrays(GL_TRIANGLES, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 12);
	/*unbind vao*/
	glBindVertexArray(0);
}

void render(GLFWwindow* window) {
	draw_pixels();
	glFlush();
	glfwSwapBuffers(window);
}

struct pixel determine_pixel_rgb(unsigned char color_id, unsigned char palette) {
	unsigned char red, green, blue;
	struct colors colors = { palette & 0b11, (palette >> 2) & 0b11, (palette >> 4) & 0b11 , (palette >> 6) & 0b11 };
	
	switch (color_id) {
	case 0b00:
		if (colors._00 == 0b00) {
			red = 245; green = 245; blue = 245;
		}
		else if (colors._00 == 0b01) {
			red = 211; green = 211; blue = 211;
		}
		else if (colors._00 == 0b10) {
			red = 169; green = 169; blue = 169;
		}
		else if (colors._00 == 0b11) {
			red = 0; green = 0; blue = 0;
		}
		break;
	case 0b01:
		if (colors._01 == 0b00) {
			red = 245; green = 245; blue = 245;
		}
		else if (colors._01 == 0b01) {
			red = 211; green = 211; blue = 211;
		}
		else if (colors._01 == 0b10) {
			red = 169; green = 169; blue = 169;
		}
		else if (colors._01 == 0b11) {
			red = 0; green = 0; blue = 0;
		}
		break;
	case 0b10:
		if (colors._10 == 0b00) {
			red = 245; green = 245; blue = 245;
		}
		else if (colors._10 == 0b01) {
			red = 211; green = 211; blue = 211;
		}
		else if (colors._10 == 0b10) {
			red = 169; green = 169; blue = 169;
		}
		else if (colors._10 == 0b11) {
			red = 0; green = 0; blue = 0;
		}
		break;
	case 0b11:
		if (colors._11 == 0b00) {
			red = 245; green = 245; blue = 245;
		}
		else if (colors._11 == 0b01) {
			red = 211; green = 211; blue = 211;
		}
		else if (colors._11 == 0b10) {
			red = 169; green = 169; blue = 169;
		}
		else if (colors._11 == 0b11) {
			red = 0; green = 0; blue = 0;
		}
		break;
	default:
			break;
	}

	struct pixel pixel = { red, green, blue, color_id };
	return pixel;
}

void process_sprites(struct sprite* sprites) {
	for (int sprite = 0; sprite < SPRITES_MAX_AMOUNT; sprite++) {
		unsigned char pos_y, pos_x;
		unsigned char index = sprite * SPRITE_SIZE_SAT_BYTES;
		
		/*Getting the Y pos*/
		readByte(SPRITES_ATTRIBUTES_TABLE_ADDRESS + index, &pos_y);
		sprites[sprite].sprite_pos_y = pos_y - SPRITE_POS_Y_OFFSET;
		
		/*Getting the X pos*/
		readByte(SPRITES_ATTRIBUTES_TABLE_ADDRESS + index + 1, &pos_x);
		sprites[sprite].sprite_pos_x = pos_x - SPRITE_POS_X_OFFSET;
		
		/*Gettign the pattern number*/
		readByte(SPRITES_ATTRIBUTES_TABLE_ADDRESS + index + 2, &(sprites[sprite].pattern_number));
		
		/*Getting the sprite attributes*/
		readByte(SPRITES_ATTRIBUTES_TABLE_ADDRESS + index + 3, &(sprites[sprite].attributes));
	}
}

void draw_background() {
	unsigned short tile_data;
	unsigned short tile_map;

	unsigned char scroll_y = get_scroll_y_register();
	unsigned char scroll_x = get_scroll_x_register();

	unsigned char lcd_control = get_lcd_control_register();
	unsigned char current_scanline = get_ly_register();

	/*Check if in VBLANK*/
	//Check if functionality is correct
	if (current_scanline > VBLANK_PERIOD_LY) {
		return;
	}
	
	/*Determining the tile data and the tile map*/
	tile_data = test_bit(lcd_control, BACKGROUND_AND_WINDOW_TILE_DATA_SELECT) ? TILE_DATA_BIT_ON_VALUE : TILE_DATA_BIT_OFF_VALUE;
	tile_map = test_bit(lcd_control, BACKGROUND_TILE_MAP_DISPLAY_SELECT) ? TILE_MAP_BIT_ON_VALUE : TILE_MAP_BIT_OFF_VALUE;
	
	/*Calculating the tile index*/
	unsigned short pos_y = ((scroll_y + current_scanline) / 8) * 32; //Y position is the same for the whole scanline

	for (int pixel = 0; pixel < WINDOW_WIDTH; pixel++) {
		unsigned char tile_id;
		/*Finding the tile index X pos*/
		unsigned short pos_x = (pixel + scroll_x) / 8;
		/*Getting the tile address according to its location*/
		unsigned short tile_addr = tile_map + pos_y + pos_x;
		/*Reading tile ID from tile address*/
		readByte(tile_addr, &tile_id);
		/*Getting tile data address according to ID*/
		unsigned short tile_data_address;
		if (tile_data == TILE_DATA_BIT_ON_VALUE) {
			/*Tile ID is an unsigned value*/
			tile_data_address = tile_data + (tile_id * TILE_SIZE_BYTES);
		}
		else {
			/*Tile ID is an unsigned value*/
			tile_data_address = tile_data + ((((signed char)tile_id) + 128) * TILE_SIZE_BYTES);
		}
		/*Determine the line of the tile to use*/
		unsigned short tile_line = (pos_y % 8) * TILE_LINE_SIZE_BYTES;
		/*Reading the tile data*/
		unsigned char tile_data_1;
		unsigned char tile_data_2;
		readByte(tile_data_address + tile_line, &tile_data_1);
		readByte(tile_data_address + tile_line + 1, &tile_data_2);
		/*Getting tile line bit - pixel 0 in the tile is bit 7 in tile data*/
		unsigned char tile_line_bit = (((pixel + scroll_x) % 8) - 7) * (-1);
		/*Getting the color ID for the pixel*/
		unsigned char color_id = (test_bit(tile_data_2, tile_line_bit) << 1) | test_bit(tile_data_1, tile_line_bit);
		/*Getting the color palette for the background*/
		unsigned char palette;
		readByte(BACKGROUND_COLOR_PALETTE_ADDRESS, &palette);
		/*Set the data in the pixels array*/
		pixels[pixel][current_scanline] = determine_pixel_rgb(color_id, palette);
	}
}

void draw_window() {
	unsigned short tile_data;
	unsigned short tile_map;

	unsigned char window_y = get_window_y_register();
	unsigned char window_x = get_window_x_register();

	unsigned char lcd_control = get_lcd_control_register();
	unsigned char current_scanline = get_ly_register();

	/*Check current window_y is bigger then scanline y - then no drawn is needed*/
	if (window_y > current_scanline) {
		return;
	}

	/*Determining the tile data and the tile map*/
	tile_data = test_bit(lcd_control, BACKGROUND_AND_WINDOW_TILE_DATA_SELECT) ? TILE_DATA_BIT_ON_VALUE : TILE_DATA_BIT_OFF_VALUE;
	tile_map = test_bit(lcd_control, WINDOW_TILE_MAP_DISPLAY_SELECT) ? TILE_MAP_BIT_ON_VALUE : TILE_MAP_BIT_OFF_VALUE;

	/*Calculating the tile index*/
	unsigned short pos_y = ((current_scanline - window_y) / 8) * 32; //Y position is the same for the whole scanline

	for (int pixel = 0; pixel < WINDOW_WIDTH; pixel++) {
		unsigned char tile_id;
		/*Finding the tile index X pos*/
		unsigned short pos_x = (pixel + (window_x - WINDOW_X_REGISTER_OFFSET)) / 8;
		/*Getting the tile address according to its location*/
		unsigned short tile_addr = tile_map + pos_y + pos_x;
		/*Reading tile ID from tile address*/
		readByte(tile_addr, &tile_id);
		/*Getting tile data address according to ID*/
		unsigned short tile_data_address;
		if (tile_data == TILE_DATA_BIT_ON_VALUE) {
			/*Tile ID is an unsigned value*/
			tile_data_address = tile_data + (tile_id * TILE_SIZE_BYTES);
		}
		else {
			/*Tile ID is an unsigned value*/
			tile_data_address = tile_data + ((((signed char)tile_id) + 128) * TILE_SIZE_BYTES);
		}
		/*Determine the line of the tile to use*/
		unsigned short tile_line = (pos_y % 8) * TILE_LINE_SIZE_BYTES;
		/*Reading the tile data*/
		unsigned char tile_data_1;
		unsigned char tile_data_2;
		readByte(tile_data_address + tile_line, &tile_data_1);
		readByte(tile_data_address + tile_line + 1, &tile_data_2);
		/*Getting tile line bit - pixel 0 in the tile is bit 7 in tile data*/
		unsigned char tile_line_bit = (((pixel + (window_x - WINDOW_X_REGISTER_OFFSET)) % 8) - 7) * (-1);
		/*Getting the color ID for the pixel*/
		unsigned char color_id = (test_bit(tile_data_2, tile_line_bit) << 1) | test_bit(tile_data_1, tile_line_bit);
		/*Getting the color palette for the background*/
		unsigned char palette;
		readByte(BACKGROUND_COLOR_PALETTE_ADDRESS, &palette);
		/*Set the data in the pixels array*/
		pixels[pixel][current_scanline] = determine_pixel_rgb(color_id, palette);
	}
}

void draw_sprites() {
	unsigned char lcd_control = get_lcd_control_register();
	unsigned char current_scanline = get_ly_register();

	/*Determining the sprites size*/
	unsigned char sprites_size;
	if (!test_bit(lcd_control, SPRITES_SIZE)) {sprites_size = _8_X_8;}
	else {sprites_size = _8_X_16;}

	/*Processing the sprites from memory*/
	struct sprite* sprites; //should initialize?
	process_sprites(&sprites);

	/*Looping through each sprite*/
	for (int sprite = 0; sprite < SPRITES_MAX_AMOUNT; sprite++) {
		bool should_y_flip = test_bit(sprites[sprite].attributes, Y_FLIP);
		bool should_x_flip = test_bit(sprites[sprite].attributes, X_FLIP);

		/*Checking if sprite intercept with the current scanline - meaning it should be render*/
		unsigned char sprite_y_size; if (sprites_size == _8_X_8) { sprite_y_size = 8; } else { sprite_y_size = 16; }
		if ((current_scanline >= sprites[sprite].sprite_pos_y) && (current_scanline < (sprites[sprite].sprite_pos_y) + sprite_y_size)) {
			/*Sprite should be rendered*/
			unsigned char sprite_line = current_scanline - sprites[sprite].sprite_pos_y;
			
			/*Checking if Y flip in enabled - read lines backwards to create flip effect*/
			if (should_y_flip) {
				sprite_line = (sprite_line - sprite_y_size) * (-1);
			}
			/*Every line occupies 2 bytes in memory*/
			sprite_line *= 2;

			/*Getting the sprite data address*/
			unsigned short sprite_data_address = SPRITES_DATA_MEMORY_ADDRESS + (sprites[sprite].pattern_number * SPRITE_SIZE_BYTES) + sprite_line;

			/*Getting the sprite data*/
			unsigned char sprite_data_1;
			unsigned char sprite_data_2;
			readByte(sprite_data_address, &sprite_data_1);
			readByte(sprite_data_address + 1, &sprite_data_2);

			/*Going throuh every pixel in the sprite row*/
			for (int pixel = 0; pixel < 8; pixel++) {
				/*Getting sprite line bit - pixel 0 in the tile is bit 7 in sprite data*//*like tiles*/
				unsigned char sprite_line_bit = (pixel - 7) * (-1);

				/*Checking if X flip is enabled - read pixels backwards to create flip effect*/
				if (should_x_flip) {
					sprite_line_bit = (sprite_line_bit - 7) * (-1);
				}

				/*Getting the color ID for the pixel*/
				unsigned char color_id = (test_bit(sprite_data_2, sprite_line_bit) << 1) | test_bit(sprite_data_1, sprite_line_bit);

				/*Getting the color palette for the background*/
				unsigned char palette;
				unsigned short palette_address = test_bit(sprites[sprite].attributes, PALETTE_NUMBER) ? SPRITES_COLOR_PALETTE_2_ADDRESS : SPRITES_COLOR_PALETTE_1_ADDRESS;
				readByte(palette_address, &palette);

				/*Set the data in the pixels array*/
				pixels[sprites[sprite].sprite_pos_x + pixel][current_scanline] = determine_pixel_rgb(color_id, palette);
			}
		}
	}
}

void draw_scanline() {
	/*Draw ScanLine*/
	unsigned char lcd_control = get_lcd_control_register();

	/*Check if background display is enabled*/
	if (test_bit(lcd_control, BACKGROUND_DISPLAY)) {
		draw_background();
	}
	/*Check if window display is enabled*/
	if (test_bit(lcd_control, WINDOW_DISPLAY_ENABLE)) {
		draw_window();
	}
	/*Check if sprites display is enabled*/
	if (test_bit(lcd_control, SPRITES_DISPLAY_ENABLE)) {
		draw_sprites();
	}
}

void set_lcd_status() {
	unsigned char mode;
	bool is_interrupt_source_enabled;

	unsigned char lyc;
	unsigned char lcd_status = get_lcd_status_register();
	unsigned char lcd_current_mode = lcd_status & 0b11;
	unsigned char ly = get_ly_register();

	readByte(LYC_REGISTER_ADDRESS, &lyc);

	/*Check if LCD is disabled*/
	if (!test_bit(get_lcd_control_register(), LCD_ENABLED_BIT)) {
		/*Set LCD mode to 1*/
		lcd_status = lcd_status & 0b11111100;
		lcd_status = lcd_status | VBLANK_STATUS;
		writeByte(LCD_STATUS_ADDRESS, &lcd_status);

		/*Reset ScanLine Counter*/
		gpu.cycles_for_scanline = SCANLINE_CYCLES;

		/*Reseting LY Register*/
		set_ly_register(0);

		return;
	}

	/*Checking If VBLANK*/
	if (ly >= VBLANK_PERIOD_LY) {
		/*Set LCD mode to 1*/
		mode = VBLANK_STATUS;
		set_bit(LCD_STATUS_ADDRESS, MODE_BIT_0);
		reset_bit(LCD_STATUS_ADDRESS, MODE_BIT_1);
		is_interrupt_source_enabled = test_bit(lcd_status, MODE_1_VBLANK_INTERRUPT_SOURCE);
	}
	else {
		/*Checking Different Modes*/
		unsigned short cycles_finished_for_scanline = SCANLINE_CYCLES - gpu.cycles_for_scanline;
		/*Mode 2*/
		if (cycles_finished_for_scanline <= MODE_2_DURATION) {
			mode = SEARCHING_OAM;
			reset_bit(LCD_STATUS_ADDRESS, MODE_BIT_0);
			set_bit(LCD_STATUS_ADDRESS, MODE_BIT_1);
			is_interrupt_source_enabled = test_bit(lcd_status, MODE_2_OAM_INTERRUPT_SOURCE);
		}
		/*Mode 3*/
		else if (cycles_finished_for_scanline <= MODE_3_DURATION) {
			mode = TRANSFER_TO_LCD_CONTROLLER;
			set_bit(LCD_STATUS_ADDRESS, MODE_BIT_0);
			set_bit(LCD_STATUS_ADDRESS, MODE_BIT_1);
		}
		/*Mode 0*/
		else {
			mode = HBLANK;
			reset_bit(LCD_STATUS_ADDRESS, MODE_BIT_0);
			reset_bit(LCD_STATUS_ADDRESS, MODE_BIT_1);
			is_interrupt_source_enabled = test_bit(lcd_status, MODE_0_HBLANK_INTERRUPT_SOURCE);
		}
	}
	/*Checking if should request interrupt*/
	if (is_interrupt_source_enabled && (mode != lcd_current_mode)) {
		set_interrupt_flag(LCD_STAT);
	}

	/*Checking the conincidence flag*/
	if (ly == lyc) {
		set_bit(LCD_STATUS_ADDRESS, LCY_LY);
		/*Check if an interupt should be requested*/
		if (test_bit(lcd_status, LCY_LY_INTERRUPT_SOURCE)) {
			set_interrupt_flag(LCD_STAT);
		}
	}
	else {
		reset_bit(LCD_STATUS_ADDRESS, LCY_LY);
	}
}

void update_graphics(unsigned char last_opcode_t_cycles) {
	/*Updating graphic*/

	/*Setting the LCD Status Register*/
	set_lcd_status();

	//Checking if LCD is enabled
	if (test_bit(get_lcd_control_register(), LCD_ENABLED_BIT)) {
		gpu.cycles_for_scanline -= last_opcode_t_cycles;
	}
	else {
		return;
	}

	//Updating Scanline
	if (gpu.cycles_for_scanline <= 0) {
		unsigned char ly = get_ly_register();

		/*Incrementing LY Register*/
		set_ly_register(ly+1);
		/*Reseting Scanline Cycle Counter*/
		gpu.cycles_for_scanline = SCANLINE_CYCLES;

		if (ly == VBLANK_PERIOD_LY) {
			/*Request VBLANK Interrupt*/
			set_interrupt_flag(VBLANK);
		}
		else if (ly > MAX_LY) {
			set_ly_register(0);
		}
		else if (ly < VBLANK_PERIOD_LY) {
			draw_scanline();
		}
		else {
			printf("Error raised in LY - Wrong value");
			return;
		}
	}
}

int gpuStep(GLFWwindow* window) {
	unsigned long long t_cycles = get_t_cycles();
	if ((t_cycles / cycles_per_frame) > gpu.frames) {
		render(window);
		gpu.frames += 1;
		return 0;
	}

	else {
		update_graphics(get_last_opcode_t_cycles());
		glfwPollEvents();

		/*check for window close*/
		if (glfwWindowShouldClose(window)) {
			glfwTerminate();
			return -1;
		}

		return 0;
	}
}
