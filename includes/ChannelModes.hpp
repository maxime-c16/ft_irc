/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelModes.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcauchy <mcauchy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:42:07 by mcauchy           #+#    #+#             */
/*   Updated: 2024/07/10 15:25:04 by mcauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMODES_HPP

# define CHANNELMODES_HPP

// Channel Modes
# define CM_INVITE_ONLY    0x01  // Invite-only channel
# define CM_MODERATED      0x02  // Moderated channel
# define CM_NO_EXTERNAL    0x04  // No external messages
# define CM_PRIVATE        0x08  // Private channel
# define CM_SECRET         0x10  // Secret channel
# define CM_TOPIC_LOCK     0x20  // Topic set by channel operators only
# define CM_NO_ANONYMOUS   0x40  // No anonymous users
# define CM_USER_LIMIT     0x80  // User limit for the channel
# define CM_KEY_PROTECTED  0x100 // Channel protected by a key (password)
# define CM_NO_COLOR       0x200 // No colored text allowed
# define CM_NO_SPAM        0x400 // Anti-spam mode
# define CM_LOGGING        0x800 // Channel logging
# define CM_LANGUAGE_FILTER 0x1000 // Filter offensive language
# define CM_SLOW_MODE      0x2000 // Slow mode (limit message frequency)
# define CM_READ_ONLY      0x4000 // Read-only channel for non-moderators
# define CM_GUESTS_ALLOWED 0x8000 // Guests allowed without registration
# define CM_NO_MEDIA       0x10000 // No media (images, videos) allowed
# define CM_NO_LINKS       0x20000 // No external links allowed
# define CM_NO_BOTS        0x40000 // No bots allowed

// Error Messages related to Channel Modes
# define ERR_INVITE_ONLY      "Error: Channel is invite-only.\r\n"
# define ERR_MODERATED        "Error: Only moderators can speak in this channel.\r\n"
# define ERR_NO_EXTERNAL      "Error: No external messages are allowed in this channel.\r\n"
# define ERR_PRIVATE          "Error: This is a private channel.\r\n"
# define ERR_SECRET           "Error: This is a secret channel.\r\n"
# define ERR_TOPIC_LOCK       "Error: Only channel operators can set the topic.\r\n"
# define ERR_NO_ANONYMOUS     "Error: No anonymous users allowed in this channel.\r\n"
# define ERR_USER_LIMIT       "Error: User limit reached for this channel.\r\n"
# define ERR_KEY_PROTECTED    "Error: Invalid channel key.\r\n"
# define ERR_NO_COLOR         "Error: No colored text allowed in this channel.\r\n"
# define ERR_NO_SPAM          "Error: Anti-spam mode is enabled in this channel.\r\n"
# define ERR_LOGGING          "Error: Channel logging is enabled.\r\n"
# define ERR_LANGUAGE_FILTER  "Error: Offensive language is not allowed in this channel.\r\n"
# define ERR_SLOW_MODE        "Error: Slow mode is enabled. Please wait before sending another message.\r\n"
# define ERR_READ_ONLY        "Error: This is a read-only channel for non-moderators.\r\n"
# define ERR_NO_MEDIA         "Error: No media (images, videos) allowed in this channel.\r\n"
# define ERR_NO_LINKS         "Error: No external links allowed in this channel.\r\n"
# define ERR_NO_BOTS          "Error: No bots allowed in this channel.\r\n"

# define PRV_ADM1 1
# define PRV_ADM2 2
# define PRV_ADM3 3
# define PRV_ADM4 4
# define PRV_ADM5 5
# define PRV_ADM6 6

#endif // CHANNELMODES_HPP
