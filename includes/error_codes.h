/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartin- <mmartin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:57:28 by mmartin-          #+#    #+#             */
/*   Updated: 2020/09/01 20:18:32 by mmartin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODES_H
# define ERROR_CODES_H

typedef enum	e_errcod
{
	CONF_MISSING	= 1,
	CONF_INV_AMB,
	CONF_INV_CAMERA,
	CONF_INV_LIGHT,
	CONF_INV_SPHERE,
	CONF_INV_PLANE,
	CONF_INV_SQUARE,
	CONF_INV_
}				t_errcod;

#endif
