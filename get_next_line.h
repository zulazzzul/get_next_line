/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-abreu <nd-abreu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:17:01 by nd-abreu          #+#    #+#             */
/*   Updated: 2026/06/28 23:26:22 by nd-abreu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* buffer e um espaco da memoria usada temporariamente para armazenar dados
enquanto eles sao transferidos de um lugar para o outro.
a file descriptor is a series of numbers linked to
a specific file that my operator system is handling
no buffer_size = ? vamos defnir o numero de bytes que vamos ler de cada vez.
pode ser qualquer valor, no caso deste projeto sera 42.
fd e onde esta a informacao p gnl ir buscar a next line
open, o int e o close. int fd tens de
abrir com o open e o fd e onde esta a informacao
o fabio pos 10 mas nao tem de ser 42 ???? */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(char *s);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif