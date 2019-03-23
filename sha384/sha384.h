/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emamenko <emamenko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 17:57:32 by emamenko          #+#    #+#             */
/*   Updated: 2019/03/23 15:45:33 by emamenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA384_H
# define SHA384_H

# include "../sha512/sha512.h"

# define SHA384_TPL		"SHA384 (%s) = %s\n"
# define SHA384_TPL_R	"%s %s\n"

void	sha384_init(t_ctx *ctx);

#endif
