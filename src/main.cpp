#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

int main() {
    if (!al_init()) {
        return -1;
    }
    if (!al_init_image_addon()) {
        return -1;
    }
    if (!al_init_native_dialog_addon()) {
        return -1;
    }

    ALLEGRO_DISPLAY* disp = al_create_display(640, 480);
    if (!disp) {
        al_show_native_message_box(NULL, "Error", "Error",
            "Could not create display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_rest(3.0);
    al_destroy_display(disp);
    return 0;
}
