/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:15:03 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:52:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_cylinder(t_point3 p)
{
	t_vec2	d;

	d.x = vec2_len((t_vec2){p.x, p.z}) - 1.0;
	d.y = fabs(p.y) - 0.5;
	return (fmin(fmax(d.x, d.y), 0.0) + vec2_len((t_vec2){fmax(d.x, 0.0),
			fmax(d.y, 0.0)}));
}
