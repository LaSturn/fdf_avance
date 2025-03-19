/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csu-ubuntu <csu-ubuntu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:19:39 by csturny           #+#    #+#             */
/*   Updated: 2025/03/18 11:18:47 by csu-ubuntu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "../mlx/mlx.h"
# include <X11/X.h> // pour inclure X.h : Constantes pour les événements X11 (défini dans X.h, ex. ButtonPress).
# include <X11/keysym.h> // pour inclure keysym : Code abstrait de la touche pressée (défini dans keysym.h, ex. XK_Escape).
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h> // !!! changer en ft_printf
# include <errno.h>
# include <string.h>  // Pour strerror()


/* ------------  LIBRARIES INCLUDED  ---------------------------------------- */
/*
# include <../include/color_config.h>
# include <../include/key_bindings_config.h>
# include <../include/mvmt_config.h>
# include <../include/error_msg.h>
*/

/* color_congif*/

/** @def B_YELLOW
 *  @brief This is a macro that holds the hexadecimal value for the color bright 
 * yellow.
 */
# define B_YELLOW	0xFFFF00

/** @def D_PURPLE
 *  @brief This is a macro that holds the hexadecimal value for the color dark 
 * purple.
 */
# define D_PURPLE	0x301934

/** @def OLIVE
 *  @brief This is a macro that holds the hexadecimal value for the color 
 * olive.
 */
# define OLIVE		0x808000

/** @def S_BROWN
 *  @brief This is a macro that holds the hexadecimal value for the color 
 * saddle brown.
 */
# define S_BROWN	0x8B4513

/** @def PURPLE
 *  @brief This is a macro that holds the hexadecimal value for the color 
 * purple.
 */
# define PURPLE		0x800080

/** @def WHITE
 *  @brief This is a macro that holds the hexadecimal value for the color 
 * white.
 */
# define WHITE		0xFFFFFF

# define BLUE 0x66CCFF // Pure blue

/** 
 * @brief The number of bits to shift to the right to isolate the red 
 * component of a color.
 */
# define RS			16

/** 
 * @brief The number of bits to shift to the right to isolate the green 
 * component of a color.
 */
# define GS			8

/** 
 * @brief The bitmask to apply to isolate the blue component of a color.
 */
# define BM			0xFF // vslrut s la base apres j ai change
//#define BM 8  // ✅ Au lieu de 0xFF (255), qui est trop grand // pas sur que ok!!!!!!


/**
 * @brief The number of bits to shift to isolate the alpha component 
 * in a 32-bit color value.
 * 
 * This macro represents the number of bits to shift a 32-bit color 
 * value to the right to isolate the alpha component. 
 * The color value is assumed to be in the format 0xRRGGBBAA, where RR 
 * represents the red component, GG the green component, 
 * BB the blue component, and AA the alpha component.
 */
# define AS			24


/* error_msh.h*/
/*
 *  @brief This macro holds an error message that is displayed when memory
 * allocation fails.
 */
# define MEM_ALL_ERR		"Unable to allocate memory."

/*
 *  @brief This macro holds an error message that is displayed when `ft_split`
 * fails to split a line into an array of strings.
 */
# define SPLIT_ERR			"Unable to split the line."

/**
 * @brief Error message for an empty map.
 */
# define EMPTY_MAP_ERROR	"The map is empty"

/**
 * @brief Error message for failed memory allocation in map.
 */
# define MAP_ALL_ERROR		"Failed to allocate memory for map"

/**
 * @brief Error message for failed memory allocation for display variables.
 */
//# define DISPLAY_ALL_ERR	"Failed to allocate memory for display variables"

/**
 * @brief Error message for invalid syntax.
 */
# define ARGS_ERR			"Invalid arguments. Syntax is './fdf map.fdf'"



/* KEY_BINDINGS_CONFIG_H*/

/* ------------  KEY BINDINGS CONFIGURATION  -------------------------------- */
/* The key codes are used in X11 windowing system. So this is valid in Ubuntu
 * and other Linux distributions. 
*/

