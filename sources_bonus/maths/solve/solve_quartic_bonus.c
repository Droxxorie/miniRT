/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quartic_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:33:56 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:40:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	normalize_coeffs(t_quartic *vars)
{
	t_real	a_inv;

	a_inv = 1.0 / vars->coeffs[4];
	vars->a = vars->coeffs[3] * a_inv;
	vars->b = vars->coeffs[2] * a_inv;
	vars->c = vars->coeffs[1] * a_inv;
	vars->d = vars->coeffs[0] * a_inv;
}

static void	solve_resolvent(t_quartic *vars)
{
	vars->sq_a = vars->a * vars->a;
	vars->cubic_vars.coeffs[3] = 1.0;
	vars->cubic_vars.coeffs[2] = -vars->b;
	vars->cubic_vars.coeffs[1] = vars->a * vars->c - 4.0 * vars->d;
	vars->cubic_vars.coeffs[0] = -vars->sq_a * vars->d + 4.0 * vars->b * vars->d
		- vars->c * vars->c;
	solve_cubic(&vars->cubic_vars);
	vars->y = vars->cubic_vars.roots[0];
}

static void	set_quartic_roots(t_quartic *vars, t_real t1, t_real t2)
{
	t_real	discrim_e;
	t_real	discrim_f;

	discrim_e = t1 + t2;
	discrim_f = t1 - t2;
	vars->roots_count = 0;
	if (discrim_e > -EPSILON)
	{
		vars->e = sqrt(fmax(discrim_e, 0.0));
		vars->roots[vars->roots_count++] = -vars->a / 4.0 + (vars->r_var
				+ vars->e) / 2.0;
		vars->roots[vars->roots_count++] = -vars->a / 4.0 + (vars->r_var
				- vars->e) / 2.0;
	}
	if (discrim_f > -EPSILON)
	{
		vars->f = sqrt(fmax(discrim_f, 0.0));
		vars->roots[vars->roots_count++] = -vars->a / 4.0 - (vars->r_var
				+ vars->f) / 2.0;
		vars->roots[vars->roots_count++] = -vars->a / 4.0 - (vars->r_var
				- vars->f) / 2.0;
	}
}

static t_bool	compute_ferrari_vars(t_quartic *vars)
{
	t_real	delta;
	t_real	t1;
	t_real	t2;

	delta = vars->sq_a / 4.0 - vars->b + vars->y;
	if (delta < -EPSILON)
		return (FALSE);
	vars->r_var = sqrt(fmax(delta, 0.0));
	if (vars->r_var < EPSILON)
	{
		t1 = 3.0 * vars->sq_a / 4.0 - 2.0 * vars->b;
		t2 = 2.0 * sqrt(fmax(vars->y * vars->y - 4.0 * vars->d, 0.0));
	}
	else
	{
		t1 = 3.0 * vars->sq_a / 4.0 - vars->r_var * vars->r_var - 2.0 * vars->b;
		t2 = (4.0 * vars->a * vars->b - 8.0 * vars->c - vars->a * vars->sq_a)
			/ (4.0 * vars->r_var);
	}
	set_quartic_roots(vars, t1, t2);
	return (TRUE);
}

t_bool	solve_quartic(t_quartic *vars)
{
	if (fabs(vars->coeffs[4]) < EPSILON)
		return (FALSE);
	normalize_coeffs(vars);
	solve_resolvent(vars);
	if (compute_ferrari_vars(vars) == FALSE)
		return (FALSE);
	if (vars->roots_count == 0)
		return (FALSE);
	return (TRUE);
}
