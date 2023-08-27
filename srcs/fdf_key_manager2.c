/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_manager2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:53:51 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 20:10:46 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_zoom(t_fdf *fdf, int key, int change)
{
	int	prev_zoom;

	prev_zoom = fdf->view.zoom;
	if ((key >> BIT_ZIN) & 1)
		fdf->view.zoom += ft_max(fdf->view.zoom / 15, 1);
	if ((key >> BIT_ZOUT) & 1)
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
	fdf->view.x_offset = fdf->mouse.cur_x - (fdf->mouse.cur_x \
	- fdf->view.x_offset) * fdf->view.zoom / prev_zoom;
	fdf->view.y_offset = fdf->mouse.cur_y - (fdf->mouse.cur_y \
	- fdf->view.y_offset) * fdf->view.zoom / prev_zoom;
	fdf->state_changed = 1;
	return (1);
}
