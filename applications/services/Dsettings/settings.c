#include "settings.h"

Dsettings* d_settings = NULL;

Dsettings* D_SETTINGS() {
    if(d_settings == NULL) {
        D_SETTINGS_LOAD();
    }
    return d_settings;
}

bool D_SETTINGS_LOAD() {
    if(d_settings == NULL) {
        d_settings = malloc(sizeof(Dsettings));
        bool loaded = saved_struct_load(
            D_SETTINGS_PATH,
            d_settings,
            sizeof(Dsettings),
            D_SETTINGS_MAGIC,
            D_SETTINGS_VERSION);
        if(!loaded) {
            memset(d_settings, 0, sizeof(Dsettings));
            loaded = D_SETTINGS_SAVE();
        }
        return loaded;
    }
    return true;
}

bool D_SETTINGS_SAVE() {
    if(d_settings == NULL) {
        D_SETTINGS_LOAD();
    }
    return saved_struct_save(
        D_SETTINGS_PATH,
        d_settings,
        sizeof(Dsettings),
        D_SETTINGS_MAGIC,
        D_SETTINGS_VERSION);
}
