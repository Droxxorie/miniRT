/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_occlusion_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:44:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 17:39:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	ao_iteration(t_scene *scene, t_point3 p, t_vec3 normal,
		t_real *occlusion)
{
	t_real	step;
	t_real	scale;
	t_real	dist;
	t_vec3	test_p;
	int		i;

	scale = 1.0;
	*occlusion = 0.0;
	i = 0;
	while (i < AO_STEPS)
	{
		step = AO_STEP_SIZE * (i + 1);
		test_p = vec3_add(p, vec3_scale(normal, step));
		dist = map_the_world(test_p, scene);
		*occlusion += (step - dist) * scale;
		scale *= AO_SCALE_DECAY;
		i++;
	}
}

t_real	compute_ao(t_scene *scene, t_point3 point, t_vec3 normal)
{
	t_real	occlusion;

	point = vec3_add(point, vec3_scale(normal, AO_INTENSITY));
	ao_iteration(scene, point, normal, &occlusion);
	return (ft_clamp(1.0 - AO_INTENSITY * occlusion, 0.0, 1.0));
}
