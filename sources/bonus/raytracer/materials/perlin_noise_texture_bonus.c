/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_noise_texture_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:11:07 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:19:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	get_turbulence(t_real x, t_real y, int octaves)
{
	t_real	value;
	t_real	scale;
	int		i;

	value = 0.0;
	scale = 1.0;
	i = 0;
	while (i < octaves)
	{
		value += noise_2d(x * scale, y * scale) / scale;
		scale *= 2.0;
		i++;
	}
	return (value);
}

t_color	pattern_perlin_noise(t_hit_record *record, t_material *material)
{
	t_real	n;
	t_real	scale;
	t_color	color;

	if (material->uv_scale > EPSILON)
		scale = material->uv_scale * 5.0;
	else
		scale = 5.0;
	n = (noise_2d(record->u * scale, record->v * scale) + 1.0) * 0.5;
	color = color_mix(material->color, (t_color){1.0, 1.0, 1.0}, n);
	return (color);
}

t_color	pattern_marble(t_hit_record *record, t_material *material)
{
	t_real	t;
	t_real	turbulence;
	t_real	scale;
	t_color	vein_color;

	if (material->uv_scale > EPSILON)
		scale = material->uv_scale * 4.0;
	else
		scale = 4.0;
	turbulence = get_turbulence(record->u * scale, record->v * scale, 5);
	t = sinf(record->v * scale * 10.0 + turbulence * 5.0);
	t = (t + 1.0) * 0.5;
	vein_color = (t_color){1.0, 1.0, 1.0};
	return (color_mix(material->color, vein_color, t));
}
