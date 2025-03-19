/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_rainbow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:25:38 by csturny           #+#    #+#             */
/*   Updated: 2025/03/13 18:27:13 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "fdf.h"
// HSV-to-RGB Conversion (rainbow effect)
int hsv_to_rgb(float h, float s, float v)
{
    float r = 0, g = 0, b = 0;
    float c = v * s; // Chroma
    float h_prime = h / 60.0;
    float x = c * (1 - fabs(fmod(h_prime, 2) - 1));
    float m = v - c;

    if (h_prime >= 0 && h_prime < 1)
	{
        r = c; g = x; b = 0;
    }
	else if (h_prime < 2)
	{
        r = x; g = c; b = 0;
    }
	else if (h_prime < 3)
	{
        r = 0; g = c; b = x;
    }
	else if (h_prime < 4)
	{
        r = 0; g = x; b = c;
    }
	else if (h_prime < 5)
	{
        r = x; g = 0; b = c;
    }
	else if (h_prime < 6)
	{
        r = c; g = 0; b = x;
    }
    r += m; g += m; b += m;
    return ((int)(r * 255) << RS) | ((int)(g * 255) << GS) | ((int)(b * 255));
}


int update_color_time(void *param)
{
    t_display *display = (t_display *)param;
    if (display->use_altitude_colors == 2) // Only rainbow pulse needs animation
    {
        display->color_time += 2.0;
        if (display->color_time >= 360.0)
            display->color_time -= 360.0;
        display->needs_redraw = 1;
        render_transformed_map(display);
    }
    return (0);
}

int get_rainbow_pulse_color(t_display *display, int z) {
    float hue;
    float percentage = get_percentage_in_range(display->map->min_z, display->map->max_z, z);
    hue = 360.0 * percentage + display->color_time;
    hue = fmod(hue, 360.0);
    //ft_printf("Pulse: z=%d, min_z=%d, max_z=%d, percentage=%.2f, hue=%.2f\n", z, display->map->min_z, display->map->max_z, percentage, hue);
    return hsv_to_rgb(hue, 1.0, 1.0);
}
// blue new
int get_blue_gradient_color(t_display *display, int z) {
    double percentage;
    int r, g, b;

    // Calculate percentage of z within min_z and max_z range
    percentage = get_percentage_in_range(display->map->min_z, display->map->max_z, z);

    // Blue gradient: Transition from dark blue (0x000066) to light blue (0x66CCFF)
    r = interpolate_light(0x00, 0x66, percentage); // Red: 0 to 102
    g = interpolate_light(0x00, 0xCC, percentage); // Green: 0 to 204
    b = interpolate_light(0x66, 0xFF, percentage); // Blue: 102 to 255

    return (r << RS) | (g << GS) | b;
}

/* ci-dessous color_utils.c*/

// ok verifie
int interpolate_color(t_point current, t_point start, t_point end, t_point delta)
{
	int r;
	int g;
	int b;
	double percentage;
	
	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = get_percentage_in_range(start.x, end.x, current.x);
	else 
		percentage = get_percentage_in_range(start.y, end.y, current.y);
	r = interpolate_light((start.color >> RS) & BM, (end.color >> RS) & BM, percentage);
	g = interpolate_light((start.color >> GS) & BM, (end.color >> GS) & BM, percentage);
	b = interpolate_light(start.color & BM, end.color & BM, percentage);
	return ((r << RS) | (g << GS) | b);
}



// a modifier celle du haut
double get_percentage_in_range(int start, int end, int curr_val)
{
    double range = end - start;
    double position = curr_val - start;
    if (!range)
        return (1.0);
    double percentage = position / range;
    //ft_printf("Percentage: start=%d, end=%d, curr=%d, range=%.2f, pos=%.2f, pct=%.2f\n", start, end, curr_val, range, position, percentage);
    return (percentage);
}

// ok verifie
int interpolate_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}
// ok verifie
int get_color_by_altitude(t_display *display, int curr_z_val)
{
	double	percentage;
	percentage = get_percentage_in_range(display->map->min_z, display->map->max_z, curr_z_val);
	if (percentage < 0.1)
		return (D_PURPLE);
	else if (percentage < 0.3)
		return (S_BROWN);
	else if (percentage < 0.5)
		return (OLIVE);
	else if (percentage < 0.7)
		return (B_YELLOW);
	else
		return (PURPLE);
}