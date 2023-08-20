/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_add_to_libft.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:55:54 by marvin            #+#    #+#             */
/*   Updated: 2023/07/17 11:55:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ternary(int cond, int true, int false)
{
	if (cond)
		return (true);
	return (false);
}

int	ft_abs(int num)
{
	return (ft_ternary(num > 0, num, -num));
}

int	ft_min(int first, int second)
{
	if (first > second)
		return (second);
	return (first);
}

int	ft_max(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}
