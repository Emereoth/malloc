/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_dump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:05:57 by acottier          #+#    #+#             */
/*   Updated: 2018/09/03 11:56:28 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	hex_to_file(int fd, t_uli address)
{
	if (address > 9)
		hex_to_file(fd, address / 16);
	address = address % 16 < 10 ? address % 16 + 48 : address % 16 + 55;
	write(fd, &address, 1);
}

static void	dump_memory(int fd, char *cursor, size_t size)
{
	char			sign;
	unsigned long	length;
	static char		table[16] = "0123456789abcdef";

	length = -1;
	while (++length < size)
	{
		if (length % 16 == 0)
		{
			if (length != 0)
				show_readable(fd, cursor - 16, 16);
			write(fd, "\n", 1);
			hex_to_file(fd, (t_uli)cursor);
			write(fd, ": ", 2);
		}
		sign = *cursor >= 0 ? 1 : -1;
		write(fd, &table[*cursor * sign / 16], 1);
		write(fd, &table[*cursor * sign % 16], 1);
		write(fd, " ", 1);
		cursor++;
	}
	if (length % 16 == 0)
		show_readable(fd, cursor - 16, 16);
	else if (length % 16 != 0)
		show_readable(fd, cursor - length % 16, length % 16);
}

static void	dump_allocs(int fd, t_ctrl *allocs)
{
	while (allocs)
	{
		if (allocs->size - CTRL > 0)
		{
			dump_memory(fd, (char *)(allocs + 1), allocs->size - CTRL);
			write(fd, "\n", 1);
		}
		allocs = allocs->next;
	}
}

static void	dump_lists(int fd)
{
	if (g_allocations.tiny)
	{
		write(fd, "TINY\n\n", 6);
		dump_allocs(fd, g_allocations.tiny);
	}
	if (g_allocations.small)
	{
		write(fd, "\n\n\nSMALL\n\n", 10);
		dump_allocs(fd, g_allocations.small);
	}
	if (g_allocations.large)
	{
		write(fd, "\n\n\nLARGE\n\n", 10);
		dump_allocs(fd, g_allocations.large);
	}
	return ;
}

void		allocation_dump(char *filename)
{
	int		fd;

	if (!filename)
	{
		ft_putstr("Invalid hexdump filename: cannot be NULL.\n");
		return ;
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRWXU | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_putstr("Error: could not open dump file.\n");
		return ;
	}
	dump_lists(fd);
	close(fd);
	return ;
}
