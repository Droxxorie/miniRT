/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:10:41 by eraad             #+#    #+#             */
/*   Updated: 2025/12/09 20:19:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

# include "libft.h"
# include "mlx.h"

# define SAVE_FLAG "--save"

# include "utils.h"
# include "error.h"
# include "constants.h"
# include "dispatch.h"
# include "vector.h"
# include "buffer.h"
# include "matrix.h"
# include "ray.h"
# include "shapes.h"
# include "entities.h"
# include "engine.h"

#endif