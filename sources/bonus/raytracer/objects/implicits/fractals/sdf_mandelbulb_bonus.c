/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_mandelbulb_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 23:43:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_mandelbulb(t_point3 p, t_object *object) //? max ité / bailout ?
{
	t_vec3	z;
	t_real	dr;
	t_real	r;
	t_real	theta;
	t_real	phi;
	t_real	zr;
	int		i;
	t_real	power;

	dr = 1.0;
	r = 0.0;
	power = object->u_data.mandelbulb.power;
	z = p;
	i = 0;
	while (i < 15)
	{
		r = vec3_len(z);
		if (r > 2.0)
			break ;
		theta = acos(z.y / r);
		phi = atan2(z.z, z.x);
		dr = pow(r, power - 1.0) * power * dr + 1.0;
		zr = pow(r, power);
		theta = theta * power;
		phi = phi * power;
		z.x = zr * sin(theta) * cos(phi);
		z.y = zr * cos(theta);
		z.z = zr * sin(theta) * sin(phi);
		z = vec3_add(z, p);
		i++;
	}
	return (0.5 * log(r) * r / dr);
}
