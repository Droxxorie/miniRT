/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:33:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:44:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_sphere(t_object *object, t_vec3 translation)
{
	t_sphere	*sphere;

	if (!object)
		return ;
	sphere = &object->u_data.sphere;
	sphere->center = vec3_add(sphere->center, translation);
	update_object_matrix(object);
}
