/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_graph_lib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:44:27 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/16 17:12:55 by igarbuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		update_tag(t_graph *graph, int tag)
{
	if (tag)
	{
		if (tag == -1 && !graph->start)
			graph->start = &graph->nodes[graph->hd_n];
		else if (tag == -2 && !graph->end)
			graph->end = &graph->nodes[graph->hd_n];
		else if (tag == -1 || tag == -2)
			error(-1);
		graph->nodes[graph->hd_n].c = tag;
	}
}

void			append_node(char **tbl, t_graph *graph, int tag)
{
	if (graph->hd_n < NODES - 1)
	{
		graph->hd_n++;
		graph->nodes[graph->hd_n].name = tbl[0];
		graph->nodes[graph->hd_n].x = ft_atoi(tbl[1]);
		graph->nodes[graph->hd_n].y = ft_atoi(tbl[2]);
		update_tag(graph, tag);
		free(tbl[1]);
		free(tbl[2]);
		free(tbl);
	}
	else
		error(-9);
}
