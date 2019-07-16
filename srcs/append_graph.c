/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:20:40 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/17 16:03:48 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		add_ants(char *line, t_graph *graph)
{
	graph->ants = check_number(line);
	if (graph->ants < 0)
		error(-1);
}

static void		add_node(char **tbl, t_graph *graph, int tag)
{
	check_node_uniq(tbl, graph);
	append_node(tbl, graph, tag);
}

static void		add_edge(char **tbl, t_graph *graph)
{
	check_append_edge(tbl, graph);
}

static void		update_dscp(int *graph_dscp, int type)
{
	if (*graph_dscp == 0 && type == 1)
		*graph_dscp += 2;
	else if (*graph_dscp == 2 && type == 3)
		*graph_dscp = 3;
}

/*
** *graph address is stored global variable g_tofree;
** it does not need to be passed as argument, but it is done
** to follow project structure;
*/

void			append_graph(t_graph *graph, char *line, int *tag)
{
	int			type;
	char		**tbl;
	static int	graph_dscp = 0;

	tbl = NULL;
	type = get_type(line, &tbl);
	if (graph_dscp == 0 && type == 1)
		add_ants(line, graph);
	else if (graph_dscp == 2 && type == 2)
		add_node(tbl, graph, *tag);
	else if ((graph_dscp == 2 || graph_dscp == 3) && type == 3)
		add_edge(tbl, graph);
	else
		error(-1);
	update_dscp(&graph_dscp, type);
	*tag = 0;
}
