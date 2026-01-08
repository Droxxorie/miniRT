/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 14:44:14 by eraad            ###   ########.fr       */
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
void	switch_light_next(t_scene *scene);
void	switch_camera_next(t_scene *scene);
void	action_camera(t_scene *scene, t_vec3 input_vector);
int		mouse_hook(int button, int x, int y, t_scene *scene);
void	action_selection(t_scene *scene, t_vec3 input_vector);
t_vec3	get_camera_relative_vector(t_vec3 input, t_camera *camera);

//* --- Handle Keys --- */
void	handle_t_key(t_scene *scene);
void	handle_c_key(t_scene *scene);
void	handle_l_key(t_scene *scene);
void	handle_tab_key(t_scene *scene);
t_bool	handle_space_key(t_scene *scene);
void	handle_h_key(void);
void	handle_r_key(t_scene *scene);
void	handle_enter_key(t_scene *scene);

//* --- Handle Mouse --- */
t_bool	handle_scroll(int button, t_scene *scene);
void	handle_left_click(t_scene *scene, int x, int y);

#endif