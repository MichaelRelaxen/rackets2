#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define rainbow_color(hue) ({ \
    int h = (hue) % 1536; \
    int r = 0, g = 0, b = 0; \
    int min_brightness = 128; \
    if (h < 256)      { r = 255;     g = h;       b = 0;     } \
    else if (h < 512) { r = 511 - h; g = 255;     b = 0;     } \
    else if (h < 768) { r = 0;       g = 255;     b = h - 512; } \
    else if (h < 1024){ r = 0;       g = 1023 - h; b = 255;   } \
    else if (h < 1280){ r = h - 1024; g = 0;      b = 255;   } \
    else              { r = 255;     g = 0;       b = 1535 - h; } \
    r = (r / 2) + min_brightness; \
    g = (g / 2) + min_brightness; \
    b = (b / 2) + min_brightness; \
    (0x80 << 24) | (g << 16) | (b << 8) | r; \
})

#define CROSS_BTN   "\x10" 
#define CIRCLE_BTN  "\x11"
#define TRI_BTN     "\x12" 
#define SQUARE_BTN  "\x13"
#define L1_BTN      "\x14"
#define R1_BTN      "\x15"
#define L2_BTN      "\x16"
#define R2_BTN      "\x17"

// Macros to draw buttons and boxes with pressed state color
#define DRAW_BTN(x, y, label, btn_bit) \
    text_small_center(x, y, ((button_bitmask & btn_bit) ? 0xFFFFFFFF : 0xFF00FF00), label, -1)

#define DRAW_BOX_COND(x1, y1, x2, y2, btn_bit) \
    draw_box(x1, y1, x2, y2, ((button_bitmask & btn_bit) ? WHITE : dpad_color), 0)

#define GREEN 0x7000FF00
#define WHITE 0x40FFFFFF

