/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:31:03 by aatieh            #+#    #+#             */
/*   Updated: 2024/09/14 16:31:07 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char	*res;
	int		fd;
	int		i;

	i = 0;
	fd = open("test.txt", O_RDWR);
	while (i++ < 3)
	{
		res = get_next_line(fd);
		printf("%d : %s", i, res);
		free(res);
	}
	return 0;
}
