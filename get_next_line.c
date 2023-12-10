/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:47:31 by ichaabi           #+#    #+#             */
/*   Updated: 2023/12/10 21:10:56 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		line = ft_strdup(s); //duppliquer la chaine s et la considerer comme une ligne
		free(*reste);
		*reste = ft_strdup("\0"); //initialiser la partie restante a une chaine vide
		return (line);
	}
	tmp = s; //sauvegarde l'adresse de la chaine d'origine
	line = extraction(s, 0, newindex + 1);//extraction de la sous chaine du debut jusqu'au '\n'
	*reste = extraction(s, newindex + 1, ft_strlen(s + newindex)); //extraction de la chaine restante apres le '\n' ignorer lign li deja khdit
	free(tmp);
	return (line);
}
#include <limits.h>
char	*get_next_line(int fd)
{
	write(1, "aa\n", 3);
	char		*buf;
	ssize_t		readd; //resulat de read
	static char	*stash; //apres buf

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1 || BUFFER_SIZE >= INT_MAX) //verification de la validite de fd; si <1 ou depasse la limite max
		return (NULL); //ela qbel +1 bash mayoverflowish
	buf = malloc(BUFFER_SIZE + 1);
	while (BUFFER_SIZE > 0)
	{
		readd = read(fd, buf, BUFFER_SIZE);
		if (readd == 0) //read a atteint la fin de fd
			return (free(buf), divising(stash, &stash));
		else if (readd == -1)
		{
			free(stash);
			stash = NULL;
			return (free(buf), NULL);
		}
		buf[readd] = '\0';
		stash = ft_strjoin(stash, buf); //concatenation de buf dans stash
		if (checknewline(stash) >= 0) //s'il contient \n
			return (free(buf), divising(stash, &stash));
	}
}

int main(void)
{
	int fd = open("/dev/urandom", O_RDONLY, 0777);
	char *s = get_next_line(fd);
	while(s)
	{
		printf("%s", s);
		s = get_next_line(fd); //kan affecter liha la ligne suivante
	}
	return 0;

}