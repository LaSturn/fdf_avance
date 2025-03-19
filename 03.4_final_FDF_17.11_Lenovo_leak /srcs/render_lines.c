/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csu-ubuntu <csu-ubuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:14:20 by csturny           #+#    #+#             */
/*   Updated: 2025/03/18 21:37:43 by csu-ubuntu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void bresenham(t_display *display, t_point start, t_point end) {
    t_point current;
    t_point sign;
    t_point delta;
    int line;
    int tmp;

    initialize_bresenham(&start, &end, &delta, &sign);
    line = delta.x - delta.y;
    current = start;
    while (current.x != end.x || current.y != end.y) {
        current.color = interpolate_color(current, start, end, delta);
        put_pixel_to_img(display, current.x, current.y, current.color);
        tmp = line * 2;
        if (tmp > -delta.y) {
            line -= delta.y;
            current.x += sign.x;
        }
        if (tmp < delta.x) {
            line += delta.x;
            current.y += sign.y;
        }
    }
}


// ok verifie
// ici initialiattion pour l alogo
void	initialize_bresenham(t_point *start, t_point *end,	t_point *delta, t_point *sign)
{
	delta->x = get_abs_value(end->x - start->x);
	delta->y = get_abs_value(end->y - start->y);
	sign->x = -1;
	sign->y = -1;
	if (start->x < end->x)
		sign->x = 1;
	if (start->y < end->y)
		sign->y = 1;
}
/*
// fonction debug a supprimer a la fin
void debug_put_pixel_to_img(int x, int y, int color)
{
    printf("Put pixel at (%d, %d) with color 0x%X\n", x, y, color);
}
*/

/* new */
void update_transformed_points(t_display *display)
{
    int y;
    int x;
    int tile_i, tile_j;
    int total_points_transformed = 0;
    int total_points = display->map_height * display->map_width;

    // Update tile visibility first
    update_tile_visibility(display);

    // Only transform points in visible tiles
    tile_i = 0;
    while (tile_i < display->tiles_y) {
        tile_j = 0;
        while (tile_j < display->tiles_x) {
            if (display->tiles[tile_i][tile_j].visible) {
                // Get tile boundaries
                int start_y = display->tiles[tile_i][tile_j].start_y;
                int end_y = display->tiles[tile_i][tile_j].end_y;
                int start_x = display->tiles[tile_i][tile_j].start_x;
                int end_x = display->tiles[tile_i][tile_j].end_x;
                
                // Transform points in this tile
                y = start_y;
                while (y <= end_y) {
                    x = start_x;
                    while (x <= end_x) {
                        display->transformed[y][x] = apply_transformations(display, create_map_point(x, y, display));
                        total_points_transformed++;
                        x++;
                    }
                    y++;
                }
            }
            tile_j++;
        }
        tile_i++;
    }
    
    ft_printf("Transformed %d of %d points (%.1f%%)\n", 
           total_points_transformed, total_points,
           (float)total_points_transformed * 100.0 / total_points);
}

