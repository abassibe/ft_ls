/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 14:28:08 by abassibe          #+#    #+#             */
/*   Updated: 2017/04/17 17:33:35 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_btoi(char *str)
{
	int		len;
	int		ret;
	int		pow;

	len = ft_strlen(str) - 1;
	ret = 0;
	pow = 0;
	while (len >= 0)
	{
		if (str[len] == '1')
			ret += ft_power(2, pow);
		pow++;
		len--;
	}
	return (ret);
}
