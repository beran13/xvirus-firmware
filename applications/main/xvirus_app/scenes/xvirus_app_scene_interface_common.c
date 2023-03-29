#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexSortDirsFirst,
    VarItemListIndexDarkMode,
    VarItemListIndexLeftHanded,
};

void xvirus_app_scene_interface_common_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xvirus_app_scene_interface_common_sort_dirs_first_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->sort_dirs_first = value;
    app->save_settings = true;
}

static void xvirus_app_scene_interface_common_dark_mode_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->dark_mode = value;
    app->save_settings = true;
}

static void xvirus_app_scene_interface_common_left_handed_changed(VariableItem* item) {
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    if(value) {
        furi_hal_rtc_set_flag(FuriHalRtcFlagHandOrient);
    } else {
        furi_hal_rtc_reset_flag(FuriHalRtcFlagHandOrient);
    }
}

void xvirus_app_scene_interface_common_on_enter(void* context) {
    XvirusApp* app = context;
    XvirusSettings* xvirus_settings = XVIRUS_SETTINGS();
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(
        var_item_list,
        "Sort Dirs First",
        2,
        xvirus_app_scene_interface_common_sort_dirs_first_changed,
        app);
    variable_item_set_current_value_index(item, xvirus_settings->sort_dirs_first);
    variable_item_set_current_value_text(item, xvirus_settings->sort_dirs_first ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list, "Dark Mode", 2, xvirus_app_scene_interface_common_dark_mode_changed, app);
    variable_item_set_current_value_index(item, xvirus_settings->dark_mode);
    variable_item_set_current_value_text(item, xvirus_settings->dark_mode ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list,
        "Left Handed",
        2,
        xvirus_app_scene_interface_common_left_handed_changed,
        app);
    bool value = furi_hal_rtc_is_flag_set(FuriHalRtcFlagHandOrient);
    variable_item_set_current_value_index(item, value);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_interface_common_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list,
        scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneInterfaceCommon));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_interface_common_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(
            app->scene_manager, XvirusAppSceneInterfaceCommon, event.event);
        consumed = true;
        switch(event.event) {
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_interface_common_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
