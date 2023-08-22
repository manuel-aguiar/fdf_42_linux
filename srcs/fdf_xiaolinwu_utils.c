/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_xiaolinwu_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:43:08 by marvin            #+#    #+#             */
/*   Updated: 2023/07/21 15:43:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	xiaolin_x_major(t_fdf *fdf, t_pixel *start, t_pixel *end, t_xldata *data)
{
	data->err_adj = ((t_ulong)data->dy << 16) / (t_ulong)data->dx;
	data->save = data->dx;
	while (--data->dx)
	{
		data->err_temp = data->err_acc;
		data->err_acc += data->err_adj;
		if (data->err_acc <= data->err_temp)
			start->y++;
		start->x += data->slope;
		data->colour = avg_colour(start->colour, end->colour, \
					data->dx, data->save);
		set_pixel(fdf, start->x, start->y, avg_colour(get_pixel(fdf, start->x, \
					start->y), data->colour, data->err_acc, USHRT_MAX));
		set_pixel(fdf, start->x, start->y + 1, avg_colour(get_pixel(fdf, \
					start->x, start->y + 1), data->colour, USHRT_MAX \
					- data->err_acc, USHRT_MAX));
	}
	set_pixel(fdf, end->x, end->y, end->colour);
	return (1);
}

int	xiaolin_y_major(t_fdf *fdf, t_pixel *start, t_pixel *end, t_xldata *data)
{
	data->err_adj = ((t_ulong)data->dx << 16) / (t_ulong)data->dy;
	data->save = data->dy;
	while (--data->dy)
	{
		data->err_temp = data->err_acc;
		data->err_acc += data->err_adj;
		if (data->err_acc <= data->err_temp)
			start->x += data->slope;
		start->y++;
		data->colour = avg_colour(start->colour, end->colour, \
					data->dy, data->save);
		set_pixel(fdf, start->x, start->y, avg_colour(get_pixel(fdf, start->x, \
					start->y), data->colour, data->err_acc, USHRT_MAX));
		set_pixel(fdf, start->x + data->slope, start->y, avg_colour \
					(get_pixel(fdf, start->x + data->slope, start->y), \
					data->colour, USHRT_MAX - data->err_acc, USHRT_MAX));
	}
	set_pixel(fdf, end->x, end->y, end->colour);
	return (1);
}
