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
	int			num;
	int			den;

	i = 0;
	while (i < fdf->lenmap)
	{
		if (!fdf->map[i].colour)
		{
			fdf->map[i].colour = avg_colour(min_rgb, max_rgb, \
				fdf->max_z - fdf->map[i].height, fdf->z_range);
		}
		i++;
	}
	return (1);
}

static void	flat_map_leveling(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->lenmap)
	{
		fdf->map[i].height = 0;
		i++;
	}
	fdf->z_range = 1;
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
	if (!fdf->z_range)
		flat_map_leveling(fdf);
	fdf->view.zoom = ft_max(ft_min(fdf->win_width / fdf->mcols * DEF_ZOOM, \
					fdf->win_height / fdf->mrows * DEF_ZOOM), 1);
	fdf->view.zoom_cap = sqrt(pow(fdf->win_width, 2) \
						+ pow(fdf->win_height, 2));
	fdf->view.z_multi = ft_fmin((float)ft_max(fdf->mrows, fdf->mcols) \
						/ (float)fdf->z_range, Z_MULTI);
	return (1);
}

static void	setup_default_vals(t_fdf *fdf)
{
	fdf->win_width = FDF_WIDTH;
	fdf->win_height = FDF_HEIGHT;
	ft_strlcpy(fdf->win_name, FDF_WINDOW_NAME, sizeof(fdf->win_name));
	fdf->view.x_angle = X_ANGLE_ISO * (MY_PI / 180.0);
	fdf->view.y_angle = Y_ANGLE_ISO * (MY_PI / 180.0);
	fdf->view.z_angle = Z_ANGLE_ISO * (MY_PI / 180.0);
	setup_trigonometry(fdf);
	fdf->low_colour = LOW_RGB;
	fdf->high_colour = HIGH_RGB;
	fdf->view.x_offset = fdf->win_width / 2;
	fdf->view.y_offset = fdf->win_height / 2;
	fdf->first_render = 1;
	fdf->map = NULL;
	fdf->vertices = NULL;
	fdf->mlx = NULL;
	fdf->mlx_win = NULL;
	fdf->front_img.img = NULL;
	fdf->back_img.img = NULL;
	fdf->state_changed = 1;
	fdf->keys = 0;
	fdf->mouse.buttons = 0;
}

int	setup_fdf(t_fdf *fdf, char *file)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".fdf", 4))
		return (error_msg("fdf: input file must be of type \".fdf\"\n"));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror_msg(ERR_OPEN));
	setup_default_vals(fdf);
	if (!file_to_map(fdf, fd))
		return (0);
	if (fdf->lenmap <= 1)
		return (error_msg("fdf: input file has less than 2 points\n") + \
				free_fdf(fdf));
	default_zoom_height(fdf);
	default_colour(fdf, fdf->low_colour, fdf->high_colour);
	fdf->view.rot_sensib = cbrt(fdf->lenmap) * 0.00045f;
	fdf->view.hgt_sensib = cbrt(fdf->lenmap) * 0.00025f;
	fdf->vertices = malloc(sizeof((*fdf->vertices)) * fdf->lenmap);
	if (!fdf->vertices)
		return (perror_msg(ERR_MALLOC) + free_fdf(fdf));
	return (1);
}
