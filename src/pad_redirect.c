#include "../include/Types.h"
#include "../include/Game.h"
#include "../include/Vars.h"
#include "../include/Pad.h"

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
    tasInputs buffer[sizeof(tasInputs)]; \
    buffer->buttons_high = (recorded_buttons >> 8) & 0xFF; \
    buffer->buttons_low = recorded_buttons & 0xFF; \
    buffer->right_analog_x = (recorded_sticks >> 0) & 0xFF; \
    buffer->right_analog_y = (recorded_sticks >> 8) & 0xFF; \
    buffer->left_analog_x = (recorded_sticks >> 16) & 0xFF; \
    buffer->left_analog_y = (recorded_sticks >> 24) & 0xFF; \
    buffer->length = recorded_pad_len; \
    buffer->padding = recorded_pad_state; \
    syscall(sys_fs_write, *tas_fd_ptr, buffer, sizeof(tasInputs), tas_nread_ptr); \
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
    frame_timer += 1;

    int32_t ret = cellPadGetData(port_no, data);

    recorded_buttons = (data->buttons_high << 8) | data->buttons_low;
    recorded_sticks = (data->right_analog_x) | (data->right_analog_y << 8)  | (data->left_analog_x  << 16) | (data->left_analog_y  << 24);
    recorded_pad_len = data->length;
    recorded_pad_state = data->padding;

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
        tasInputs inputBuffer[sizeof(tasInputs)];

        // Read from file
        syscall(sys_fs_read, *tas_fd_ptr, inputBuffer, sizeof(tasInputs), tas_nread_ptr);

        if (inputBuffer->render == 0xDEAD) {
            tas_stop_api = 1;
            return ret;
        }

        if (inputBuffer->breakp == 1) {
            framestep_mode = 1;
        }

        // render scripting
        // BIT 0: change frameskip?
        // BIT 1: frameskip value
        // BIT 2: change render?
        // BIT 3: render value
        if (inputBuffer->render >> 0 & 1 == 1) {
            desired_gcm_flip = inputBuffer->render >> 1 & 1;
        }
        if (inputBuffer->render >> 2 & 1 == 1) {
            desired_should_render = inputBuffer->render >> 3 & 1;
        }

        set_gcm_flip = desired_gcm_flip;
        should_render = desired_should_render;

        // Overwrite the inputs!
        // For input recording we need both the length and the bytes that are set in "padding", or else it desyncs.
        // According to the SDK documentation, if the data output from the controller is the same as the data obtained before, then length should be 0.
        // Realistically, easiest way to get around this is to just record the length anyway so fuk it.
        data->length = inputBuffer->length;
        data->padding = inputBuffer->padding;
        data->buttons_high = inputBuffer->buttons_high;
        data->buttons_low = inputBuffer-> buttons_low;
        data->right_analog_x = inputBuffer->right_analog_x;
        data->right_analog_y = inputBuffer->right_analog_y;
        data->left_analog_x = inputBuffer->left_analog_x;
        data->left_analog_y = inputBuffer->left_analog_y;
    } else {
        set_gcm_flip = 0;
        should_render = 0;
    }

    if ((tas_state == TAS_PLAYBACK) && tas_stop_api) {
        TAS_DONE();
    }
    if ((tas_state == TAS_RECORDING) && tas_stop_api) {
        // So that we know where the file ends.
        uint32_t endBuffer[4];
        endBuffer[0] = 0xDEADDEAD;
        endBuffer[1] = 0xDEADDEAD;
        endBuffer[2] = 0xDEADDEAD;
        endBuffer[3] = frame_timer;
        syscall(sys_fs_write, *tas_fd_ptr, endBuffer, 16, tas_nread_ptr); \
        TAS_DONE();
    }

    if(tas_stop_api && tas_state == 6)
        tas_stop_api = 0;

    return ret;
} 