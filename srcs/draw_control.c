/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:33:38 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/26 17:11:26 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		viewer_control(t_sdl *sdl)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT
			|| (e.key.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			sdl_exit(sdl);
		if (e.key.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_SPACE)
				sdl->state ^= 1;
			else if (e.key.keysym.sym == SDLK_LEFT)
				return (1);
			else if (e.key.keysym.sym == SDLK_RIGHT)
				return (1);
			else if (e.key.keysym.sym == SDLK_RETURN)
				return (1);
			else if (e.key.keysym.sym == SDLK_DOWN)
				sdl->delay += 5;
			else if (e.key.keysym.sym == SDLK_UP && sdl->delay >= 5)
				sdl->delay -= 5;
		}
	}
	return (0);
}

int		draw_control(t_graph *graph, t_sdl *sdl)
{
	SDL_Event	e;

	(void)graph;
	while (SDL_PollEvent(&e))
	{
		if (e.key.type == SDL_KEYDOWN)
		{
			if (e.type == SDL_QUIT
				|| (e.key.keysym.sym == SDLK_ESCAPE))
				sdl_exit(sdl);
			else if (e.key.keysym.sym == SDLK_DOWN)
				sdl->delay += 5;
			else if (e.key.keysym.sym == SDLK_UP
				&& sdl->delay >= 5)
				sdl->delay -= 5;
			else if (e.key.keysym.sym == SDLK_SPACE
				|| e.key.keysym.sym == SDLK_RIGHT
				|| e.key.keysym.sym == SDLK_LEFT
				|| e.key.keysym.sym == SDLK_RETURN)
				sdl->state = 0;
		}
	}
	return (0);
}
