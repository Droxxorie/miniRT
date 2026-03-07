/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:28:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 00:43:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_BONUS_H
# define MACROS_BONUS_H

//* ========================================================================= */
//*                                MATHS & LOGIC                              */
//* ========================================================================= */
# define EPSILON 1e-4f
# define PI 3.14159265359f
# define INV_PI 0.31830988618f
# define INV_TWO_PI 0.15915494309f
# define TWO_PI 6.28318530718f
# define INV_255 0.00392156862f
# define INV_SQRT_2 0.70710678118f

# define MOVE_SPEED 2.5
# define ROT_SPEED 0.2
# define RESIZE_SPEED 0.1

# define STEP_MOVE 1.0
# define STEP_ROT 1.0

# define DEF_WINDOW_WIDTH 720
# define DEF_WINDOW_HEIGHT 480
# define MAX_WINDOW_WIDTH 10000
# define MAX_WINDOW_HEIGHT 10000

# define MAX_LIGHTS 10
# define MAX_CAMERAS 10
# define MAX_OBJECTS 100

# define PLANE_SCALE 2000.0

# define BVH_PADDING 0.005
# define SDF_THICKNESS 0.001
# define MAX_SDF_STEPS 256
# define MAX_SDF_DISTANCE 1000.0

# define WHITESPACE_CHARS " \t\n\v\f\r"

# define SHADOW_SAMPLES 64
# define LIGHT_RADIUS 0.5
# define SDF_MAX_STEPS 64

# define AO_STEPS 4
# define AO_STEP_SIZE 0.5
# define AO_INTENSITY 0.2
# define AO_SCALE_DECAY 0.85

# define AO_SAMPLES 64
# define AO_RADIUS 1.5

# define TILE_SIZE 32
# define BORDER_COLOR 0xFF8000
# define DISPLAY_INTERVAL_US 100000

# define MAX_REFLECTION_DEPTH 50
# define ROULETTE_START_DEPTH 15

//* ========================================================================= */
//*                                KEYS (LINUX/X11)                           */
//* ========================================================================= */
//* --- Events --- */
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
// # define ON_MOUSEUP 5
# define ON_DESTROY 17

# define MASK_NO_EVENT 0L
# define MASK_KEY_PRESS 1L
# define MASK_KEY_RELEASE 2L
# define MASK_BUTTON_PRESS 4L
// # define MASK_BUTTON_RELEASE 8L

//* --- Mouse --- */
# define LEFT_CLICK 1
// # define RIGHT_CLICK 3
// # define MIDDLE_CLICK 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5

//* --- Numpad --- */
// # define KEY_PLUS 65451
// # define KEY_MINUS 65453
// # define KEY_NP_0 65456
// # define KEY_NP_1 65457
// # define KEY_NP_2 65458
// # define KEY_NP_3 65459
// # define KEY_NP_4 65460
// # define KEY_NP_5 65461
// # define KEY_NP_6 65462
// # define KEY_NP_7 65463
// # define KEY_NP_8 65464
// # define KEY_NP_9 65465

//* --- Special Keys --- */
# define KEY_ESC 65307
# define KEY_TAB 65289
# define KEY_SPACE 32
# define KEY_ENTER 65293
# define KEY_SHIFT_L 65505
# define KEY_SHIFT_R 65506
# define KEY_CTRL_L 65507
# define KEY_CTRL_R 65508
# define KEY_ALT_L 65513
# define KEY_ALT_R 65514

//* --- Arrows --- */
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

//* --- Letters --- */
// # define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_Z 122
# define KEY_L 108
# define KEY_C 99
# define KEY_T 116
# define KEY_H 104
# define KEY_R 114
# define KEY_I 105

//* --- Numbers --- */
# define KEY_1 38
# define KEY_2 233
# define KEY_3 34
# define KEY_4 39
# define KEY_5 40
# define KEY_6 45
# define KEY_7 232
# define KEY_8 95
// # define KEY_9 231
// # define KEY_0 224

//* ========================================================================= */
//*                                TEXT                                       */
//* ========================================================================= */
//* --- STYLE --- */
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"

//* --- COLORS --- */
# define BLACK "\033[30m"
# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define W "\033[37m"

//* --- BOLD COLORS --- */
# define B_R "\033[1;31m"
# define B_G "\033[1;32m"
# define B_Y "\033[1;33m"
# define B_B "\033[1;34m"
# define B_MAGENTA "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define B_W "\033[1;37m"

#endif