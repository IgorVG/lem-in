/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_count_for_paths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:05:57 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/26 18:01:50 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

char		check_colisions(t_path *new_path, t_graph *graph)
{
	while (new_path)
	{
		if (new_path->node->c <= 0
				&& new_path->node != graph->start
				&& new_path->node != graph->end)
			return (1);
		new_path = new_path->next;
	}
	return (0);
}

int			forbidden_from_here(t_node *node, t_solution *solution)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i <= node->hd)
	{
		if (!can_we_go(node, node->edges[i], solution->path))
			j++;
		i++;
	}
	return (j);
}

int			is_visited_by(t_node *node, t_path *path)
{
	while (path)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

t_node		*can_we_go(t_node *node, t_edge *edge, t_path *path)
{
	int		cap;
	t_node	*node_to_check;

	node_to_check = (edge->a1 == node ? edge->a2 : edge->a1);
	cap = (edge->a1 == node ? edge->c1_2 : edge->c2_1);
	if (cap == 0 || is_visited_by(node_to_check, path) || edge->ignore)
		return (NULL);
	return (node_to_check);
}

char		is_skip(int branches, t_solution *curr_sol, t_graph *graph)
{
	return (!branches || curr_sol->last_node == graph->end
		|| curr_sol->backward >= MAX_BACK
		|| check_colisions(curr_sol->path, graph) != 0);
}
