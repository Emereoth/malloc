/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/07/26 17:53:42 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		main(void)
{
	int		i;
	char	*a;

	i = 0;
	while (i < 12)
	{ 
		// ft_putnbr(i);
		// ft_putchar('\n');
		a = (char*)ft_malloc(115);
		// a[0] = 42;
		i++;
	}
	// show_alloc_mem();
	return (0);
}
