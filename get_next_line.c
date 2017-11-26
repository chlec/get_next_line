/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:14 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/25 14:25:16 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		buf_nl(char *buf)
{
	int		i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_reste(char *buf)
{
	char	*end;
	int		i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			end = (char*)malloc(sizeof(char) * (i + 1));
			//REMPLACER NCY PAR UNE AUTRE FCT
			ft_strncpy(end, buf, i);
			return (end);
		}
		i++;
	}
	end = ft_strdup(buf);
	return (end);
}

int			get_next_line(const int fd, char **line)
{
	static char	*reste;
	char	buf[BUFF_SIZE + 1];
	int		ret;
	char	*tab1;
	char	*tab2;
	int		len;
	int		jl_pos;

	if (fd < 0 || fd == 1 || fd == 2 || BUFF_SIZE <= 0 || !line)
		return (-1);
	len = BUFF_SIZE;
	tab2 = 0;
	if (reste)
	{
		tab2 = get_reste(reste);
		reste = &reste[ft_strlen(tab2) + 1];
		if (ft_strlen(reste) > 0)
		{
			*line = tab2;
			return (1);
		}
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(tab1 = (char*)malloc(sizeof(char) * (len + 1))))
			return (-1);
		if (tab2)
		{
			tab1 = ft_strcpy(tab1, tab2);
			free(tab2);
		}
		len += ret;
		if (!(tab2 = (char*)malloc(sizeof(char) * (len + 1))))
			return (-1);
		ft_strcpy(tab2, tab1);
		free(tab1);
		if ((jl_pos = buf_nl(buf)) > -1)
		{
			reste = ft_strsub(buf, jl_pos + 1, ret - jl_pos);
			ft_strncat(tab2, buf, (size_t)jl_pos);
			*line = tab2;
			return (1);
		}
		else {
			ft_strcat(tab2, buf);
		}
	}
	*line = tab2;
	if (ret == 0 && !*reste)
		return (0);
	return (1);
}

int		main(void)
{
	int	fd;
	char	*line;

	fd = open("test", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	get_next_line(fd, &line);
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	free(line);
	printf("-----------\n");
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	printf("-----------\n");
	free(line);
	printf("%d\n", get_next_line(fd, &line));
	return (0);
}