/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:33:50 by ichaabi           #+#    #+#             */
/*   Updated: 2023/12/10 21:26:54 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	checknewline(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

char	*divising(char *s, char **reste)
{
	char	*line;
	char	*tmp;
	int		newindex;

	if (!s)
		return (NULL);
	if (*reste && **reste == '\0')
	{
		free(*reste);
		*reste = NULL;
		return (NULL);
	}
	//F HALAT MABQA F LRESTE WALOU BASH NHBES LOOP DIAL LMAIN
	newindex = checknewline(s);
	if (newindex == -1)
	{
		line = ft_strdup(s);
		free(*reste);
		*reste = ft_strdup("\0");
		return (line);
	}
	tmp = s; //sauvegarde de l'adresse de la chaine d'origine
	line = extraction(s, 0, newindex + 1);//extraction de la sous chaine du debut jusqu'au '\n'
	*reste = extraction(s, newindex + 1, ft_strlen(s + newindex)); //extraction de la chaine restante apres le '\n' ignorer lign li deja khdit
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	ssize_t		readd; //resulat de read nbre d'octets lus
	static char	*stash[OPEN_MAX]; //tableau statique de pointeurs pour stocker les donnees lues du fichier associe a fd

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX) //verification de la validite de fd; si <1 ou depasse la limite max
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	while (BUFFER_SIZE > 0)
	{
		readd = read(fd, buf, BUFFER_SIZE);
		if (readd == 0) //read a atteint la fin de fd
			return (free(buf), divising(stash[fd], &stash[fd]));
		else if (readd == -1)
		{
			free(stash[fd]);
			stash[fd] = NULL;
			return (free(buf), NULL);
		}
		buf[readd] = '\0';
		stash[fd] = ft_strjoin(stash[fd], buf); //concatenation de buf dans stash
		if (checknewline(stash[fd]) >= 0) //s'il contient \n
			return (free(buf), divising(stash[fd], &stash[fd]));
	}
}