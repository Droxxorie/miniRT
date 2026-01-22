/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_light_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:14:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 19:22:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	resize_quad_dim(t_light *light, int mode, t_real factor)
{
	if (mode == RESIZE_X)
		light->u = vec3_scale(light->u, factor);
	else if (mode == RESIZE_Y)
		light->v = vec3_scale(light->v, factor);
	else
	{
		light->u = vec3_scale(light->u, factor);
		light->v = vec3_scale(light->v, factor);
	}
}

static void	resize_spot_angle(t_light *light, t_real factor)
{
	t_real	current_angle;
	t_real	new_angle;
	t_real	step;

	step = 2.0;
	current_angle = acos(light->cos_theta) * 180.0 * INV_PI;
	if (factor > 1.0)
		new_angle = current_angle + step;
	else
		new_angle = current_angle - step;
	new_angle = ft_clamp(new_angle, 1.0, 179.0);
	light->cos_theta = cos(new_angle * PI / 180.0);
}

void	resize_light(t_light *light, t_camera *camera, int mode, int direction)
{
	t_real	factor;
	t_real	intensity;

	if (!light)
		return ;
	intensity = camera->scale_factor * RESIZE_SPEED;
	if (direction > 0)
		factor = 1.0 + intensity;
	else
		factor = 1.0 - intensity;
	if (light->type == LIGHT_SPOT)
		resize_spot_angle(light, factor);
	else if (light->type == LIGHT_QUAD)
		resize_quad_dim(light, mode, factor);
}
