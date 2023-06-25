/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

const uint GREEN_CAR = 13;
const uint RED_CAR = 1;
const uint RED_PEDESTRIAN = 0;
const uint GREEN_PEDESTRIAN = 12;
const uint SOUND_PEDESTRIAN = 11;
const uint BUTTON_PEDESTRIAN = 16;

int pedestrian_phase()
{
    gpio_put(GREEN_PEDESTRIAN, 0);
    gpio_put(RED_PEDESTRIAN, 1);
    for (int i = 0; i < 5; i++)
    {
        gpio_put(GREEN_CAR, 0);
        sleep_ms(500);
        gpio_put(GREEN_CAR, 1);
        sleep_ms(500);
    }
    gpio_put(GREEN_CAR, 0);
    gpio_put(RED_CAR, 1);
    sleep_ms(1000);
    gpio_put(RED_PEDESTRIAN, 0);
    gpio_put(GREEN_PEDESTRIAN, 1);
    for (int i = 0; i < 25; i++)
    {
        gpio_put(SOUND_PEDESTRIAN, 1);
        sleep_ms(100);
        gpio_put(SOUND_PEDESTRIAN, 0);
        sleep_ms(100);
    }
    for (int i = 0; i < 5; i++)
    {
        gpio_put(GREEN_PEDESTRIAN, 0);
        sleep_ms(500);
        gpio_put(GREEN_PEDESTRIAN, 1);
        sleep_ms(500);
    }
    gpio_put(GREEN_PEDESTRIAN, 0);
    gpio_put(RED_PEDESTRIAN, 1);
    sleep_ms(1000);
    gpio_put(GREEN_CAR, 1);
    gpio_put(RED_CAR, 0);
}

int main()
{
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else

    gpio_init(GREEN_CAR);
    gpio_init(RED_CAR);
    gpio_init(RED_PEDESTRIAN);
    gpio_init(GREEN_PEDESTRIAN);
    gpio_init(SOUND_PEDESTRIAN);
    gpio_init(BUTTON_PEDESTRIAN);

    gpio_set_dir(GREEN_CAR, GPIO_OUT);
    gpio_set_dir(RED_CAR, GPIO_OUT);
    gpio_set_dir(RED_PEDESTRIAN, GPIO_OUT);
    gpio_set_dir(GREEN_PEDESTRIAN, GPIO_OUT);
    gpio_set_dir(SOUND_PEDESTRIAN, GPIO_OUT);
    gpio_set_dir(BUTTON_PEDESTRIAN, GPIO_IN);

    gpio_pull_up(BUTTON_PEDESTRIAN);

    gpio_put(GREEN_PEDESTRIAN, 0);
    gpio_put(RED_PEDESTRIAN, 1);
    gpio_put(GREEN_CAR, 1);
    gpio_put(RED_CAR, 0);

    while (true)
    {
        if (!gpio_get(BUTTON_PEDESTRIAN))
        {
            pedestrian_phase();
        }
    }

#endif
}