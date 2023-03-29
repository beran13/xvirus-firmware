#include "../xvirus_app.h"

enum VarItemListIndex {
    VarItemListIndexInterface,
    VarItemListIndexProtocols,
    VarItemListIndexMisc,
    VarItemListIndexVersion,
};

void xvirus_app_scene_start_var_item_list_callback(void* context, uint32_t index) {
    XvirusApp* app = context;
    view_dispatcher_send_custom_event(app->view_dispatcher, index);
}

void xvirus_app_scene_start_on_enter(void* context) {
    XvirusApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;

    variable_item_list_add(var_item_list, "Interface", 0, NULL, app);
    variable_item_list_add(var_item_list, "Protocols", 0, NULL, app);
    variable_item_list_add(var_item_list, "Misc", 0, NULL, app);
    variable_item_list_add(var_item_list, furi_string_get_cstr(app->version_tag), 0, NULL, app);

    variable_item_list_set_enter_callback(
        var_item_list, xvirus_app_scene_start_var_item_list_callback, app);

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, XvirusAppSceneStart));

    view_dispatcher_switch_to_view(app->view_dispatcher, XvirusAppViewVarItemList);
}

bool xvirus_app_scene_start_on_event(void* context, SceneManagerEvent event) {
    XvirusApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        scene_manager_set_scene_state(app->scene_manager, XvirusAppSceneStart, event.event);
        consumed = true;
        switch(event.event) {
        case VarItemListIndexInterface:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneInterface);
            break;
        case VarItemListIndexProtocols:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneProtocols);
            break;
        case VarItemListIndexMisc:
            scene_manager_next_scene(app->scene_manager, XvirusAppSceneMisc);
            break;
        case VarItemListIndexVersion: {
            if(storage_common_copy(
                   furi_record_open(RECORD_STORAGE),
                   EXT_PATH("dolphin/dm0firstboot.bin"),
                   EXT_PATH(".slideshow"))) {
                app->show_slideshow = true;
                xvirus_app_apply(app);
            }
            break;
        }
        default:
            break;
        }
    }

    return consumed;
}

void xvirus_app_scene_start_on_exit(void* context) {
    XvirusApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
