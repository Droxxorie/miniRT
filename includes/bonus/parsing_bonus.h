/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:14 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 15:45:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "structs/s_scene_bonus.h"

//* ========================================================================= */
//*                                PARSING                                    */
//* ========================================================================= */
t_status	parse_int(char **line, int *value);
t_status	parse_real(char **line, t_real *value);
t_status	parse_comma(t_scene *scene, char **line);
t_status	parse_dim(t_scene *scene, char **line, t_real *dim);
t_status	parse_axis(t_scene *scene, char **line, t_vec3 *axis);
t_status	parse_vec3(t_scene *scene, char **line, t_vec3 *vector);
t_status	parse_scene_file(t_scene *scene, const char *file_path);
t_status	parse_color(t_scene *scene, char **line, t_color *color);
t_status	parse_ratio(t_scene *scene, char **line, t_real *ratio,
				t_bool is_negative);

//* ========================================================================= */
//*                                OBJECTS                                    */
//* ========================================================================= */
t_status	parse_box(t_scene *scene, char **line);
t_status	parse_disk(t_scene *scene, char **line);
t_status	parse_cone(t_scene *scene, char **line);
t_status	parse_plane(t_scene *scene, char **line);
t_status	parse_torus(t_scene *scene, char **line);
t_status	parse_sphere(t_scene *scene, char **line);
t_status	parse_cylinder(t_scene *scene, char **line);
t_status	parse_triangle(t_scene *scene, char **line);
t_status	parse_rectangle(t_scene *scene, char **line);

//* ========================================================================= */
//*                                ENTITIES                                   */
//* ========================================================================= */
t_status	parse_light(t_scene *scene, char **line);
t_status	parse_camera(t_scene *scene, char **line);
t_status	parse_ambient(t_scene *scene, char **line);
t_status	parse_resolution(t_scene *scene, char **line);

//* ========================================================================= */
//*                                UTILS                                      */
//* ========================================================================= */
void		skip_whitespace(char **line);
int			get_light_count(t_light *lights);
int			get_camera_count(t_camera *cameras);
int			get_object_count(t_object *objects);
t_status	check_eol(t_scene *scene, char **line);
void		add_object_to_scene(t_scene *scene, t_object *object);
t_bool		has_extension(const char *file, const char *extension);
t_status	skip_required(t_scene *scene, char **line, const char *charset);

#endif