/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:54:08 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 20:09:13 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	mouse_zoom(t_fdf *fdf, int key, int change)
{
	int	prev_zoom;

	prev_zoom = fdf->view.zoom;
	if ((key >> BUT_U) & 1)
		fdf->view.zoom += ft_max(fdf->view.zoom / 15, 1);
	if ((key >> BUT_D) & 1)
		fdf->view.zoom -= ft_max(fdf->view.zoom / 15, 1);
	if (fdf->view.zoom < 1)
	{
		fdf->view.zoom = 1;
		return (1);
	}
	if (fdf->view.zoom > fdf->view.zoom_cap)
	{
		fdf->view.zoom = fdf->view.zoom_cap;
		return (1);
	}
	fdf->mouse.buttons &= ~(1 << BUT_U);
	fdf->mouse.buttons &= ~(1 << BUT_D);
	fdf->view.x_offset = fdf->mouse.cur_x - (fdf->mouse.cur_x \
	- fdf->view.x_offset) * fdf->view.zoom / prev_zoom;
	fdf->view.y_offset = fdf->mouse.cur_y - (fdf->mouse.cur_y \
	- fdf->view.y_offset) * fdf->view.zoom / prev_zoom;
	fdf->state_changed = 1;
	return (1);
}

int	mouse_manager(t_fdf *fdf)
{
	int	buttons;

	buttons = fdf->mouse.buttons;
	if ((buttons >> BUT_L) & 1)
	{
		fdf->view.x_offset += (fdf->mouse.cur_x - fdf->mouse.prev_x);
		fdf->view.y_offset += (fdf->mouse.cur_y - fdf->mouse.prev_y);
		fdf->mouse.prev_x = fdf->mouse.cur_x;
		fdf->mouse.prev_y = fdf->mouse.cur_y;
		fdf->state_changed = 1;
	}
	if ((buttons >> BUT_U) & 1 || (buttons >> BUT_D) & 1)
		mouse_zoom(fdf, buttons, 1);
	return (1);
}
