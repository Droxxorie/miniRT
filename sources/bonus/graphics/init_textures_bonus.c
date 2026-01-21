/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:18:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 22:53:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_image	*load_texture(void *mlx_ptr, char *path)
{
	t_image	*map;

	if (!path)
		return (NULL);
	map = ft_calloc(1, sizeof(t_image));
	if (!map)
		return (print_error(ERR_MEM), NULL);
	map->ptr = mlx_xpm_file_to_image(mlx_ptr, path, &map->width, &map->height);
	if (!map->ptr)
	{
		free(map);
		return (NULL);
	}
	map->addr = mlx_get_data_addr(map->ptr, &map->bpp, &map->line_len,
			&map->endian);
	return (map);
}

static void	safe_load(void *mlx, char *path, t_image **dest, char *name)
{
	if (path)
	{
		*dest = load_texture(mlx, path);
		if (*dest)
			log_event(stdout, "INFO", "Loaded %s texture: %s\n", name, path);
		else
			log_event(stderr, "WARN", "Could not load %s texture: %s\n", name,
				path);
	}
}

static void	load_skybox_texture(t_scene *scene)
{
	if (scene->skybox_texture_path)
		safe_load(scene->mlx_window.mlx_ptr, scene->skybox_texture_path,
			&scene->skybox_map, "skybox");
	if (!scene->skybox_map)
		log_event(stderr, "WARN",
			"No skybox texture loaded. Using procedural skybox.\n");
	return ;
}

t_status	init_textures(t_scene *scene)
{
	t_material	*mat;
	void		*img_ptr;

	log_event(stdout, "INFO", "Loading textures...\n");
	mat = scene->materials;
	img_ptr = scene->mlx_window.mlx_ptr;
	while (mat)
	{
		safe_load(img_ptr, mat->albedo_texture_path, &mat->albedo_map,
			"albedo");
		safe_load(img_ptr, mat->normal_texture_path, &mat->normal_map,
			"normal");
		safe_load(img_ptr, mat->roughness_texture_path, &mat->roughness_map,
			"roughness");
		safe_load(img_ptr, mat->emission_texture_path, &mat->emission_map,
			"emission");
		safe_load(img_ptr, mat->metallic_texture_path, &mat->metallic_map,
			"metallic");
		safe_load(img_ptr, mat->specular_texture_path, &mat->specular_map,
			"specular");
		mat = mat->next;
	}
	load_skybox_texture(scene);
	log_event(stdout, "SUCCESS", "Textures loaded successfully!\n");
	return (EXIT_SUCCESS);
}