void render_transformed_map(t_display *display)
{
    int x;
    int y;
    int tile_i, tile_j;
    
    if (!display->needs_redraw)
        return;
        
    ft_bzero(display->img->img_addr, WIN_HEIGHT * WIN_WIDTH * (display->img->bpp / 8));
    
    if (display->zoom) {
        // If tile culling is enabled, use the tile-based rendering approach
        if (display->use_tile_culling) {
            // Update tile visibility before rendering
            update_tile_visibility(display);
            
            // Only update points in visible tiles
            tile_i = 0;
            while (tile_i < display->tiles_y) {
                tile_j = 0;
                while (tile_j < display->tiles_x) {
                    if (display->tiles[tile_i][tile_j].visible) {
                        // Get tile boundaries
                        int start_y = display->tiles[tile_i][tile_j].start_y;
                        int end_y = display->tiles[tile_i][tile_j].end_y;
                        int start_x = display->tiles[tile_i][tile_j].start_x;
                        int end_x = display->tiles[tile_i][tile_j].end_x;
                        
                        // Update transformed points only for this tile
                        y = start_y;
                        while (y <= end_y) {
                            x = start_x;
                            while (x <= end_x) {
                                display->transformed[y][x] = apply_transformations(display, create_map_point(x, y, display));
                                x++;
                            }
                            y++;
                        }
                    }
                    tile_j++;
                }
                tile_i++;
            }
            
            // Render lines/points for visible tiles
            y = -1;
            while (++y < display->map_height) {
                x = -1;
                while (++x < display->map_width) {
                    // Find which tile this point belongs to
                    tile_i = y / display->tile_size;
                    tile_j = x / display->tile_size;
                    
                    // Only render if the tile is visible
                    if (tile_i < display->tiles_y && tile_j < display->tiles_x && 
                        display->tiles[tile_i][tile_j].visible) {
                        
                        if (display->points_only) {
                            plot_point(display, display->transformed[y][x].x, 
                                       display->transformed[y][x].y, 
                                       display->transformed[y][x].color);
                        } else {
                            // Draw horizontal line if the next point is in same row
                            if (x < display->map_width - 1) {
                                // Check if the next point's tile is also visible
                                int next_tile_j = (x + 1) / display->tile_size;
                                if (next_tile_j == tile_j || 
                                    (next_tile_j < display->tiles_x && 
                                     display->tiles[tile_i][next_tile_j].visible)) {
                                    bresenham(display, display->transformed[y][x], 
                                             display->transformed[y][x + 1]);
                                }
                            }
                            
                            // Draw vertical line if the next point is in same column
                            if (y < display->map_height - 1) {
                                // Check if the next point's tile is also visible
                                int next_tile_i = (y + 1) / display->tile_size;
                                if (next_tile_i == tile_i || 
                                    (next_tile_i < display->tiles_y && 
                                     display->tiles[next_tile_i][tile_j].visible)) {
                                    bresenham(display, display->transformed[y][x], 
                                             display->transformed[y + 1][x]);
                                }
                            }
                        }
                    }
                }
            }
        }
        // If tile culling is disabled, render all points
        else {
            // Transform all points
            y = 0;
            while (y < display->map_height) {
                x = 0;
                while (x < display->map_width) {
                    display->transformed[y][x] = apply_transformations(display, create_map_point(x, y, display));
                    x++;
                }
                y++;
            }
            
            // Render all points/lines
            y = 0;
            while (y < display->map_height) {
                x = 0;
                while (x < display->map_width) {
                    if (display->points_only) {
                        plot_point(display, display->transformed[y][x].x, 
                                  display->transformed[y][x].y, 
                                  display->transformed[y][x].color);
                    } else {
                        // Draw horizontal line
                        if (x < display->map_width - 1) {
                            bresenham(display, display->transformed[y][x], 
                                     display->transformed[y][x + 1]);
                        }
                        
                        // Draw vertical line
                        if (y < display->map_height - 1) {
                            bresenham(display, display->transformed[y][x], 
                                     display->transformed[y + 1][x]);
                        }
                    }
                    x++;
                }
                y++;
            }
        }
    }
    
    mlx_put_image_to_window(display->mlx_ptr, display->window_ptr, 
                           display->img->img_ptr, 0, 0);
    display_control_info(display);
    display->needs_redraw = 0;
}

void plot_point(t_display *display, int x, int y, int color)
{
	int	size;
	int dy;
	int dx;

	size = display->point_size;
	dy = -size;	
	while (dy <= size)
	{
		dx = -size;
		while (dx <= size)
		{
			if (x + dx >= 0 && x + dx < WIN_WIDTH && y + dy >= 0 && y +dy < WIN_HEIGHT)
				put_pixel_to_img(display, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}	
}
