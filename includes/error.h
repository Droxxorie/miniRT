/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:39:27 by eraad             #+#    #+#             */
/*   Updated: 2025/12/09 17:21:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_SCENE_MEM "Failed to allocate scene"
# define ERR_SCENE_INIT "Failed to initialize scene"
# define ERR_MLX_INIT "Failed to initialize MLX"
# define ERR_SCENE_RENDER "Failed to render scene"
# define ERR_FILE_OPEN "Failed to open scene file" //? ou wrong fd ?
# define ERR_FILE_FORMAT "File format does not conform to .rt specifications"

void	print_error_exit(const char *error_message);
void	sys_print_error_exit(const char *error_message);
void	print_error(const char *error_message);
void	sys_print_error(const char *error_message);

#endif