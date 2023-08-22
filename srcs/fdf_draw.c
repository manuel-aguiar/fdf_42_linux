/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:32:46 by marvin            #+#    #+#             */
/*   Updated: 2023/07/21 15:32:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform_pixel(t_fdf *fdf, t_pixel *pixel)
{
	t_pixel	og;

	og = *pixel;
	pixel->y = og.y * fdf->view.cos_x + pixel->z * fdf->view.sin_x;
	pixel->z = og.y * -fdf->view.sin_x + pixel->z * fdf->view.cos_x;
	og = *pixel;
	pixel->x = og.x * fdf->view.cos_y + pixel->z * fdf->view.sin_y;
	pixel->z = og.x * -fdf->view.sin_y + pixel->z * fdf->view.cos_y;
	og = *pixel;
	pixel->x = og.x * fdf->view.cos_z - og.y * fdf->view.sin_z;
	pixel->y = og.x * fdf->view.sin_z + og.y * fdf->view.cos_z;
}

void	offset_from_center(t_fdf *fdf)
{
	t_pixel		corner;
	t_pixel		center;
	int			dx;
	int			dy;
	t_uint		i;

	corner = fdf->vertices[(fdf->mcols * (fdf->mrows - 1))];
	center = fdf->vertices[(fdf->mcols * (fdf->mrows / 2) + fdf->mcols / 2)];
	dx = corner.x - center.x;
	dy = corner.y - center.y;
	i = 0;
	while (i < fdf->lenmap)
	{
		fdf->vertices[i].x += dx;
		fdf->vertices[i].y += dy;
		i++;
	}
}

int	setup_vertices(t_fdf *fdf)
{
	t_uint	i;

	i = 0;
	while (i < fdf->lenmap)
	{
		fdf->vertices[i].x = (i % fdf->mcols) * fdf->view.zoom;
		fdf->vertices[i].y = (fdf->mrows - (i / fdf->mcols + 1)) \
						* fdf->view.zoom;
		fdf->vertices[i].z = fdf->map[i].height * fdf->view.zoom \
						* fdf->view.z_multi;
		fdf->vertices[i].colour = fdf->map[i].colour;
		transform_pixel(fdf, &fdf->vertices[i]);
		fdf->vertices[i].x += fdf->view.x_offset;
		fdf->vertices[i].y += fdf->view.y_offset;
		i++;
	}
	offset_from_center(fdf);
	return (1);
}

int	draw_image(t_fdf *fdf)
{
	t_uint		i;
	t_pixel		new[2];

	i = 0;
	while (i < fdf->lenmap)
	{
		if (i + fdf->mcols < fdf->lenmap && liang_barsky_clipper \
			(fdf, fdf->vertices[i], fdf->vertices[i + fdf->mcols], new))
			xiaolinwu_line(fdf, new[0], new[1]);
		if (i / fdf->mcols == (i + 1) / fdf->mcols && liang_barsky_clipper \
			(fdf, fdf->vertices[i], fdf->vertices[i + 1], new))
			xiaolinwu_line(fdf, new[0], new[1]);
		i++;
	}
	return (1);
}
