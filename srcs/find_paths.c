/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 12:40:27 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/26 18:00:39 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			add_edge_and_node_to_path(t_solution *sol, t_edge *edge,
					t_node *node)
{
	t_path		*path;

	path = sol->last_step;
	path->next = init_path(node);
	path->next->prev = path;
	path->edge = edge;
	sol->last_edge = edge;
	sol->last_node = node;
	sol->last_step = path->next;
	if (node->visited)
		sol->backward++;
	node->visited = 1;
	sol->ln++;
}

static void			check_new_solution(t_graph *graph, t_solution *new_sol,
					t_solution **curr_sol)
{
	t_solution	*next;

	next = new_sol->next;
	if (new_sol->last_node == graph->end)
	{
		path_is_found(new_sol, graph->curr_bfs, graph);
		if (new_sol == *curr_sol)
			*curr_sol = next;
	}
}

static void			append_next_step(t_graph *graph, t_solution *curr_sol,
					int branches, int *stop_if_zero)
{
	int			i;
	int			j;
	t_node		*next_node;
	t_edge		*next_edge;
	t_solution	*new_sol;

	i = 0;
	j = -1;
	while (i < branches && ++j >= 0)
	{
		next_edge = curr_sol->last_node->edges[j];
		if (!(next_node = can_we_go(curr_sol->last_node, next_edge,
				curr_sol->path)))
			continue ;
		*stop_if_zero = 1;
		new_sol = curr_sol;
		if (i + 1 != branches)
		{
			++graph->curr_bfs->paths;
			new_sol = copy_solution(curr_sol, NULL, 1);
		}
		add_edge_and_node_to_path(new_sol, next_edge, next_node);
		check_new_solution(graph, new_sol, &curr_sol);
		i++;
	}
}

static char			apply_bfs(t_graph *graph, int stop_if_zero,
					t_solution *curr_sol, t_solution *rem_sol)
{
	t_solution	*next;
	int			branches;

	while (stop_if_zero)
	{
		stop_if_zero = 0;
		curr_sol = graph->curr_bfs->solution;
		while (curr_sol)
		{
			next = curr_sol->next;
			branches = 1 + curr_sol->last_node->hd
				- forbidden_from_here(curr_sol->last_node, curr_sol);
			if (is_skip(branches, curr_sol, graph))
			{
				rem_sol = curr_sol;
				curr_sol = curr_sol->next;
				if (rem_sol->last_node != graph->end)
					remove_solution(graph->curr_bfs, rem_sol);
				continue ;
			}
			append_next_step(graph, curr_sol, branches, &stop_if_zero);
			curr_sol = next;
		}
	}
	return (graph->curr_bfs->there_is_path);
}

void				find_paths(t_graph *graph)
{
	int		found;
	int		count;

	count = MAX_ITER;
	found = 1;
	while (found == 1 && count--)
	{
		graph->curr_bfs = push_new_bfs(graph);
		found = apply_bfs(graph, 1, NULL, NULL);
		if (found)
		{
			calc_steps_bfs(graph->curr_bfs, graph->ants);
			if (graph->curr_bfs->paths)
				find_opt_solution(graph->curr_bfs);
			check_colisions_and_reset(graph);
			if (graph->curr_bfs->steps <= graph->iters)
				break ;
		}
	}
	if (!graph->bfs->there_is_path)
		error(-1);
}
