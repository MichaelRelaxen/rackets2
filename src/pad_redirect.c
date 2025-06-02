#include "../include/Moby.h"
#include "../include/Game.h"
#include "../include/Macros.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

#define cellPadGetData ((int32_t (*)(uint32_t, cellPadData *))0x122479C)

#define TAS_RECORDING_WAIT 1
#define TAS_RECORDING 2
#define TAS_PLAYBACK_WAIT 4
#define TAS_PLAYBACK 5
#define TAS_STOP 6

#define TAS_START_RECORDING() do { \
    syscall(sys_fs_open, "/dev_hdd0/game/NPEA00386/USRDIR/recording.rtas", 0x241, tas_fd_ptr, 0, 0, 0); \
    tas_state = TAS_RECORDING; \
} while(0)

#define TAS_RECORD_INPUT() do { \
    uint8_t buffer[6]; \
    buffer[0] = (fmt_buttons >> 8) & 0xFF; \
    buffer[1] = fmt_buttons & 0xFF; \
    buffer[2] = (fmt_sticks >> 0) & 0xFF; \
    buffer[3] = (fmt_sticks >> 8) & 0xFF; \
    buffer[4] = (fmt_sticks >> 16) & 0xFF; \
    buffer[5] = (fmt_sticks >> 24) & 0xFF; \
    syscall(sys_fs_write, *tas_fd_ptr, buffer, 6, tas_nread_ptr); \
} while(0)

#define TAS_DONE() do { \
    syscall(sys_fs_close, *tas_fd_ptr); \
    *tas_fd_ptr = 0; \
    tas_state = TAS_STOP; \
    tas_stop_api = 0; \
} while(0)


#define TAS_START_PLAYBACK() do { \
    syscall(sys_fs_open, "/dev_hdd0/game/NPEA00386/USRDIR/recording.rtas", 0, tas_fd_ptr, 0, 0, 0); \
    tas_state = TAS_PLAYBACK; \
} while(0)


int32_t _start(uint32_t port_no, cellPadData *data) {
    int32_t ret = cellPadGetData(port_no, data);

    int32_t len = data->length;

    // Compress the input data into 6 bytes, first 2 bytes for buttons, last 4 for each of the sticks.
    fmt_buttons = (data->buttons_high << 8) | data->buttons_low;
    fmt_sticks = (data->right_analog_x) | (data->right_analog_y << 8)  | (data->left_analog_x  << 16) | (data->left_analog_y  << 24);

    // Prepare for recording and record on level load in.
    if (tas_state == TAS_RECORDING_WAIT && load_in_level) {
        TAS_START_RECORDING();
    }

    if (tas_state == TAS_RECORDING) {
        TAS_RECORD_INPUT();
    }

    // Prepare for playback, then playback inputs on level load-in.
    if (tas_state == TAS_PLAYBACK_WAIT && load_in_level) {
        TAS_START_PLAYBACK();
    }

    if (tas_state == TAS_PLAYBACK) {
        // Memset only if we want to block player from putting down their own inputs?
        memset(data, 0, 24);

        data->length = len;

        if (data->length == 0 && (remote_pressed_buttons != last_remote_pressed_buttons)) {
            data->length = 24;
        }

        tasInputs inputBuffer[6];

        // Read from file
        syscall(sys_fs_read, *tas_fd_ptr, inputBuffer, 6, tas_nread_ptr);

        // Overwrite the inputs!
        data->buttons_high = inputBuffer->buttons_high;
        data->buttons_low = inputBuffer-> buttons_low;
        data->right_analog_x = inputBuffer->right_analog_x;
        data->right_analog_y = inputBuffer->right_analog_y;
        data->left_analog_x = inputBuffer->left_analog_x;
        data->left_analog_y = inputBuffer->left_analog_y;
    }

    if ((tas_state == TAS_RECORDING || tas_state == TAS_PLAYBACK) && tas_stop_api) {
        TAS_DONE();
    }

    last_remote_pressed_buttons = remote_pressed_buttons;

    return ret;
} 