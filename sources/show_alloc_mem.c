/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 13:22:08 by acottier          #+#    #+#             */
/*   Updated: 2018/06/21 14:21:45 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

static void		to_hex(t_uli address)
{
	if (address > 9)
		to_hex(address / 16);
	address = (address <= 9 ? 48 + address : address - 10 + 65);
	write(1, &address, 1);
}

static void		display_chunk(t_ctrl *alloc_list)
{
	to_hex((t_uli)alloc_list + CTRL);
	ft_putstr(" - ");
	to_hex((t_uli)alloc_list + alloc_list->size);
	ft_putstr(" : ");
	ft_putnbr(alloc_list->size - CTRL);
	ft_putstr(" octets\n");
}

static void		display_zone(t_ctrl *alloc_list, char *type)
{
	size_t		zone;

	ft_putstr(type);
	to_hex((t_uli)alloc_list);
	ft_putchar('\n');
	zone = alloc_list->zone;
	while (alloc_list && alloc_list->zone == zone)
	{
		display_chunk(alloc_list);
		alloc_list = alloc_list->next;
	}
	ft_putchar('\n');
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
	while (cursor)
	{
		display_zone(cursor, "TINY : ");
		cursor = next_zone(cursor);
	}
	cursor = g_allocations.small;
	while (cursor)
	{
		display_zone(cursor, "SMALL : ");
		cursor = next_zone(cursor);
	}
	cursor = g_allocations.large;
	while (cursor)
	{
		display_zone(cursor, "LARGE : ");
		cursor = next_zone(cursor);
	}
}
