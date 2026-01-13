/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 15:58:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "structs/s_scene_bonus.h"

long		get_time_ms(void);
void		swap_real(t_real *a, t_real *b);
size_t		ft_strspn(const char *str, const char *accept);
t_real		ft_clamp(t_real v, t_real min, t_real max);
t_real		ft_sign(t_real x);

#endif