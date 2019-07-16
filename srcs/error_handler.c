/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 18:27:08 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/16 17:09:54 by igarbuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_all_solutions(t_solution *sol)
{
	t_path		*path;
	void		*next;

	while (sol)
	{
		path = sol->path;
		while (path)
		{
			next = path->next;
			free(path);
			path = (t_path*)next;
		}
		next = sol->next;
		free(sol);
		sol = (t_solution*)next;
	}
}

void		free_bfs(t_bfs *bfs)
{
	t_bfs		*next;

	while (bfs)
	{
		free_all_solutions(bfs->solution);
		free_all_solutions(bfs->sol_sort);
		next = bfs->next;
		free(bfs);
		bfs = next;
	}
}

void		free_input(t_input *in)
{
	int	i;

	i = 0;
	if (!in)
		return ;
	while (i < in->last)
	{
		free(in->buf[i]);
		i++;
	}
	free(in);
}

void		ft_free(void)
{
	int			i;

	i = 0;
	while ((*g_tofree.graph)->nodes[i].name && i < NODES)
	{
		free((*g_tofree.graph)->nodes[i].name);
		i++;
	}
	free_bfs((*g_tofree.graph)->bfs);
	free_input((*g_tofree.graph)->input);
	free(*g_tofree.graph);
}

void		error(int code)
{
	if (code == -1)
		write(1, "ERROR\n", 6);
	else if (code == -2)
		write(1, "ERROR: Can't allocate memory\n", 29);
	else if (code == -4)
		write(1, "ERROR: Can't append node, name exists\n", 38);
	else if (code == -5)
		write(1, "ERROR: Can't append node, coordinates exist\n", 44);
	else if (code == -6)
		write(1, "ERROR: Can't create edge: node doesn't exist\n", 45);
	else if (code == -7)
		write(1, "ERROR: Can't create edge: already exists\n", 41);
	else if (code == -8)
		write(1, "ERROR: There is no ##start and/or ##end\n", 40);
	else if (code == -9)
		write(1, "ERROR: input nodes overflow\n", 28);
	else if (code == -10)
		write(1, "usage: ./lem-in [-v] < map_file\n", 32);
	ft_free();
	exit(EXIT_FAILURE);
}
