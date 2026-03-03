/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_materials_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:57:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 22:40:02 by eraad            ###   ########.fr       */
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
	EMISSIVE,
	OREN_NAYAR,
	COOK_TORRANCE
}						t_material_type;

typedef struct s_material
{
	char				*name;
	struct s_material	*next;
	t_color				ambient_color;
	t_color				absorbance;
	t_color				color;
	t_color				emission_color;
	t_color				specular_color;
	struct s_image		*albedo_map;
	char				*albedo_texture_path;
	struct s_image		*normal_map;
	char				*normal_texture_path;
	struct s_image		*roughness_map;
	char				*roughness_texture_path;
	struct s_image		*emission_map;
	char				*emission_texture_path;
	struct s_image		*metallic_map;
	char				*metallic_texture_path;
	struct s_image		*specular_map;
	char				*specular_texture_path;
	t_real				a;
	t_real				b;
	t_real				ior;
	t_real				transparency;
	t_real				roughness;
	t_real				metallic;
	t_real				uv_scale;
	t_material_type		type;
	t_pattern			pattern_type;
}						t_material;

#endif