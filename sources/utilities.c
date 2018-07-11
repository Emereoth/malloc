/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:45:24 by acottier          #+#    #+#             */
/*   Updated: 2018/07/11 15:55:36 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

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

void		ft_memcpy(void *dst, void *src, size_t n)
{
	size_t			i;
	unsigned char	*new_dst;
	unsigned char	*new_src;

	if (!dst || !src || n == 0)
		return ;
	new_dst = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		new_dst[i] = new_src[i];
		i++;
	}
}

void		show_address(t_ctrl *address)
{
	write(1, "0x", 2);
	to_hex((t_uli)address);
	ft_putchar('\n');
}