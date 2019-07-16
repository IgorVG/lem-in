/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 09:40:13 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:37:09 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		set_iterations(char **tbl)
{
	int	i;
	int num;

	i = 0;
	num = -1;
	while (tbl[i])
		i++;
	if (i == 2)
		num = ft_atoi(tbl[1]);
	i = 0;
	while (tbl[i])
	{
		free(tbl[i]);
		i++;
	}
	free(tbl);
	return (num);
}

static int		check_tag(char *line, t_graph *graph)
{
	char	**tbl;

	if (*line == '#')
	{
		if (!ft_strcmp(line, START))
			return (-1);
		else if (!ft_strcmp(line, END))
			return (-2);
		else if (ft_strchr(line, ':'))
		{
			tbl = ft_strsplit(line, ':');
			graph->iters = set_iterations(tbl);
		}
		return (1);
	}
	return (0);
}

/*
** read_file will be modified to append each line to *out in order to print
** the output in case of success;
*/

static void		read_file(t_graph *graph)
{
	int		rd;
	int		tag;
	char	*line;

	tag = 0;
	init_input(graph);
	while ((rd = get_next_line_lite(0, &line)) == 1)
	{
		if (!line)
			error(-1);
		if (!*line)
		{
			free(line);
			break ;
		}
		if (check_tag(line, graph) < 0)
			tag = check_tag(line, graph);
		else if (!check_tag(line, graph))
			append_graph(graph, line, &tag);
		retain_input(graph, line);
	}
	if (rd == -1)
		error(-1);
	if (!graph->start || !graph->end)
		error(-8);
}

static void		check_argc(t_graph *graph, int rc, char **rv)
{
	int	i;

	i = 0;
	while (rc > 1 && rv[1][0] == '-' && rv[1][i])
	{
		i++;
		if (rv[1][i] && rv[1][i] == 'v')
			graph->vis = 1;
		else if (rv[1][i])
			error(-10);
	}
}

int				main(int argc, char **argv)
{
	t_graph		*graph;

	init_graph(&graph);
	check_argc(graph, argc, argv);
	read_file(graph);
	find_paths(graph);
	find_shortest(graph);
	if (graph->vis)
		send_ants_view(graph);
	else
		send_ants(graph);
	ft_free();
	return (0);
}
