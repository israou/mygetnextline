/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:51:42 by ichaabi           #+#    #+#             */
/*   Updated: 2023/12/03 22:52:15 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while(s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*pa;

	i = 0;
	len= ft_strlen(s);
	pa = (char *)malloc(sizeof(char) * (len + 1));
	if (!pa)
		return (NULL);
	while (i < len)
	{
		pa[i] = s[i];
		i++;
	}
	pa[i] = '\0';
	return (pa);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	line = (char *)malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (line == NULL)
		return (NULL);
	while (s1[i])
	{
		line[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		line[i + j] = s2[j];
		j++;
	}
	line[i + j] = '\0';
	return (line);
}

char	*extraction(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	// size_t	r;

	if (s == NULL)
		return (NULL);
	i = 0;
	// r = ft_strlen(s);
	str = (char *) malloc (sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

