/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:43:18 by aatieh            #+#    #+#             */
/*   Updated: 2025/01/28 19:54:40 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_list
{
	int				fd;
	char			*buff;
	struct s_list	*next;
}	t_line_list;

void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);
void	*ft_memmove(void *dest, const void *src, size_t n);

char	*ft_lstclear_item(t_line_list **lst, int fd);
char	*get_next_line(int fd);

#endif
