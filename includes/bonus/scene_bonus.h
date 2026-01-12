/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 15:46:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_BONUS_H
# define SCENE_BONUS_H

# include "structs/s_scene_bonus.h"

void		prepare_cameras(t_scene *scene);
void		save_scene_state(t_scene *scene);
void		reset_scene_state(t_scene *scene);
void		reset_light_state(t_light *light);
void		reset_object_state(t_object *object);
void		reset_camera_state(t_camera *camera);
t_status	load_scene(t_scene *scene, const char *file_path);
void		update_camera(t_camera *camera, t_real aspect_ratio);

#endif