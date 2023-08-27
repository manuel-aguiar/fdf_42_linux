/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_windows.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:55:36 by marvin            #+#    #+#             */
/*   Updated: 2023/07/20 16:55:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_release(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf->keys &= ~(1 << BIT_ESC);
	else if (keycode == KEY_MVL)
		fdf->keys &= ~(1 << BIT_MVL);
	else if (keycode == KEY_MVU)
		fdf->keys &= ~(1 << BIT_MVU);
	else if (keycode == KEY_MVR)
		fdf->keys &= ~(1 << BIT_MVR);
	else if (keycode == KEY_MVD)
		fdf->keys &= ~(1 << BIT_MVD);
	else if (keycode == KEY_RX_L)
		fdf->keys &= ~(1 << BIT_RX_L);
	else if (keycode == KEY_RX_R)
		fdf->keys &= ~(1 << BIT_RX_R);
	else if (keycode == KEY_RY_L)
		fdf->keys &= ~(1 << BIT_RY_L);
	else if (keycode == KEY_RY_R)
		fdf->keys &= ~(1 << BIT_RY_R);
	else if (keycode == KEY_RZ_L)
		fdf->keys &= ~(1 << BIT_RZ_L);
	else if (keycode == KEY_RZ_R)
		fdf->keys &= ~(1 << BIT_RZ_R);
	else if (keycode == KEY_H_UP)
		fdf->keys &= ~(1 << BIT_H_UP);
	else if (keycode == KEY_H_DOWN)
		fdf->keys &= ~(1 << BIT_H_DOWN);
	else if (keycode == KEY_ZIN)
		fdf->keys &= ~(1 << BIT_ZIN);
	else if (keycode == KEY_ZOUT)
		fdf->keys &= ~(1 << BIT_ZOUT);
	else if (keycode == KEY_VISO)
		fdf->keys &= ~(1 << BIT_VISO);
	else if (keycode == KEY_VPLL)
		fdf->keys &= ~(1 << BIT_VPLL);
	else if (keycode == KEY_VTOP)
		fdf->keys &= ~(1 << BIT_VTOP);
	return (0);
}

int key_press(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		fdf->keys |= (1 << BIT_ESC);
	else if (keycode == KEY_MVL)
		fdf->keys |= (1 << BIT_MVL);
	else if (keycode == KEY_MVU)
		fdf->keys |= (1 << BIT_MVU);
	else if (keycode == KEY_MVR)
		fdf->keys |= (1 << BIT_MVR);
	else if (keycode == KEY_MVD)
		fdf->keys |= (1 << BIT_MVD);
	else if (keycode == KEY_RX_L)
		fdf->keys |= (1 << BIT_RX_L);
	else if (keycode == KEY_RX_R)
		fdf->keys |= (1 << BIT_RX_R);
	else if (keycode == KEY_RY_L)
		fdf->keys |= (1 << BIT_RY_L);
	else if (keycode == KEY_RY_R)
		fdf->keys |= (1 << BIT_RY_R);
	else if (keycode == KEY_RZ_L)
		fdf->keys |= (1 << BIT_RZ_L);
	else if (keycode == KEY_RZ_R)
		fdf->keys |= (1 << BIT_RZ_R);
	else if (keycode == KEY_H_UP)
		fdf->keys |= (1 << BIT_H_UP);
	else if (keycode == KEY_H_DOWN)
		fdf->keys |= (1 << BIT_H_DOWN);
	else if (keycode == KEY_VISO)
		fdf->keys |= (1 << BIT_VISO);
	else if (keycode == KEY_VPLL)
		fdf->keys |= (1 << BIT_VPLL);
	else if (keycode == KEY_VTOP)
		fdf->keys |= (1 << BIT_VTOP);
	else if (keycode == KEY_HELP)
	{
		if (!((fdf->keys >> BIT_HELP) & 1))
			fdf->keys |= (1 << BIT_HELP);
		else
			fdf->keys &= ~(1 << BIT_HELP);
		fdf->state_changed = 1;
	}
	return (0);
}

int	init_window(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free_fdf(fdf));
	fdf->mlx_win = mlx_new_window(fdf->mlx, fdf->win_width, fdf->win_height, \
		fdf->win_name);
	fdf->front_img.img = mlx_new_image(fdf->mlx, fdf->win_width, \
		fdf->win_height);
	fdf->back_img.img = mlx_new_image(fdf->mlx, fdf->win_width, \
		fdf->win_height);
	if (!fdf->mlx_win || !fdf->front_img.img || !fdf->back_img.img)
		return (free_fdf(fdf));
	fdf->front_img.addr = mlx_get_data_addr(fdf->front_img.img, \
		&(fdf->front_img.bpp), &(fdf->front_img.line_len), \
		&(fdf->front_img.endian));
	fdf->back_img.addr = mlx_get_data_addr(fdf->back_img.img, \
		&(fdf->back_img.bpp), &(fdf->back_img.line_len), \
		&(fdf->back_img.endian));
	return (1);
}

int	img_to_window(t_fdf *fdf)
{
	t_mlx_img	swap;

	ft_memset(fdf->back_img.addr, 0, fdf->win_width * fdf->win_height \
		* sizeof(fdf->back_img.bpp));
	key_manager(fdf);
	mouse_manager(fdf);
	if (fdf->state_changed)
	{
		draw_image(fdf);
		swap = fdf->back_img;
		fdf->back_img = fdf->front_img;
		fdf->front_img = swap;
		mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, \
								fdf->front_img.img, 0, 0);
		help_string(fdf);
		fdf->state_changed = 0;
	}
	return (1);
}

int	rendering_loop(t_fdf *fdf)
{
	mlx_hook(fdf->mlx_win, 2, (1L << 0), key_press, fdf);
	mlx_hook(fdf->mlx_win, 3, (1L << 1), key_release, fdf);
	mlx_hook(fdf->mlx_win, 4, (1L << 2), mouse_press, fdf);
	mlx_hook(fdf->mlx_win, 5, (1L << 3), mouse_release, fdf);
	mlx_hook(fdf->mlx_win, 6, (1L << 6), mouse_position, fdf);
	mlx_hook(fdf->mlx_win, 17, (1L << 1), free_fdf, fdf);
	mlx_do_key_autorepeatoff(fdf->mlx);
	mlx_loop_hook(fdf->mlx, img_to_window, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
