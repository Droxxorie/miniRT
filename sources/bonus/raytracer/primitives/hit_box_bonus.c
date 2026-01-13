/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_box_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:55:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 10:28:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	update_intervals(t_real dir, t_real origin, t_real *t_min,
		t_real *t_max)
{
	t_real	t0;
	t_real	t1;
	t_real	inv_dir;

	if (fabs(dir) < EPSILON)
	{
		if (origin < -0.5 || origin > 0.5)
			return (FALSE);
		return (TRUE);
	}
	inv_dir = 1.0 / dir;
	t0 = (-0.5 - origin) * inv_dir;
	t1 = (0.5 - origin) * inv_dir;
	if (t0 > t1)
	{
		t0 = t0 + t1;
		t1 = t0 - t1;
		t0 = t0 - t1;
	}
	*t_min = fmax(t0, *t_min);
	*t_max = fmin(t1, *t_max);
	return (*t_max > *t_min);
}

static t_bool	check_slab(t_ray *ray, t_real *t_min, t_real *t_max)
{
	t_real	*origin;
	t_real	*dir;
	int		i;

	origin = (t_real *)&ray->origin;
	dir = (t_real *)&ray->direction;
	i = -1;
	while (++i < 3)
	{
		if (update_intervals(dir[i], origin[i], t_min, t_max) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

static void	get_box_normal(t_point3 *p, t_vec3 *n)
{
	t_real	max;

	max = fmax(fabs(p->x), fmax(fabs(p->y), fabs(p->z)));
	if (max == fabs(p->x))
	{
		if (p->x > 0)
			n->x = 1.0;
		else
			n->x = -1.0;
	}
	else if (max == fabs(p->y))
	{
		if (p->y > 0)
			n->y = 1.0;
		else
			n->y = -1.0;
	}
	else
	{
		if (p->z > 0)
			n->z = 1.0;
		else
			n->z = -1.0;
	}
}

static void	set_box_record(t_object *object, t_ray *world_ray, t_ray *local_ray,
		t_hit_record *record)
{
	t_point3	p;
	t_vec3		n;

	record->object = object;
	record->color = object->color;
	record->hit_point = ray_at(world_ray, record->t);
	if (world_ray->is_shadow_ray == TRUE)
		return ;
	p = ray_at(local_ray, record->t);
	n = (t_vec3){0, 0, 0};
	get_box_normal(&p, &n);
	record->normal = mat4_mult_vec3(object->transposed_inverse, n);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_box(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	local_ray;
	t_real	t_min;
	t_real	t_max;

	local_ray = transform_ray(*world_ray, object->inverse);
	t_min = -INFINITY;
	t_max = INFINITY;
	if (check_slab(&local_ray, &t_min, &t_max) == FALSE)
		return (FALSE);
	if (t_min > world_ray->max || t_max < world_ray->min)
		return (FALSE);
	record->t = t_min;
	if (t_min < world_ray->min)
	{
		record->t = t_max;
		if (t_max > world_ray->max)
			return (FALSE);
	}
	set_box_record(object, world_ray, &local_ray, record);
	return (TRUE);
}
