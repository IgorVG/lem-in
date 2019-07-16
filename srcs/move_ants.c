/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:06:29 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:38:31 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		move_ants_path(t_path *path, t_graph *graph, t_solution *sol)
{
	while (path && path->next && !path->ant
			&& graph->sent >= graph->shortest->opt_paths)
		path = path->next;
	while (path && path->next && path->ant)
		path = path->next;
	if (path->node == graph->end && sol->moving > 0)
		sol->moving--;
	while (path && path->prev && path->prev->ant)
	{
		path->ant = path->prev->ant;
		path = path->prev;
	}
	if (graph->sent < graph->ants && sol->ants > 0)
	{
		graph->sent++;
		sol->ants--;
		path->ant = graph->sent;
	}
	else
		path->ant = 0;
}

static int		check_graph_empty(t_solution *sol)
{
	while (sol && !sol->moving)
		sol = sol->next;
	if (!sol)
		return (1);
	return (0);
}

static int		update_graph_ants(char *str, t_graph *graph)
{
	int			i;
	t_solution	*sol;
	t_path		*path;

	sol = graph->shortest->sol_sort;
	i = graph->shortest->opt_paths;
	while (i > 0)
	{
		path = sol->path;
		move_ants_path(path->next, graph, sol);
		if (print_path_ants(str, path->next) && i > 1)
			if ((ft_sprintf(str, " ")) == -1)
				error(-1);
		if (graph->sent == graph->ants
				&& check_graph_empty(graph->shortest->sol_sort))
		{
			return (write_result(str, graph));
		}
		sol = sol->next;
		i--;
	}
	if ((ft_sprintf(str, "\n")) == -1)
		error(-1);
	return (0);
}

void			send_ants(t_graph *graph)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char)
			* BUFF_SIZE_LEMIN & BUFF_SIZE_LEMIN_M)))
		error(-2);
	*str = '\0';
	while (!update_graph_ants(str, graph))
		;
	free(str);
}

void			send_ants_view(t_graph *graph)
{
	char		*str;
	t_sdl		sdl;

	if (!(str = (char*)malloc(sizeof(char)
			* BUFF_SIZE_LEMIN & BUFF_SIZE_LEMIN_M)))
		error(-2);
	if (!(sdl_init(graph, &sdl)))
		sdl_exit(&sdl);
	*str = '\0';
	while (!update_graph_ants(str, graph))
		viewer(graph, &sdl);
	sdl_exit(&sdl);
	free(str);
}
