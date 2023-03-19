#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexAssetPack,
    VarItemListIndexAnimSpeed,
    VarItemListIndexCycleAnims,
    VarItemListIndexUnlockAnims,
};

void xvirus_app_scene_graphics_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xvirus_app_scene_graphics_asset_pack_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(
        item, index == 0 ? "SFW" : *asset_packs_get(app->asset_packs, index - 1));
    strlcpy(
        XVIRUS_SETTINGS()->asset_pack,
        index == 0 ? "" : *asset_packs_get(app->asset_packs, index - 1),
        MAX_PACK_NAME_LEN);
    app->asset_pack = index;
    app->save_settings = true;
    app->require_reboot = true;
}

const char* const anim_speed_names[] =
    {"25%", "50%", "75%", "100%", "125%", "150%", "175%", "200%", "225%", "250%", "275%", "300%"};
const int32_t anim_speed_values[COUNT_OF(anim_speed_names)] =
    {25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300};
static void xvirus_app_scene_graphics_anim_speed_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, anim_speed_names[index]);
    XVIRUS_SETTINGS()->anim_speed = anim_speed_values[index];
    app->save_settings = true;
}

const char* const cycle_anims_names[] = {
    "OFF",
    "Meta.txt",
    "30 S",
    "1 M",
    "5 M",
    "10 M",
    "15 M",
    "30 M",
    "1 H",
    "2 H",
    "6 H",
    "12 H",
    "24 H"};
const int32_t cycle_anims_values[COUNT_OF(cycle_anims_names)] =
    {-1, 0, 30, 60, 300, 600, 900, 1800, 3600, 7200, 21600, 43200, 86400};
static void xvirus_app_scene_graphics_cycle_anims_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, cycle_anims_names[index]);
    XVIRUS_SETTINGS()->cycle_anims = cycle_anims_values[index];
    app->save_settings = true;
}

static void xvirus_app_scene_graphics_unlock_anims_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->unlock_anims = value;
    app->save_settings = true;
}

void xvirus_app_scene_graphics_on_enter(void* context) {
    XvirusApp* app = context;
    XvirusSettings* xvirus_settings = XVIRUS_SETTINGS();
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;
    uint8_t value_index;

    item = variable_item_list_add(
        var_item_list,
        "Asset Pack",
        asset_packs_size(app->asset_packs) + 1,
        xvirus_app_scene_graphics_asset_pack_changed,
        app);
    variable_item_set_current_value_index(item, app->asset_pack);
    variable_item_set_current_value_text(
        item,
        app->asset_pack == 0 ? "SFW" : *asset_packs_get(app->asset_packs, app->asset_pack - 1));

    item = variable_item_list_add(
        var_item_list,
        "Anim Speed",
        COUNT_OF(anim_speed_names),
        xvirus_app_scene_graphics_anim_speed_changed,
        app);
    value_index = value_index_int32(
        xvirus_settings->anim_speed, anim_speed_values, COUNT_OF(anim_speed_names));
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, anim_speed_names[value_index]);

    item = variable_item_list_add(
        var_item_list,
        "Cycle Anims",
        COUNT_OF(cycle_anims_names),
        xvirus_app_scene_graphics_cycle_anims_changed,
        app);
    value_index = value_index_int32(
        xvirus_settings->cycle_anims, cycle_anims_values, COUNT_OF(cycle_anims_names));
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, cycle_anims_names[value_index]);

    item = variable_item_list_add(
        var_item_list, "Unlock Anims", 2, xvirus_app_scene_graphics_unlock_anims_changed, app);
    variable_item_set_current_value_index(item, xvirus_settings->unlock_anims);
    variable_item_set_current_value_text(item, xvirus_settings->unlock_anims ? "ON" : "OFF");

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_graphics_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneGraphics));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_graphics_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, XvirusAppSceneGraphics, event.event);
        consumed = true;
        switch(event.event) {
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_graphics_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
