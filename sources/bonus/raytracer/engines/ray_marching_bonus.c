/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marching_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:45:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:34:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_vec3	get_sdf_normal(t_point3 p, t_object *object)
{
	t_real	d;
	t_vec3	n;

	d = dispatch_sdf(p, object);
	n.x = dispatch_sdf((t_point3){p.x + EPSILON, p.y, p.z}, object) - d;
	n.y = dispatch_sdf((t_point3){p.x, p.y + EPSILON, p.z}, object) - d;
	n.z = dispatch_sdf((t_point3){p.x, p.y, p.z + EPSILON}, object) - d;
	return (vec3_normalize(n));
}

static t_bool	set_sdf_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	t_point3	local_hit;
	t_vec3		local_normal;

	record->object = object;
	record->color = object->color;
	record->hit_point = ray_at(world_ray, record->t);
	if (world_ray->is_shadow_ray == TRUE)
		return (TRUE);
	local_hit = mat4_mult_point3(object->inverse, record->hit_point);
	local_normal = get_sdf_normal(local_hit, object);
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
	return (TRUE);
}

t_bool	ray_march(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray_march_data	d;

	d.depth = world_ray->min;
	d.scale = object->sdf_scale;
	d.steps = 0;
	while (d.steps++ < MAX_SDF_STEPS)
	{
		d.world_p = ray_at(world_ray, d.depth);
		d.local_p = mat4_mult_point3(object->inverse, d.world_p);
		d.local_dist = dispatch_sdf(d.local_p, object);
		d.world_dist = d.local_dist * d.scale;
		if (d.world_dist < EPSILON)
		{
			record->t = d.depth;
			return (set_sdf_record(object, world_ray, record));
		}
		d.depth += d.world_dist;
		if (d.depth > world_ray->max)
			return (FALSE);
	}
	return (FALSE);
}
