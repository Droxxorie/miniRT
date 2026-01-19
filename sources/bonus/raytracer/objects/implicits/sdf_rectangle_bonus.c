/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_rectangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:08:01 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:25:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_rectangle(t_point3 p)
{
	t_vec3	d;
	t_vec3	abs_p;
	t_real	distance;

	abs_p = (t_vec3){fabs(p.x), fabs(p.y), fabs(p.z)};
	d = vec3_add(abs_p, (t_vec3){-0.5, -SDF_THICKNESS, -0.5});
	distance = vec3_len((t_vec3){fmax(d.x, 0.0), fmax(d.y, 0.0), fmax(d.z,
				0.0)}) + fmin(fmax(fmax(d.x, d.y), d.z), 0.0);
	return (distance);
}
