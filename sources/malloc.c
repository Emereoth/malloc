/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:50:45 by acottier          #+#    #+#             */
/*   Updated: 2017/12/12 18:55:10 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

void		*malloc(size_t size)
{
	(void)size;
	ft_putnbr(getpagesize());
	return (mmap(0, 1000, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
}
