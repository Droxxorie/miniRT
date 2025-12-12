/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:39:27 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 18:54:52 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_MEM "Memory allocation failed"
# define ERR_MEM_CAMERA "Failed to allocate camera"
# define ERR_MEM_SCENE "Failed to allocate scene"
# define ERR_MEM_LIGHT "Failed to allocate light"
# define ERR_MEM_OBJECT "Failed to allocate object"
# define ERR_MEM_SPHERE "Failed to allocate sphere"
# define ERR_MEM_PLANE "Failed to allocate plane"
# define ERR_MEM_CYLINDER "Failed to allocate cylinder"

# define ERR_INIT_NO_CAM "No camera defined in the scene (missing 'C')"
# define ERR_INIT_NO_AMB "No ambient light defined in the scene (missing 'A')"
# define ERR_INIT_MLX "Failed to initialize MLX"
# define ERR_INIT_RES "Invalid resolution settings"
# define ERR_INIT_WIN "Failed to create window"
# define ERR_INIT_FB "Failed to initialize frame buffer"
# define ERR_INIT_GRAPHICS "Failed to initialize graphics"
# define ERR_INIT_SCENE "Failed to initialize scene"

# define ERR_RENDER "Failed to render scene"

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
# define ERR_PARSE_MAX_LIGHTS "Exceeded maximum number of lights"
# define ERR_PARSE_MAX_CAMERAS "Exceeded maximum number of cameras"
# define ERR_PARSE_MAX_OBJECTS "Exceeded maximum number of objects"

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
void	print_error_limit(const char *entity_name, int limit);

#endif