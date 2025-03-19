/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvmt_config.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturny <csturny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:31:41 by csturny           #+#    #+#             */
/*   Updated: 2025/01/27 17:31:54 by csturny          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


// a refaire!!!!!!
#ifndef MOVEMENTS_CONFIG_H
# define MOVEMENTS_CONFIG_H

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

/* ------------  STRUCT TYPEDEFS  ------------------------------------------- */

typedef struct s_point		t_point;
typedef struct s_map		t_map;
typedef struct s_imagedata	t_imagedata;
typedef struct s_display	t_display;

#endif