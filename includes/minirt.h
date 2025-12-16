/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:44 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 20:19:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* minirt.h                                           :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/12/07 14:10:41 by eraad             #+#    #+#             */
/* Updated: 2025/12/16 11:30:00 by eraad            ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* --- Standard Libraries --- */
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* --- External Libraries --- */
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

/* --- Core Definitions --- */
# include "macros.h"
# include "structures.h"

/* --- Modules Prototypes --- */
# include "errors.h"
# include "graphics.h"
# include "inputs.h"
# include "maths.h"
# include "parsing.h"
# include "raytracer.h"
# include "scene.h"
# include "utils.h"

#endif