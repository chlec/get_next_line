/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:14 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/27 15:29:17 by clecalie         ###   ########.fr       */
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
			end = ft_strndup(buf, i);
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
	char	*temp;
	char	*content;
	int		nl_pos;
	char	*temprest;

	if (fd < 0 || fd == 1 || fd == 2 || BUFF_SIZE <= 0 || !line)
		return (-1);
	content = 0;
	if (ft_strlen(reste) > 0)
	{
		content = get_reste(reste);
		temprest = ft_strdup(&reste[ft_strlen(content) + 1]);
		free(reste);
		reste = temprest;
		if (ft_strlen(reste) > 0)
		{
			*line = content;
			return (1);
		}
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(temp = ft_strnew(ft_strlen(content) + 1)))
			return (-1);
		if (content)
		{
			ft_strcpy(temp, content);
			free(content);
		}
		if (!(content = ft_strnew(ft_strlen(temp) + ft_strlen(buf) + 1)))
			return (-1);
		ft_strcpy(content, temp);
		free(temp);
		if ((nl_pos = buf_nl(buf)) > -1)
		{
			reste = ft_strsub(buf, nl_pos + 1, ret - nl_pos);
			ft_strncat(content, buf, (size_t)nl_pos);
			*line = content;
			return (1);
		}
		ft_strcat(content, buf);
	}
	*line = content;
	if (content == NULL && ret == 0 && !*reste)
		return (0);
	return (1);
}

int		main(void)
{
	int		fd;
	char	*line;
	int		ret;

	fd = 0;//open("test", O_RDONLY);
	while ((ret = get_next_line(fd, &line)))
	{
		printf("Ret: %d Line: %s\n", ret, line);
	}
	printf("Ret: %d Line: %s\n", ret, line);
	return (0);
}
