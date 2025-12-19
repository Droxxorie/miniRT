/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:52:18 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 10:37:09 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_face_normal(t_hit_record *record, t_ray *ray, t_vec3 outward_normal)
{
	if (vec3_dot(ray->direction, outward_normal) < 0)
	{
		record->front_face = TRUE;
		record->normal = outward_normal;
	}
	else
	{
		record->front_face = FALSE;
		record->normal = vec3_scale(outward_normal, -1.0);
	}
}
