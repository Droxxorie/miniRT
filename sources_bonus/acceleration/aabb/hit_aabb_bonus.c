/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_aabb_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:03:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 16:36:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	check_axis(t_real *ray_data, t_real *box_data, t_real *range)
{
	t_real	t0;
	t_real	t1;
	t_real	inv_dir;

	if (fabs(ray_data[1]) < EPSILON)
	{
		if (ray_data[0] < box_data[0] || ray_data[0] > box_data[1])
			return (FALSE);
		return (TRUE);
	}
	inv_dir = 1.0 / ray_data[1];
	t0 = (box_data[0] - ray_data[0]) * inv_dir;
	t1 = (box_data[1] - ray_data[0]) * inv_dir;
	if (t0 > t1)
		swap_real(&t0, &t1);
	range[0] = fmax(t0, range[0]);
	range[1] = fmin(t1, range[1]);
	return (range[1] > range[0]);
}

t_bool	hit_aabb(t_aabb *box, t_ray *ray, t_real t_min, t_real t_max)
{
	t_real	range[2];
	t_real	ray_data[2];
	t_real	box_data[2];
	int		i;

	range[0] = t_min;
	range[1] = t_max;
	i = 0;
	while (i < 3)
	{
		ray_data[0] = ((t_real *)&ray->origin)[i];
		ray_data[1] = ((t_real *)&ray->direction)[i];
		box_data[0] = ((t_real *)&box->min)[i];
		box_data[1] = ((t_real *)&box->max)[i];
		if (check_axis(ray_data, box_data, range) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
