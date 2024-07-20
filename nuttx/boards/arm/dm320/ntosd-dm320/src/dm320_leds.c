/****************************************************************************
 * boards/arm/dm320/ntosd-dm320/src/dm320_leds.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/board.h>

#include "arm_internal.h"
#include "chip.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: board_autoled_initialize
 ****************************************************************************/

#ifdef CONFIG_ARCH_LEDS
void board_autoled_initialize(void)
{
  GIO_OUTPUT(GIO_LED_GREEN);
  GIO_OUTPUT(GIO_LED_RED);
  GIO_SET_OUTPUT(GIO_LED_GREEN);
  GIO_CLEAR_OUTPUT(GIO_LED_RED);
}

/****************************************************************************
 * Name: board_autoled_on
 ****************************************************************************/

void board_autoled_on(int led)
{
  if (led == GIO_LED_GREEN)
    {
      GIO_SET_OUTPUT(GIO_LED_GREEN);
    }
  else if (led == GIO_LED_RED)
    {
      GIO_SET_OUTPUT(GIO_LED_RED);
    }
}

/****************************************************************************
 * Name: board_autoled_off
 ****************************************************************************/

void board_autoled_off(int led)
{
  if (led == GIO_LED_GREEN)
    {
      GIO_CLEAR_OUTPUT(GIO_LED_GREEN);
    }
  else if (led == GIO_LED_RED)
    {
      GIO_CLEAR_OUTPUT(GIO_LED_RED);
    }
}
#endif /* CONFIG_ARCH_LEDS */
