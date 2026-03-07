/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_occlusion_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:44:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 19:56:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	ao_iterations(t_scene *scene, t_point3 p, t_vec3 normal,
		t_real *occlusion)
{
	t_real	step_dist;
	t_real	scale;
	t_real	sdf_dist;
	t_vec3	test_p;
	int		i;

	*occlusion = 0.0;
	scale = 1.0;
	i = 0;
	while (i < AO_STEPS)
	{
		step_dist = AO_STEP_SIZE * (t_real)(i + 1);
		test_p = vec3_add(p, vec3_scale(normal, step_dist));
		sdf_dist = map_the_world(test_p, scene);
		*occlusion += fmaxf(0.0, step_dist - sdf_dist) * scale;
		scale *= AO_SCALE_DECAY;
		i++;
	}
}

t_real	compute_sdf_ao(t_scene *scene, t_hit_record *record)
{
	t_real		occlusion;
	t_point3	point;
	t_real		intensity;

	if (record->object->is_fractal == TRUE)
		intensity = 0.2;
	else
		intensity = AO_INTENSITY;
	point = vec3_add(record->hit_point, vec3_scale(record->normal, 0.01));
	ao_iterations(scene, point, record->normal, &occlusion);
	return (ft_clamp(1.0 - (occlusion * intensity), 0.0, 1.0));
}

static t_real	compute_rt_ao(t_scene *scene, t_hit_record *record)
{
	int				hits;
	t_ray			ao_ray;
	t_hit_record	ao_record;
	unsigned int	seed;
	int				i;

	hits = 0;
	ao_ray.origin = vec3_add(record->hit_point, vec3_scale(record->normal,
				0.001));
	ao_ray.is_shadow_ray = TRUE;
	seed = generate_seed(record->hit_point);
	i = 0;
	while (i < AO_SAMPLES)
	{
		ao_ray.direction = vec3_normalize(random_hemisphere_dir(record->normal,
					&seed));
		ao_ray.min = EPSILON;
		ao_ray.max = 2.0;
		if (hit_bvh(scene->bvh_root, &ao_ray, &ao_record))
			hits++;
		i++;
	}
	return (ft_clamp(1.0 - (((t_real)hits / (t_real)AO_SAMPLES)), 0.0, 1.0));
}

t_real	compute_ao(t_scene *scene, t_hit_record *record)
{
	if (record->object->render_as_sdf)
		return (compute_sdf_ao(scene, record));
	else
		return (compute_rt_ao(scene, record));
}
