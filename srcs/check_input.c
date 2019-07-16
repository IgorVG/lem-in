/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:51:01 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/17 11:24:49 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			ft_freetbl(char **tbl)
{
	int i;

	i = 0;
	while (tbl[i])
	{
		free(tbl[i]);
		i++;
	}
	free(tbl);
}

/*
** graph descriptor file is give in the format:
** n - number of ants (flow quants)
** nodes (name, x, y) - name and coordiantes of nodes
** edges (nameX-nameY) - list of edges connectig nodes
** ##start - tag that indicates that following node is the start
** ##end - tag that indicated that the following node is the end
** Starting and ending nodes has unlimited capacity, in oposite to all
** other nodes with the capacity c = 1; all edges also have the capacity c = 1;
** #[string] - comments that are ignored
** graphDescriptor is an ID:
** 0 - graph is emtpy; Initialized;
** 1 - N quants;
** 2 - nodes;
** 3 - edges;
*/

static int		tbllen(char **tbl)
{
	char **tmp;

	tmp = tbl;
	while (*tbl)
		tbl++;
	return ((int)(tbl - tmp));
}

/*
** get_type to be optimised : check order must depend on the current
** graph_dscp;
*/

char			get_type(char *line, char ***tbl)
{
	if ((*tbl = ft_strsplit(line, ' ')))
	{
		if (tbllen(*tbl) == 3)
		{
			check_node(*tbl);
			return (2);
		}
		ft_freetbl(*tbl);
	}
	if ((*tbl = ft_strsplit(line, '-')))
	{
		if (tbllen(*tbl) == 2)
		{
			check_edge(*tbl);
			return (3);
		}
		ft_freetbl(*tbl);
	}
	check_number(line);
	return (1);
}
