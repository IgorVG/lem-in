/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:11:55 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:37:52 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_graph(t_graph *graph)
{
	int i;
	int j;

	ft_printf("graph lenght: %d\n", graph->hd_n + 1);
	ft_printf("graph edges: %d\n", graph->hd_e + 1);
	ft_printf("ants: %d\n", graph->ants);
	ft_printf("start: %s\n", graph->start->name);
	ft_printf("end: %s\n", graph->end->name);
	i = 0;
	while (i <= graph->hd_e) {
		ft_printf("edge: %s - %s\n", graph->edges[i].a1->name, graph->edges[i].a2->name);
		i++;
	}
	i = 0;
	while (i <= graph->hd_n)
	{
		ft_printf("\nNode name: %s\n", graph->nodes[i].name);
		ft_printf("edges: %d\n", graph->nodes[i].hd + 1);
		ft_printf("x: %d, y: %d\n", graph->nodes[i].x, graph->nodes[i].y);
		ft_printf("c: %d\n", graph->nodes[i].c);
		ft_printf("%s : \n", graph->nodes[i].name);
		j = 0;
		while(j <= graph->nodes[i].hd && graph->nodes[i].edges[j]->a1) 
		{
			ft_printf("%s - ", graph->nodes[i].edges[j]->a1->name);
			ft_printf("%s\n", graph->nodes[i].edges[j]->a2->name);
			j++;
		}
		//ft_printf("NIL\n");
		i++;
	}
}

void		print_path(t_path *path);

void		print_solution_dimention(t_graph *graph)
{
	t_bfs		*bfs_tmp;
	t_solution	*sol_tmp;

	bfs_tmp = graph->bfs;
	ft_printf("shortest bfs: %d\n", graph->shortest->steps);
	while (bfs_tmp)
	{
		if (bfs_tmp->paths)
		{
			ft_printf("\nbfs paths: %d\n", bfs_tmp->paths);
			ft_printf("bfs opt_paths: %d\n", bfs_tmp->opt_paths);
			ft_printf("bfs steps: %d\n", bfs_tmp->steps);
			sol_tmp = bfs_tmp->sol_sort;
			while (sol_tmp)
			{
				ft_printf("1st node: %s\n", sol_tmp->path->next->node->name);
				//print_path(sol_tmp->path);
				ft_printf("sol ln: %d\n", sol_tmp->ln);
				ft_printf("steps: %d\n", sol_tmp->steps);
				ft_printf("ants to send: %d\n", sol_tmp->ants);
				sol_tmp = sol_tmp->next;
			}
		}
		bfs_tmp = bfs_tmp->next;
		ft_printf("\n");
	}
}
