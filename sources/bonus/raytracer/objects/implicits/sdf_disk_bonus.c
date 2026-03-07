/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_disk_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:07:51 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 15:24:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_disk(t_point3 p)
{
	t_vec2	d;

	d.x = vec2_len((t_vec2){p.x, p.z}) - 1.0;
	d.y = fabsf(p.y) - SDF_THICKNESS;
	return (fminf(fmaxf(d.x, d.y), 0.0) + vec2_len((t_vec2){fmaxf(d.x, 0.0),
			fmaxf(d.y, 0.0)}));
}
