/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecalie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 14:20:14 by clecalie          #+#    #+#             */
/*   Updated: 2017/11/25 14:25:16 by clecalie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 99999	

char			*ft_strcpy(char *dst, char *src);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strdup(const char *s1);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);
char			*ft_strncpy(char *dst, const char *src, size_t len);

#endif