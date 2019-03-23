/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 14:04:06 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 15:50:40 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include <stdlib.h>

void	process_md5(size_t f, int cnt, char **av);
void	process_sha256(size_t f, int cnt, char **av);
void	process_sha384(size_t f, int cnt, char **av);
void	process_sha512(size_t f, int cnt, char **av);

#endif
