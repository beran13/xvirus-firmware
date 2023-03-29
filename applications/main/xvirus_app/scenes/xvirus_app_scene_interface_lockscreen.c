#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexShowClock,
    VarItemListIndexShowDate,
};

void xvirus_app_scene_interface_lockscreen_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

static void xvirus_app_scene_interface_lockscreen_show_time_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->lockscreen_time = value;
    app->save_settings = true;
}

static void xvirus_app_scene_interface_lockscreen_show_date_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->lockscreen_date = value;
    app->save_settings = true;
}

static void xvirus_app_scene_interface_lockscreen_show_statusbar_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->lockscreen_statusbar = value;
    app->save_settings = true;
}

static void xvirus_app_scene_interface_lockscreen_unlock_prompt_changed(VariableItem* item) {
    XvirusApp* app = variable_item_get_context(item);
    bool value = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, value ? "ON" : "OFF");
    XVIRUS_SETTINGS()->lockscreen_prompt = value;
    app->save_settings = true;
}

void xvirus_app_scene_interface_lockscreen_on_enter(void* context) {
    XvirusApp* app = context;
    XvirusSettings* xvirus_settings = XVIRUS_SETTINGS();
    VariableItemList* var_item_list = app->var_item_list;
    VariableItem* item;

    item = variable_item_list_add(
        var_item_list,
        "Show Time",
        2,
        xvirus_app_scene_interface_lockscreen_show_time_changed,
        app);
    variable_item_set_current_value_index(item, xvirus_settings->lockscreen_time);
    variable_item_set_current_value_text(item, xvirus_settings->lockscreen_time ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list,
        "Show Date",
        2,
        xvirus_app_scene_interface_lockscreen_show_date_changed,
        app);
    variable_item_set_current_value_index(item, xvirus_settings->lockscreen_date);
    variable_item_set_current_value_text(item, xvirus_settings->lockscreen_date ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list,
        "Show Statusbar",
        2,
        xvirus_app_scene_interface_lockscreen_show_statusbar_changed,
        app);
    variable_item_set_current_value_index(item, xvirus_settings->lockscreen_statusbar);
    variable_item_set_current_value_text(
        item, xvirus_settings->lockscreen_statusbar ? "ON" : "OFF");

    item = variable_item_list_add(
        var_item_list,
        "Unlock Prompt",
        2,
        xvirus_app_scene_interface_lockscreen_unlock_prompt_changed,
        app);
    variable_item_set_current_value_index(item, xvirus_settings->lockscreen_prompt);
    variable_item_set_current_value_text(item, xvirus_settings->lockscreen_prompt ? "ON" : "OFF");

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_interface_lockscreen_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list,
        scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneInterfaceLockscreen));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_interface_lockscreen_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(
            app->scene_manager, XvirusAppSceneInterfaceLockscreen, event.event);
        consumed = true;
        switch(event.event) {
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_interface_lockscreen_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
