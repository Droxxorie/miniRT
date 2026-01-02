/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 22:29:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:41:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	solve_quadratic(t_poly *vars)
{
	t_real	delta;
	t_real	sqrt_delta;
	t_real	inv_a;

	delta = (vars->half_b * vars->half_b) - (vars->a * vars->c);
	if (delta < 0)
		return (FALSE);
	sqrt_delta = sqrt(delta);
	if (vars->a != 0)
		inv_a = 1 / vars->a;
	else
		return (FALSE);
	vars->root1 = (-vars->half_b - sqrt_delta) * inv_a;
	vars->root2 = (-vars->half_b + sqrt_delta) * inv_a;
	return (TRUE);
}
