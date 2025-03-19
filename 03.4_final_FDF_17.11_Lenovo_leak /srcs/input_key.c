#include "fdf.h"

void zoom_in_and_out(int keycode, t_display *display)
{
    float old_zoom = display->zoom;
    float new_zoom = old_zoom;
    float mode_scale;
    
    // Select the appropriate scaling factor based on movement mode
    if (display->movement_mode == 0)
        mode_scale = SMALL_MAP_ZOOM_SCALE;
    else if (display->movement_mode == 1)
        mode_scale = LARGE_MAP_ZOOM_SCALE;
    else
        mode_scale = VERY_LARGE_MAP_ZOOM_SCALE;
    
    if (keycode == KC_PLUS)
        new_zoom *= mode_scale;
    else if (keycode == KC_MINUS)
        new_zoom /= mode_scale;
    
    if (new_zoom != old_zoom)
    {
        display->zoom = new_zoom;
        display->needs_redraw = 1;
    }
}

void translation(int keycode, t_display *display)
{
    float mode_scale;
    
    // Select the appropriate scaling factor based on movement mode
    if (display->movement_mode == 0)
        mode_scale = SMALL_MAP_TRANS_SCALE;
    else if (display->movement_mode == 1)
        mode_scale = LARGE_MAP_TRANS_SCALE;
    else
        mode_scale = VERY_LARGE_MAP_TRANS_SCALE;
    
    if (keycode == KC_UP)
        display->offset_y -= mode_scale;
    else if (keycode == KC_DOWN)
        display->offset_y += mode_scale;
    else if (keycode == KC_LEFT)
        display->offset_x -= mode_scale;
    else if (keycode == KC_RIGHT)
        display->offset_x += mode_scale;
    
    display->needs_redraw = 1;
}

void rotation(int keycode, t_display *display)
{
    float rot_step;
    float mode_scale;
    
    // Select the appropriate scaling factor based on movement mode
    if (display->movement_mode == 0)
        mode_scale = SMALL_MAP_ROT_SCALE;
    else if (display->movement_mode == 1)
        mode_scale = LARGE_MAP_ROT_SCALE;
    else
        mode_scale = VERY_LARGE_MAP_ROT_SCALE;
    
    if (keycode == KC_Q)
        display->rotation_angle -= mode_scale;
    else if (keycode == KC_E)
        display->rotation_angle += mode_scale;
    
    display->needs_redraw = 1;
}

int handel_key_in(int keycode, t_display *display)
{
    if (keycode == KC_ESC)
        exit(0);
    else if (keycode == KC_PLUS || keycode == KC_MINUS)
        zoom_in_and_out(keycode, display);
    else if (keycode == KC_UP || keycode == KC_DOWN || keycode == KC_LEFT || keycode == KC_RIGHT)
        translation(keycode, display);
    else if (keycode == KC_Q || keycode == KC_E)
        rotation(keycode, display);
    else if (keycode == KC_N) // Toggle movement mode
    {
        // Cycle through the three movement modes
        display->movement_mode = (display->movement_mode + 1) % 3;
        
        const char *mode_str;
        if (display->movement_mode == 0)
            mode_str = "Small map";
        else if (display->movement_mode == 1)
            mode_str = "Large map";
        else
            mode_str = "Very large map";
            
        ft_printf("Movement mode changed to: %s\n", mode_str);
        display->needs_redraw = 1;
    }
    
    return (0);
}
