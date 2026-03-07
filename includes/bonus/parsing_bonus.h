/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:14 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 10:26:39 by eraad            ###   ########.fr       */
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
t_status	parse_dim_relative(t_scene *scene, char **line, t_real *dim);
t_status	parse_axis(t_scene *scene, char **line, t_vec3 *axis);
t_status	parse_vec3(t_scene *scene, char **line, t_vec3 *vector);
t_status	parse_vec4(t_scene *scene, char **line, t_vec4 *vector);
t_status	parse_scene_file(t_scene *scene, const char *file_path);
t_status	parse_color(t_scene *scene, char **line, t_color *color);
t_status	parse_ratio(t_scene *scene, char **line, t_real *ratio,
				t_bool is_negative);
t_status	parse_bool(t_scene *scene, char **line, t_bool *value);
t_status	parse_sdf(t_scene *scene, char **line, t_object *object);
t_status	parse_options(t_scene *scene, char **line, t_object *object);

//* ========================================================================= */
//*                                OBJECTS                                    */
//* ========================================================================= */
//* Parametric Objects */
t_status	parse_box(t_scene *scene, char **line);
t_status	parse_disk(t_scene *scene, char **line);
t_status	parse_cone(t_scene *scene, char **line);
t_status	parse_plane(t_scene *scene, char **line);
t_status	parse_torus(t_scene *scene, char **line);
t_status	parse_sphere(t_scene *scene, char **line);
t_status	parse_obj(t_scene *scene, char **line);
t_status	parse_cylinder(t_scene *scene, char **line);
t_status	parse_triangle(t_scene *scene, char **line);
t_status	parse_rectangle(t_scene *scene, char **line);
//* Implicit Objects */
t_status	parse_menger_sponge(t_scene *scene, char **line);
t_status	parse_mandelbulb(t_scene *scene, char **line);
t_status	parse_mandelbox(t_scene *scene, char **line);
t_status	parse_julia_set(t_scene *scene, char **line);

//* ========================================================================= */
//*                                ENTITIES                                   */
//* ========================================================================= */
t_status	parse_camera(t_scene *scene, char **line);
t_status	parse_ambient(t_scene *scene, char **line);
t_status	parse_resolution(t_scene *scene, char **line);
t_status	parse_skybox(t_scene *scene, char **line);
t_status	parse_aa(t_scene *scene, char **line);
t_status	parse_filter(t_scene *scene, char **line);
//* ---- Light ---- *//
t_light		*alloc_new_light(t_scene *scene, char **line);
void		add_light_to_scene(t_scene *scene, t_light *new_light);
void		init_quad_light(t_light *light);
void		init_spot_light(t_light *light, t_real cutoff_angle);
t_status	parse_light(t_scene *scene, char **line);
t_status	parse_sun(t_scene *scene, char **line);
t_status	parse_spot(t_scene *scene, char **line);
t_status	parse_quad(t_scene *scene, char **line);

//* ========================================================================= */
//*                                UTILS                                      */
//* ========================================================================= */
t_status	dispatch_parse(t_scene *scene, char *line);
void		skip_whitespace(char **line);
int			get_light_count(t_light *lights);
int			get_camera_count(t_camera *cameras);
int			get_object_count(t_object *objects);
t_status	check_eol(t_scene *scene, char **line);
void		add_object_to_scene(t_scene *scene, t_object *object);
t_bool		has_extension(const char *file, const char *extension);
t_status	skip_required(t_scene *scene, char **line, const char *charset);
void		init_fractal_matrix(t_object *obj, t_point3 position, t_vec3 normal,
				t_real size);
t_status	match_and_consume(char **line, const char *identifier);

//* ========================================================================= */
//*                                MATERIALS                                  */
//* ========================================================================= */
char		*extract_string(char **line);
t_material	*find_material(t_material *materials, char *name);
t_status	parse_texture_path(char **line, char **texture_path);
t_status	parse_illum(char **line, t_material **material);
t_status	parse_color_mtl(char **line, t_color *color);
t_status	parse_roughness(char **line, t_material *material);
t_status	parse_newmtl(t_scene *scene, t_material **current, char **line);
t_status	dispatch_mtl_line(t_scene *scene, t_material **current, char *line);
t_status	parse_mtl_lib(t_scene *scene, char **line);
t_status	parse_usemtl(t_scene *scene, char **line, t_object *object);
t_status	parse_pattern(char **line, t_material *material);

t_status	parse_obj_vertex(t_scene *scene, t_obj_data *data, char **line);
t_status	parse_obj_normal(t_scene *scene, t_obj_data *data, char **line);
t_status	parse_obj_texcoord(t_scene *scene, t_obj_data *data, char **line);
t_status	parse_obj_face(t_scene *scene, t_obj_data *data, char **line);
t_vec3		transform_vertex(t_vec3 v, t_obj_data *data);
void		init_obj_triangle(t_object *obj, t_vec3 p[3], t_vec2 uv[3]);
t_bool		check_obj_indices(t_obj_data *data, int *v_idx);
t_status	parse_obj_mtllib(t_scene *scene, t_obj_data *data, char **line);
t_status	parse_obj_usemtl(t_scene *scene, t_obj_data *data, char **line);
t_status	dispatch_obj_line(t_scene *scene, t_obj_data *data, char *line);
t_status	process_obj_line(t_scene *scene, int fd, t_obj_data *data);

#endif