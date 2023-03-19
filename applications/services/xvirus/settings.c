#include "settings.h"

#define TAG "XvirusSettings"

XvirusSettings* xvirus_settings = NULL;

XvirusSettings* XVIRUS_SETTINGS() {
    if(xvirus_settings == NULL) {
        XVIRUS_SETTINGS_LOAD();
    }
    return xvirus_settings;
}

void XVIRUS_SETTINGS_LOAD() {
    if(xvirus_settings == NULL) {
        xvirus_settings = malloc(sizeof(XvirusSettings));
        bool loaded = false;
        bool skip = furi_hal_rtc_get_boot_mode() != FuriHalRtcBootModeNormal;

        if(skip) {
            FURI_LOG_W(TAG, "Load skipped. Device is in special startup mode.");
            loaded = false;
        } else {
            loaded = saved_struct_load(
                XVIRUS_SETTINGS_PATH,
                xvirus_settings,
                sizeof(XvirusSettings),
                XVIRUS_SETTINGS_MAGIC,
                XVIRUS_SETTINGS_VERSION);
        }

        if(!loaded) {
            if(!skip) {
                storage_simply_remove(furi_record_open(RECORD_STORAGE), XVIRUS_SETTINGS_PATH_OLD);
                furi_record_close(RECORD_STORAGE);
            }
            memset(xvirus_settings, 0, sizeof(XvirusSettings));
            strlcpy(xvirus_settings->asset_pack, "", MAX_PACK_NAME_LEN); // SFW
            xvirus_settings->anim_speed = 100; // 100%
            xvirus_settings->cycle_anims = 0; // Meta.txt
            xvirus_settings->unlock_anims = false; // OFF
            xvirus_settings->battery_icon = BatteryIconBarPercent; // Bar %
            xvirus_settings->status_icons = true; // ON
            xvirus_settings->bar_borders = true; // ON
            xvirus_settings->bar_background = false; // OFF
            xvirus_settings->bad_bt = false; // USB
            xvirus_settings->bad_bt_remember = false; // OFF
            xvirus_settings->butthurt_timer = 43200; // 12 H
            xvirus_settings->sort_dirs_first = true; // ON
            xvirus_settings->dark_mode = false; // OFF
            xvirus_settings->left_handed = false; // OFF
        }
    }
}

bool XVIRUS_SETTINGS_SAVE() {
    if(xvirus_settings == NULL) {
        XVIRUS_SETTINGS_LOAD();
    }

    if(furi_hal_rtc_get_boot_mode() != FuriHalRtcBootModeNormal) {
        return true;
    }

    return saved_struct_save(
        XVIRUS_SETTINGS_PATH,
        xvirus_settings,
        sizeof(XvirusSettings),
        XVIRUS_SETTINGS_MAGIC,
        XVIRUS_SETTINGS_VERSION);
}