/** 
 * @brief Key code for the Escape key. 
*/
# define KC_ESC	65307

/**
 * @brief Key code for the 'S' key.
 */
# define KC_S		115

/**
 * @brief Key code for the 'W' key.
 */
# define KC_W		119

/**
 * @brief Key code for the 'D' key.
 */
# define KC_D		100

/**
 * @brief Key code for the 'A' key.
 */
# define KC_A		97

/*
 * @brief Key code for 'R' key.
 */
# define KC_R		114

/*
 * @brief Key code for '1'.
 */
# define KC_1		49

/* 
 * @brief Key code for '2'. 
 * 
*/
# define KC_2		50

/*
 * @brief Key code for '3'. 
*/
# define KC_3		51

/*
 * @brief Key code for '4'. 
 * 
*/
# define KC_4		52

/* 
 * @brief Key code for '5'. 
 */
# define KC_5		53

/*
 * @brief Key code for '6'. 
 */
# define KC_6		54

/*
 * @brief Key code for '7'. 
 */
# define KC_7 		55	

/*
 * @brief Key code for '8'. 
 */
# define KC_8 		56

/*
 * @brief Key code for 'TAB'. 
 */
# define KC_TAB		65289

/*
 * @brief Key code for 'I'. 
 */
# define KC_I		105

/*
 * @brief Key code for 'O'. 
 */
# define KC_O		111

/**
 * @brief The event code for a key press event in the MiniLibX library.
 */
# define KPE			2
// P  pour point only
# define KC_P		112 // ok

// C use_altitude_color pour mettre en mode mettre set de couleur (pas couleur de base de la carte)
# define KC_C		99 // a tester
// rainbow mode
# define KC_V 118 // 'V' key

/*
 * @brief Key code for 't'. 
 */
# define KC_t        116 // lowercase t key for toggling tile culling

/*
 * @brief Key code for 'F'. 
 */
# define KC_F        102 // lowercase f key for resetting flattening factor

/* Key code for 'N' key to toggle movement mode */
# define KC_N        110

/**
 * @brief The event code for a key press event in the MiniLibX library.
 
# define KPM			(1L << 0)
*/

/**
 * @brief The event code for a window close event (also known as
 *  the destroy notify event) in the MiniLibX library.
 */
# define CE			17

/**
 * @brief The event mask for a window close event in the MiniLibX library.

# define CM			(1L << 17)
*/

/* MOVEMENTS_CONFIG_H */
/** @def TRANS
 *  @brief This macro defines the step size for translation movements.
 */
# define TRANS	1

/** @def ROT
 *  @brief This macro defines the step size for rotation movements.
 */
# define ROT	0.01

/** @def ZOOM
 *  @brief This macro defines the step size for zoom movements.
 */
# define ZOOM	0.1

/** @def FF
 *  @brief This macro defines the step size for flattening factor adjustments.
 */
# define FF		0.01

/**
 * @brief Scaling factor for the z-coordinate in 3D transformations.
 * 
 */
# define SF		10

/** 
 * @brief Reset view command description.
 */
# define RESET	"Reset View: Press 'R'"

/** 
 * @brief Move view command description.
 */
# define MOVE	"Move View: Use 'W', 'A', 'S', 'D'"

/** 
 * @brief Zoom in/out command description.
 */
# define ZOOMIO	"Zoom In/Out: Use 'I' / 'O'"

/** 
 * @brief Flattening factor command description.
 */
# define FLAT	"Flattening Factor: Use '7' / '8'"

/** 
 * @brief Rotate view around X-axis command description.
 */
# define ROTX	"Around X-Axis: Use '1' / '2'"

/** 
 * @brief Rotate view around Y-axis command description.
 */
# define ROTY	"Around Y-Axis: Use '3' / '4'"

/** 
 * @brief Rotate view around Z-axis command description.
 */
# define ROTZ	"Around Z-Axis: Use '5' / '6'"

/** 
 * @brief Change perspective command description.
 */
