/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:56:31 by marvin            #+#    #+#             */
/*   Updated: 2023/07/11 09:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_glfw(t_fdf *fdf)
{
	return (1);
}

int	free_fdf(t_fdf *fdf)
{
	if (fdf->map)
		free(fdf->map);
	if (fdf->vertices)
		free(fdf->vertices);
	if (fdf->front_win)
		free(fdf->front_win);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
		return (0);
	if (!setup_fdf(&fdf, av[1]))
		return (0);
	if (!init_window(&fdf))
		return (0);
	new_render(&fdf);
	free_fdf(&fdf);
	return (0);
}
