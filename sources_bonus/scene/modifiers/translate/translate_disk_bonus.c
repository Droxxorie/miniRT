/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_disk_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:25:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 21:42:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_disk(t_object *object, t_vec3 translation)
{
	t_disk	*disk;

	if (!object)
		return ;
	disk = &object->u_data.disk;
	disk->center = vec3_add(disk->center, translation);
	update_object_matrix(object);
}
