/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:18:47 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:14:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_BONUS_H
# define ERRORS_BONUS_H

# include "structures_bonus.h"

//* ========================================================================= */
//*                                SYSTEM ERRORS                              */
//* ========================================================================= */
# define ERR_MEM "Memory allocation failed"
# define ERR_MEM_CAMERA "Failed to allocate camera structure"
# define ERR_MEM_SCENE "Failed to allocate scene structure"
# define ERR_MEM_LIGHT "Failed to allocate light structure"
# define ERR_MEM_OBJECT "Failed to allocate object structure"

//* ========================================================================= */
//*                            INITIALIZATION ERRORS                          */
//* ========================================================================= */
# define ERR_NO_AMB "No ambient light defined in the scene (missing 'A')"
# define ERR_NO_CAM "No camera defined in the scene (missing 'C')"
# define ERR_MLX "MLX initialization failed"
# define ERR_RES "Invalid resolution settings (width or height <= 0)"
# define ERR_WIN "Window creation failed"
# define ERR_IMG "Image creation failed"
# define ERR_GRAPHICS "Graphics initialization failed"
# define ERR_RENDER "Frame rendering failed"

//* ========================================================================= */
//*                               PARSING ERRORS                              */
//* ========================================================================= */
//* --- File & Syntax --- */
# define ERR_FILE_EXT "File format does not conform to .rt specifications"
# define ERR_EMPTY "Scene file is empty"
# define ERR_UID "Unknown identifier in scene file"
# define ERR_EOL "Unexpected characters at end of line (garbage found)"
# define ERR_COMMA "Missing required delimiter (comma)"
# define ERR_DELIM "Missing required delimiter (whitespace)"

//* --- Colors --- */
# define ERR_RED "Invalid red color value"
# define ERR_RED_OOR "Red color value out of range [0, 255]"
# define ERR_GREEN "Invalid green color value"
# define ERR_GREEN_OOR "Green color value out of range [0, 255]"
# define ERR_BLUE "Invalid blue color value"
# define ERR_BLUE_OOR "Blue color value out of range [0, 255]"

//* --- Vectors & Points --- */
# define ERR_X "Invalid X component in vector"
# define ERR_UX_OOR "X component out of range [-1.0, 1.0]"
# define ERR_Y "Invalid Y component in vector"
# define ERR_UY_OOR "Y component out of range [-1.0, 1.0]"
# define ERR_Z "Invalid Z component in vector"
# define ERR_UZ_OOR "Z component out of range [-1.0, 1.0]"
# define ERR_VEC3_ZERO "Vector cannot be the zero vector (0,0,0)"

//* --- Light --- */
# define ERR_RATIO "Invalid ratio value"
# define ERR_RATIO_OOR "Value out of range [-1.0, 1.0]"
# define ERR_AMBIENT_DUP "Duplicate ambient light definition"

//* --- Camera --- */
# define ERR_FOV "Invalid field of view (FOV) value"
# define ERR_FOV_OOR "Camera FOV out of range ]0, 180["

//* --- Objects --- */
# define ERR_D "Invalid diameter value"
# define ERR_H "Invalid height value"
# define ERR_D_OOR "Diameter must be positive (> 0)"
# define ERR_H_OOR "Cylinder height must be positive (> 0)"

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
void	print_error(const char *error_message);
void	sys_print_error(const char *error_message);
void	print_error_exit(const char *error_message);
void	print_line_context(t_scene *scene, char *pos);
void	sys_print_error_exit(const char *error_message);
void	print_error_free_exit(t_scene *scene, const char *error_message);
void	print_error_loc(t_scene *scene, char *current_pos, char *message);
void	sys_print_error_free_exit(t_scene *scene, const char *error_message);
void	print_error_limit(t_scene *scene, char *start_ptr, char *entity_name,
			int limit);

#endif