/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_bmp388_shot.h
 * @brief     driver bmp388 shot header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-04-12
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/04/12  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/20  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_BMP388_SHOT_H
#define DRIVER_BMP388_SHOT_H

#include "driver_bmp388_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup bmp388_example_driver
 * @{
 */

/**
 * @brief bmp388 shot example default definition
 */
#define BMP388_SHOT_DEFAULT_SPI_WIRE                 BMP388_SPI_WIRE_4                        /**< 4 wire spi */
#define BMP388_SHOT_DEFAULT_IIC_WATCHDOG_TIMER       BMP388_BOOL_TRUE                         /**< enable iic watchdog timer */
#define BMP388_SHOT_DEFAULT_IIC_WATCHDOG_PERIOD      BMP388_IIC_WATCHDOG_PERIOD_40_MS         /**< set watchdog timer period 40ms */
#define BMP388_SHOT_DEFAULT_PRESSURE                 BMP388_BOOL_TRUE                         /**< enable pressure */
#define BMP388_SHOT_DEFAULT_TEMPERATURE              BMP388_BOOL_TRUE                         /**< enable temperature */
#define BMP388_SHOT_DEFAULT_PRESSURE_OVERSAMPLING    BMP388_OVERSAMPLING_x32                  /**< pressure oversampling x32 */
#define BMP388_SHOT_DEFAULT_TEMPERATURE_OVERSAMPLING BMP388_OVERSAMPLING_x2                   /**< temperature oversampling x2 */
#define BMP388_SHOT_DEFAULT_ODR                      BMP388_ODR_12P5_HZ                       /**< output data rate 12.5Hz */
#define BMP388_SHOT_DEFAULT_FILTER_COEFFICIENT       BMP388_FILTER_COEFFICIENT_15             /**< set filter coefficient 15 */

/**
 * @brief     shot example init
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bmp388_shot_init(bmp388_interface_t interface, bmp388_address_t addr_pin);

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bmp388_shot_deinit(void);

/**
 * @brief      shot example read
 * @param[out] *temperature_c points a converted temperature data buffer
 * @param[out] *pressure_pa points a converted pressure data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bmp388_shot_read(float *temperature_c, float *pressure_pa);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
