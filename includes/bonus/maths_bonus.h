/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:36:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 12:59:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_BONUS_H
# define MATHS_BONUS_H

# include "structs/s_math_bonus.h"

//* ========================================================================= */
//*                                VECTOR                                     */
//* ========================================================================= */
t_real	vec3_len(const t_vec3 v);
t_vec3	vec3_normalize(const t_vec3 v);
t_real	vec3_len_squared(const t_vec3 v);
t_vec3	vec3_add(const t_vec3 u, const t_vec3 v);
t_real	vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_sub(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_cross(const t_vec3 u, const t_vec3 v);
t_vec3	vec3_scale(const t_vec3 v, const t_real k);
t_vec3	vec3_add_scalar(const t_vec3 v, const t_real k);
t_vec3	vec3_abs(const t_vec3 v);

t_real	vec2_dot(const t_vec2 u, const t_vec2 v);
t_real	vec2_len(const t_vec2 v);
t_real	vec2_len_squared(const t_vec2 v);
t_vec2	vec2_sub(const t_vec2 u, const t_vec2 v);
t_vec2	vec2_scale(const t_vec2 v, const t_real k);
t_vec2	vec2_abs(const t_vec2 v);

//* ========================================================================= */
//*                                COLOR                                      */
//* ========================================================================= */
t_color	color_add(const t_color c1, const t_color c2);
t_color	color_prod(const t_color c1, const t_color c2);
t_color	color_scale(const t_color color, const t_real k);

//* ========================================================================= */
//*                                MATRIX                                     */
//* ========================================================================= */
t_mat4	identity_matrix(void);
t_mat4	mat4_inverse(t_mat4 mat);
t_mat4	mat4_transpose(t_mat4 mat);
t_mat4	rotation_align(t_vec3 dest);
t_mat4	rotation_mat_y(t_real angle);
t_mat4	rotation_mat_z(t_real angle);
t_mat4	make_scale_matrix(t_vec3 scale);
t_mat4	mat4_mult_mat4(t_mat4 a, t_mat4 b);
t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 vec);
t_vec3	mat4_mult_point3(t_mat4 mat, t_point3 pt);
t_mat4	make_translation_matrix(t_vec3 translation);
t_mat4	matrix_axis_angle(t_vec3 axis, t_real angle);
t_real	get_min_scale_factor(t_mat4 mat);

//* ========================================================================= */
//*                                SOLVER                                     */
//* ========================================================================= */
t_bool	solve_quadratic(t_quadratic *vars);
t_bool	solve_cubic(t_cubic *vars);
t_bool	solve_quartic(t_quartic *vars);

#endif