/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:36:48 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 19:30:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "structures.h"
# include "macros.h"

t_bool	solve_quadratic(t_poly *vars);

//* Vector operations */
t_vec3	vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_add_scalar(const t_vec3 v, const t_real k);
t_vec3	vec3_scale(const t_vec3 v, const t_real k);
t_vec3	vec3_prod(const t_vec3 u, const t_vec3 v);
t_real	vec3_len_squared(const t_vec3 v);
t_real	vec3_len(const t_vec3 v);
t_vec3	vec3_normalize(const t_vec3 v);
t_vec3	vec3_cross(const t_vec3 u, const t_vec3 v);
t_real	vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_sub(const t_vec3 u, const t_vec3 v);

//* Color operations */
t_color	color_add(const t_color c1, const t_color c2);
t_color	color_add_scalar(const t_color color, const t_real k);
t_color	color_scale(const t_color color, const t_real k);
t_color	color_prod(const t_color c1, const t_color c2);
t_real	color_dot(const t_color c1, const t_color c2);
		//* code mort pour le moment

//* Matrix operations */
t_mat4	identity_matrix(void);
t_mat4	make_rotation_matrix(t_vec3 angles);
t_mat4	make_translation_matrix(t_vec3 translation);
t_vec3	mat3_mult_vec3(t_mat4 mat, t_vec3 vec);
t_vec3	mat4_mult_point(t_mat4 mat, t_point3 point);
t_mat4	mat4_mult_mat4(t_mat4 a, t_mat4 b);

#endif