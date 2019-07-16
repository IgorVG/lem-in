/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:42:04 by igarbuz           #+#    #+#             */
/*   Updated: 2019/06/27 11:39:59 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	const char *mystr;

	if (!s)
		return (0);
	mystr = s;
	while (*mystr)
		mystr++;
	return (mystr - s);
}
