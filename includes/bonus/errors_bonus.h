/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:18:47 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 11:09:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_BONUS_H
# define ERRORS_BONUS_H

# include "structs/s_scene_bonus.h"

//* ========================================================================= */
//*                                SYSTEM ERRORS                              */
//* ========================================================================= */
# define ERR_MEM "Memory allocation failed"
# define ERR_MEM_CAMERA "Failed to allocate camera structure"
# define ERR_MEM_SCENE "Failed to allocate scene structure"
# define ERR_MEM_LIGHT "Failed to allocate light structure"
# define ERR_MEM_OBJECT "Failed to allocate object structure"
# define ERR_THREAD "Thread creation failed"
# define ERR_ITOA "Integer to ASCII conversion failed"
# define ERR_MUTEX "Mutex initialization failed"
# define ERR_WRITE "File write operation failed"

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
# define ERR_SAVE_FILE "Cannot create or write to save file"
# define ERR_ARG "Invalid argument"
# define ERR_SAVE_EXT "Save file must have a .bmp extension"
# define ERR_DEBUG "Debug mode requires an argument: 'AO' or 'NORMAL'"
# define ERR_AA_OOB "Anti-aliasing samples out of range [1, 16]"

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
# define ERR_OPTION "Invalid option identifier, expected '-usemtl' or '-sdf'"

//* --- Colors --- */
# define ERR_RED "Invalid red color value"
# define ERR_RED_OOB "Red color value out of range [0, 255]"
# define ERR_GREEN "Invalid green color value"
# define ERR_GREEN_OOB "Green color value out of range [0, 255]"
# define ERR_BLUE "Invalid blue color value"
# define ERR_BLUE_OOB "Blue color value out of range [0, 255]"

//* --- Vectors & Points --- */
# define ERR_X "Invalid X component in vector"
# define ERR_UX_OOB "X component out of range [-1.0, 1.0]"
# define ERR_Y "Invalid Y component in vector"
# define ERR_UY_OOB "Y component out of range [-1.0, 1.0]"
# define ERR_Z "Invalid Z component in vector"
# define ERR_UZ_OOB "Z component out of range [-1.0, 1.0]"
# define ERR_W "Invalid W component in vector"
# define ERR_VEC3_ZERO "Vector cannot be the zero vector (0,0,0)"

//* --- Resolution --- */
# define ERR_RES_DUP "Duplicate resolution definition"
# define ERR_RES_WITDH "Invalid resolution width value"
# define ERR_RES_HEIGHT "Invalid resolution height value"
# define ERR_RES_WITDH_OOB "Resolution width out of range [1, 3840]"
# define ERR_RES_HEIGHT_OOB "Resolution height out of range [1, 2160]"

//* --- Light --- */
# define ERR_RATIO "Invalid ratio value"
# define ERR_RATIO_OOB "Value out of range [-1.0, 1.0]"
# define ERR_AMBIENT_DUP "Duplicate ambient light definition"

//* --- Camera --- */
# define ERR_FOV "Invalid field of view (FOV) value"
# define ERR_FOV_OOB "Camera FOV out of range ]0, 180["

//* --- Objects --- */
# define ERR_DIM "Invalid dimension value"
# define ERR_DIM_OOB "Dimension must be positive (> 0)"
# define ERR_BOOL "Invalid boolean value (expected TRUE or FALSE)"
# define ERR_SDF_DUP "SDF option already assigned to object"

//* --- Materials --- */
# define ERR_MTL_FILE "Could not open MTL file"
# define ERR_MTL_EXT "Invalid MTL file extension (expected .mtl)"
# define ERR_MTL_DEF "Material property defined before 'newmtl'"
# define ERR_MTL_UID "Unknown material property identifier"
# define ERR_MTL_OBJ "Material already assigned to object"
# define ERR_MTL_NF "Material not found in the material library"
# define ERR_MAT_DUP "Duplicate material name definition"

# define ERR_SKYBOX_DUP "Duplicate skybox texture definition"

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
void	print_error(const char *error_message);
void	sys_print_error(const char *error_message);
void	print_error_exit(const char *error_message);
void	sys_print_error_exit(const char *error_message);
void	print_error_free_exit(t_scene *scene, const char *error_message);
void	print_error_loc(t_scene *scene, char *current_pos, char *message);
void	print_error_detail(const char *error_message, const char *detail);
void	sys_print_error_free_exit(t_scene *scene, const char *error_message);
void	print_error_limit(t_scene *scene, char *start_ptr, char *entity_name,
			int limit);

#endif