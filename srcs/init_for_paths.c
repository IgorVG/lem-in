/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:59:15 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/26 12:59:53 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		*init_path(t_node *first)
{
	t_path		*new_path;

	if (!(new_path = (t_path*)malloc(sizeof(t_path))))
		error(-2);
	new_path->node = first;
	new_path->edge = NULL;
	new_path->next = NULL;
	new_path->prev = NULL;
	new_path->ant = 0;
	return (new_path);
}

t_solution	*init_solution(t_node *first)
{
	t_solution	*new_solution;

	if (!(new_solution = (t_solution*)malloc(sizeof(t_solution))))
		error(-2);
	new_solution->path = init_path(first);
	new_solution->last_step = new_solution->path;
	new_solution->last_node = first;
	new_solution->last_edge = NULL;
	new_solution->next = NULL;
	new_solution->prev = NULL;
	new_solution->is_valid = 0;
	new_solution->ln = -1;
	new_solution->moving = 0;
	new_solution->ants = 0;
	new_solution->rotated = 0;
	new_solution->backward = 0;
	return (new_solution);
}

t_bfs		*init_bfs(t_node *first)
{
	t_bfs	*new_bfs;

	if (!(new_bfs = (t_bfs*)malloc(sizeof(t_bfs))))
		error(-2);
	new_bfs->solution = init_solution(first);
	new_bfs->sol_sort = NULL;
	new_bfs->last_sol_sort = NULL;
	new_bfs->next = NULL;
	new_bfs->there_is_path = 0;
	new_bfs->paths = 1;
	return (new_bfs);
}

t_bfs		*push_new_bfs(t_graph *graph)
{
	t_bfs	*new_bfs;

	new_bfs = init_bfs(graph->start);
	if (!graph->bfs)
		graph->bfs = new_bfs;
	else
		graph->curr_bfs->next = new_bfs;
	return (new_bfs);
}

t_solution	*copy_solution(t_solution *sol, t_solution *copy, char x)
{
	t_path			*path;
	t_path			*copy_path;

	path = sol->path;
	while (path)
	{
		if (!copy)
		{
			copy = init_solution(path->node);
			copy->path->edge = path->edge;
			copy_path = copy->path;
		}
		else
		{
			copy_path->next = init_path(path->node);
			copy_path->next->prev = copy_path;
			copy_path->next->edge = path->edge;
			copy_path = copy_path->next;
		}
		path = path->next;
	}
	copy->last_step = copy_path;
	copy->backward = sol->backward;
	clone_solution_field(sol, copy, x);
	return (copy);
}
