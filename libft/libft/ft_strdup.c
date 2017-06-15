/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:09:47 by abassibe          #+#    #+#             */
/*   Updated: 2017/04/29 04:44:26 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *src)
{
	size_t		c;
	char		*dst;

	c = 0;
	dst = ft_strnew((int)ft_strlen(src));
	while (c != ft_strlen(src))
	{
		dst[c] = src[c];
		c++;
	}
	return (dst);
}
