/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:01:03 by marvin            #+#    #+#             */
/*   Updated: 2023/06/15 10:01:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	map_err_handler(char ***split, t_vdmlist **list)
{
	if (split)
		ft_free_charmat_null(split, &free);
	if (list)
		vdmlist_destroy(list, &ft_free_split);
	return (perror_msg(ERR_MALLOC));
}

static int	fdf_atoi(char *str, t_coord *single)
{
	int	res;
	int	sign;

	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	single->height = (res * sign);
	if (*str == ',')
		single->colour = ft_atoi_base(&str[3], HEX);
	else
		single->colour = 0;
	return (1);
}

static int	fill_row(t_coord *array, void *split_place, int num_cols)
{
	char	**split;
	int		i;

	split = *(char ***)split_place;
	i = -1;
	while (++i < num_cols)
		fdf_atoi(split[i], &array[i]);
	ft_free_charmat_null(split_place, &free);
	return (1);
}

static int	list_to_map(t_fdf *fdf, t_vdmlist **list)
{
	t_coord		*big_arr;
	t_vdmnode	*cur;
	int			index;

	fdf->mrows = (*list)->len;
	fdf->lenmap = fdf->mcols * fdf->mrows;
	big_arr = malloc(sizeof(*big_arr) * fdf->lenmap);
	if (!big_arr)
		return (map_err_handler(NULL, list));
	index = 0;
	cur = (*list)->head;
	while (cur)
	{
		fill_row(&big_arr[index], &(cur->data), fdf->mcols);
		cur = cur->next;
		index += fdf->mcols;
	}
	vdmlist_destroy(list, &free);
	fdf->map = big_arr;
	return (1);
}

int	file_to_map(t_fdf *fdf, int fd)
{
	char		*line;
	char		**split;
	t_vdmlist	*list;

	list = vdmlist_new();
	if (!list)
		return (perror_msg(ERR_MALLOC));
	line = (char *)1;
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			split = ft_split_count(line, " \n", (int *)&((fdf->mcols)));
			free(line);
			if (!split || !vdmlist_in_tail(list, split))
				return (map_err_handler(&split, &list));
		}
	}
	close(fd);
	return (list_to_map(fdf, &list));
}
