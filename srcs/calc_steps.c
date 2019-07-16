/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:05:59 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/17 18:46:14 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			solution_ln(t_solution *solution)
{
	t_path		*path;

	path = solution->path;
	solution->ln = -1;
	while (path)
	{
		path = path->next;
		solution->ln++;
	}
}

void				calc_paths_bfs(t_bfs *bfs)
{
	t_solution	*sol;
	int			i;

	while (bfs)
	{
		sol = bfs->sol_sort;
		i = 0;
		while (sol)
		{
			if (sol->is_valid)
			{
				solution_ln(sol);
				i++;
			}
			sol = sol->next;
		}
		bfs->paths = i;
		bfs = bfs->next;
	}
}

static int			find_cumul_length(t_solution *sol, int paths)
{
	int total_len;

	total_len = 0;
	while (sol && paths)
	{
		total_len += sol->ln;
		sol = sol->next;
		paths--;
	}
	return (total_len);
}

static void			calc_steps_solution(t_solution *sol, int ants, int paths)
{
	t_solution	*sol_tmp;
	int			i;

	sol_tmp = sol;
	i = 1;
	while (i <= paths)
	{
		sol->steps = ft_ceil((find_cumul_length(sol_tmp, i) + ants), i);
		sol = sol->next;
		i++;
	}
}

void				calc_steps_bfs(t_bfs *bfs, int ants)
{
	while (bfs)
	{
		if (bfs->paths)
			calc_steps_solution(bfs->sol_sort, ants, bfs->paths);
		bfs = bfs->next;
	}
}
