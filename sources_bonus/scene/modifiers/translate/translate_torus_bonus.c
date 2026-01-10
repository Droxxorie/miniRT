/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_torus_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:54:27 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:54:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_torus(t_object *object, t_vec3 translation)
{
	t_torus	*torus;

	if (!object)
		return ;
	torus = &object->u_data.torus;
	torus->center = vec3_add(torus->center, translation);
	update_object(object);
}
