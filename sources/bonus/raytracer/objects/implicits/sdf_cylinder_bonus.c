/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:15:03 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:25:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_cylinder(t_point3 p)
{
	t_vec2	d;

	d.x = vec2_len((t_vec2){p.x, p.z}) - 1.0;
	d.y = fabsf(p.y) - 0.5;
	return (fminf(fmaxf(d.x, d.y), 0.0) + vec2_len((t_vec2){fmaxf(d.x, 0.0),
			fmaxf(d.y, 0.0)}));
}