# define PERSP	"Toggle Isometric/Parallel: Press 'TAB'"

/** 
 * @brief Close application command description.
 */
# define CLOSE	"Close: Press 'ESC' or Click on 'X'"

/* ci dessous suite de fdf.h  */

/* ------------  HEXADECIMAL LOWERCASE DEFINITION  -------------------------- */
# define HEXALOW "0123456789abcdef"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
// The event code for a key press event in the MiniLibX library.
# define KPE		2 // KeyPress
//# define KeyPressMask  (1L << 0) //KeyPressMask Mask X11
//# define StructureNotifyMask (1L << 17)

/** @def ZOOM
 *  @brief This macro defines the step size for zoom movements.
 */
# define ZOOM	0.1
/* ------ STRUCTUR TYPEDEFS ---------------*/
/* ------------  INT MAX DEFINITION  ---------------------------------------- */
# define INT_MAX 2147483647

/* ------------  INT min DEFINITION  ---------------------------------------- */
# define INT_MIN -2147483648

/** @def TRANS
 *  @brief This macro defines the step size for translation movements.
 */
# define TRANS	1

#include <math.h>
# define FF		0.01


// message d erreur avec strerror
#define DISPLAY_ALL_ERR "Erreur d'affichage"


// typedef struct s_point t_point; structure representing a point in 3D space whith color
typedef struct s_point
{
	int x; // x is the x-coordinate of the point.
	int y; // y is the y-coordinate of the point.
	int z; // z is the z-coordinate of the point.
	int color; // color is the color of the point.
} t_point;


// typedef struct s_map t_map; structure representing 3D map
typedef struct s_map
{
	int map_width;  // width is the number of columns in the map. ou simplement largeur!!!!!!
	int map_height; // height is the number of rows in the map. ou simlement hauteur!!!!!!
	int min_z; // min_z is the minimum z-coordinate (or elevation) of the map.
	int max_z; // max_z is the maximum z-coordinate (or elevation) of the map.
	int **z_ij; //z_ij is defined as a 2D array of integers (int**) representing the z-coordinates (or elevations) of points on a 3D map.
	int **color;
	int is_color;
} t_map;

// structure representing an image data
typedef struct s_imagedata 
{
	void *img_ptr; // image pointer, is a pointer to the image object
	char *img_addr; // image address, is a ptr to the image data.
	int bpp; // bits per pixel, indicates the number of bits used to represent a pixel color.
	int size_line; // repesent the size of a line in bytes
	int endianness; 
} t_imagedata;


// Structure for tile-based culling optimization
typedef struct s_tile
{
    int start_x, start_y;     // Starting coordinates in the original map
    int end_x, end_y;         // Ending coordinates
    int visible;              // Visibility flag (0=invisible, 1=visible)
    int min_z, max_z;         // Z-range for potential further optimization
    int point_count;          // Number of points in this tile
} t_tile;

// structure representing the display parameters
typedef struct s_display 
{
	void *mlx_ptr; // mlx_ptr is a pointer to mlx object
	void *window_ptr; // window_ptr is a pointer to the window object
	t_map *map; // map is a pointer to the map data structure
	t_imagedata *img; // img is a pointer to the image data structure
	int shift_x; // shift_x is the horizontal shift of the map.
	int shift_y; // shift_y is the vertical shift of the map.
	float rot_x; // rot_x is the rotation angle around the x-axis.
	float rot_y; // rot_y is the rotation angle around the y-axis.
	float rot_z; // rot_z is the rotation angle around the z-axis.
	float zoom; // zoom is the zoom factor of the map.
	int is_isometric; // is_isometric is a flag to indicate if the map is in isometric projection.
	float flat_f; // "ff" for flat factor, is a factor to flatten the map.
	int needs_redraw;     // Optimize rendering
    t_point **transformed;// Precompute points array
    int points_only;      // Point cloud toggle
    int point_size;       // Adjustable point size
	int map_width;  // Add this line
    int map_height; // Add this line
	int use_altitude_colors; // 0 = default, 1 = altitude, 2 = rainbow pulse, 3 = rainbow shift
	float color_time;        // Add for animation

    // Map center coordinates (for centered zoom and rotation)
    float map_center_x;     // Center of the map in model coordinates
    float map_center_y;     
    float map_center_z;     

    // Movement mode (0 = small map mode, 1 = large map mode)
    int movement_mode;

    // Tile-based culling fields
    t_tile **tiles;           // 2D array of tiles
    int tile_size;            // Size of tiles (points per tile)
    int tiles_x;              // Number of tiles in x direction
    int tiles_y;              // Number of tiles in y direction
    int total_tiles;          // Total number of tiles
    int visible_tiles;        // Number of visible tiles (for statistics)
    int use_tile_culling;     // Flag to enable/disable tile culling (1 = enabled, 0 = disabled)
} t_display;

