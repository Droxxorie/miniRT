/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:15:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_BONUS_H
# define INPUTS_BONUS_H

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
t_vec3	get_input_vector(int key);
void	input_manager(t_scene *scene);
int		key_hook(int key, t_scene *scene);
void	switch_camera_next(t_scene *scene);
t_bool	try_select_light(t_scene *scene, t_ray *ray);
void	action_camera(t_scene *scene, t_vec3 input_vector);
t_bool	hit_light(t_light *light, t_ray *ray, t_real radius);
int		mouse_hook(int button, int x, int y, t_scene *scene);
void	action_selection(t_scene *scene, t_vec3 input_vector);

#endif