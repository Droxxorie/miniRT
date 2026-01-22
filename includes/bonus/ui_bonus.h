/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:58:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 13:59:12 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_BONUS_H
# define UI_BONUS_H

# include "structs/s_scene_bonus.h"
# include <stdio.h>

void	print_usage(void);
void	entry_message(void);
void	print_controls(void);
void	log_light_info(t_light *light);
void	log_object_info(t_object *object);
void	log_camera_info(t_camera *camera);
char	*get_object_type_str(t_object_type type);
char	*get_light_type_str(t_light_type type);
void	display_progress(int current, int total);
void	log_event(FILE *stream, char *type, char *format, ...);
void	get_scale_and_position(t_object *object, t_vec3 *s, t_vec3 *p,
			t_color *c);

#endif