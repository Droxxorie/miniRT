/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:37:26 by eraad             #+#    #+#             */
/*   Updated: 2025/12/08 15:15:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <vector.h>

/*
* origin: Ray origin point
* direction: Normalized direction vector
* min: Minimum t value (start of ray segment)
* max: Maximum t value (end of ray segment)
*/
typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
	t_real		min;
	t_real		max;
}	t_ray;

#endif