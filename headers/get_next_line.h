/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:05:56 by avoltorb          #+#    #+#             */
/*   Updated: 2022/09/25 15:09:33 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

int		ft_gnl_strlen(char *s);
char	*get_next_line(int fd);
char	*ft_gnl_strjoin(char *cache, char *buf);
char	*ft_gnl_strchr(char *str, char c);
void	ft_gnl_strcpy(char *dest, char *src, int len);

#endif
