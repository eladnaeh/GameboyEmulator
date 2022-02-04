#pragma once

#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CLOCK_SPEED (4194304)
#define FRAME_RATE (60)

/*OPENGL*/
#define OPENGL_NDC_X_START (-1.0f)
#define OPENGL_NDC_Y_START (1.0f)

/*SCANLINE*/
#define SCANLINE_CYCLES (456)

/*TILES*/
#define TILE_DATA_BIT_ON_VALUE (0x8000)
#define TILE_DATA_BIT_OFF_VALUE (0x9000)
#define TILE_MAP_BIT_ON_VALUE (0x9c00)
#define TILE_MAP_BIT_OFF_VALUE (0x9800)

#define TILE_SIZE_BYTES (16)
#define TILE_LINE_SIZE_BYTES (2)

/*SPRITES*/
#define SPRITE_SIZE_BYTES (16)
#define SPRITE_SIZE_SAT_BYTES (4) //In SAT - Sprite Attributes Table

#define SPRITES_MAX_AMOUNT (40)

#define SPRITES_ATTRIBUTES_TABLE_ADDRESS (0xfe00)

#define SPRITE_POS_Y_OFFSET (16)
#define SPRITE_POS_X_OFFSET (8)

#define SPRITES_DATA_MEMORY_ADDRESS (0x8000)

/*PALETTES*/
#define BACKGROUND_COLOR_PALETTE_ADDRESS (0xff47)

#define SPRITES_COLOR_PALETTE_1_ADDRESS (0xff48)
#define SPRITES_COLOR_PALETTE_2_ADDRESS (0xff49)

/*LCD Control Register*/
#define LCD_CONTROL_MEMORY_ADDRESS (0xff40)
#define LCD_ENABLED_BIT (7)

#define MODE_2_DURATION (80)
#define MODE_3_DURATION (172)

/*STAT Register*/
#define LCD_STATUS_ADDRESS (0xff41)

/*LY Register*/
#define LCD_Y_COORDINATE_ADDRESS (0xff44)
#define VBLANK_PERIOD_LY (144)
#define MAX_LY (153)

/*CLY Register*/
#define LYC_REGISTER_ADDRESS (0xff45)

/*Scroll Y Register*/
#define SCROLL_Y_REGISTER_ADDRESS (0xff42)

/*Scroll X Register*/
#define SCROLL_X_REGISTER_ADDRESS (0xff43)

/*Window Y Register*/
#define WINDOW_Y_REGISTER_ADDRESS (0xff4a)

/*Window X Register*/
#define WINDOW_X_REGISTER_ADDRESS (0xff4b)

/*Window X Register Offset*/
#define WINDOW_X_REGISTER_OFFSET (7)

/*Window Sizes*/
#define WINDOW_WIDTH (160)
#define WINDOW_HEIGHT (144)

enum LCD_STATUS_MODES {
	HBLANK = 0b00,
	VBLANK_STATUS = 0b01,
	SEARCHING_OAM = 0b10,
	TRANSFER_TO_LCD_CONTROLLER = 0b11
};

enum LCD_STATUS_BITS {
	MODE_BIT_0 = 0,
	MODE_BIT_1 = 1,
	LCY_LY = 2,
	MODE_0_HBLANK_INTERRUPT_SOURCE = 3,
	MODE_1_VBLANK_INTERRUPT_SOURCE = 4,
	MODE_2_OAM_INTERRUPT_SOURCE = 5,
	LCY_LY_INTERRUPT_SOURCE = 6
};

enum LCD_CONTROL_BITS {
	BACKGROUND_DISPLAY = 0,
	SPRITES_DISPLAY_ENABLE = 1,
	SPRITES_SIZE = 2,
	BACKGROUND_TILE_MAP_DISPLAY_SELECT = 3,
	BACKGROUND_AND_WINDOW_TILE_DATA_SELECT = 4,
	WINDOW_DISPLAY_ENABLE = 5,
	WINDOW_TILE_MAP_DISPLAY_SELECT = 6,
	LCD_DISPLAY_ENABLE = 7
};

enum SPRITE_ATTRIBUTES_BITS {
	PALETTE_NUMBER = 4,
	X_FLIP = 5,
	Y_FLIP = 6,
	SPRITE_BACKGROUND_PRIORITY = 7
};

enum SPRITES_SIZES {
	_8_X_8 = 1,
	_8_X_16 = 2,
};

struct colors {
	unsigned char _00;
	unsigned char _01;
	unsigned char _10;
	unsigned char _11;
};

struct sprite {
	unsigned char sprite_pos_y;
	unsigned char sprite_pos_x;
	unsigned char pattern_number;
	unsigned char attributes;
};

struct pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char colorCode;
};

struct GPU {
	unsigned char frames;
	unsigned short cycles_for_scanline;
};

struct GPU gpu;

struct pixel pixels[WINDOW_WIDTH][WINDOW_HEIGHT];

static const char* vertex_shader_source = "#version 330 core\n"
									"layout (location = 0) in vec2 input_position;\n"
									"layout (location = 1) in vec3 input_color;\n"
									"out vec4 output_color;\n"
									"void main()\n"
									"{\n"
									"	output_color = vec4(input_color, 1.0);"
									"	gl_Position = vec4(input_position.x, input_position.y, 0.0, 1.0);"
									"}\n";

static const char* fragment_shader_source = "#version 330 core\n"
									"in vec4 output_color;\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"	FragColor = output_color;"
									"}\n";

unsigned int position_vbo, color_vbo;
unsigned int vao;

GLfloat position_vertices[WINDOW_WIDTH * WINDOW_HEIGHT * 12];
GLfloat color_vertices[WINDOW_WIDTH * WINDOW_HEIGHT * 18];

void initialize_glfw();

int initialize_glad();

void clear_background(GLFWwindow* window);

GLFWwindow* create_window(int width, int height, char* name);

unsigned int create_vertex_shader();

unsigned int create_fragment_shader();

void initialize_buffers();

unsigned int link_shaders(unsigned int vertex_shader, unsigned int fragment_shader);

int gpuStep(GLFWwindow* window);
