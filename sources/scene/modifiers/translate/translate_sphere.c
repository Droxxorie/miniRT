/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:33:23 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:09:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_sphere(t_object *object, t_vec3 translation)
{
	t_sphere	*sphere;

	if (!object)
		return ;
	sphere = &object->u_data.sphere;
	sphere->center = vec3_add(sphere->center, translation);
	update_object_matrix(object);
}
