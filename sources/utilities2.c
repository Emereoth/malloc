/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:56:34 by acottier          #+#    #+#             */
/*   Updated: 2018/08/02 15:42:09 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t		aligned_size(size_t size)
{
	while (size % 16 != 0)
		size++;
	return (size);
}

void		show_readable(int fd, char *cursor, size_t limit)
{
	size_t		i;

	i = 0;
	write(fd, "   ", 3);
	while (limit < 16)
	{
		write(fd, "   ", 3);
		limit++;
	}
	while (i < limit)
	{
		if (*cursor > 32 && *cursor < 126)
			write(fd, cursor, 1);
		else
			write(fd, ".", 1);
		i++;
		cursor++;
	}
}

void		init(void)
{
	static int	tiny = 0;
	static int	small = 0;
	static int	large = 0;
	
	if (tiny == 0)
	{
		g_allocations.tiny = NULL;
		tiny++;
	}
	if (small == 0)
	{
		g_allocations.small = NULL;
		small++;
	}
	if (large == 0)
	{
		g_allocations.large = NULL;
		large++;
	}
	return ;
}