/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:41:15 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/01 18:09:09 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

char	*gnl_strdup(const char *s);
char	*gnl_substr(const char *s, int start, int len);
char	*gnl_strjoin(const char *s1, const char *s2);
int		gnl_strlen(const char *s);
int		gnl_strchr(const char *s, char c);
int		get_next_line(int fd, char **line);

#endif
