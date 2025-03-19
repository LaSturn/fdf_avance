/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_culling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csu-ubuntu <csu-ubuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:15:00 by csturny           #+#    #+#             */
/*   Updated: 2025/03/17 18:11:41 by csu-ubuntu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Calculate the optimal tile size based on map dimensions
 * This automatically adjusts tile size for performance optimization
 */
int calculate_optimal_tile_size(t_display *display)
{
    int total_points = display->map_width * display->map_height;
    int optimal_size;
    
    // Target a reasonable number of tiles based on map size
    // For small maps (<1000 points), use larger tiles or no tiles
    // For large maps, use smaller tiles for better culling
    if (total_points < 1000) {
        // For very small maps, use a single tile or very few tiles
        optimal_size = get_max_int(display->map_width, display->map_height);
    } else if (total_points < 10000) {
        // For medium maps, target around 16-64 tiles total
        optimal_size = sqrt(total_points / 25); // ~25 tiles
    } else if (total_points < 100000) {
        // For larger maps, target 64-256 tiles
        optimal_size = sqrt(total_points / 100); // ~100 tiles
    } else {
        // For very large maps, use smaller tiles
        optimal_size = sqrt(total_points / 400); // ~400 tiles
    }
    
    // Ensure tile size is at least 16 points and at most 128 points
    if (optimal_size < 16)
        optimal_size = 16;
    if (optimal_size > 128)
        optimal_size = 128;
    
    ft_printf("Map size: %dx%d (%d points) → Optimal tile size: %d\n", 
              display->map_width, display->map_height, 
              total_points, optimal_size);
              
    return optimal_size;
}

/**
 * Initializes the tile-based culling system
 * This is the main entry point for setting up the tile structure
 */
void init_tile_system(t_display *display)
{
    int i;

    // Calculate optimal tile size based on map dimensions
    display->tile_size = calculate_optimal_tile_size(display);
    
    // Calculate how many tiles we need based on map dimensions and tile size
    display->tiles_x = (display->map_width + display->tile_size - 1) / display->tile_size;
    display->tiles_y = (display->map_height + display->tile_size - 1) / display->tile_size;
    display->total_tiles = display->tiles_x * display->tiles_y;
    
    // Allocate memory for the 2D array of tiles
    display->tiles = (t_tile **)ft_calloc(display->tiles_y, sizeof(t_tile *));
    if (!display->tiles)
        print_error_and_exit("Failed to allocate tiles array", 0);
    
    // Allocate each row of tiles
    i = 0;
    while (i < display->tiles_y)
    {
        display->tiles[i] = (t_tile *)ft_calloc(display->tiles_x, sizeof(t_tile));
        if (!display->tiles[i])
        {
            while (--i >= 0)
                free(display->tiles[i]);
            free(display->tiles);
            display->tiles = NULL;
            print_error_and_exit("Failed to allocate tiles row", 0);
        }
        i++;
    }

    // Create and initialize each tile
    create_tiles(display);
    ft_printf("Tile system initialized: %d tiles (%d x %d), tile size: %d\n", 
              display->total_tiles, display->tiles_x, display->tiles_y, display->tile_size);
}

/**
 * Creates and initializes all tiles based on the map dimensions
 */
void create_tiles(t_display *display)
{
    int i, j;
    int x, y;
    t_tile *tile;
    
    i = 0;
    while (i < display->tiles_y)
    {
        j = 0;
        while (j < display->tiles_x)
        {
            tile = &display->tiles[i][j];
            
            // Calculate tile coordinates in original map space
            tile->start_x = j * display->tile_size;
            tile->start_y = i * display->tile_size;
            tile->end_x = tile->start_x + display->tile_size - 1;
            tile->end_y = tile->start_y + display->tile_size - 1;
            
            // Clamp to map boundaries
            if (tile->end_x >= display->map_width)
                tile->end_x = display->map_width - 1;
            if (tile->end_y >= display->map_height)
                tile->end_y = display->map_height - 1;
            
            // Calculate point count in this tile
            tile->point_count = (tile->end_x - tile->start_x + 1) * 
                               (tile->end_y - tile->start_y + 1);
            
            // Calculate min/max z values for this tile
            tile->min_z = INT_MAX;
            tile->max_z = INT_MIN;
            
            y = tile->start_y;
            while (y <= tile->end_y)
            {
                x = tile->start_x;
                while (x <= tile->end_x)
                {
                    // Find min/max z values
                    if (display->map->z_ij[y][x] < tile->min_z)
                        tile->min_z = display->map->z_ij[y][x];
                    if (display->map->z_ij[y][x] > tile->max_z)
                        tile->max_z = display->map->z_ij[y][x];
                    x++;
                }
                y++;
            }
            
            // Default to visible for now (will be updated later)
            tile->visible = 1;
            j++;
        }
        i++;
    }
}

/**
 * Determines if a tile is potentially visible after transformation
 * 
 * The function applies the same transformation pipeline as the main renderer
 * to representative points of the tile (corners and extremes), and checks if
 * any of them fall within the screen bounds plus a margin.
 */
