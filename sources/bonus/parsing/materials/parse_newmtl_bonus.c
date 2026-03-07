/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_newmtl_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:55:41 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 21:51:07 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	mtl_add_back(t_material **head, t_material *new)
{
	t_material	*temp;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

static void	init_default_material_properties(t_material *m)
{
	m->type = LAMBERT;
	m->color = (t_color){1.0, 1.0, 1.0};
	m->specular_color = (t_color){0.0, 0.0, 0.0};
	m->emission_color = (t_color){0.0, 0.0, 0.0};
	m->roughness = 0.5;
	m->ior = 1.0;
	m->transparency = 0.0;
	m->absorbance = (t_color){0.0, 0.0, 0.0};
	m->metallic = 0.0;
	m->uv_scale = 1.0;
	m->pattern_type = PATTERN_NONE;
	m->albedo_texture_path = NULL;
	m->normal_texture_path = NULL;
	m->roughness_texture_path = NULL;
	m->emission_texture_path = NULL;
	m->next = NULL;
}

t_status	parse_newmtl(t_scene *scene, t_material **current, char **line)
{
	char		*name;
	t_material	*new_material;

	name = extract_string(line);
	if (name == NULL)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	if (find_material(scene->materials, name) != NULL)
	{
		print_error_loc(scene, *line, ERR_MAT_DUP);
		free(name);
		return (EXIT_FAILURE);
	}
	new_material = ft_calloc(1, sizeof(t_material));
	if (new_material == NULL)
	{
		free(name);
		return (print_error(ERR_MEM), EXIT_FAILURE);
	}
	new_material->name = name;
	init_default_material_properties(new_material);
	mtl_add_back(&scene->materials, new_material);
	*current = new_material;
	return (EXIT_SUCCESS);
}
