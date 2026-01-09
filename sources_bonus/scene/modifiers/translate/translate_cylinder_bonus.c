/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cylinder_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 09:16:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_cylinder(t_object *object, t_vec3 translation)
{
	t_cylinder	*cylinder;

	if (!object)
		return ;
	cylinder = &object->u_data.cylinder;
	cylinder->center = vec3_add(cylinder->center, translation);
	update_object(object);
}