/* ------------  TILE-BASED CULLING CONFIG  ---------------------------------- */
# define DEFAULT_TILE_SIZE 64  // Default tile size (adjustable)
# define VISIBILITY_MARGIN 100 // Increased from 50 to 200 for smoother transitions during rotation

/* Movement scale factors for different map sizes */
# define SMALL_MAP_ROT_SCALE 1.0
# define SMALL_MAP_ZOOM_SCALE 0.5 
# define SMALL_MAP_TRANS_SCALE 1.0

/* Updated scaling factors for large maps - reduced for smoother control */
# define LARGE_MAP_ROT_SCALE 0.4     /* Further reduced for smoother rotation */
# define LARGE_MAP_ZOOM_SCALE 0.3    /* Further reduced for more precise zoom */
# define LARGE_MAP_TRANS_SCALE 0.8   /* Further reduced for less jumpy translation */

/* New scaling factors for very large maps like julia.fdf */
# define VERY_LARGE_MAP_ROT_SCALE 0.05   /* Extremely fine rotation control */
# define VERY_LARGE_MAP_ZOOM_SCALE 0.05  /* Extremely small zoom increments */
# define VERY_LARGE_MAP_TRANS_SCALE 0.5  /* Extremely slow translation */

/* Threshold for very large maps (in number of points) */
# define VERY_LARGE_MAP_THRESHOLD 100000

/* ------ FONCTIONS ---------------*/


/*---- main.c ----*/

int main(int argc, char *argv[]); // fonction principale
// void print_map_data(t_map *map); // imprimer les données de la carte


/*---- map_parse.c ----*/ // new
t_map *parse_map_dimensions(char *file_name);// Reads file once, sets dimensions, validates 
t_map *init_map(char *file_name); // a remplacer
int nbr_in_a_line(t_map *map, char *line); // compte le nombre de nombres dans une ligne
void	check_file_readable(const char *filename); //check_file_readable(const char *filename) – Verifies file accessibility.
int	check_map_format(char *file_name, t_map *map); // a modifier

/*---- map_data.c ----*/
void    get_map(char *file_name, t_map *map);
void    alloc_memory_for_map(t_map *map);
void    stock_map_values(char *file_name, t_map *map);
void    extract_map_data_z_color(int fd, t_map *map);
int     get_color(char *str, t_map *map);

/*---- display_init.c ----*/
int	start_mlx(t_map *map);
void initialize_display(t_display *display, t_map *map); // allocate memory for display variable for the map
int initialize_mlx(t_display *display);

//t_map *init_map(char *file_name); // initialise la carte à partir du fichier passé en argument
//void debug_display(t_display *display);
void	configure_default_display(t_display *display); // mettre les valeurs initialiser les valeurs pour display (donner valeur par defaut adapte a la carte a afficher)



/*---- render_points.c ----*/
void   render_transformed_map(t_display *display);
void plot_point(t_display *display, int x, int y, int color); // Point cloud rendering.

