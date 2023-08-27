/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_moves_cont.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:27:56 by marvin            #+#    #+#             */
/*   Updated: 2023/08/14 14:27:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_zoom(t_fdf *fdf, int key, int change);

static int	adjust_height(t_fdf *fdf, int key, float change)
{
	float	chg;

	if (fdf->view.z_multi < 0.000005f)
		return (1);
	chg = ft_fmin(ft_max(fdf->mrows, fdf->mcols) / (float)fdf->z_range, change);
	if ((key >> BIT_H_UP) & 1)
		fdf->view.z_multi += chg;
	if ((key >> BIT_H_DOWN) & 1)
		fdf->view.z_multi -= chg;
	if (fdf->view.z_multi < 0.00001f)
		fdf->view.z_multi = 0.00001f;
	fdf->state_changed = 1;
	return (1);
}

static int	adjust_rotation(t_fdf *fdf, int key, float change)
{
	if ((key >> BIT_RX_L) & 1)
		fdf->view.x_angle -= change;
	if ((key >> BIT_RX_R) & 1)
		fdf->view.x_angle += change;
	if ((key >> BIT_RY_L) & 1)
		fdf->view.y_angle -= change;
	if ((key >> BIT_RY_R) & 1)
		fdf->view.y_angle += change;
	if ((key >> BIT_RZ_L) & 1)
		fdf->view.z_angle -= change;
	if ((key >> BIT_RZ_R) & 1)
		fdf->view.z_angle += change;
	setup_trigonometry(fdf);
	fdf->state_changed = 1;
	return (1);
}

static void	reset_defaults(t_fdf *fdf)
{
	fdf->view.zoom = ft_max(ft_min(fdf->win_width / fdf->mcols * 2 / 3, \
					fdf->win_height / fdf->mrows * 2 / 3), 1);
	fdf->view.z_multi = ft_fmin((float)ft_max(fdf->mrows, fdf->mcols) \
						/ (float)ft_max(fdf->z_range, 1), Z_MULTI);
	fdf->view.x_offset = fdf->win_width / 2;
	fdf->view.y_offset = fdf->win_height / 2;
	fdf->first_render = 1;
	fdf->state_changed = 1;
}

static int	apply_projection(t_fdf *fdf, int key)
{
	if ((key >> BIT_VISO) & 1)
	{
		fdf->view.x_angle = X_ANGLE_ISO * (MY_PI / 180.0);
		fdf->view.y_angle = Y_ANGLE_ISO * (MY_PI / 180.0);
		fdf->view.z_angle = Z_ANGLE_ISO * (MY_PI / 180.0);
	}
	else if ((key >> BIT_VPLL) & 1)
	{
		fdf->view.x_angle = X_ANGLE_PLL * (MY_PI / 180.0);
		fdf->view.y_angle = Y_ANGLE_PLL * (MY_PI / 180.0);
		fdf->view.z_angle = Z_ANGLE_PLL * (MY_PI / 180.0);
	}
	else if ((key >> BIT_VTOP) & 1)
	{
		fdf->view.x_angle = X_ANGLE_TOP * (MY_PI / 180.0);
		fdf->view.y_angle = Y_ANGLE_TOP * (MY_PI / 180.0);
		fdf->view.z_angle = Z_ANGLE_TOP * (MY_PI / 180.0);
	}
	setup_trigonometry(fdf);
	reset_defaults(fdf);
	return (1);
}

int	key_manager(t_fdf *fdf)
{
	int	key;

	key = fdf->keys;
	if ((key >> BIT_ESC) & 1)
		free_fdf(fdf);
	if ((key >> BIT_H_UP) & 1 || (key >> BIT_H_DOWN) & 1)
		adjust_height(fdf, key, fdf->view.hgt_sensib);
	if ((key >> BIT_ZIN) & 1 || (key >> BIT_ZOUT) & 1)
		key_zoom(fdf, key, 1);
	if ((key >> BIT_RX_L) & 1 || (key >> BIT_RX_R) & 1 \
	|| (key >> BIT_RY_L) & 1 || (key >> BIT_RY_R) & 1 \
	|| (key >> BIT_RZ_L) & 1 || (key >> BIT_RZ_R) & 1)
		adjust_rotation(fdf, key, fdf->view.rot_sensib);
	if ((key >> BIT_VISO) & 1)
		apply_projection(fdf, key);
	if ((key >> BIT_VPLL) & 1)
		apply_projection(fdf, key);
	if ((key >> BIT_VTOP) & 1)
		apply_projection(fdf, key);
	return (0);
}
