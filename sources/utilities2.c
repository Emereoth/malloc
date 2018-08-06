/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:56:34 by acottier          #+#    #+#             */
/*   Updated: 2018/08/06 18:09:22 by acottier         ###   ########.fr       */
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

int			zone_is_empty(t_ctrl *alloc)
{
	t_ctrl	*cursor;
	int		i;

	// ft_putstr("zone_is_empty()\n");
	// show_alloc_mem();
	i = 0;
	cursor = alloc;
	while (cursor && cursor->zone == alloc->zone)
	{
		// show_address(cursor);
		if (cursor->size > 0)
			i++;
		cursor = cursor->prev;
	}
	// ft_putstr("prev done\n");
	cursor = alloc;
	while (cursor && cursor->zone == alloc->zone)
	{
		if (cursor->size > 0)
			i++;
		cursor = cursor->next;
	}
	// ft_putstr("nexts done\n");
	// ft_putstr("total elements in zone: ");
	// ft_putnbr(i);
	// ft_putchar('\n');
	if (i > 2)
		return (1);
	// ft_putstr("zone IS empty\n");
	return (0);
}

int			only_zone(t_ctrl	*alloc)
{
	t_ctrl	*cursor;

	cursor = alloc;
	while (cursor && cursor->zone == alloc->zone)
		cursor = cursor->prev;
	if (cursor)
		return (1);
	cursor = alloc;
	while (cursor && (cursor->zone == alloc->zone || cursor->size == 0))
		cursor = cursor->next;
	if (cursor)
		return (1);
	return (0);
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
