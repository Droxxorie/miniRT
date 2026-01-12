/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:42:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 14:59:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

//* ========================================================================= */
//*                                STANDARD LIBRARIES                         */
//* ========================================================================= */
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>

//* ========================================================================= */
//*                                EXTERNAL LIBRARIES                         */
//* ========================================================================= */
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

//* ========================================================================= */
//*                                CORE                                       */
//* ========================================================================= */
# include "macros_bonus.h"
# include "structs/s_base_bonus.h"
# include "structs/s_math_bonus.h"
# include "structs/s_ray_bonus.h"
# include "structs/s_object_bonus.h"
# include "structs/s_scene_bonus.h"

# include "errors_bonus.h"
# include "maths_bonus.h"
# include "acceleration_bonus.h"
# include "graphics_bonus.h"
# include "ui_bonus.h"
# include "parsing_bonus.h"
# include "scene_bonus.h"
# include "modifiers_bonus.h"
# include "inputs_bonus.h"
# include "utils_bonus.h"
# include "./raytracer/raytracer_bonus.h"

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
void		destroy_scene(t_scene *scene);
t_status	clean_exit(t_scene *scene, t_status status);
void		setup_save_mode(int argc, char **argv, t_scene *scene);
void		save_image_to_bmp(t_scene *scene);

#endif