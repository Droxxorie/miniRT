/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marching_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:45:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 18:45:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

static void	set_sdf_record(t_object *object, t_ray *world_ray,
		t_hit_record *record, t_real depth)
{
	t_point3	local_hit;

	record->object = object;
	record->t = depth;
	if (world_ray->is_shadow_ray == TRUE)
		return ;
	record->hit_point = ray_at(world_ray, record->t);
	record->normal = get_sdf_normal(record->hit_point, object);
	set_face_normal(record, world_ray, record->normal);
	record->color = object->color;
	record->u = 0.0;
	record->v = 0.0;
	if (object->is_fractal == TRUE)
	{
		local_hit = mat4_mult_point3(object->inverse, record->hit_point);
		record->color = get_fractal_color(local_hit, object);
	}
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

	init_ray_march_data(object, &d, world_ray);
	while (d.steps++ < d.max_steps && d.depth <= world_ray->max)
	{
		d.world_p = ray_at(world_ray, d.depth);
		d.world_dist = dispatch_sdf(d.world_p, object) * d.scale;
		d.world_dist *= d.step_factor;
		if (fabsf(d.world_dist) < d.threshold)
		{
			set_sdf_record(object, world_ray, record, d.depth);
			if (world_ray->is_shadow_ray == FALSE && (d.steps < 2
					|| vec3_len(record->normal) < 0.1f))
				d.world_dist = d.threshold * 2.0f;
			else
				return (TRUE);
		}
		if (d.world_dist < -0.01f)
			d.depth += 0.001f;
		else
			d.depth += d.world_dist;
	}
	return (FALSE);
}
