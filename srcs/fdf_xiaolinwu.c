/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_xiaolinwu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:22:41 by marvin            #+#    #+#             */
/*   Updated: 2023/07/18 13:22:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	xiaolin_diagonal(t_fdf *fdf, t_pixel *start, \
t_pixel *end, t_xldata *data)
{
	data->save = data->dy;
	while (--data->dy != 0)
	{
		data->colour = avg_colour(start->colour, end->colour, \
					data->dy, data->save);
		start->x += data->slope;
		start->y++;
		set_pixel(fdf, start->x, start->y, data->colour);
	}
	return (1);
}

static int	xiaolin_vertical(t_fdf *fdf, t_pixel *start, \
t_pixel *end, t_xldata *data)
{
	data->save = data->dy;
	while (data->dy-- != 0)
	{
		data->colour = avg_colour(start->colour, end->colour, \
					data->dy, data->save);
		start->y++;
		set_pixel(fdf, start->x, start->y, data->colour);
	}
	return (1);
}

static int	xiaolin_horizontal(t_fdf *fdf, t_pixel *start, \
t_pixel *end, t_xldata *data)
{
	data->save = data->dx;
	while (--data->dx != 0)
	{
		data->colour = avg_colour(start->colour, end->colour, \
					data->dx, data->save);
		start->x += data->slope;
		set_pixel(fdf, start->x, start->y, data->colour);
	}
	return (1);
}

int	xiaolinwu_line(t_fdf *fdf, t_pixel start, t_pixel end)
{
	t_xldata	data;

	if (start.y > end.y)
		swap_pixels(&start, &end);
	set_pixel(fdf, start.x, start.y, start.colour);
	data.dx = end.x - start.x;
	if (data.dx >= 0)
		data.slope = 1;
	else
	{
		data.slope = -1;
		data.dx = -data.dx;
	}
	data.dy = end.y - start.y;
	if (data.dx == 0)
		return (xiaolin_vertical(fdf, &start, &end, &data));
	if (data.dy == 0)
		return (xiaolin_horizontal(fdf, &start, &end, &data));
	if (data.dx == data.dy)
		return (xiaolin_diagonal(fdf, &start, &end, &data));
	data.err_acc = 0;
	if (data.dy > data.dx)
		return (xiaolin_y_major(fdf, &start, &end, &data));
	return (xiaolin_x_major(fdf, &start, &end, &data));
}
