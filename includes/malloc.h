/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:46:46 by acottier          #+#    #+#             */
/*   Updated: 2018/06/27 16:37:12 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>

typedef unsigned long int 	t_uli;

typedef struct	s_ctrl
{
	size_t			size;
	size_t			zone;
	size_t			zone_start;
	int				pos;
	int				zone_size;
	struct s_ctrl	*prev;
	struct s_ctrl	*next;

}				t_ctrl;

typedef struct	s_data
{
	t_ctrl	*tiny;
	t_ctrl	*small;
	t_ctrl	*large;
}				t_data;

t_data		g_allocations;

enum
{
	CTRL = sizeof(struct s_ctrl),
	TINY = 4096,
	SMALL = 4096 * 16,
	TINY_ZONE = (TINY + CTRL) * 100,
	SMALL_ZONE = (SMALL + CTRL) * 100
};

/*
** MALLOC
*/

void			*ft_malloc(size_t size);
t_ctrl			**find_alloc_point(size_t size, t_ctrl **alloc_list,
				int zone_type);
int				available_space(t_ctrl **cur, t_ctrl *next, size_t size);
t_ctrl			*new_zone(t_ctrl *prev, size_t size, int zone_type);
void			*allocate(t_ctrl **alloc_point, size_t size, t_ctrl *next);

/*
** FREE
*/

void			ft_free(void *ptr);
t_ctrl			*find_memory(void *ptr, t_ctrl *alloc_list);

/*
** REALLOC
*/

void			*ft_realloc(void *ptr, size_t size);

/*
** SHOW_ALLOC_MEM.C
*/

void			show_alloc_mem();
void			to_hex(t_uli address);

/*
** UTILITIES
*/

void			ft_putchar(char c);
void			ft_putnbr(int n);
void			ft_putstr(char *str);
void			ft_memcpy(void *dst, void *src, size_t n);
void			show_address(t_ctrl **address);

#endif