int is_tile_visible(t_display *display, t_tile *tile)
{
    // Define an effective margin - larger during rotation for smoother transitions
    int effective_margin = VISIBILITY_MARGIN;
    
    // Increase the margin significantly if any rotation is happening
    // This prevents "popping" of tiles during rotation
    if (fabs(display->rot_x) > 0.001 || fabs(display->rot_y) > 0.001 || fabs(display->rot_z) > 0.001) {
        effective_margin = VISIBILITY_MARGIN * 2; // Double margin during rotation
    }
    
    // Add corners and midpoints of edges for better visibility detection
    int test_points[12][3] = {
        // 8 corners of the 3D tile box
        {tile->start_x, tile->start_y, tile->min_z},  // Corner 1, bottom
        {tile->end_x, tile->start_y, tile->min_z},    // Corner 2, bottom
        {tile->start_x, tile->end_y, tile->min_z},    // Corner 3, bottom
        {tile->end_x, tile->end_y, tile->min_z},      // Corner 4, bottom
        {tile->start_x, tile->start_y, tile->max_z},  // Corner 1, top
        {tile->end_x, tile->start_y, tile->max_z},    // Corner 2, top
        {tile->start_x, tile->end_y, tile->max_z},    // Corner 3, top
        {tile->end_x, tile->end_y, tile->max_z},      // Corner 4, top
        
        // 4 midpoints of edges for better detection
        {(tile->start_x + tile->end_x)/2, tile->start_y, (tile->min_z + tile->max_z)/2}, // Mid of bottom front
        {(tile->start_x + tile->end_x)/2, tile->end_y, (tile->min_z + tile->max_z)/2},   // Mid of bottom back
        {tile->start_x, (tile->start_y + tile->end_y)/2, (tile->min_z + tile->max_z)/2}, // Mid of left side
        {tile->end_x, (tile->start_y + tile->end_y)/2, (tile->min_z + tile->max_z)/2}    // Mid of right side
    };
    
    // Test each point
    for (int i = 0; i < 12; i++) {
        int x = test_points[i][0];
        int y = test_points[i][1];
        int z = test_points[i][2];
        
        // Apply same transformations as in the render pipeline
        float centered_x = x - display->map_center_x;
        float centered_y = y - display->map_center_y;
        float centered_z = z - display->map_center_z;
        
        int tx = centered_x * display->zoom;
        int ty = centered_y * display->zoom;
        int tz = centered_z * (display->zoom / SF) * display->flat_f;
        
        // Apply rotations
        apply_rot_x(display, &ty, &tz);
        apply_rot_y(display, &tx, &tz);
        apply_rot_z(display, &tx, &ty);
        
        // Translate back
        tx += display->map_center_x * display->zoom;
        ty += display->map_center_y * display->zoom;
        
        // Apply projection
        if (display->is_isometric)
            apply_isometric(display, &tx, &ty, tz);
        else
            apply_parallel(display, &tx, &ty, tz);
        
        // Apply translation
        tx += display->shift_x;
        ty += display->shift_y;
        
        // Check if the point is within view bounds (with margin)
        if (tx >= -effective_margin && tx < WIN_WIDTH + effective_margin &&
            ty >= -effective_margin && ty < WIN_HEIGHT + effective_margin) {
            return 1; // Tile is visible
        }
    }
    
    return 0; // Tile is not visible
}

/**
 * Updates visibility status for all tiles
 * 
 * This function applies the visibility test to each tile and
 * keeps track of how many tiles are considered visible.
 */
void update_tile_visibility(t_display *display)
{
    int i, j;
    int visible_count = 0;
    
    i = 0;
    while (i < display->tiles_y)
    {
        j = 0;
        while (j < display->tiles_x)
        {
            // Apply visibility test to each tile
            display->tiles[i][j].visible = is_tile_visible(display, &display->tiles[i][j]);
            if (display->tiles[i][j].visible)
                visible_count++;
            j++;
        }
        i++;
    }
    
    display->visible_tiles = visible_count;
    ft_printf("Visibility updated: %d of %d tiles visible (%.1f%%)\n",
           visible_count, display->total_tiles,
           (float)visible_count * 100.0 / display->total_tiles);
}

/**
 * Frees all tile-related memory
 */
void free_tile_system(t_display *display)
{
    int i;
    
    if (!display || !display->tiles)
        return;
        
    i = 0;
    while (i < display->tiles_y)
    {
        if (display->tiles[i])
            free(display->tiles[i]);
        i++;
    }
    
    free(display->tiles);
    display->tiles = NULL;
}

/**
 * Draws tile boundaries for debugging purposes
 * This function draws a rectangle around each visible tile
 */
void draw_tile_boundaries(t_display *display)
{
    int i, j;
    int color = 0xFF0000; // Red for tile boundaries
    
    i = 0;
    while (i < display->tiles_y)
    {
        j = 0;
        while (j < display->tiles_x)
        {
            if (display->tiles[i][j].visible)
            {
                // Get tile corner points
                t_point p1, p2, p3, p4;
                
                // Create points for the four corners
                p1 = create_map_point(display->tiles[i][j].start_x, 
                                     display->tiles[i][j].start_y, display);
                p2 = create_map_point(display->tiles[i][j].end_x, 
                                     display->tiles[i][j].start_y, display);
                p3 = create_map_point(display->tiles[i][j].end_x, 
                                     display->tiles[i][j].end_y, display);
                p4 = create_map_point(display->tiles[i][j].start_x, 
                                     display->tiles[i][j].end_y, display);
                
                // Transform points
                p1 = apply_transformations(display, p1);
                p2 = apply_transformations(display, p2);
                p3 = apply_transformations(display, p3);
                p4 = apply_transformations(display, p4);
                
                // Override color
                p1.color = p2.color = p3.color = p4.color = color;
                
                // Draw tile boundary
                bresenham(display, p1, p2);
                bresenham(display, p2, p3);
                bresenham(display, p3, p4);
                bresenham(display, p4, p1);
            }
            j++;
        }
        i++;
    }
}
