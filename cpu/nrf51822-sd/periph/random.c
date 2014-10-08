/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     cpu_nrf51822
 * @{
 *
 * @file
 * @brief       Driver for the NRF51822 random number generator
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "cpu.h"
#include "periph_conf.h"
#include "periph/random.h"

/* guard file in case no random device was specified */
#if RANDOM_NUMOF

void random_init(void)
{
}

int random_read(char *buf, unsigned int num)
{
    unsigned int count = 0;

    while (count < num) {
        uint8_t available = 0;
        sd_rand_application_bytes_available(&available);
        if (available == 0)
            continue;
        if (available > num - count)
            available = num - count;
        if (sd_rand_application_vector_get(&buf[count], available) != NRF_SUCCESS)
            continue;
        count += available;
    }

    return count;
}

void random_poweron(void)
{
}

void random_poweroff(void)
{
}

#endif /* RANDOM_NUMOF */
