/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marching_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:45:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:26:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* OLD VERSION
// static t_vec3	get_sdf_normal(t_point3 p, t_object *object)
// {
// 	t_real	d;
// 	t_vec3	n;

// 	d = dispatch_sdf(p, object);
// 	n.x = dispatch_sdf((t_point3){p.x + EPSILON, p.y, p.z}, object) - d;
// 	n.y = dispatch_sdf((t_point3){p.x, p.y + EPSILON, p.z}, object) - d;
// 	n.z = dispatch_sdf((t_point3){p.x, p.y, p.z + EPSILON}, object) - d;
// 	return (vec3_normalize(n));
// }

static t_vec3	get_sdf_normal(t_point3 p, t_object *object)
{
	t_vec3	n;
	t_real	e;

	e = 0.001;
	n.x = dispatch_sdf((t_point3){p.x + e, p.y, p.z}, object)
		- dispatch_sdf((t_point3){p.x - e, p.y, p.z}, object);
	n.y = dispatch_sdf((t_point3){p.x, p.y + e, p.z}, object)
		- dispatch_sdf((t_point3){p.x, p.y - e, p.z}, object);
	n.z = dispatch_sdf((t_point3){p.x, p.y, p.z + e}, object)
		- dispatch_sdf((t_point3){p.x, p.y, p.z - e}, object);
	return (vec3_normalize(n));
}

static t_bool	set_sdf_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	t_point3	local_hit;

	record->object = object;
	if (world_ray->is_shadow_ray == TRUE)
		return (TRUE);
	record->hit_point = ray_at(world_ray, record->t);
	record->normal = get_sdf_normal(record->hit_point, object);
	set_face_normal(record, world_ray, record->normal);
	record->color = object->color;
	if (object->is_fractal == TRUE)
	{
		local_hit = mat4_mult_point3(object->inverse, record->hit_point);
		record->color = get_fractal_color(local_hit, object);
	}
	return (TRUE);
}

static void	init_ray_march_data(t_object *object, t_ray_march_data *data,
		t_ray *world_ray)
{
	if (object->is_fractal == TRUE)
	{
		data->threshold = 0.00001;
		data->step_factor = 0.15;
		data->max_steps = 2000;
	}
	else
	{
		data->threshold = EPSILON;
		data->step_factor = 1.0;
		data->max_steps = MAX_SDF_STEPS;
	}
	data->depth = world_ray->min;
	data->scale = object->sdf_scale;
	data->steps = 0;
}

t_bool	ray_march(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray_march_data	d;
	t_real				local_dist;

	init_ray_march_data(object, &d, world_ray);
	while (d.steps++ < d.max_steps)
	{
		d.world_p = ray_at(world_ray, d.depth);
		local_dist = dispatch_sdf(d.world_p, object);
		d.world_dist = local_dist * d.scale;
		d.world_dist *= d.step_factor;
		if (d.world_dist < d.threshold)
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
