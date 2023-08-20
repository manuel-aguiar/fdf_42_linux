/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:58:35 by marvin            #+#    #+#             */
/*   Updated: 2023/07/20 16:58:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	default_colour(t_fdf *fdf, int min_rgb, int max_rgb)
{
	t_uint		i;
	float		perc;
	t_rgb		res[3];

	res[1] = rgb_split(max_rgb);
	res[2] = rgb_split(min_rgb);
	i = 0;
	while (i < fdf->lenmap)
	{
		if (!fdf->map[i].colour)
		{
			perc = (float)(fdf->map[i].height - fdf->min_z) \
				/ (float)fdf->z_range;
			res[0].r = (t_uchar)(res[1].r * perc + res[2].r * (1 - perc));
			res[0].g = (t_uchar)(res[1].g * perc + res[2].g * (1 - perc));
			res[0].b = (t_uchar)(res[1].b * perc + res[2].b * (1 - perc));
			fdf->map[i].colour = RGB(res[0].r, res[0].g, res[0].b);
		}
		i++;
	}
	return (1);
}

static int	default_zoom_height(t_fdf *fdf)
{
	t_uint	i;
	int		height;

	fdf->min_z = INT_MAX;
	fdf->max_z = INT_MIN;
	i = 0;
	while (i < fdf->lenmap)
	{
		height = fdf->map[i].height;
		if (height > fdf->max_z)
			fdf->max_z = height;
		if (height < fdf->min_z)
			fdf->min_z = height;
		i++;
	}
	fdf->z_range = fdf->max_z - fdf->min_z;
	fdf->view.zoom = ft_min(fdf->win_width / fdf->mcols / 2, \
					fdf->win_height / fdf->mrows / 2);
	return (1);
}

static void	setup_default_vals(t_fdf *fdf)
{
	fdf->win_width = FDF_WIDTH;
	fdf->win_height = FDF_HEIGHT;
	ft_strlcpy(fdf->win_name, FDF_WINDOW_NAME, sizeof(fdf->win_name));
	fdf->rgb_size = FDF_RGB_SIZE;
	fdf->view.x_angle = X_ANGLE_ISO * (MY_PI / 180.0);
	fdf->view.y_angle = Y_ANGLE_ISO * (MY_PI / 180.0);
	fdf->view.z_angle = Z_ANGLE_ISO * (MY_PI / 180.0);
	setup_trigonometry(fdf);
	fdf->low_colour = LOW_RGB;
	fdf->high_colour = HIGH_RGB;
	fdf->view.x_offset = fdf->win_width / 2;
	fdf->view.y_offset = fdf->win_height / 2;
	fdf->view.z_multi = Z_MULTI;
	fdf->map = NULL;
	fdf->vertices = NULL;
	fdf->front_win = NULL;
}

int	setup_trigonometry(t_fdf *fdf)
{
	fdf->view.cos_x = cosf(fdf->view.x_angle);
	fdf->view.sin_x = sinf(fdf->view.x_angle);
	fdf->view.cos_y = cosf(fdf->view.y_angle);
	fdf->view.sin_y = sinf(fdf->view.y_angle);
	fdf->view.cos_z = cosf(fdf->view.z_angle);
	fdf->view.sin_z = sinf(fdf->view.z_angle);
	return (1);
}

int	setup_fdf(t_fdf *fdf, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_msg(ERR_OPEN));
	setup_default_vals(fdf);
	if (!file_to_map(fdf, fd))
		return (0);
	default_zoom_height(fdf);
	default_colour(fdf, fdf->low_colour, fdf->high_colour);
	fdf->vertices = malloc(sizeof((*fdf->vertices)) * fdf->lenmap);
	if (!fdf->vertices)
		return (error_msg(ERR_MALLOC) + free_fdf(fdf));
	setup_vertices(fdf);
	fdf->front_win = ft_calloc(fdf->win_width * fdf->win_height \
					* fdf->rgb_size, sizeof(t_uchar));
	if (!fdf->front_win)
		return (error_msg(ERR_MALLOC) + free_fdf(fdf));
	return (1);
}
