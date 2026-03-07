/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_obj_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 00:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 00:00:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_OBJ_BONUS_H
# define S_OBJ_BONUS_H

# include "s_math_bonus.h"
# include "s_materials_bonus.h"

typedef struct s_obj_data
{
	t_vec3		*v_array;
	int			v_count;
	int			v_capacity;
	t_vec3		*vn_array;
	int			vn_count;
	int			vn_capacity;
	t_material	*active_material;
	t_point3	position;
	t_vec3		rotation;
	t_real		scale;
	t_color		base_color;
}				t_obj_data;

#endif