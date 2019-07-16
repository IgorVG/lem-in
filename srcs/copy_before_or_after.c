/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_before_or_after.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 14:02:14 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/27 14:02:31 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		copy_before(t_solution *copy, t_solution *sol_to_paste, t_bfs *bfs)
{
	copy->prev = sol_to_paste->prev;
	if (sol_to_paste->prev)
		sol_to_paste->prev->next = copy;
	else
		bfs->sol_sort = copy;
	copy->next = sol_to_paste;
	sol_to_paste->prev = copy;
}

void		copy_after(t_solution *copy, t_solution *sol_to_paste, t_bfs *bfs)
{
	copy->next = sol_to_paste->next;
	if (sol_to_paste->next)
		sol_to_paste->next->prev = copy;
	else
		bfs->last_sol_sort = copy;
	sol_to_paste->next = copy;
	copy->prev = sol_to_paste;
}
