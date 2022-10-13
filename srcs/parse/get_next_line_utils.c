/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:05:51 by avoltorb          #+#    #+#             */
/*   Updated: 2022/10/13 15:13:30 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_gnl_strcpy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while ((dest[i] || src[i]) && len--)
	{
		dest[i] = src[i];
		i++;
	}
}

int	ft_gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_gnl_strjoin(char *cache, char *buf)
{
	int		clen;
	int		blen;
	char	*str;

	if (cache == NULL)
	{
		cache = (char *)malloc(sizeof(char));
		if (!cache)
			return (NULL);
		cache[0] = '\0';
	}
	clen = ft_gnl_strlen(cache);
	blen = ft_gnl_strlen(buf);
	str = (char *)malloc(sizeof(char) * (clen + blen + 1));
	if (!str)
		return (NULL);
	str[clen + blen] = '\0';
	ft_gnl_strcpy(str, cache, clen);
	ft_gnl_strcpy(&str[clen], buf, blen);
	free(cache);
	return (str);
}

char	*ft_gnl_strchr(char *str, char c)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return (&str[i]);
}
