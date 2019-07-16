/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_reset_for_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:04:16 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/17 19:17:01 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		reset_edge_capacities(t_graph *graph)
{
	int		i;

	i = 0;
	while (i <= graph->hd_e)
	{
		graph->edges[i].c1_2 = 1;
		graph->edges[i].c2_1 = 1;
		if (&graph->nodes[i] == graph->start)
			graph->nodes[i].c = -1;
		else if (&graph->nodes[i] == graph->end)
			graph->nodes[i].c = -2;
		i++;
	}
}

void		reset_node_capacities(t_graph *graph)
{
	int		i;

	i = 0;
	while (i <= graph->hd_e)
	{
		graph->nodes[i].c = 1;
		graph->nodes[i].visited = 0;
		if (&graph->nodes[i] == graph->start || &graph->nodes[i] == graph->end)
			graph->nodes[i].c = -1;
		i++;
	}
}

void		capacity_to_zero(t_path *path)
{
	char	*capacity_to_change;

	while (path)
	{
		if (path->next)
		{
			capacity_to_change = (path->edge->a1 == path->node ?
				&path->edge->c1_2 : &path->edge->c2_1);
			*capacity_to_change = 0;
		}
		path->node->c--;
		path = path->next;
	}
}

void		check_colisions_and_reset(t_graph *graph)
{
	int		i;
	int		reset;

	reset = 0;
	i = 0;
	while (i <= graph->hd_e)
	{
		if (graph->edges[i].c1_2 + graph->edges[i].c2_1 == 0)
		{
			reset = 1;
			graph->edges[i].ignore = 1;
		}
		i++;
	}
	reset_node_capacities(graph);
	if (reset)
		reset_edge_capacities(graph);
}

void		clone_solution_field(t_solution *sol, t_solution *copy, char x)
{
	copy->last_edge = sol->last_edge;
	copy->last_node = sol->last_node;
	copy->ln = sol->ln;
	if (x)
	{
		copy->next = sol->next;
		copy->prev = sol;
		if (sol->next)
			sol->next->prev = copy;
		sol->next = copy;
	}
}
