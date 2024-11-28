// Copyright 2024 Andres Sakk (@dr3san)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

#define SERIAL_USART_TX_PIN GP0
#define PMW33XX_CS_PIN GP21
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT

#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP23
#define POINTING_DEVICE_ROTATION_90
#define PMW33XX_CPI 400
#define POINTING_DEVICE_INVERT_X

#define SPLIT_USB_DETECT

#define CAPS_WORD_IDLE_TIMEOUT 0

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
