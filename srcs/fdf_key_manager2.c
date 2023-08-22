/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:49:32 by marvin            #+#    #+#             */
/*   Updated: 2023/07/20 16:49:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	adjust_offset(t_fdf *fdf, int key, int change)
{
	if (key == ARR_U)
		fdf->view.y_offset += -change;
	if (key == ARR_D)
		fdf->view.y_offset += change;
	if (key == ARR_R)
		fdf->view.x_offset += change;
	if (key == ARR_L)
		fdf->view.x_offset += -change;
	return (1);
}

int	adjust_zoom(t_fdf *fdf, int key, int change)
{
	int	prev_zoom;

	prev_zoom = fdf->view.zoom;
	if (key == 'p')
		change *= -1;
	fdf->view.zoom += change;
	if (fdf->view.zoom < 1)
		fdf->view.zoom = 1;
	fdf->view.x_offset = fdf->win_width / 2 - (fdf->win_width / 2 \
	- fdf->view.x_offset) * fdf->view.zoom / prev_zoom;
	fdf->view.y_offset = fdf->win_height / 2 - (fdf->win_height / 2 \
	- fdf->view.y_offset) * fdf->view.zoom / prev_zoom;
	return (1);
}

int	apply_projection(t_fdf *fdf, int key)
{
	if (key == 'b')
	{
		fdf->view.x_angle = X_ANGLE_ISO * (MY_PI / 180.0);
		fdf->view.y_angle = Y_ANGLE_ISO * (MY_PI / 180.0);
		fdf->view.z_angle = Z_ANGLE_ISO * (MY_PI / 180.0);
	}
	else if (key == 'n')
	{
		fdf->view.x_angle = X_ANGLE_PLL * (MY_PI / 180.0);
		fdf->view.y_angle = Y_ANGLE_PLL * (MY_PI / 180.0);
		fdf->view.z_angle = Z_ANGLE_PLL * (MY_PI / 180.0);
	}
	else if (key == 'm')
	{
		fdf->view.x_angle = X_ANGLE_TOP * (MY_PI / 180.0);
		fdf->view.y_angle = Y_ANGLE_TOP * (MY_PI / 180.0);
		fdf->view.z_angle = Z_ANGLE_TOP * (MY_PI / 180.0);
	}
	setup_trigonometry(fdf);
	return (1);
}
