/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csu-ubuntu <csu-ubuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:30:22 by csu-ubuntu        #+#    #+#             */
/*   Updated: 2025/03/18 12:43:40 by csu-ubuntu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Puts a pixel into the image buffer at the specified coordinates with the given color
 * 
 * @param display The display structure containing the image data
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @param color The color value to set
 */
void put_pixel_to_img(t_display *display, int x, int y, int color)
{
    int position;
    char *addr;
    
    if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
        return;
    
    position = (y * display->img->size_line) + (x * (display->img->bpp / 8));
    addr = display->img->img_addr + position;
    *(unsigned int *)addr = color;
}

/**
 * Display control information on the window
 * Shows keyboard controls and current display state
 * 
 * @param display The display structure
 */
void display_control_info(t_display *display)
{
    int vertical_pos = 20; // Starting position for text
    char *temp_str; // Temporary pointer for ft_strjoin result
    char *temp_itoa; // Temporary pointer for ft_itoa result

    // Display state info
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "--- CURRENT STATE ---");
    vertical_pos += 20;

    temp_str = ft_strjoin("Projection: ", display->is_isometric ? "Isometric" : "Parallel");
    if (!temp_str) // Optional: Add error handling
        print_error_and_exit("Failed to allocate string in display_control_info", 0);
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, temp_str);
    free(temp_str);
    vertical_pos += 20;

    // Show the current movement mode
    char *mode_text;
    if (display->movement_mode == 0)
        mode_text = "Small map";
    else if (display->movement_mode == 1)
        mode_text = "Large map";
    else
        mode_text = "Very large map";
    temp_str = ft_strjoin("Movement mode: ", mode_text);
    if (!temp_str)
        print_error_and_exit("Failed to allocate string in display_control_info", 0);
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, temp_str);
    free(temp_str);
    vertical_pos += 20;

    // Show the current color mode
    temp_str = ft_strjoin("Color mode: ", get_color_mode_str(display->use_altitude_colors));
    if (!temp_str)
        print_error_and_exit("Failed to allocate string in display_control_info", 0);
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, temp_str);
    free(temp_str);
    vertical_pos += 20;

    temp_str = ft_strjoin("View: ", display->points_only ? "Points only" : "Wireframe");
    if (!temp_str)
        print_error_and_exit("Failed to allocate string in display_control_info", 0);
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, temp_str);
    free(temp_str);
    vertical_pos += 20;

    // Fix for the flat factor line
    temp_itoa = ft_itoa((int)(display->flat_f * 100)); // Store ft_itoa result separately
    if (!temp_itoa)
        print_error_and_exit("Failed to allocate itoa string in display_control_info", 0);
    temp_str = ft_strjoin("Flat factor: ", temp_itoa);
    if (!temp_str)
    {
        free(temp_itoa); // Clean up temp_itoa if ft_strjoin fails
        print_error_and_exit("Failed to allocate string in display_control_info", 0);
    }
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, temp_str);
    free(temp_str);  // Free ft_strjoin result
    free(temp_itoa); // Free ft_itoa result
    vertical_pos += 20;

    temp_str = ft_strjoin("Tile culling: ", display->use_tile_culling ? "On" : "Off");
    if (!temp_str)
        print_error_and_exit("Failed to allocate string in display_control_info", 0);
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, temp_str);
    free(temp_str);
    vertical_pos += 30;

    // Display controls (static strings, no allocation)
    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "--- CONTROLS ---");
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, RESET);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, MOVE);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, ZOOMIO);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, PERSP);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "Toggle Point/Wire: Press 'P'");
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "Toggle Color On/Off: Press 'C'");
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "Toggle Color Mode: Press 'V'");
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, ROTX);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, ROTY);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, ROTZ);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, FLAT);
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "Toggle Normal/Flat: Press 'F'");
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "Toggle Movement Mode: Press 'N'");
    vertical_pos += 20;

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, CLOSE);

    mlx_string_put(display->mlx_ptr, display->window_ptr, 10, vertical_pos, WHITE, 
                  "Toggle Tile Culling: Press 't'");
}

/**
 * Returns a string representation of the current color mode
 * 
 * @param mode The color mode index
 * @return A string describing the color mode
 */
char *get_color_mode_str(int mode)
{
    if (mode == 0)
        return "Default";
    else if (mode == 1)
        return "Altitude";
    else if (mode == 2)
        return "Rainbow pulse";
    else if (mode == 3)
        return "Blue gradient";
    else
        return "Unknown";
}
