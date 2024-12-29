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
 * @file      driver_bmp388_interrupt.c
 * @brief     driver bmp388 interrupt source file
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

#include "driver_bmp388_interrupt.h"

static bmp388_handle_t gs_handle;        /**< bmp388 handle */

/**
 * @brief  interrupt example irq handler
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t bmp388_interrupt_irq_handler(void)
{
    /* run irq handler */
    if (bmp388_irq_handler(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     interrupt example init
 * @param[in] interface chip interface
 * @param[in] addr_pin iic device address
 * @param[in] *interrupt_receive_callback pointer to a interrupt receive callback
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t bmp388_interrupt_init(bmp388_interface_t interface, bmp388_address_t addr_pin, 
                              void (*interrupt_receive_callback)(uint8_t type))
{
    uint8_t res;
    
    /* link functions */
    DRIVER_BMP388_LINK_INIT(&gs_handle, bmp388_handle_t);
    DRIVER_BMP388_LINK_IIC_INIT(&gs_handle, bmp388_interface_iic_init);
    DRIVER_BMP388_LINK_IIC_DEINIT(&gs_handle, bmp388_interface_iic_deinit);
    DRIVER_BMP388_LINK_IIC_READ(&gs_handle, bmp388_interface_iic_read);
    DRIVER_BMP388_LINK_IIC_WRITE(&gs_handle, bmp388_interface_iic_write);
    DRIVER_BMP388_LINK_SPI_INIT(&gs_handle, bmp388_interface_spi_init);
    DRIVER_BMP388_LINK_SPI_DEINIT(&gs_handle, bmp388_interface_spi_deinit);
    DRIVER_BMP388_LINK_SPI_READ(&gs_handle, bmp388_interface_spi_read);
    DRIVER_BMP388_LINK_SPI_WRITE(&gs_handle, bmp388_interface_spi_write);
    DRIVER_BMP388_LINK_DELAY_MS(&gs_handle, bmp388_interface_delay_ms);
    DRIVER_BMP388_LINK_DEBUG_PRINT(&gs_handle, bmp388_interface_debug_print);
    DRIVER_BMP388_LINK_RECEIVE_CALLBACK(&gs_handle, interrupt_receive_callback);
    
    /* set interface */
    res = bmp388_set_interface(&gs_handle, interface);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bmp388_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set addr pin failed.\n");
       
        return 1;
    }
    
    /* bmp388 init */
    res = bmp388_init(&gs_handle);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: init failed.\n");
       
        return 1;
    }
    
    /* set default spi wire */
    res = bmp388_set_spi_wire(&gs_handle, BMP388_INTERRUPT_DEFAULT_SPI_WIRE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set spi wire failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default iic watchdog timer */
    res = bmp388_set_iic_watchdog_timer(&gs_handle, BMP388_INTERRUPT_DEFAULT_IIC_WATCHDOG_TIMER);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog timer failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default iic watchdog period */
    res = bmp388_set_iic_watchdog_period(&gs_handle, BMP388_INTERRUPT_DEFAULT_IIC_WATCHDOG_PERIOD);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog period failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable fifo */
    res = bmp388_set_fifo(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default interrupt pin type */
    res = bmp388_set_interrupt_pin_type(&gs_handle, BMP388_INTERRUPT_DEFAULT_INTERRUPT_PIN_TYPE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt pin type failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default interrupt active level */
    res = bmp388_set_interrupt_active_level(&gs_handle, BMP388_INTERRUPT_DEFAULT_INTERRUPT_ACTIVE_LEVEL);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt active level failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable latch interrupt pin and interrupt status */
    res = bmp388_set_latch_interrupt_pin_and_interrupt_status(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set latch interrupt pin and interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable interrupt fifo watermark */
    res = bmp388_set_interrupt_fifo_watermark(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable interrupt fifo full */
    res = bmp388_set_interrupt_fifo_full(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable interrupt data ready */
    res = bmp388_set_interrupt_data_ready(&gs_handle,BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt data ready failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pressure */
    res = bmp388_set_pressure(&gs_handle, BMP388_INTERRUPT_DEFAULT_PRESSURE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default temperature */
    res = bmp388_set_temperature(&gs_handle, BMP388_INTERRUPT_DEFAULT_TEMPERATURE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default pressure oversampling */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_INTERRUPT_DEFAULT_PRESSURE_OVERSAMPLING);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default temperature oversampling */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_INTERRUPT_DEFAULT_TEMPERATURE_OVERSAMPLING);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default odr */
    res = bmp388_set_odr(&gs_handle, BMP388_INTERRUPT_DEFAULT_ODR);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default filter coefficient */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_INTERRUPT_DEFAULT_FILTER_COEFFICIENT);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set normal mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_NORMAL_MODE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      interrupt example read
 * @param[out] *temperature_c pointer a converted temperature data buffer
 * @param[out] *pressure_pa pointer a converted pressure data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t bmp388_interrupt_read(float *temperature_c, float *pressure_pa)
{
    uint32_t temperature_raw;
    uint32_t pressure_raw;
    
    /* read temperature and pressure */
    if (bmp388_read_temperature_pressure(&gs_handle, (uint32_t *)&temperature_raw, temperature_c,
                                        (uint32_t *)&pressure_raw, pressure_pa) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t bmp388_interrupt_deinit(void)
{
    uint8_t res;
    
    /* set sleep mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_SLEEP_MODE);
    if (res != 0)
    {
        return 1;
    }
    
    if (bmp388_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
