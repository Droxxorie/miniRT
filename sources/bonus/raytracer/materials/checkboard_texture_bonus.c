/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkboard_texture_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 20:10:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:30:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	pattern_checker(t_hit_record *record, t_material *material)
{
	t_real	sines;
	t_real	frequency;

	if (material->uv_scale > EPSILON)
		frequency = material->uv_scale * 10.0;
	else
		frequency = 10.0;
	sines = sinf(frequency * record->u * TWO_PI) * sinf(frequency * record->v
			* TWO_PI);
	if (sines < 0)
		return (material->color);
	return ((t_color){0.0, 0.0, 0.0});
}
