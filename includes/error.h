/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:39:27 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 12:17:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_MEM "Memory allocation failed"
# define ERR_CAMERA_MEM "Failed to allocate camera"
# define ERR_SCENE_MEM "Failed to allocate scene"
# define ERR_LIGHT_MEM "Failed to allocate light"
# define ERR_OBJ_MEM "Failed to allocate object"
# define ERR_SPHERE_MEM "Failed to allocate sphere"
# define ERR_PLANE_MEM "Failed to allocate plane"
# define ERR_CYLINDER_MEM "Failed to allocate cylinder"

# define ERR_INIT_NO_CAM "No camera defined in the scene (missing 'C')"
# define ERR_INIT_NO_AMB "No ambient light defined in the scene (missing 'A')"
# define ERR_INIT_RES "Invalid resolution settings"

# define ERR_SCENE_INIT "Failed to initialize scene"
# define ERR_SCENE_RENDER "Failed to render scene"

# define ERR_MLX_INIT "Failed to initialize MLX"

# define ERR_FILE_OPEN "Failed to open scene file" //? ou wrong fd ?
# define ERR_FILE_FORMAT "File format does not conform to .rt specifications"

# define ERR_PARSE_UID "Unknown identifier in scene file"
# define ERR_PARSE_OOR "Value out of range [-1.0, 1.0]"
# define ERR_PARSE_NUM "Failed to parse number"
# define ERR_PARSE_DELIM "Expected delimiters not found"
# define ERR_PARSE_EOL "Unexpected characters at end of line (garbage found)"
# define ERR_PARSE_COMMA "Expected comma ',' not found"
# define ERR_PARSE_VEC3 "Failed to parse vec3"
# define ERR_PARSE_SP_D "Sphere diameter must be positive"
# define ERR_PARSE_CYL_D "Cylinder diameter must be positive"
# define ERR_PARSE_CYL_H "Cylinder height must be positive"
# define ERR_PARSE_CYL_A "Cylinder axis vector cannot be zero vector"
# define ERR_PARSE_PL_N "Plane normal vector cannot be zero vector"

# define ERR_AMBIENT_DUPL "Duplicate ambient light definition"
# define ERR_COLOR_RANGE "Color value out of range [0, 255]"
# define ERR_CAMERA_DIR "Camera direction vector cannot be zero vector"
# define ERR_FOV_RANGE "Camera FOV out of range ]0, 180["

void	print_error_exit(const char *error_message);
void	sys_print_error_exit(const char *error_message);
void	print_error(const char *error_message);
void	sys_print_error(const char *error_message);
void	print_error_free_exit(t_scene *scene, const char *error_message);
void	sys_print_error_free_exit(t_scene *scene, const char *error_message);

#endif