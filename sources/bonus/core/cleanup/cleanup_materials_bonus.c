/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_materials_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:24:12 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:25:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	free_texture_image(void *mlx_ptr, t_image *img)
{
	if (img)
	{
		if (img->ptr)
			mlx_destroy_image(mlx_ptr, img->ptr);
		free(img);
	}
}

static void	free_materials_textures(void *mlx_ptr, t_material *mat)
{
	free_texture_image(mlx_ptr, mat->albedo_map);
	free_texture_image(mlx_ptr, mat->normal_map);
	free_texture_image(mlx_ptr, mat->roughness_map);
	free_texture_image(mlx_ptr, mat->emission_map);
	free_texture_image(mlx_ptr, mat->metallic_map);
	free_texture_image(mlx_ptr, mat->specular_map);
}

void	free_materials(void *mlx_ptr, t_material *mat)
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
		if (mat->metallic_texture_path)
			free(mat->metallic_texture_path);
		if (mat->specular_texture_path)
			free(mat->specular_texture_path);
		if (mlx_ptr)
			free_materials_textures(mlx_ptr, mat);
		free(mat);
		mat = temp;
	}
}
