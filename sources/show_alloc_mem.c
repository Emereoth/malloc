/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 13:22:08 by acottier          #+#    #+#             */
/*   Updated: 2018/09/18 15:25:49 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

/*
** Displays an allocation.
*/

static void		display_chunk(t_ctrl *alloc_list)
{
	if (alloc_list->size == 0)
		return ;
	write(1, "0x", 2);
	to_hex((t_uli)(alloc_list + 1));
	ft_putstr(" - ");
	write(1, "0x", 2);
	if (alloc_list->size == 0)
		to_hex((t_uli)(alloc_list + 1));
	else
		to_hex((t_uli)((void*)alloc_list + alloc_list->size));
	ft_putstr(" : ");
	ft_putnbr(alloc_list->size - CTRL);
	ft_putstr(" bytes (zone ");
	ft_putnbr(alloc_list->zone);
	ft_putstr(")\n");
}

/*
** Displays all allocations in a zone.
*/

static size_t	display_zone(t_ctrl *alloc_list, char *type)
{
	size_t		zone_total;

	zone_total = 0;
	ft_putstr(type);
	write(1, "0x", 2);
	to_hex((t_uli)alloc_list);
	ft_putchar('\n');
	while (alloc_list)
	{
		display_chunk(alloc_list);
		zone_total += alloc_list->size - CTRL;
		alloc_list = alloc_list->next;
		// ft_putstr("chunk size added to total, moving on to next chunk\n");
	}
	return (zone_total);
}

/*
** Transforms a pointer into an hexadecimal address.
*/

void			to_hex(t_uli address)
{
	if (address > 9)
		to_hex(address / 16);
	address = address % 16 < 10 ? address % 16 + 48 : address % 16 + 55;
	write(1, &address, 1);
}

/*
** Displays all allocated memory.
*/

void			show_alloc_mem(void)
{
	t_ctrl				*cursor;
	size_t				total_size;

	total_size = 0;
	cursor = g_allocations.tiny;
	if (cursor)
		total_size += display_zone(cursor, "TINY : ");
	cursor = g_allocations.small;
	if (cursor)
		total_size += display_zone(cursor, "SMALL : ");
	cursor = g_allocations.large;
	if (cursor)
		total_size += display_zone(cursor, "LARGE : ");
	ft_putstr("Total: ");
	ft_putnbr(total_size);
	ft_putstr(" bytes\n");
}
