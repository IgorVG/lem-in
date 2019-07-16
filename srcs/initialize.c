/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 14:15:15 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/18 15:31:22 by igarbuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_node(t_node *node)
{
	node->x = -1;
	node->y = -1;
	node->c = 1;
	node->name = NULL;
	node->hd = -1;
	node->visited = 0;
}

void	init_edge(t_edge *edge)
{
	edge->a1 = NULL;
	edge->a2 = NULL;
	edge->ignore = 0;
	edge->c1_2 = 1;
	edge->c2_1 = 1;
}

void	init_graph(t_graph **graph)
{
	int i;

	g_tofree.graph = graph;
	if (!(*graph = (t_graph *)malloc(sizeof(t_graph))))
		error(-3);
	i = NODES;
	while (--i >= 0)
		init_node(&(*graph)->nodes[i]);
	i = EDGES;
	while (--i >= 0)
		init_edge(&(*graph)->edges[i]);
	(*graph)->hd_n = -1;
	(*graph)->hd_e = -1;
	(*graph)->start = NULL;
	(*graph)->end = NULL;
	(*graph)->ants = -1;
	(*graph)->bfs = NULL;
	(*graph)->sent = 0;
	(*graph)->vis = 0;
	(*graph)->iters = -1;
}
