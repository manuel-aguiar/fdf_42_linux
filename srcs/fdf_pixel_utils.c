/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rgb_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:30:05 by marvin            #+#    #+#             */
/*   Updated: 2023/07/21 15:30:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel	temp;

	temp = *start;
	*start = *end;
	*end = temp;
}

void	set_pixel(t_fdf *fdf, int x, int y, int rgb)
{
	int	index;

	index = getindex(fdf, y, x);
	fdf->front_win[index++] = (rgb >> 16) & 0xff;
	fdf->front_win[index++] = (rgb >> 8) & 0xff;
	fdf->front_win[index] = rgb & 0xff;
}

int	avg_colour(int start, int end, int num, int den)
{
	int	r;
	int	g;
	int	b;

	r = ((start >> 16) & 0xff) * num / den \
		+ ((end >> 16) & 0xff) * (den - num) / den;
	g = ((start >> 8) & 0xff) * num / den \
		+ ((end >> 8) & 0xff) * (den - num) / den;
	b = (start & 0xff) * num / den \
		+ (end & 0xff) * (den - num) / den;
	return (RGB(r, g, b));
}

int	get_rgb(t_fdf *fdf, int x, int y)
{
	int	index;
	int	r;
	int	g;
	int	b;

	index = getindex(fdf, y, x);
	r = fdf->front_win[index++];
	g = fdf->front_win[index++];
	b = fdf->front_win[index];
	return (RGB(r, g, b));
}

t_rgb	rgb_split(int colour)
{
	t_rgb	res;

	res.r = RGB_R(colour);
	res.g = RGB_G(colour);
	res.b = RGB_B(colour);
	return (res);
}
