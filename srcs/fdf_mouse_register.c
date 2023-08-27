/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse_register.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:40:36 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 18:17:15 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_press(int button, int x, int y, t_fdf *fdf)
{
	fdf->mouse.prev_x = x;
	fdf->mouse.prev_y = y;
	if (button == BUT_L)
	{
		fdf->mouse.buttons |= (1 << BUT_L);
		fdf->mouse.prev_x = x;
		fdf->mouse.prev_y = y;
	}
	else if (button == BUT_R)
		fdf->mouse.buttons |= (1 << BUT_R);
	else if (button == BUT_M)
		fdf->mouse.buttons |= (1 << BUT_M);
	else if (button == BUT_U)
		fdf->mouse.buttons |= (1 << BUT_U);
	else if (button == BUT_D)
		fdf->mouse.buttons |= (1 << BUT_D);
	return (1);
}

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	if (button == BUT_L)
		fdf->mouse.buttons &= ~(1 << BUT_L);
	else if (button == BUT_R)
		fdf->mouse.buttons &= ~(1 << BUT_R);
	else if (button == BUT_M)
		fdf->mouse.buttons &= ~(1 << BUT_M);
	return (1);
}

int	mouse_position(int x, int y, t_fdf *fdf)
{
	fdf->mouse.cur_x = x;
	fdf->mouse.cur_y = y;
	return (1);
}
