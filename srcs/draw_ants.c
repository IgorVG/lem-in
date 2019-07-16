/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:05:05 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:31:34 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		lerp(int x1, int x2, int k)
{
	float	x;
	int		d;

	x1 += 10;
	x2 += 10;
	d = x1 - x2;
	x = x2 + ((d * k) / NB_FRAME);
	return ((int)x);
}

void			init_rect(SDL_Rect *rect)
{
	rect->w = 10;
	rect->h = 10;
}

int				draw_ants(t_graph *graph, t_sdl *sdl, int k, int i)
{
	SDL_Rect	rect;
	t_path		*path;
	t_solution	*sol;

	init_rect(&rect);
	sol = graph->shortest->sol_sort;
	while (--i >= 0)
	{
		path = sol->path;
		while (path)
		{
			SDL_SetRenderDrawColor(sdl->rend, 0, 255, 255, 0);
			if ((path->node == graph->start && sol->ants)
					|| (path->ant && path->edge))
			{
				rect.x = lerp(path->edge->a2->x, path->edge->a1->x, k);
				rect.y = lerp(path->edge->a2->y, path->edge->a1->y, k);
				if (SDL_RenderFillRect(sdl->rend, &rect) != 0)
					return (0);
			}
			path = path->next;
		}
		sol = sol->next;
	}
	return (1);
}
