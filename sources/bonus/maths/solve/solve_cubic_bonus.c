/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_cubic_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:25:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 01:04:58 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	solve_for_one_root(t_cubic *vars)
{
	vars->sqrt_delta = sqrt(vars->delta);
	vars->u = cbrt(-vars->q / 2.0 + vars->sqrt_delta);
	vars->v = cbrt(-vars->q / 2.0 - vars->sqrt_delta);
	vars->roots[0] = vars->u + vars->v - vars->a / 3.0;
	vars->roots_count = 1;
}

static void	solve_for_three_roots(t_cubic *vars)
{
	t_real	factor;
	t_real	offset;
	t_real	arg;

	if (fabs(vars->p) < EPSILON)
	{
		vars->roots_count = 1;
		vars->roots[0] = -vars->a / 3.0;
		return ;
	}
	factor = 2.0 * sqrt(-vars->p / 3.0);
	arg = -sqrt(-27.0 / (vars->cube_p)) * (vars->q / 2.0);
	if (arg < -1.0)
		arg = -1.0;
	else if (arg > 1.0)
		arg = 1.0;
	vars->phi = acos(arg);
	offset = vars->a / 3.0;
	vars->roots[0] = factor * cos(vars->phi / 3.0) - offset;
	vars->roots[1] = factor * cos((vars->phi + 2.0 * PI) / 3.0) - offset;
	vars->roots[2] = factor * cos((vars->phi + 4.0 * PI) / 3.0) - offset;
	vars->roots_count = 3;
}

static void	init_cubic_vars(t_cubic *vars)
{
	vars->a = vars->coeffs[2] / vars->coeffs[3];
	vars->b = vars->coeffs[1] / vars->coeffs[3];
	vars->c = vars->coeffs[0] / vars->coeffs[3];
	vars->sq_a = vars->a * vars->a;
	vars->p = vars->b - vars->sq_a / 3.0;
	vars->q = vars->a * (2.0 * vars->sq_a - 9.0 * vars->b) / 27 + vars->c;
	vars->cube_p = vars->p * vars->p * vars->p;
	vars->delta = (vars->q * vars->q) / 4.0 + (vars->cube_p) / 27.0;
}

t_bool	solve_cubic(t_cubic *vars)
{
	if (fabs(vars->coeffs[3]) < EPSILON)
		return (FALSE);
	init_cubic_vars(vars);
	if (vars->delta < 0)
		solve_for_three_roots(vars);
	else
		solve_for_one_root(vars);
	return (TRUE);
}
