/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:47:04 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:19:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "graphics.h"

void		skip_whitespace(char **line);
t_status	skip_required(char **line, const char *charset);
t_status	check_eol(char **line);
t_status	parse_int(char **line, int *value);
t_status	parse_real(char **line, t_real *value);
t_status	parse_comma(char **line);
t_status	parse_color(char **line, t_color *color);
t_status	parse_vec3(char **line, t_vec3 *vector);
t_status	parse_ratio(char **line, t_real *ratio, t_bool is_negative);
void		add_object_to_scene(t_scene *scene, t_object *object);
int			get_light_count(t_light *lights);
int			get_camera_count(t_camera *cameras);
int			get_object_count(t_object *objects);

t_status	parse_scene_file(t_scene *scene, const char *file_path);
t_status	parse_ambient(t_scene *scene, char **line);
t_status	parse_camera(t_scene *scene, char **line);
t_status	parse_light(t_scene *scene, char **line);
t_status	parse_sphere(t_scene *scene, char **line);
t_status	parse_plane(t_scene *scene, char **line);
t_status	parse_cylinder(t_scene *scene, char **line);

#endif