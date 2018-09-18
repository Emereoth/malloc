/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_dump.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:05:57 by acottier          #+#    #+#             */
/*   Updated: 2018/09/18 15:12:10 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** Writes the hexadecimal address of the current 16-byte segment to a file.
*/

static void	hex_to_file(int fd, t_uli address)
{
	if (address > 9)
		hex_to_file(fd, address / 16);
	address = address % 16 < 10 ? address % 16 + 48 : address % 16 + 55;
	write(fd, &address, 1);
}

/*
** Dumps one allocation.
*/

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

/*
** Dumps all the allocs in an allocation list.
*/

static void	dump_allocs(int fd, t_ctrl *allocs)
{
	while (allocs)
	{
		ft_putstr("Dumping alloc #");
		show_address(allocs);
		ft_putstr("(size ");
		ft_putnbr(allocs->size - CTRL);
		ft_putstr(")\n");
		if (allocs->size - CTRL > 0)
		{
			dump_memory(fd, (char *)(allocs + 1), allocs->size - CTRL);
			write(fd, "\n", 1);
		}
		else
			ft_putstr("Alloc too small, passing to next one.\n");
		allocs = allocs->next;
	}
}

/*
** Dumps the three different allocation lists.
*/

static void	dump_lists(int fd)
{
	if (g_allocations.tiny)
	{
		write(fd, "TINY\n\n", 6);
		dump_allocs(fd, g_allocations.tiny);
	}
	ft_putstr("TINY section dumped.\n");
	// if (g_allocations.small)
	// {
	// 	write(fd, "\n\n\nSMALL\n\n", 10);
	// 	dump_allocs(fd, g_allocations.small);
	// }
	// ft_putstr("SMALL section dumped.\n");
	// if (g_allocations.large)
	// {
	// 	write(fd, "\n\n\nLARGE\n\n", 10);
	// 	dump_allocs(fd, g_allocations.large);
	// }
	// ft_putstr("LARGE section dumped.\n");
	return ;
}

/*
** Performs a memory dump into the file specified.
*/

void		allocation_dump(char *filename)
{
	int		fd;

	ft_putstr("Starting dump.\n");
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
	ft_putstr("Dump file is valid.\n");
	dump_lists(fd);
	ft_putstr("Dump over.\n");
	close(fd);
	return ;
}
