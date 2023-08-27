/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_register.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:36:28 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 17:54:12 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press_cont(int keycode, t_fdf *fdf)
{
	int	keys;

	keys = fdf->keys;
	if (keycode == KEY_VISO)
		keys |= (1 << BIT_VISO);
	else if (keycode == KEY_VPLL)
		keys |= (1 << BIT_VPLL);
	else if (keycode == KEY_VTOP)
		keys |= (1 << BIT_VTOP);
	else if (keycode == KEY_HELP)
	{
		if (!((fdf->keys >> BIT_HELP) & 1))
			keys |= (1 << BIT_HELP);
		else
			keys &= ~(1 << BIT_HELP);
		fdf->state_changed = 1;
	}
	fdf->keys = keys;
	return (1);
}

static int	key_release_cont(int keycode, t_fdf *fdf)
{
	int	keys;

	keys = fdf->keys;
	if (keycode == KEY_H_UP)
		keys &= ~(1 << BIT_H_UP);
	else if (keycode == KEY_H_DOWN)
		keys &= ~(1 << BIT_H_DOWN);
	else if (keycode == KEY_VISO)
		keys &= ~(1 << BIT_VISO);
	else if (keycode == KEY_VPLL)
		keys &= ~(1 << BIT_VPLL);
	else if (keycode == KEY_VTOP)
		keys &= ~(1 << BIT_VTOP);
	fdf->keys = keys;
	return (1);
}

int	key_press(int keycode, t_fdf *fdf)
{
	int	keys;

	keys = fdf->keys;
	if (keycode == KEY_ESC)
		keys |= (1 << BIT_ESC);
	else if (keycode == KEY_RX_L)
		keys |= (1 << BIT_RX_L);
	else if (keycode == KEY_RX_R)
		keys |= (1 << BIT_RX_R);
	else if (keycode == KEY_RY_L)
		keys |= (1 << BIT_RY_L);
	else if (keycode == KEY_RY_R)
		keys |= (1 << BIT_RY_R);
	else if (keycode == KEY_RZ_L)
		keys |= (1 << BIT_RZ_L);
	else if (keycode == KEY_RZ_R)
		keys |= (1 << BIT_RZ_R);
	else if (keycode == KEY_H_UP)
		keys |= (1 << BIT_H_UP);
	else if (keycode == KEY_H_DOWN)
		keys |= (1 << BIT_H_DOWN);
	fdf->keys = keys;
	return (key_press_cont(keycode, fdf));
}

int	key_release(int keycode, t_fdf *fdf)
{
	int	keys;

	keys = fdf->keys;
	if (keycode == KEY_ESC)
		keys &= ~(1 << BIT_ESC);
	else if (keycode == KEY_RX_L)
		keys &= ~(1 << BIT_RX_L);
	else if (keycode == KEY_RX_R)
		keys &= ~(1 << BIT_RX_R);
	else if (keycode == KEY_RY_L)
		keys &= ~(1 << BIT_RY_L);
	else if (keycode == KEY_RY_R)
		keys &= ~(1 << BIT_RY_R);
	else if (keycode == KEY_RZ_L)
		keys &= ~(1 << BIT_RZ_L);
	else if (keycode == KEY_RZ_R)
		keys &= ~(1 << BIT_RZ_R);
	fdf->keys = keys;
	return (key_release_cont(keycode, fdf));
}
