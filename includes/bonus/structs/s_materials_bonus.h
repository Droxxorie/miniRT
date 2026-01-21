/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_materials_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:57:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 22:40:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_MATERIALS_BONUS_H
# define S_MATERIALS_BONUS_H

# include "s_ray_bonus.h"

typedef enum e_pattern
{
	PATTERN_NONE,
	PATTERN_CHECKER,
	PATTERN_WAVE,
	PATTERN_RAINBOW,
	PATTERN_PERLIN_NOISE,
	PATTERN_MARBLE,
}						t_pattern;

typedef enum e_material_type
{
	LAMBERT,
	PHONG,
	METAL,
	DIELECTRIC,
	EMISSIVE
}						t_material_type;

typedef struct s_material
{
	char				*name;
	t_material_type		type;
	t_color				color;
	t_color				ambient_color;
	t_color				specular_color;
	t_color				emission_color;
	t_real				roughness;
	t_real				ior;
	t_real				transparency;
	char				*albedo_texture_path;
	struct s_image		*albedo_map;
	char				*normal_texture_path;
	struct s_image		*normal_map;
	char				*roughness_texture_path;
	struct s_image		*roughness_map;
	char				*emission_texture_path;
	struct s_image		*emission_map;
	char				*metallic_texture_path;
	struct s_image		*metallic_map;
	char				*specular_texture_path;
	struct s_image		*specular_map;
	t_real				uv_scale;
	t_pattern			pattern_type;

	struct s_material	*next;
}						t_material;

#endif