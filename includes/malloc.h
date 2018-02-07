/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:46:46 by acottier          #+#    #+#             */
/*   Updated: 2017/12/12 18:55:36 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem();

//      UTILITIES
void		ft_putchar(char c);
void		ft_putnbr(int n);
void		ft_putstr(char *str);
void		ft_putendl(char *str);
