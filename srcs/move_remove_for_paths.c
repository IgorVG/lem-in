/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_remove_for_paths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:02:52 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/26 17:55:19 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_solution(t_solution *sol)
{
	t_path		*path;
	void		*next;

	path = sol->path;
	while (path)
	{
		next = (void*)path->next;
		free(path);
		path = (t_path*)next;
	}
	free(sol);
}

void		unchain_solution(t_solution *sol, t_bfs *curr_bfs)
{
	if (curr_bfs->solution == sol)
		curr_bfs->solution = sol->next;
	if (sol->prev)
		sol->prev->next = sol->next;
	if (sol->next)
		sol->next->prev = sol->prev;
}

void		remove_solution(t_bfs *curr_bfs, t_solution *new_sol)
{
	unchain_solution(new_sol, curr_bfs);
	curr_bfs->paths--;
	free_solution(new_sol);
}

void		move_to_sorted(t_solution *new_sol, t_bfs *curr_bfs)
{
	unchain_solution(new_sol, curr_bfs);
	if (!curr_bfs->sol_sort)
		curr_bfs->sol_sort = new_sol;
	else
		curr_bfs->last_sol_sort->next = new_sol;
	new_sol->prev = curr_bfs->last_sol_sort;
	new_sol->next = NULL;
	curr_bfs->last_sol_sort = new_sol;
}

void		path_is_found(t_solution *new_sol, t_bfs *curr_bfs, t_graph *graph)
{
	check_add_to_previous(new_sol, graph, graph->bfs);
	if (check_colisions(new_sol->path, graph) == 0)
	{
		capacity_to_zero(new_sol->path);
		curr_bfs->there_is_path = 1;
		new_sol->is_valid = 1;
		move_to_sorted(new_sol, curr_bfs);
	}
	else
		remove_solution(curr_bfs, new_sol);
}
