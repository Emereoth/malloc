/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brutalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 18:05:32 by tvallee           #+#    #+#             */
/*   Updated: 2018/09/18 16:16:21 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# define SMALL_ZONE ((2573 + CTRL) * 100 + 44)
#include <stdlib.h>
#include <unistd.h>
#include "includes/malloc.h"

void			to_hex(t_uli address)
{
	if (address > 9)
		to_hex(address / 16);
	address = address % 16 < 10 ? address % 16 + 48 : address % 16 + 55;
	write(1, &address, 1);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void		ft_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar('0' + n);
}


void	ft_putendl(char const *str)
{
	size_t	n;

	n = 0;
	while (str[n])
		n++;
	write(1, str, n);
	write(1, "\n", 1);
}

typedef struct	s_dataesutnhaosnt
{
	void		*ptr;
	uint32_t	size;
}				t_datastneuhsnthsn;

static uint32_t	get_random_size(unsigned *type)
{
	uint32_t	ret;

	*type = arc4random_uniform(3);
	switch (*type)
	{
		case 0:
			ret = arc4random_uniform(TINY + 1);
			break;
		case 1:
			do {
				ret = arc4random_uniform(SMALL + 1);
			} while (ret <= TINY);
			break;
		case 2:
		default:
			do {
				ret = arc4random_uniform(1024 * 1024 * 42);
			} while (ret <= SMALL);
			break;
	}
	return (ret);
}

int main()
{
	t_datastneuhsnthsn		table[200] = { {.ptr = NULL, .size = 0 } };
	t_datastneuhsnthsn		*current;
	unsigned	type;
	char		type_map[3][6] = {"TINY", "SMALL", "LARGE"};

	write(1, "=========BEGIN BRUTALIZE=========\n", sizeof("=========BEGIN BRUTALIZE========="));
	while (1)
	{
		// allocation_dump("dump");
		show_alloc_mem();
		ft_putstr("\n=> new iteration: ");

		current = &(table[arc4random_uniform(5)]);
		if (current->ptr == NULL)
		{
			current->size = get_random_size(&type);

			ft_putstr("malloc ");
			ft_putstr(type_map[type]);
			ft_putstr(" size ");
			ft_putnbr(current->size);
			ft_putchar(10);

			current->ptr = malloc(current->size);
			if (current->ptr == NULL)
			{
				write(2, "malloc returned NULL !\n", sizeof("malloc returned NULL !\n") - 1);
				return (1);
			}
		}
		else {
			switch (arc4random_uniform(5))
			{
				case 0:
					ft_putendl("free");
					free(current->ptr);
					ft_putendl("/free");
					current->ptr = NULL;
					break;
					
				case 1:
					ft_putstr("realloc size: ");
					ft_putnbr(current->size);
					ft_putstr(" => ");
					current->size = get_random_size(&type);
					ft_putnbr(current->size);
					ft_putchar(10);
					current->ptr = realloc(current->ptr, current->size);
					break;
				default:
					ft_putendl("no op");
					break;
			}
		}
		if (current->ptr != NULL)
		{
			ft_putstr("=> filling available memory: ");
			// arc4random_buf(current->ptr, current->size);
			ft_putendl("OK !");
		}
	}
}
