/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_dir_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:59:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 17:52:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static	t_vec3	random_in_unit_sphere(unsigned int *seed)
{
	t_real	theta;
	t_real	phi;
	t_real	r;
	t_real	u;
	t_real	v;

	u = random_double(seed);
	v = random_double(seed);
	theta = TWO_PI * u;
	phi = acos(2.0 * v - 1.0);
	r = cbrt(random_double(seed));
	return ((t_vec3){
		r * sin(phi) * cos(theta),
		r * sin(phi) * sin(theta),
		r * cos(phi)
	});
}

t_vec3	random_hemisphere_dir(t_vec3 normal, unsigned int *seed)
{
	t_vec3	rand_dir;

	rand_dir = random_in_unit_sphere(seed);
	if (vec3_dot(rand_dir, normal) > 0.0)
		return (rand_dir);
	return (vec3_scale(rand_dir, -1.0));
}
