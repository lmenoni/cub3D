/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:04:19 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 14:12:59 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int convert_purple_to_green(int color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    
    // Controlla se è una sfumatura di viola
    // Viola = rosso e blu dominanti, verde basso
    if (r > g && b > g && (r + b) > (g * 2))
    {
        // Converte mantenendo la luminosità
        int new_g = (r + b) / 2;  // Usa la media di rosso e blu per il verde
        int new_r = g;            // Il rosso diventa il vecchio verde (basso)
        int new_b = g;            // Il blu diventa il vecchio verde (basso)
        
        return (new_r << 16) | (new_g << 8) | new_b;
    }
    
    return color; // Se non è viola, restituisce il colore originale
}