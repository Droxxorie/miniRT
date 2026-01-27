/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_cosine_dir_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:16:27 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 16:19:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	random_cosine_dir(t_vec3 n, unsigned int *seed)
{
	t_real	r[2];
	t_real	phi;
	t_vec3	u;
	t_vec3	t;
	t_vec3	b;

	r[0] = random_double(seed);
	r[1] = random_double(seed);
	phi = 2.0 * PI * r[0];
	u.x = cos(phi) * sqrt(r[1]);
	u.y = sin(phi) * sqrt(r[1]);
	u.z = sqrt(1 - r[1]);
	build_onb(n, &t, &b);
	return (vec3_add(vec3_add(vec3_scale(t, u.x), vec3_scale(b, u.y)),
			vec3_scale(n, u.z)));
}
