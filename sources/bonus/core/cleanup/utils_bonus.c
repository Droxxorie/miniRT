/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:09:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 15:13:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_objects(t_object *object)
{
	t_object	*temp;

	while (object)
	{
		temp = object->next;
		free(object);
		object = temp;
	}
}

void	free_lights(t_light *light)
{
	t_light	*temp;

	while (light)
	{
		temp = light->next;
		free(light);
		light = temp;
	}
}

void	free_cameras(t_camera *camera)
{
	t_camera	*temp;

	while (camera)
	{
		temp = camera->next;
		free(camera);
		camera = temp;
	}
}

void	free_materials(t_material *mat)
{
	t_material	*temp;

	while (mat)
	{
		temp = mat->next;
		if (mat->name)
			free(mat->name);
		if (mat->albedo_texture_path)
			free(mat->albedo_texture_path);
		if (mat->normal_texture_path)
			free(mat->normal_texture_path);
		if (mat->roughness_texture_path)
			free(mat->roughness_texture_path);
		if (mat->emission_texture_path)
			free(mat->emission_texture_path);
		free(mat);
		//? peut etre destroy ici pour les images mlx liées
		mat = temp;
	}
}
