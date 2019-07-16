/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_tofree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:38:10 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/13 19:51:28 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** g_tofree[0] - pointer to (t_node *)graph->nodes[];
** table of pointers to be attempted to be freed in order:
** 	- t_node->name;
** 	- t_node;
** g_tofree[1] -
*/

t_free		g_tofree = {.graph = NULL};
