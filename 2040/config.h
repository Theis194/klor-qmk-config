// Copyright 2022 @geigeigeist
// SPDX-License-Identifier: GPL-2.0+
// here you find only RP2040 specific configurations

#pragma once

// ┌─────────────────────────────────────────────────┐
// │ a u d i o                                       │
// └─────────────────────────────────────────────────┘

#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4

/* #define USE_SERIAL
#define SOFT_SERIAL_PIN D4
#define SERIAL_USE_MULTI_TRANSACTION
//#define SPLIT_LAYER_STATE_ENABLE
#define MASTER_LEFT */
