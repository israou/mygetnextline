/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:47:31 by ichaabi           #+#    #+#             */
/*   Updated: 2023/12/09 16:24:00 by ichaabi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		checknewline(char *s)
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
		return (NULL); //F HALAT MABQA F LRESTE WALOU BASH NHBES LOOP DIAL LMAIN
	newindex = checknewline(s);

	tmp = s; //sauvegarde de l'adresse de la chaine d'origine
	line = extraction(s, 0, newindex + 1);//extraction de la sous chaine du debut jusqu'au '\n'
	*reste = extraction(s, newindex + 1, ft_strlen(s + newindex)); //extraction de la chaine restante apres le '\n' ignorer lign li deja khdit
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	// char		*s; //s d orgine
	ssize_t		readd; //resulat de read
	char		buf[BUFFER_SIZE + 1];
	static char	*stash; //apres buf

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	while (BUFFER_SIZE > 0)
	{
		readd = read(fd, buf, BUFFER_SIZE);
		if (readd == 0)
			return (divising(stash, &stash));
		else if (readd == -1)
		{
			free_(&stash);
			stash = NULL;
			return (NULL);
		}
		buf[readd] = '\0';
		stash = ft_strjoin(stash, buf);
		if (checknewline(stash) >= 0)
			return (divising(stash, &stash));
	}
}

void	free_(char **s)
{
	if (*s)// n est pas nul donc allocation dynamique a ete effectuee
	{
		free(*s);
		*s = NULL; //optionnel pour s'assurer que le* est null apres liberation
	}				//pour eviter que * ne pointe vers une zone de memoire liberee
}

// int main(void)
// {
// 	int fd = open("iss.txt", O_RDWR);
// 	char *line = get_next_line(fd);
// 	printf("%s", line);
// 	free (line);
// }
