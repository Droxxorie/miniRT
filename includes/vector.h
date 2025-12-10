/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:07:38 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 09:41:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define U_X 0
# define U_Y 1
# define U_Z 2

typedef double	t_real;
typedef t_vec3	t_point3;

typedef struct s_vec2
{
	t_real	u;
	t_real	v;
}	t_vec2;

typedef struct s_vec3
{
	t_real	x;
	t_real	y;
	t_real	z;
}	t_vec3;

#endif