/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:34:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 12:09:07 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	render_debug(t_scene *scene, t_hit_record *record)
{
	t_real	ao_factor;

	if (scene->render_mode == RENDER_NORMAL)
		return ((t_color){
			(record->normal.x + 1.0) * 0.5,
			(record->normal.y + 1.0) * 0.5,
			(record->normal.z + 1.0) * 0.5});
	else if (scene->render_mode == RENDER_AO)
	{
		ao_factor = compute_ao(scene, record);
		return ((t_color){ao_factor, ao_factor, ao_factor});
	}
	return ((t_color){0.0, 0.0, 0.0});
}
