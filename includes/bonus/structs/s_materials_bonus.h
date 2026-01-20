/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_materials_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:57:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 15:01:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_MATERIALS_BONUS_H
# define S_MATERIALS_BONUS_H

# include "s_ray_bonus.h"

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
	t_color				color;			//* Kd
	t_color				ambient_color;	//* Ka
	t_color				specular_color;	//* Ks
	t_color				emission_color;	//* Ke

	//* Scalar properties
	// t_color				roughness_color;
	// t_real				emission;
	t_real				roughness;		//* Ns
	t_real				ior;			//* Ni
	t_real				transparency;	//* d
	
	//* Texture maps
	// char				*diffuse_texture_path;
	char				*albedo_texture_path; //* map_Kd
	char				*normal_texture_path; //* map_Bump / Bump
	char				*roughness_texture_path; //* map_Ns
	char				*emission_texture_path; //* map_Ke
	
	//* Custome scaling
	t_real				uv_scale;
	// t_real				scale_x;
	// t_real				scale_y;
	t_bool				has_wave;

	
	struct s_material	*next;
}						t_material;

#endif