/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_first_render.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:03:14 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 18:12:19 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_to_center(t_fdf *fdf, t_center_start *center)
{
	int	i;

	center->x_offset = fdf->win_width / 2 \
					- (center->max_x + center->min_x) / 2;
	center->y_offset = fdf->win_height / 2 \
					- (center->max_y + center->min_y) / 2;
	fdf->view.x_offset += center->x_offset;
	fdf->view.y_offset += center->y_offset;
	i = 0;
	while (i < fdf->lenmap)
	{
		fdf->vertices[i].x += center->x_offset;
		fdf->vertices[i].y += center->y_offset;
		i++;
	}
}

void	center_first_render(t_fdf *fdf)
{
	t_center_start	center;
	int				i;

	center.max_x = fdf->vertices[0].x;
	center.min_x = fdf->vertices[0].x;
	center.max_y = fdf->vertices[0].y;
	center.min_y = fdf->vertices[0].y;
	i = 1;
	while (i < fdf->lenmap)
	{
		if (fdf->vertices[i].x > center.max_x)
			center.max_x = fdf->vertices[i].x;
		if (fdf->vertices[i].x < center.min_x)
			center.min_x = fdf->vertices[i].x;
		if (fdf->vertices[i].y > center.max_y)
			center.max_y = fdf->vertices[i].y;
		if (fdf->vertices[i].y < center.min_y)
			center.min_y = fdf->vertices[i].y;
		i++;
	}
	move_to_center(fdf, &center);
}
