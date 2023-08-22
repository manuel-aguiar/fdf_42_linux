/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:52:30 by marvin            #+#    #+#             */
/*   Updated: 2023/07/20 16:52:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_height(t_fdf *fdf)
{
	int	i;
	int	total;

	total = (*fdf).mrows * (*fdf).mcols;
	i = 0;
	while (i < total)
	{
		if (!(i % (*fdf).mcols) && i != 0)
			printf("\n");
		printf("%4d", fdf->map[i].height);
		i++;
	}
}

void	print_coords(t_fdf *fdf)
{
	t_uint	i;

	i = 0;
	printf("total rows %d, total cols %d\n", fdf->mrows, fdf->mcols);
	printf("min_z %d, max_z %d\n", fdf->min_z, fdf->max_z);
	printf("zoom %d\n", fdf->view.zoom);
	while (i < fdf->lenmap)
	{
		printf("row %d, col %d, height %d:", i / fdf->mcols, \
		i % fdf->mcols, fdf->map[i].height);
		printf(" x %d, y %d, col %d\n", fdf->vertices[i].x, \
		fdf->vertices[i].y, fdf->vertices[i].colour);
		i++;
	}
}
