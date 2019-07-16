/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_for_check_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:51:01 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/17 16:04:01 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			check_number(char *str)
{
	long long		num;
	char			*tmp;

	tmp = str;
	num = ft_atoli(str);
	if (*tmp && *tmp == '-')
		tmp++;
	else if (*tmp && *tmp == '+')
		tmp++;
	while (*tmp && *tmp == '0')
		tmp++;
	str = tmp;
	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
			error(-1);
		tmp++;
	}
	if ((tmp - str) > 10 || num > 2147483647 || num < -2147483648)
		error(-1);
	return ((int)num);
}

void		check_node(char **tbl)
{
	check_number(tbl[1]);
	check_number(tbl[2]);
	if (*tbl[0] == 'L' || ft_strchr(*tbl, '-'))
	{
		ft_freetbl(tbl);
		error(-1);
	}
}

void		check_edge(char **tbl)
{
	if (!*tbl[0] || !*tbl[1] || *tbl[0] == 'L' || *tbl[0] == 'L')
	{
		ft_freetbl(tbl);
		error(-1);
	}
}
