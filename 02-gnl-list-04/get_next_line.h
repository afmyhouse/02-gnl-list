/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:59:20 by slynn-ev          #+#    #+#             */
/*   Updated: 2023/03/01 23:58:28 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10
# define OPEN_MAX 1000

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
//# include "libft/libft.h"

/*typedef struct		s_gnl
{
	char		*str;
	int			fd;
}					t_gnl;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;*/

typedef struct	s_fd_lst
{
	int		fd;
	char	*str;
	int		ret;
	struct s_fd_lst	*next;
}				t_fd_lst;

char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strjoin_free(char const *s1, char const *s2);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
t_fd_lst	*check_fd(int fd, t_fd_lst **list);
//t_fd_lst	*check_fd(int fd, t_fd_lst **list);
char		*split_read(t_fd_lst *fd_node, char *line);
//int			split_read(char **line, t_fd_lst *gnl_buf);
char	*new_line(int fd, char *line);
//int			new_line(int fd, char *line);
//int			new_line(int fd, char **line);
char	*pending_line(t_fd_lst *fd_node, char *line);
//char		*pending_line(char *str, char *line);
//int			pending_line(char **str, char **line);
char			*get_next_line(int fd);

#endif