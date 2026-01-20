/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:27:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 15:03:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

// printf("Using material: %s\n", object->material->name);
// printf("Albedo texture: %s\n",
// 	object->material->albedo_texture_path);
// printf("Normal texture: %s\n",
// 	object->material->normal_texture_path);
// printf("Roughness texture: %s\n",
// 	object->material->roughness_texture_path);
// printf("Emission texture: %s\n",
// 	object->material->emission_texture_path);
// printf("Roughness: %f\n", object->material->roughness);
// printf("IOR: %f\n", object->material->ior);
// printf("Transparency: %f\n", object->material->transparency);
// printf("UV Scale: %f\n", object->material->uv_scale);
// printf("Has Wave: %d\n", object->material->has_wave);
// printf("Illumination Model: %d\n", object->material->type);
// printf("Specular Color: (%f, %f, %f)\n",
// 	object->material->specular_color.r,
// 	object->material->specular_color.g,
// 	object->material->specular_color.b);
// printf("Emission Color: (%f, %f, %f)\n",
// 	object->material->emission_color.r,
// 	object->material->emission_color.g,
// 	object->material->emission_color.b);
// printf("Diffuse Color: (%f, %f, %f)\n",
// 	object->material->color.r,
// 	object->material->color.g,
// 	object->material->color.b);
// printf("Ambient Color: (%f, %f, %f)\n",
// 	object->material->ambient_color.r,
// 	object->material->ambient_color.g,
// 	object->material->ambient_color.b);
// printf("--------------------------------------------------\n");

t_status	parse_options(t_scene *scene, char **line, t_object *object)
{
	while (**line)
	{
		skip_whitespace(line);
		if (**line == '\0' || **line == '#' || **line == '\n')
			return (EXIT_SUCCESS);
		if (match_and_consume(line, "-usemtl") == EXIT_SUCCESS)
		{
			if (parse_usemtl(scene, line, object) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (match_and_consume(line, "-sdf") == EXIT_SUCCESS)
		{
			if (parse_sdf(scene, line, object) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			print_error_loc(scene, *line, ERR_OPTION);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
