// a midifier

#ifndef COLOR_CONFIG_H
# define COLOR_CONFIG_H

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

/* ------------  STRUCT TYPEDEFS  ------------------------------------------- */

typedef struct s_point		t_point;
typedef struct s_map		t_map;
typedef struct s_imagedata	t_imagedata;
typedef struct s_display	t_display;

#endif