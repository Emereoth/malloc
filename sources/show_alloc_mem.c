/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 13:22:08 by acottier          #+#    #+#             */
/*   Updated: 2018/06/30 17:34:25 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

static void		display_chunk(t_ctrl *alloc_list)
{
	write(1, "0x", 2);
	to_hex((t_uli)alloc_list + CTRL);
	ft_putstr(" - ");
	write(1, "0x", 2);
	to_hex((t_uli)alloc_list + alloc_list->size);
	ft_putstr(" : ");
	ft_putnbr(alloc_list->size - CTRL);
	ft_putstr(" octets\n");
}

static void		display_zone(t_ctrl *alloc_list, char *type)
{
	size_t		zone;

	ft_putstr(type);
	write(1, "0x", 2);
	to_hex((t_uli)alloc_list);
	ft_putchar('\n');
	zone = alloc_list->zone;
	while (alloc_list && alloc_list->zone == zone)
	{
		display_chunk(alloc_list);
		alloc_list = alloc_list->next;
	}
}

void			to_hex(t_uli address)
{
	if (address > 9)
		to_hex(address / 16);
	address = address % 16 < 10 ? address % 16 + 48 : address % 16 + 55;
	write(1, &address, 1);
}

t_ctrl			*next_zone(t_ctrl *alloc_list)
{
	size_t			zone;

	zone = alloc_list->zone;
	while (alloc_list && alloc_list->zone == zone)
		alloc_list = alloc_list->next;
	return (alloc_list);
}

void			show_alloc_mem(void)
{
	t_ctrl	*cursor;

	cursor = g_allocations.tiny;
	if (!cursor)
		ft_putstr("no tiny allocations\n");
	while (cursor)
	{ 
		display_zone(cursor, "TINY : ");
		cursor = next_zone(cursor);
	}
	cursor = g_allocations.small;
	if (!cursor)
		ft_putstr("no small allocations\n");
	while (cursor)
	{
		display_zone(cursor, "SMALL : ");
		cursor = next_zone(cursor);
	}
	cursor = g_allocations.large;
	if (!cursor)
		ft_putstr("no large allocations\n");
	while (cursor)
	{
		display_zone(cursor, "LARGE : ");
		cursor = next_zone(cursor);
	}
}
