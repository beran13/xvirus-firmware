#include "settings.h"
#include "assets.h"

void Dsettings_on_system_start() {
    D_SETTINGS_LOAD();
    D_ASSETS_LOAD();
}
