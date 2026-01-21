/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shininess_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:42:30 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 12:19:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	get_shininess(t_material *mat, t_hit_record *record)
{
	t_real	roughness;
	t_color	texture_color;
	t_real	shininess;

	if (!mat)
		return (32.0);
	if (mat->roughness_map)
	{
		texture_color = sample_texture(mat->roughness_map, record->u,
				record->v);
		roughness = color_mean(texture_color);
	}
	else
		roughness = mat->roughness;
	shininess = (1.0 - roughness) * 1000.0;
	return (fmax(1.0, shininess));
}
