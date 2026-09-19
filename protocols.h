#include <stdbool.h>
#include <wayland-server-core.h>
#include <wlr/types/wlr_layer_shell_v1.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_output_management_v1.h>
#include <wlr/types/wlr_scene.h>

/*
 * TinyWay keeps its compositor in one small translation unit.  These wrappers
 * install the wlroots protocol managers at the points where the existing
 * compositor creates its output layout and scene, without making the protocol
 * code depend on TinyWay's private server structures.
 */
static struct wl_display *tinyway_display;
static struct wlr_output_layout *tinyway_output_layout;
static struct wlr_output_manager_v1 *tinyway_output_manager;
static struct wlr_scene *tinyway_scene;
static struct wlr_layer_shell_v1 *tinyway_layer_shell;
static struct wl_listener tinyway_output_apply_listener;
static struct wl_listener tinyway_output_test_listener;
static struct wl_listener tinyway_layer_new_surface_listener;

extern struct wlr_output_layout *tinyway_real_output_layout_create(
    struct wl_display *) __asm__("wlr_output_layout_create");
extern struct wlr_scene *tinyway_real_scene_create(void)
    __asm__("wlr_scene_create");

static void tinyway_output_apply(struct wl_listener *listener, void *data)
{
    struct wlr_output_configuration_v1 *configuration = data;
    (void)listener;

    if (wlr_output_configuration_v1_apply(configuration,
            tinyway_output_layout)) {
        wlr_output_manager_v1_set_configuration(tinyway_output_manager,
            configuration);
    } else {
        wlr_output_configuration_v1_send_failed(configuration);
    }
    wlr_output_configuration_v1_destroy(configuration);
}

static void tinyway_output_test(struct wl_listener *listener, void *data)
{
    struct wlr_output_configuration_v1 *configuration = data;
    (void)listener;

    if (wlr_output_configuration_v1_test(configuration,
            tinyway_output_layout)) {
        wlr_output_configuration_v1_send_succeeded(configuration);
    } else {
        wlr_output_configuration_v1_send_failed(configuration);
    }
    wlr_output_configuration_v1_destroy(configuration);
}

static struct wlr_output_layout *tinyway_output_layout_create(
    struct wl_display *display)
{
    tinyway_display = display;
    tinyway_output_layout = tinyway_real_output_layout_create(display);
    if (tinyway_output_layout == NULL)
        return NULL;

    tinyway_output_manager = wlr_output_manager_v1_create(display);
    if (tinyway_output_manager == NULL)
        return tinyway_output_layout;

    tinyway_output_apply_listener.notify = tinyway_output_apply;
    wl_signal_add(&tinyway_output_manager->events.apply,
        &tinyway_output_apply_listener);
    tinyway_output_test_listener.notify = tinyway_output_test;
    wl_signal_add(&tinyway_output_manager->events.test,
        &tinyway_output_test_listener);
    return tinyway_output_layout;
}

static void tinyway_layer_new_surface(struct wl_listener *listener, void *data)
{
    struct wlr_layer_surface_v1 *layer_surface = data;
    (void)listener;

    /* The scene helper handles layer ordering, anchors, margins and exclusive
     * zones. It also updates the scene on every layer-surface commit. */
    if (tinyway_scene != NULL)
        wlr_scene_layer_surface_v1_create(&tinyway_scene->tree,
            layer_surface);
}

static struct wlr_scene *tinyway_scene_create(void)
{
    tinyway_scene = tinyway_real_scene_create();
    if (tinyway_scene == NULL || tinyway_display == NULL)
        return tinyway_scene;

    tinyway_layer_shell = wlr_layer_shell_v1_create(tinyway_display, 4);
    if (tinyway_layer_shell != NULL) {
        tinyway_layer_new_surface_listener.notify = tinyway_layer_new_surface;
        wl_signal_add(&tinyway_layer_shell->events.new_surface,
            &tinyway_layer_new_surface_listener);
    }
    return tinyway_scene;
}

#define wlr_output_layout_create tinyway_output_layout_create
#define wlr_scene_create tinyway_scene_create
