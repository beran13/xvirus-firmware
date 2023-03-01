#pragma once

#include "settings_filename.h"

#include <furi_hal.h>
#include <stdint.h>
#include <stdbool.h>
#include <toolbox/saved_struct.h>
#include <storage/storage.h>
#include <power/power_service/power.h>

#define MAX_PACK_NAME_LEN 32

#define D_SETTINGS_VERSION (2)
#define D_SETTINGS_PATH INT_PATH(D_SETTINGS_FILE_NAME)
#define D_SETTINGS_MAGIC (0x69)

// Some settings function backwards (logically) in
// order to fit the default value we want
// (values will default to 0 / false)
typedef struct {
    char asset_pack[MAX_PACK_NAME_LEN];
    uint16_t anim_speed;
    int32_t cycle_anims;
    bool unlock_anims;
    BatteryIcon battery_icon;
    bool status_icons;
    bool bar_borders;
    bool bar_background;
    bool bad_bt;
    bool sort_ignore_dirs;
} Dsettings;

Dsettings* D_SETTINGS();

bool D_SETTINGS_LOAD();

bool D_SETTINGS_SAVE();
