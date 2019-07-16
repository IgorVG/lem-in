/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_graph_lib_checks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:44:27 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/17 11:19:44 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_node		*check_node_exist(char *name, t_graph *graph)
{
	int	sldr;

	sldr = 0;
	while (sldr < NODES && graph->nodes[sldr & NODES_M].name)
	{
		if (!ft_strcmp(graph->nodes[sldr].name, name))
			return (&graph->nodes[sldr]);
		sldr++;
	}
	return (0);
}

char		check_edge_exist(t_node *node_1, t_node *node_2, t_graph *graph)
{
	int i;

	i = 0;
	while (i < EDGES && graph->edges[i & EDGES_M].a1)
	{
		if ((graph->edges[i].a1 == node_1 && graph->edges[i].a2 == node_2)
				|| (graph->edges[i].a1 == node_2
				&& graph->edges[i].a2 == node_1))
			return (1);
		i++;
	}
	return (0);
}

void		check_node_uniq(char **tbl, t_graph *graph)
{
	int		sldr;
	int		x;
	int		y;

	sldr = 0;
	x = ft_atoi(tbl[1]);
	y = ft_atoi(tbl[2]);
	while (sldr < NODES && graph->nodes[sldr & NODES_M].name)
	{
		if (!ft_strcmp(graph->nodes[sldr].name, tbl[0]))
			error(-4);
		if (graph->nodes[sldr].x == x && graph->nodes[sldr].y == y)
			error(-5);
		sldr++;
	}
}

void		append_edge(t_node *node_1, t_node *node_2, t_graph *graph)
{
	if (graph->hd_e < EDGES_M)
	{
		node_1->hd++;
		node_2->hd++;
		graph->hd_e++;
		graph->edges[graph->hd_e].a1 = node_1;
		graph->edges[graph->hd_e].a2 = node_2;
		node_1->edges[node_1->hd & EDGES_N_M] = &graph->edges[graph->hd_e];
		node_2->edges[node_2->hd & EDGES_N_M] = &graph->edges[graph->hd_e];
		if (node_1->hd >= EDGES_N_M || node_2->hd >= EDGES_N_M)
			error(-4);
	}
	else
		error(-4);
}

/*
** check if names exists;
** check that edge does not exist;
*/

void		check_append_edge(char **tbl, t_graph *graph)
{
	t_node	*node_1;
	t_node	*node_2;

	node_1 = check_node_exist(tbl[0], graph);
	node_2 = check_node_exist(tbl[1], graph);
	free(tbl[0]);
	free(tbl[1]);
	free(tbl);
	if (!node_1 || !node_2)
		error(-6);
	if (node_1 == node_2)
		error(-1);
	if (check_edge_exist(node_1, node_2, graph))
		error(-7);
	append_edge(node_1, node_2, graph);
}
