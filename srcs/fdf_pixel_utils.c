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

void	set_pixel(t_fdf *fdf, int x, int y, int color)
{
	char		*dst;

	dst = fdf->back_img.addr + (y * fdf->back_img.line_len + \
		x * (fdf->back_img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_fdf *fdf, int x, int y)
{
	char		*dst;

	dst = fdf->back_img.addr + (y * fdf->back_img.line_len + \
		x * (fdf->back_img.bpp / 8));
	return (*(unsigned int *)dst);
}

void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel	temp;

	temp = *start;
	*start = *end;
	*end = temp;
}

int	avg_colour(int start, int end, int num, int den)
{
	t_ulong	r;
	t_ulong	g;
	t_ulong b;

	if (den == 0)
		return (start);
	r = ((start >> 16) & 0xff) * num / den \
		+ ((end >> 16) & 0xff) * (den - num) / den;
	g = ((start >> 8) & 0xff) * num / den \
		+ ((end >> 8) & 0xff) * (den - num) / den;
	b = (start & 0xff) * num / den \
		+ (end & 0xff) * (den - num) / den;
	return (RGB(r, g, b));
}
