/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_emissive_list_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:33:33 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 16:48:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	is_object_emissive(t_object *obj)
{
	if (!obj->material)
		return (FALSE);
	if (obj->material->emission_color.r > EPSILON)
		return (TRUE);
	if (obj->material->emission_color.g > EPSILON)
		return (TRUE);
	if (obj->material->emission_color.b > EPSILON)
		return (TRUE);
	return (FALSE);
}

static t_status	add_emissive_node(t_scene *scene, t_object *obj)
{
	t_emissive	*node;

	node = ft_calloc(1, sizeof(t_emissive));
	if (!node)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	node->object = obj;
	node->next = scene->emissive_lights;
	scene->emissive_lights = node;
	return (EXIT_SUCCESS);
}

t_status	build_emissive_list(t_scene *scene)
{
	t_object	*obj;

	scene->emissive_lights = NULL;
	obj = scene->objects;
	while (obj)
	{
		if (is_object_emissive(obj))
			if (add_emissive_node(scene, obj) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		obj = obj->next;
	}
	return (EXIT_SUCCESS);
}
