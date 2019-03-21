/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 18:28:41 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/20 19:41:07 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdlib.h>

# define MD5_TEMPLATE	"MD5 (%s) = %s\n"
# define MD5_TEMPLATE_R	"%s %s\n"

void	process_md5(size_t f, int cnt, char **av);

#endif
