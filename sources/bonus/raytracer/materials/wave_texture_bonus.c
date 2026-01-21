/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:31:40 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 20:10:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	pattern_wave(t_hit_record *record, t_material *material)
{
	t_real	t;
	t_color	noise;

	t = sin(record->v * 20.0 + sin(record->u * 30.0) * 2.0);
	t = (t + 1.0) * 0.5;
	noise = (t_color){1.0, 1.0, 1.0};
	return (color_mix(material->color, noise, t));
}
