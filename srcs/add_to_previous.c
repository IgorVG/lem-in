/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_previous.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 17:54:55 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/27 14:02:33 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		copy_solution_to(t_solution *new_sol,
			t_bfs *bfs)
{
	t_solution	*sol_to_paste;
	t_solution	*copy;

	sol_to_paste = bfs->sol_sort;
	copy = copy_solution(new_sol, NULL, 0);
	if (!sol_to_paste)
		return ;
	while (sol_to_paste && sol_to_paste->next)
	{
		if (sol_to_paste->ln > new_sol->ln)
			break ;
		sol_to_paste = sol_to_paste->next;
	}
	if (sol_to_paste->ln > new_sol->ln)
		copy_before(copy, sol_to_paste, bfs);
	else
		copy_after(copy, sol_to_paste, bfs);
	bfs->paths++;
}

char		q_a(t_node *node, t_graph *graph)
{
	return (node != graph->start && node != graph->end);
}

char		no_name(t_solution *new_sol,
			t_graph *graph, t_bfs *bfs)
{
	return (!bfs || !bfs->next || (new_sol->path
		&& new_sol->path->node == graph->start && new_sol->path->next
		&& new_sol->path->next->node == graph->end
		&& bfs->sol_sort->path && bfs->sol_sort->path->node == graph->start
		&& bfs->sol_sort->path->next
		&& bfs->sol_sort->path->next->node == graph->end));
}

void		check_add_to_previous(t_solution *new_sol,
			t_graph *graph, t_bfs *bfs)
{
	t_path		*path;
	t_path		*prev_path;
	t_solution	*prev_sol;

	if (no_name(new_sol, graph, bfs))
		return ;
	prev_sol = bfs->sol_sort;
	while (prev_sol)
	{
		prev_path = prev_sol->path;
		while (prev_path)
		{
			path = new_sol->path;
			while (path)
			{
				if (prev_path->node == path->node && q_a(path->node, graph))
					return (check_add_to_previous(new_sol, graph, bfs->next));
				path = path->next;
			}
			prev_path = prev_path->next;
		}
		prev_sol = prev_sol->next;
	}
	copy_solution_to(new_sol, bfs);
	check_add_to_previous(new_sol, graph, bfs->next);
}
