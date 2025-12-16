/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:06 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 20:47:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

void	input_manager(t_scene *scene);
int		close_window(t_scene *scene);
int		key_hook(int key, t_scene *scene);
int		mouse_hook(int button, int x, int y, t_scene *scene);
void	switch_camera_next(t_scene *scene);
t_vec3	get_input_vector(int key);
t_bool	hit_light(t_light *light, t_ray *ray, t_real radius);
void	action_camera(t_scene *scene, t_vec3 input_vector);
void	action_selection(t_scene *scene, t_vec3 input_vector);

#endif