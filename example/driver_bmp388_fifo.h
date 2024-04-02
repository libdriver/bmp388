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
 * @file      driver_bmp388_fifo.h
 * @brief     driver bmp388 fifo header file
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

#ifndef DRIVER_BMP388_FIFO_H
#define DRIVER_BMP388_FIFO_H

#include "driver_bmp388_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup bmp388_example_driver
 * @{
 */

/**
 * @brief bmp388 fifo example default definition
 */
#define BMP388_FIFO_DEFAULT_SPI_WIRE                 BMP388_SPI_WIRE_4                        /**< 4 wire spi */
#define BMP388_FIFO_DEFAULT_IIC_WATCHDOG_TIMER       BMP388_BOOL_TRUE                         /**< enable iic watchdog timer */
#define BMP388_FIFO_DEFAULT_IIC_WATCHDOG_PERIOD      BMP388_IIC_WATCHDOG_PERIOD_40_MS         /**< set watchdog timer period 40ms */
#define BMP388_FIFO_DEFAULT_FIFO_STOP_ON_FULL        BMP388_BOOL_FALSE                        /**< disable fifo stop on full */
#define BMP388_FIFO_DEFAULT_FIFO_WATERMARK           256                                      /**< 256 fifo watermark */
#define BMP388_FIFO_DEFAULT_FIFO_SENSORTIME_ON       BMP388_BOOL_TRUE                         /**< enable fifo sensor time on */
#define BMP388_FIFO_DEFAULT_FIFO_PRESSURE_ON         BMP388_BOOL_TRUE                         /**< enable fifo pressure on */
#define BMP388_FIFO_DEFAULT_FIFO_TEMPERATURE_ON      BMP388_BOOL_TRUE                         /**< enable fifo temperature on */
#define BMP388_FIFO_DEFAULT_FIFO_SUBSAMPLING         0                                        /**< fifo subsampling */
#define BMP388_FIFO_DEFAULT_FIFO_DATA_SOURCE         BMP388_FIFO_DATA_SOURCE_FILTERED         /**< fifo data source filtered */
#define BMP388_FIFO_DEFAULT_INTERRUPT_PIN_TYPE       BMP388_INTERRUPT_PIN_TYPE_PUSH_PULL      /**< interrupt pin type push pull */
#define BMP388_FIFO_DEFAULT_INTERRUPT_ACTIVE_LEVEL   BMP388_INTERRUPT_ACTIVE_LEVEL_HIGHER     /**< interrupt pin active level higher */
#define BMP388_FIFO_DEFAULT_INTERRUPT_WATERMARK      BMP388_BOOL_TRUE                         /**< enable interrupt watermark */
#define BMP388_FIFO_DEFAULT_INTERRUPT_FIFO_FULL      BMP388_BOOL_FALSE                        /**< disable interrupt fifo full */
#define BMP388_FIFO_DEFAULT_INTERRUPT_DATA_READY     BMP388_BOOL_FALSE                        /**< disable interrupt data ready */
#define BMP388_FIFO_DEFAULT_LATCH_INTERRUPT          BMP388_BOOL_FALSE                        /**< latch interrupt pin and interrupt status */
#define BMP388_FIFO_DEFAULT_PRESSURE                 BMP388_BOOL_TRUE                         /**< enable pressure */
#define BMP388_FIFO_DEFAULT_TEMPERATURE              BMP388_BOOL_TRUE                         /**< enable temperature */
#define BMP388_FIFO_DEFAULT_PRESSURE_OVERSAMPLING    BMP388_OVERSAMPLING_x32                  /**< pressure oversampling x32 */
#define BMP388_FIFO_DEFAULT_TEMPERATURE_OVERSAMPLING BMP388_OVERSAMPLING_x2                   /**< temperature oversampling x2 */
#define BMP388_FIFO_DEFAULT_ODR                      BMP388_ODR_12P5_HZ                       /**< output data rate 12.5Hz */
#define BMP388_FIFO_DEFAULT_FILTER_COEFFICIENT       BMP388_FILTER_COEFFICIENT_15             /**< set filter coefficient 15 */

/**
 * @brief  fifo example irq handler
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t bmp388_fifo_irq_handler(void);

/**
 * @brief     fifo example init
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @param[in] *fifo_receive_callback points to a fifo receive callback
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bmp388_fifo_init(bmp388_interface_t interface, bmp388_address_t addr_pin,
                         void (*fifo_receive_callback)(uint8_t type));

/**
 * @brief  fifo example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bmp388_fifo_deinit(void);

/**
 * @brief         fifo example read
 * @param[in]     *buf points a data buffer
 * @param[in]     buf_len is the data buffer
 * @param[out]    *frame points a frame structure
 * @param[in,out] *frame_len points a frame data buffer
 * @return        status code
 *                - 0 success
 *                - 1 read failed
 * @note          none
 */
uint8_t bmp388_fifo_read(uint8_t *buf, uint16_t buf_len, bmp388_frame_t *frame, uint16_t *frame_len);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
