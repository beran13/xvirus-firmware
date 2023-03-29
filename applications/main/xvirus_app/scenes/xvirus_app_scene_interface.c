#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexGraphics,
    VarItemListIndexMainmenu,
    VarItemListIndexLockscreen,
    VarItemListIndexStatusbar,
    VarItemListIndexCommon,
};

void xvirus_app_scene_interface_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void xvirus_app_scene_interface_on_enter(void* context) {
    XvirusApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;

    variable_item_list_add(var_item_list, "Graphics", 0, NULL, app);
    variable_item_list_add(var_item_list, "Mainmenu", 0, NULL, app);
    variable_item_list_add(var_item_list, "Lockscreen", 0, NULL, app);
    variable_item_list_add(var_item_list, "Statusbar", 0, NULL, app);
    variable_item_list_add(var_item_list, "Common", 0, NULL, app);

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_interface_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneInterface));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_interface_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, XvirusAppSceneInterface, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexGraphics:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneInterfaceGraphics);
            break;
        case VarItemListIndexMainmenu:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneInterfaceMainmenu);
            break;
        case VarItemListIndexLockscreen:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneInterfaceLockscreen);
            break;
        case VarItemListIndexStatusbar:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneInterfaceStatusbar);
            break;
        case VarItemListIndexCommon:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneInterfaceCommon);
            break;
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_interface_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
