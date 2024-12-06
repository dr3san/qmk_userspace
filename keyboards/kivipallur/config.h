// Copyright 2024 Andres Sakk (@dr3san)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// #define SERIAL_USART_TX_PIN GP0

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23

#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_INVERT_X
#define PMW33XX_CS_PIN GP21
#define PMW33XX_CPI 800
#define SPLIT_POINTING_ENABLE

#define MOUSE_EXTENDED_REPORT
#define MACCEL_TAKEOFF 2.0      // lower/higher value = curve takes off more smoothly/abruptly
#define MACCEL_GROWTH_RATE 0.25 // lower/higher value = curve reaches its upper limit slower/faster
#define MACCEL_OFFSET 3.5       // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 0.1        // lower limit of accel curve (minimum acceleration factor)

#define SPLIT_USB_DETECT

#define CAPS_WORD_IDLE_TIMEOUT 0
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define TAPPING_TERM 200

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
