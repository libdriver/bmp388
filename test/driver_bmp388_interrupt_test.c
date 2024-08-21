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
 * @file      driver_bmp388_interrupt_test.h
 * @brief     driver bmp388 interrupt test header file
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

#include "driver_bmp388_interrupt_test.h"

static bmp388_handle_t gs_handle;                 /**< bmp388 handle */
static volatile uint8_t gs_data_ready_flag;       /**< data ready flag */
static float gs_temperature_c;                    /**< temperature */
static float gs_pressure_pa;                      /**< pressure */

/**
 * @brief  interrupt test irq handler
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t bmp388_interrupt_test_irq_handler(void)
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
 * @brief     interface test receive callback
 * @param[in] type is the interrupt type
 * @note      none
 */
static void a_bmp388_interface_test_receive_callback(uint8_t type)
{
    switch (type)
    {
        case BMP388_INTERRUPT_STATUS_FIFO_WATERMARK :
        {
            break;
        }
        case BMP388_INTERRUPT_STATUS_FIFO_FULL :
        {
            break;
        }
        case BMP388_INTERRUPT_STATUS_DATA_READY :
        {
            uint32_t temperature_raw;
            uint32_t pressure_raw;
            
            /* read temperature pressure */
            if (bmp388_read_temperature_pressure(&gs_handle, (uint32_t *)&temperature_raw, (float *)&gs_temperature_c,
                                                (uint32_t *)&pressure_raw, (float *)&gs_pressure_pa) != 0)
            {
                bmp388_interface_debug_print("bmp388: read temperature and pressure failed.\n");
           
                return;
            }
            gs_data_ready_flag  = 1;
            
            break;
        }
        default :
        {
            break;
        }
    }
}

/**
 * @brief     interrupt test
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bmp388_interrupt_test(bmp388_interface_t interface, bmp388_address_t addr_pin, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    bmp388_info_t info;
    
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
    DRIVER_BMP388_LINK_RECEIVE_CALLBACK(&gs_handle, a_bmp388_interface_test_receive_callback);
    
    /* bmp388 info */
    res = bmp388_info(&info);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        bmp388_interface_debug_print("bmp388: chip is %s.\n", info.chip_name);
        bmp388_interface_debug_print("bmp388: manufacturer is %s.\n", info.manufacturer_name);
        bmp388_interface_debug_print("bmp388: interface is %s.\n", info.interface);
        bmp388_interface_debug_print("bmp388: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        bmp388_interface_debug_print("bmp388: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bmp388_interface_debug_print("bmp388: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bmp388_interface_debug_print("bmp388: max current is %0.2fmA.\n", info.max_current_ma);
        bmp388_interface_debug_print("bmp388: max temperature is %0.1fC.\n", info.temperature_max);
        bmp388_interface_debug_print("bmp388: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start interrupt test */
    bmp388_interface_debug_print("bmp388: start interrupt test.\n");
    
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
    
    /* set spi wire 4 */
    res = bmp388_set_spi_wire(&gs_handle, BMP388_SPI_WIRE_4);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set spi wire failed.\n");
        (void)bmp388_deinit(&gs_handle);   
        
        return 1;
    }
    
    /* enable iic watchdog timer */
    res = bmp388_set_iic_watchdog_timer(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog timer failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set iic watchdog period */
    res = bmp388_set_iic_watchdog_period(&gs_handle, BMP388_IIC_WATCHDOG_PERIOD_40_MS);
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
    
    /* disable fifo stop on full */
    res = bmp388_set_fifo_stop_on_full(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo stop on full failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set fifo watermark 256 */
    res = bmp388_set_fifo_watermark(&gs_handle, 256);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable fifo sensor time on */
    res = bmp388_set_fifo_sensortime_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo sensor time on failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable fifo sensor time on */
    res = bmp388_set_fifo_pressure_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo sensor time on failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set fifo temperature on */
    res = bmp388_set_fifo_temperature_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo temperature on failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set fifo subsampling 0 */
    res = bmp388_set_fifo_subsampling(&gs_handle, 0);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo subsampling failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set fifo data source filtered */
    res = bmp388_set_fifo_data_source(&gs_handle, BMP388_FIFO_DATA_SOURCE_FILTERED);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo data source failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set interrupt pin type push pull */
    res = bmp388_set_interrupt_pin_type(&gs_handle, BMP388_INTERRUPT_PIN_TYPE_PUSH_PULL);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt pin type failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set interrupt active level higher */
    res = bmp388_set_interrupt_active_level(&gs_handle, BMP388_INTERRUPT_ACTIVE_LEVEL_HIGHER);
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
        bmp388_interface_debug_print("bmp388: set set latch interrupt pin and interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable interrupt fifo watermark */
    res = bmp388_set_interrupt_fifo_watermark(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable interrupt fifo full */
    res = bmp388_set_interrupt_fifo_full(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo full failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable interrupt data ready */
    res = bmp388_set_interrupt_data_ready(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt data ready failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable pressure */
    res = bmp388_set_pressure(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable temperature */
    res = bmp388_set_temperature(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set pressure oversampling x32 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x32);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set temperature oversampling x2 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x2);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set odr 12.5Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_12P5_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set filter coefficient 15 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_15);
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
    for (i = 0; i < times; i++)
    {
        gs_data_ready_flag = 0;
        bmp388_interface_delay_ms(500);  
        bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", gs_temperature_c);
        bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", gs_pressure_pa);
    
        /* check data ready flag */
        if (gs_data_ready_flag == 0)
        {
            bmp388_interface_debug_print("bmp388: interrupt failed.\n");
            (void)bmp388_deinit(&gs_handle); 
            
            return 1;
        }
        bmp388_interface_delay_ms(1000);
    }

    /* finish interrupt test */
    bmp388_interface_debug_print("bmp388: finish interrupt test.\n");
    (void)bmp388_deinit(&gs_handle); 
    
    return 0;
}
