/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:42:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 18:52:19 by eraad            ###   ########.fr       */
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

//* ========================================================================= */
//*                                EXTERNAL LIBRARIES                         */
//* ========================================================================= */
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

//* ========================================================================= */
//*                                CORE                                       */
//* ========================================================================= */
# include "macros_bonus.h"
# include "structures_bonus.h"

//* ========================================================================= */
//*                                MODULES                                    */
//* ========================================================================= */
# include "errors_bonus.h"
# include "graphics_bonus.h"
# include "inputs_bonus.h"
# include "maths_bonus.h"
# include "parsing_bonus.h"
# include "raytracer_bonus.h"
# include "scene_bonus.h"
# include "utils_bonus.h"

#endif