void	put_pixel_to_img(t_display *display, int x, int y, int color);
//void debug_pixel_data(int pixel, char *addr); // attention fonction debug
// a deplacer void	mlx_put_image_to_window(t_display display, int x, int y, int color);
void	display_control_info(t_display *display);
// ci dessous nouveau
//static void display_state(t_display *display, int *vertical_pos);
//static void display_controls(t_display *display, int *vertical_pos);
//static void display_rotation_and_exit(t_display *display, int *vertical_pos);
void display_control_info(t_display *display); // nouveau ploint d entrre
char *get_color_mode_str(int mode);

/*---- render_lines   ----*/
void    bresenham(t_display *dispay, t_point start, t_point end);
void	initialize_bresenham(t_point *start, t_point *end,	t_point *delta, t_point *sign);
void	update_transformed_points(t_display *display); // Precomputes points.

/*---- transform_points.c    ----*/
t_point apply_transformations(t_display *display, t_point point);
t_point create_map_point(int x, int y, t_display *display);
void	apply_isometric(t_display *display, int *x, int *y, int z);
void	apply_parallel(t_display *display, int *x, int *y, int z);  // New for parallel projection.
void    calculate_projected_bounds(t_display *display, int bounds[4], int use_current_zoom);
float   calculate_optimal_zoom(t_display *display, float margin);

/*---- transorm_rotation.c ----*/
void	apply_rot_x(t_display *display, int *y, int *z);
void	apply_rot_y(t_display *display, int *x, int *z);
void	apply_rot_z(t_display *display, int *x, int *y);
int get_max_int(int v1, int v2);


/*---- input_key.c ----*/
void    zoom_in_and_out(int keycode, t_display *display);
void    translation(int keycode, t_display *display);
void rotation(int keycode, t_display *display);
void    activ_ff(int keycode, t_display *display);
int handel_key_in(int keycode, t_display *display);
// a coder activ_ff(int keycode, t_display *display)


/*---- memory.c ----*/
void free_map_memory(t_map *map); // libere la memoire allouee pour la carte
void free_matrix(char **matrix); // libere la memoire allouee pour un tableau 2d
void    free_all_struct_display(t_display *vars); // free / destroy all variable of the struct s_display (destroy w et d free map et free img et free vars)


/*---- errors_msg.c ----*/
void exit_error_msg(char *error_message); // message d'erreur et quitte le programme
void error_msg(char *error_message); // message d'erreur sans quitter le programme
void exit_with_err(const char *error_type); 
void print_error_and_exit(const char *type, int use_errno);
void print_error_without_exit(const char *type, int use_errno);

/*---- color_utils.c   ----*/
int interpolate_color(t_point current, t_point start, t_point end, t_point delta);
double  get_percentage_in_range(int start, int end, int curr_val);
int interpolate_light(int start, int end, double percentage);
int get_color_by_altitude(t_display *display, int curr_z_val);

/*---- exit_utils.c    ----*/
int	shutdown_fdf(t_display *display);
int win_exit_and_cleanup(t_display *dispay);

/*---- map_utils.c    ----*/
void	ft_striter_tolower(char *str);
void	get_z_min_max(t_map *map);
int	get_abs_value(int value);

/*---- color_rainbow.c    ----*/
int hsv_to_rgb(float h, float s, float v);
int get_rainbow_pulse_color(t_display *display, int z);
int update_color_time(void *param);
// plus besoin int get_rainbow_shift_color(t_display *display, int z); // attention peut etre probleme avec fonction fmod?????
int get_blue_gradient_color(t_display *display, int z); // Replace rainbow shift

/*---- tile_culling.c ----*/
void    init_tile_system(t_display *display);
void    create_tiles(t_display *display);
int     is_tile_visible(t_display *display, t_tile *tile);
void    update_tile_visibility(t_display *display);
void    free_tile_system(t_display *display);
int     calculate_optimal_tile_size(t_display *display);

void calculate_map_center(t_display *display);












// a deplacer void debug_put_pixel_to_img(int x, int y, int color); // attention fonction de debugg






/*---- rotation.c    ----*/







/*---- test ----*/
/*
//void test_file(const char *filename); // a enlever
int main(void);
*/


#endif