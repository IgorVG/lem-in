/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:51:49 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:39:06 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		sdl_exit(t_sdl *sdl)
{
	if (sdl->win)
		SDL_DestroyWindow(sdl->win);
	if (sdl->rend)
		SDL_DestroyRenderer(sdl->rend);
	if (sdl->texture)
		SDL_DestroyTexture(sdl->texture);
	if (sdl->surface)
		SDL_FreeSurface(sdl->surface);
	SDL_Quit();
}

int			sdl_init(t_graph *graph, t_sdl *sdl)
{
	*sdl = (t_sdl){NULL, NULL, NULL, NULL, 0, 15};
	if (!setup_map(graph))
		return (0);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	if (!(sdl->win = SDL_CreateWindow("Lem-in", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		return (0);
	if (!(sdl->rend = SDL_CreateRenderer(sdl->win, -1,
		SDL_RENDERER_ACCELERATED)))
		return (0);
	if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 25))
		return (0);
	SDL_RenderClear(sdl->rend);
	if (!(draw_map(graph, sdl)))
		return (0);
	if (!(draw_ants(graph, sdl, NB_FRAME, graph->shortest->opt_paths)))
		return (0);
	SDL_RenderPresent(sdl->rend);
	return (1);
}

static int	draw(t_graph *graph, t_sdl *sdl)
{
	int i;

	i = 0;
	while (i <= NB_FRAME)
	{
		if (SDL_SetRenderDrawColor(sdl->rend, 0, 25, 25, 25))
			return (0);
		SDL_RenderClear(sdl->rend);
		if (!draw_map(graph, sdl))
			return (0);
		if (!draw_ants(graph, sdl, i, graph->shortest->opt_paths))
			return (0);
		SDL_RenderPresent(sdl->rend);
		draw_control(graph, sdl);
		SDL_Delay(sdl->delay);
		i++;
	}
	return (1);
}

void		viewer(t_graph *graph, t_sdl *sdl)
{
	if (!draw(graph, sdl))
		sdl_exit(sdl);
	if (sdl->state == 1)
	{
		if (!draw(graph, sdl))
			sdl_exit(sdl);
		SDL_Delay(50);
	}
}
