/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_occlusion_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:44:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 00:02:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	ao_iteration(t_object *object, t_point3 local_point,
		t_vec3 local_normal, t_real *occlusion)
{
	t_real	step;
	t_real	scale;
	t_real	distance;
	int		i;

	scale = 1.0;
	i = 0;
	while (i < AO_STEPS)
	{
		step = AO_STEP_SIZE * (i + 1);
		distance = dispatch_sdf(vec3_add(local_point, vec3_scale(local_normal,
						step)), object);
		*occlusion += (step - distance) * scale;
		scale *= AO_SCALE_DECAY;
		i++;
	}
}

t_real	compute_ao(t_point3 point, t_vec3 normal, t_object *object)
{
	t_real		occlusion;
	t_vec3		local_normal;
	t_point3	local_point;

	occlusion = 0.0;
	local_point = mat4_mult_point3(object->inverse, point);
	local_normal = mat4_mult_vec3(object->transposed_inverse, normal);
	local_normal = vec3_normalize(local_normal);
	ao_iteration(object, local_point, local_normal, &occlusion);
	return (ft_clamp(1.0 - AO_INTENSITY * occlusion, 0.0, 1.0));
}
