/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:01:08 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:35:59 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		get_boundaries(t_graph *graph, t_point *min, t_point *max)
{
	int i;

	i = 0;
	min->x = INT_MAX;
	max->x = 0;
	min->y = INT_MAX;
	max->y = 0;
	while (i <= graph->hd_n)
	{
		if (graph->nodes[i].x < min->x)
			min->x = graph->nodes[i].x;
		if (graph->nodes[i].y < min->y)
			min->y = graph->nodes[i].y;
		if (graph->nodes[i].x > max->x)
			max->x = graph->nodes[i].x;
		if (graph->nodes[i].y > max->y)
			max->y = graph->nodes[i].y;
		i++;
	}
}

int				setup_map(t_graph *graph)
{
	t_point min;
	t_point max;
	int		i;
	int		rw;
	int		rh;

	i = 0;
	get_boundaries(graph, &min, &max);
	rw = max.x - min.x;
	rh = max.y - min.y;
	while (i <= graph->hd_n)
	{
		graph->nodes[i].x = rw > 0
			? ((graph->nodes[i].x - min.x) * (WIDTH - 50)) / rw + 10
				: WIDTH / 2 + 10;
		graph->nodes[i].y = rh > 0
			? ((graph->nodes[i].y - min.y) * (HEIGHT - 50)) / rh + 10
			: HEIGHT / 2 + 10;
		i++;
	}
	return (1);
}

/*
** create functino that checks the link exist;
*/

static int		draw_edges(t_graph *graph, t_sdl *sdl)
{
	int i;

	i = 0;
	while (i <= graph->hd_e)
	{
		SDL_SetRenderDrawColor(sdl->rend, 255, 25, 25, 255);
		if (SDL_RenderDrawLine(sdl->rend,
			graph->edges[i].a1->x + 15, graph->edges[i].a1->y + 15,
			graph->edges[i].a2->x + 15, graph->edges[i].a2->y + 15))
			return (0);
		i++;
	}
	return (1);
}

static int		draw_nodes(t_graph *graph, t_sdl *sdl)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
	rect.h = 30;
	rect.w = 30;
	while (i <= graph->hd_n)
	{
		rect.x = graph->nodes[i].x;
		rect.y = graph->nodes[i].y;
		if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 255) != 0)
			return (0);
		if (SDL_RenderFillRect(sdl->rend, &rect) != 0)
			return (0);
		if (&graph->nodes[i] == graph->start || &graph->nodes[i] == graph->end
				? SDL_SetRenderDrawColor(sdl->rend, 255, 25, 25, 255) != 0
				: SDL_SetRenderDrawColor(sdl->rend, 255, 255, 25, 255) != 0)
			return (0);
		if (SDL_RenderDrawRect(sdl->rend, &rect) != 0)
			return (0);
		i++;
	}
	return (1);
}

int				draw_map(t_graph *graph, t_sdl *sdl)
{
	if (!(draw_edges(graph, sdl)))
		return (0);
	if (!(draw_nodes(graph, sdl)))
		return (0);
	return (1);
}