void _start() {
	// Crash if we run this code on the loading screens... so just don't run it.
	// Also crashes on boot, so we should not write anything if current planet is -1.
	if(current_planet == -1 || should_load || hide_gui)
		return;
	
	uint32_t color = rainbow_color(frames_since_spawn * 5);

    // Offsets for positioning
    uint y_ofs = 0x14F;
    uint x_ofs = 0x4e;

    // Constants for layout
    const int BOX_LEFT   = -0x4B;
    const int BOX_RIGHT  = 0x40;
    const int BOX_TOP    = -0x5;
    const int BOX_BOTTOM = 0x55;
    const uint BOX_COLOR = 0x70000000;

    const int TEXT_BASE_X = -0x47;  // Common x-offset for text
    const int LINE_HEIGHT = 0x10;         // Distance between lines



    // Draw the background box
    draw_box(BOX_RIGHT + x_ofs, y_ofs + BOX_TOP, BOX_LEFT + x_ofs, y_ofs + BOX_BOTTOM, BOX_COLOR, 0);

    // Draw each line of text, right-aligned
    text_small_left(TEXT_BASE_X + x_ofs, y_ofs + LINE_HEIGHT * 0, color, formatted_time_string, -1);
    text_small_left(TEXT_BASE_X + x_ofs, y_ofs + LINE_HEIGHT * 1, color, formatted_frames, -1);
    text_small_left(TEXT_BASE_X + x_ofs, y_ofs + LINE_HEIGHT * 2, color, formatted_status_string, -1);
    text_small_left(TEXT_BASE_X + x_ofs, y_ofs + LINE_HEIGHT * 3, color, formatted_ntrl, -1);
    text_small_left(TEXT_BASE_X + x_ofs, y_ofs + LINE_HEIGHT * 4, color, formatted_state, -1);

    // Dont render input display if toggled off.
    if(input_display_toggle)
        return;

    // Input display offsets
    const int input_display_ofs_x = 490;
    const int input_display_ofs_y = 370;

    const int trigger_buttons_y = 0x22;

    // Draw button labels.
    DRAW_BTN(input_display_ofs_x - 31, input_display_ofs_y - trigger_buttons_y, R1_BTN, BTN_R1);
    DRAW_BTN(input_display_ofs_x - 1, input_display_ofs_y - trigger_buttons_y, R2_BTN, BTN_R2);

    DRAW_BTN(input_display_ofs_x - 78, input_display_ofs_y - trigger_buttons_y, L2_BTN, BTN_L2);
    DRAW_BTN(input_display_ofs_x - 108, input_display_ofs_y - trigger_buttons_y, L1_BTN, BTN_L1);

    DRAW_BTN(input_display_ofs_x - 0x10, input_display_ofs_y - 0x10, TRI_BTN, BTN_TRIANGLE);
    DRAW_BTN(input_display_ofs_x, input_display_ofs_y, CIRCLE_BTN, BTN_CIRCLE);
    DRAW_BTN(input_display_ofs_x - 0x20, input_display_ofs_y, SQUARE_BTN, BTN_SQUARE);
    DRAW_BTN(input_display_ofs_x - 0x10, input_display_ofs_y + 0x10,CROSS_BTN, BTN_CROSS);

    // Dpad properties
    const int dpad_box_size = 14;
    const int dpad_spacing = 7;
    const uint dpad_color = 0x70000000;

    int dpad_center_x = input_display_ofs_x - 90;
    int dpad_center_y = input_display_ofs_y + 10;

    // Draw dpad boxes with color depending on button state
    DRAW_BOX_COND(
        dpad_center_x - dpad_box_size / 2,
        dpad_center_y - dpad_spacing - dpad_box_size,
        dpad_center_x + dpad_box_size / 2,
        dpad_center_y - dpad_spacing,
        BTN_UP);

    DRAW_BOX_COND(
        dpad_center_x - dpad_box_size / 2,
        dpad_center_y + dpad_spacing,
        dpad_center_x + dpad_box_size / 2,
        dpad_center_y + dpad_spacing + dpad_box_size,
        BTN_DOWN);

    DRAW_BOX_COND(
        dpad_center_x - dpad_spacing - dpad_box_size,
        dpad_center_y - dpad_box_size / 2,
        dpad_center_x - dpad_spacing,
        dpad_center_y + dpad_box_size / 2,
        BTN_LEFT);

    DRAW_BOX_COND(
        dpad_center_x + dpad_spacing,
        dpad_center_y - dpad_box_size / 2,
        dpad_center_x + dpad_spacing + dpad_box_size,
        dpad_center_y + dpad_box_size / 2,
        BTN_RIGHT);

    // Start button box properties
    const int start_width = 10;
    const int start_height = 6;

    int start_x = input_display_ofs_x - 49;
    int start_y = input_display_ofs_y - 10;

    // Draw start button box
    draw_box(
        start_x - 1, start_y - 1,
        start_x + start_width + 1, start_y + start_height + 1,
        (button_bitmask & BTN_START) ? WHITE : dpad_color,
        0);

    // Offset Select to the left of Start
    int select_x = start_x - 20;

    // Draw Select button box
    draw_box(
        select_x - 1, start_y - 1,
        select_x + start_width + 1, start_y + start_height + 1,
        (button_bitmask & BTN_SELECT) ? WHITE : dpad_color,
        0);
    
    
    // Analog stick display
    const int stick_box_size = 16;
    const int stick_radius = stick_box_size / 2;
    const uint stick_box_color = 0x70000000;
    uint stick_dot_color_left = (button_bitmask & BTN_L3) ? GREEN : 0xFFFFFFFF;
    uint stick_dot_color_right = (button_bitmask & BTN_R3) ? GREEN : 0xFFFFFFFF;

    // Base positions
    const int left_stick_box_x = input_display_ofs_x - 70;
    const int left_stick_box_y = input_display_ofs_y + 33;

    const int right_stick_box_x = left_stick_box_x + 30;
    const int right_stick_box_y = left_stick_box_y;

    // Draw left stick box
    draw_box(
        left_stick_box_x - stick_radius,
        left_stick_box_y - stick_radius,
        left_stick_box_x + stick_radius,
        left_stick_box_y + stick_radius,
        stick_box_color,
        0);

    // Draw right stick box
    draw_box(
        right_stick_box_x - stick_radius,
        right_stick_box_y - stick_radius,
        right_stick_box_x + stick_radius,
        right_stick_box_y + stick_radius,
        stick_box_color,
        0);

    // Get stick positions and clamp
    float lx = LEFT_STICK_X;
    float ly = LEFT_STICK_Y;
    float rx = RIGHT_STICK_X;
    float ry = RIGHT_STICK_Y;

    // Clamp values between -1.0 and 1.0
    if (lx < -1) lx = -1; if (lx > 1) lx = 1;
    if (ly < -1) ly = -1; if (ly > 1) ly = 1;
    if (rx < -1) rx = -1; if (rx > 1) rx = 1;
    if (ry < -1) ry = -1; if (ry > 1) ry = 1;

    // Convert to pixel offset from center
    int left_dot_x = left_stick_box_x - 2 + (int)(lx * stick_radius);
    int left_dot_y = left_stick_box_y - 13 + (int)(ly * stick_radius);

    int right_dot_x = right_stick_box_x - 2 + (int)(rx * stick_radius);
    int right_dot_y = right_stick_box_y - 13 + (int)(ry * stick_radius);

    // Draw dots using small centered text
    text_small_center(left_dot_x, left_dot_y, stick_dot_color_left, ".", -1);
    text_small_center(right_dot_x, right_dot_y, stick_dot_color_right, ".", -1);
} 

