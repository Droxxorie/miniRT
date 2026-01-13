/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_box_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 21:38:24 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:52:35 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_box(t_point3 p)
{
	t_vec3	d;
	t_vec3	abs_p;
	t_real	distance;

	abs_p = (t_vec3){fabs(p.x), fabs(p.y), fabs(p.z)};
	d = vec3_add_scalar(abs_p, -0.5);
	distance = vec3_len((t_vec3){fmax(d.x, 0.0), fmax(d.y, 0.0), fmax(d.z,
				0.0)}) + fmin(fmax(d.x, fmax(d.y, d.z)), 0.0);
	return (distance);
}
