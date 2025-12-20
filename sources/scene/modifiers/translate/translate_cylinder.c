/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:02 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:08:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_cylinder(t_object *object, t_vec3 translation)
{
	t_cylinder	*cylinder;

	if (!object)
		return ;
	cylinder = &object->u_data.cylinder;
	cylinder->center = vec3_add(cylinder->center, translation);
	update_object_matrix(object);
}
