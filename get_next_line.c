/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:14 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/29 14:56:44 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		nl_index(char *buf)
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

static char		*get_rest(char *buf)
{
	char	*end;
	int		i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			end = ft_strndup(buf, i + 1);
			return (end);
		}
		i++;
	}
	end = ft_strdup(buf);
	return (end);
}

static	int		check_rest(char **rest, char **content, char *buf, int ret)
{
	int		nl_pos;

	if ((nl_pos = nl_index(buf)) > -1)
	{
		*rest = ft_strsub(buf, nl_pos + 1, ret - nl_pos);
		ft_strncat(*content, buf, (size_t)nl_pos);
		return (1);
	}
	return (0);
}

static int		readfile(int fd, char **content, char **rest)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*temp;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		if (!(temp = ft_strnew(ft_strlen(*content) + 1)))
			return (-1);
		if (*content)
		{
			ft_strcpy(temp, *content);
			free(*content);
		}
		if (!(*content = ft_strnew(ft_strlen(temp) + ft_strlen(buf) + 1)))
			return (-1);
		ft_strcpy(*content, temp);
		free(temp);
		if (check_rest(rest, content, buf, ret))
			return (1);
		ft_strcat(*content, buf);
	}
	return (!(*content == NULL && ret <= 0 && !ft_strlen(*rest)));
}

int				get_next_line(const int fd, char **line)
{
	static char	*rest;
	char		*content;
	char		*temp;
	int			ret;

	if (BUFF_SIZE <= 0 || fd < 0 || fd == 1 || fd == 2 || !line)
		return (-1);
	content = 0;
	temp = 0;
	if (ft_strlen(rest) > 0)
	{
		content = get_rest(rest);
		if (rest[ft_strlen(content) - 1])
			temp = ft_strdup(&rest[ft_strlen(content)]);
		free(rest);
		rest = temp;
		if (ft_strlen(rest) > 0 || ft_strchr(content, '\n'))
		{
			*line = ft_strndup(content, ft_strlen(content) - 1);
			return (1);
		}
	}
	ret = readfile(fd, &content, &rest);
	*line = content;
	return (ret);
}
