/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retain_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 10:48:16 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/15 17:36:24 by igarbuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		init_input(t_graph *graph)
{
	t_input		*in;

	if (!(in = (t_input *)malloc(sizeof(t_input))))
		error(-2);
	in->buf[IN_BUF_M] = NULL;
	in->last = 0;
	graph->input = in;
}

void		retain_input(t_graph *graph, char *str)
{
	graph->input->buf[graph->input->last & IN_BUF_M] = str;
	graph->input->last++;
}
