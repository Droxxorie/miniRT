/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 14:02:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs/s_scene_bonus.h"

long			get_time_ms(void);
void			swap_real(t_real *a, t_real *b);
size_t			ft_strspn(const char *str, const char *accept);
t_real			ft_clamp(t_real v, t_real min, t_real max);
t_real			ft_sign(t_real x);

t_real			ft_smoothstep(t_real edge0, t_real edge1, t_real x);
t_color			color_mix(t_color c1, t_color c2, t_real a);
t_color			apply_shading(t_color color, t_real n);
t_color			gamma_correction(t_color color);
t_color			aces_tone_mapping(t_color hdr);

//* ---- Random ---- *
t_real			hash_rand(t_point3 p, int seed);
unsigned int	pcg_hash(unsigned int input);
t_real			random_double(unsigned int *seed);
unsigned int	generate_seed(t_point3 p);
t_vec3			random_hemisphere_dir(t_vec3 normal, unsigned int *seed);
t_real			random_real(void);
t_real			random_real_range(t_real min, t_real max);
t_vec3			random_vec3_in_unit_sphere(void);
t_vec3			random_in_unit_sphere(unsigned int *seed);
t_real			noise_2d(t_real x, t_real y);

#endif