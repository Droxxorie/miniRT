/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_materials_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:57:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 19:45:49 by eraad            ###   ########.fr       */
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
	PATTERN_PERLIN_NOISE,	//TODO
	PATTERN_MARBLE,			//TODO
}						t_pattern;

typedef enum e_material_type
{
	LAMBERT,    //*Mat
	PHONG,      //* platique/brillant
	METAL,      //* reflet teinté
	DIELECTRIC, //* transparent
	EMISSIVE    //* lumière surfacique
}						t_material_type;

typedef struct s_material
{
	char				*name;
	t_material_type		type;

	//* Surface properties
	t_color color;          //* Kd
	t_color ambient_color;  //* Ka
	t_color specular_color; //* Ks
	t_color emission_color; //* Ke

	//* Scalar properties
	t_real roughness;    //* Ns
	t_real ior;          //* Ni
	t_real transparency; //* d

	//* Texture maps
	char 				*albedo_texture_path; //* map_Kd
	struct s_image		*albedo_map;
	char 				*normal_texture_path; //* map_Bump / Bump
	struct s_image		*normal_map;
	char 				*roughness_texture_path; //* map_Ns
	struct s_image		*roughness_map;
	char 				*emission_texture_path;  //* map_Ke
	struct s_image		*emission_map;
	char 				*metallic_texture_path;  //* map_Pr
	struct s_image		*metallic_map;
	char				*specular_texture_path;  //* map_Ks
	struct s_image		*specular_map;

	//* Custome scaling
	t_real				uv_scale;
	t_pattern			pattern_type;

	struct s_material	*next;
}						t_material;

#endif