/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:13:41 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 18:29:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <mlx.h>
# include <vector.h>

typedef struct s_buffer
{
	void *img;
	char *addr;
	int	bpp; 	   // bits per pixel
	int size;
	int row_size;
	int width;
	int height;
	int	endian;
	int de_gamma;
}	t_buffer;

typedef struct s_window
{
	void	*ptr;
	void	*win;
	int		width;
	int		height;
	t_real	aspect_ratio;
}	t_window;

typedef enum e_buftype
{
	BUFFER_MISSIING,
	BUFFER_IMAGE,
	BUFFER_TEXTURE,
	BUFFER_FILTER,
	BUFFER_DEBUG
}	t_buftype;

#endif