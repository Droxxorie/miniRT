/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_light_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 09:26:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:30:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_light(t_light *light, t_camera *camera, t_vec3 translation)
{
	t_real	speed;

	if (!light)
		return ;
	speed = camera->scale_factor * MOVE_SPEED;
	translation = vec3_scale(translation, speed);
	light->position = vec3_add(light->position, translation);
}
