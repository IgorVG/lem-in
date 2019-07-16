/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:20:38 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:33:46 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** K + N - 1 = number of steps to send K ants through path of length N;
** Start by sending all ants throught shortest and save the number
** of itterations;
** after send K - 1 to shortest and 1 to 2nd shortest;
** send not more than (K - n) + N1 - 1 <= n + N1 - 1;
** after, send (K - n1) + N1 - 1 >= (K - n2) + N2
*/

void			find_opt_solution(t_bfs *bfs)
{
	t_solution	*sol;
	int			i;

	sol = bfs->sol_sort;
	bfs->steps = sol->steps;
	bfs->opt_paths = 1;
	i = 1;
	while (sol)
	{
		if (sol->steps < bfs->steps)
		{
			bfs->steps = sol->steps;
			bfs->opt_paths = i;
		}
		i++;
		sol = sol->next;
	}
}

static void		find_opt_bfs(t_graph *graph)
{
	float		opt;
	t_bfs		*bfs;

	bfs = graph->bfs;
	while (bfs)
	{
		if (bfs->paths)
			find_opt_solution(bfs);
		bfs = bfs->next;
	}
	bfs = graph->bfs;
	opt = bfs->steps;
	graph->shortest = bfs;
	while (bfs)
	{
		if (bfs->paths && bfs->steps < opt)
		{
			opt = bfs->steps;
			graph->shortest = bfs;
		}
		bfs = bfs->next;
	}
}

static void		find_opt_ants(t_graph *graph)
{
	int			i;
	t_solution	*sol;

	i = 1;
	sol = graph->shortest->sol_sort;
	while (i < graph->shortest->opt_paths)
	{
		sol = sol->next;
		i++;
	}
	i = 0;
	while (sol && sol->prev)
	{
		sol->ants = graph->shortest->steps - sol->ln;
		sol->moving = sol->ants;
		i += sol->ants;
		sol = sol->prev;
	}
	sol->ants = graph->ants - i;
	sol->moving = sol->ants;
}

void			find_shortest(t_graph *graph)
{
	calc_steps_bfs(graph->bfs, graph->ants);
	find_opt_bfs(graph);
	find_opt_ants(graph);
}
