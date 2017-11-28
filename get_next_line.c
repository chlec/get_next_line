/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:14 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/28 12:10:38 by clecalie         ###   ########.fr       */
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

	if (BUFF_SIZE <= 0 || fd < 0 || fd == 1 || fd == 2 || !line)
		return (-1);
	content = 0;
	if (ft_strlen(reste) > 0)
	{
		/* issue here: the get reste give juste "ipsum" instead of all the strings
		 * on the last strings, temprest should give NULL instead of "ipsum"*/
		content = get_reste(reste);
		temprest = ft_strdup(&reste[ft_strlen(content) + 1]);
		free(reste);
		reste = temprest;	
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
	if (content == NULL && ret == 0 && !ft_strlen(reste))
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;
	int		cmp;
	
	(void)argc;
	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)))
	{
		if ((cmp = ft_strcmp(line, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus")) != 0)
		{	
			printf("error: %d\n", cmp);
			if (line)
				printf("line: %s\n", line);
		}
		//printf("Ret: %d Line: %s\n", ret, line);
	}
	printf("Ret: %d Line: %s\n", ret, line);
	free(line);
	return (0);
}
