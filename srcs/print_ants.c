/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarbuz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 22:06:06 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/16 22:08:49 by igarbuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			print_path_ants(char *str, t_path *path)
{
	while (path && !path->ant)
		path = path->next;
	while (path && path->next && path->ant && path->next->ant)
	{
		if ((ft_sprintf(str, "L%d-%s ", path->ant, path->node->name)) == -1)
			error(-1);
		path = path->next;
	}
	if (path && path->ant)
	{
		if ((ft_sprintf(str, "L%d-%s", path->ant, path->node->name)) == -1)
			error(-1);
	}
	else
		return (0);
	return (1);
}

void		write_input(t_graph *graph)
{
	int i;

	i = 0;
	while (i < graph->input->last)
	{
		ft_printf("%s\n", graph->input->buf[i]);
		i++;
	}
	write(1, "\n", 1);
}

int			write_result(char *str, t_graph *graph)
{
	if ((ft_sprintf(str, "\n")) == -1)
		error(-1);
	write_input(graph);
	if (graph->ants)
		write(1, str, ft_strlen(str));
	return (1);
}
