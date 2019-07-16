/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:37:26 by ibaran            #+#    #+#             */
/*   Updated: 2019/06/27 11:39:03 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** function ft_memncat concatenates two locations of memory nito one;
** it is useful to safely concatenate strings that contain '\0'
** concatenation is done in freshly allocated memory, pointed by **mainstr;
** previously allocated memory pointed by **mainstr is freed;
*/

int		ft_memncat(char **mainstr, char *adder, int lenadder)
{
	char	*newstr;
	int		lenstr;

	if (lenadder && mainstr && adder)
	{
		newstr = NULL;
		lenstr = ft_strlen(*mainstr);
		if (!(newstr = (char *)malloc(sizeof(char) * (lenstr + lenadder + 1))))
			return (-1);
		ft_memcpy(newstr, *mainstr, lenstr);
		ft_memcpy(newstr + lenstr, adder, lenadder);
		newstr[lenstr + lenadder] = '\0';
		if (*mainstr)
			free(*mainstr);
		*mainstr = newstr;
		return (1);
	}
	return (0);
}
