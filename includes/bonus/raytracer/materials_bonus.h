/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:39:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 20:46:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_BONUS_H
# define MATERIALS_BONUS_H

# include "../structs/s_scene_bonus.h"

t_color	pattern_checker(t_hit_record *record, t_material *material);
t_color	pattern_rainbow(t_hit_record *record);
t_color	pattern_wave(t_hit_record *record, t_material *material);
t_color	pattern_perlin_noise(t_hit_record *record, t_material *material);
t_color	pattern_marble(t_hit_record *record, t_material *material);

#endif