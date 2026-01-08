/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_triangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:31:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 23:33:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	save_triangle_state(t_triangle *triangle)
{
	triangle->initial_p1 = triangle->p1;
	triangle->initial_p2 = triangle->p2;
	triangle->initial_p3 = triangle->p3;
}
