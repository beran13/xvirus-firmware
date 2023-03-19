#include "settings.h"
#include "assets.h"

int32_t xvirus_srv(void* p) {
    UNUSED(p);

    XVIRUS_SETTINGS_LOAD();
    XVIRUS_ASSETS_LOAD();

    return 0;
}
