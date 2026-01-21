/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_albedo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:42:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 20:48:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	get_albedo(t_material *mat, t_hit_record *record)
{
	if (mat && mat->albedo_map)
		return (sample_texture(mat->albedo_map, record->u, record->v));
	if (mat->pattern_type == PATTERN_CHECKER)
		return (pattern_checker(record, mat));
	if (mat->pattern_type == PATTERN_RAINBOW)
		return (pattern_rainbow(record));
	if (mat->pattern_type == PATTERN_WAVE)
		return (pattern_wave(record, mat));
	if (mat->pattern_type == PATTERN_PERLIN_NOISE)
		return (pattern_perlin_noise(record, mat));
	if (mat->pattern_type == PATTERN_MARBLE)
		return (pattern_marble(record, mat));
	if (mat)
		return (mat->color);
	return (record->color);
}
