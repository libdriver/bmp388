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
 * @file      driver_bmp388_register_test.c
 * @brief     driver bmp388 register test source file
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

#include "driver_bmp388_register_test.h"
#include <stdlib.h>

static bmp388_handle_t gs_handle;        /**< bmp388 handle */

/**
 * @brief     register test
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bmp388_register_test(bmp388_interface_t interface, bmp388_address_t addr_pin)
{
    uint8_t res;
    uint16_t fifo_watermark_in;
    uint16_t fifo_watermark_out;
    uint8_t subsampling_in;
    uint8_t subsampling_out;
    uint8_t err;
    uint8_t status;
    uint8_t data;
    uint16_t length;
    uint32_t sensortime;
    bmp388_event_t event;
    bmp388_info_t info;
    bmp388_interface_t interface_test;
    bmp388_address_t addr_pin_test;
    bmp388_bool_t enable;
    bmp388_fifo_data_source_t source;
    bmp388_interrupt_pin_type_t pin_type;
    bmp388_interrupt_active_level_t level;
    bmp388_spi_wire_t wire;
    bmp388_iic_watchdog_period_t period;
    bmp388_mode_t mode;
    bmp388_oversampling_t oversampling;
    bmp388_odr_t odr;
    bmp388_filter_coefficient_t coef;
    
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
    DRIVER_BMP388_LINK_RECEIVE_CALLBACK(&gs_handle, bmp388_interface_receive_callback);
    
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
    
    /* start register test */
    bmp388_interface_debug_print("bmp388: start register test.\n");
    
    /* bmp388_set_interface/bmp388_get_interface test */
    bmp388_interface_debug_print("bmp388: bmp388_set_interface/bmp388_get_interface test.\n");
    
    /* set iic */
    res = bmp388_set_interface(&gs_handle, BMP388_INTERFACE_IIC);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interface failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interface iic.\n");
    res = bmp388_get_interface(&gs_handle, &interface_test);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interface failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interface %s.\n", interface_test==BMP388_INTERFACE_IIC?"ok":"error");
    
    /* set spi */
    res = bmp388_set_interface(&gs_handle, BMP388_INTERFACE_SPI);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interface failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interface spi.\n");
    res = bmp388_get_interface(&gs_handle, &interface_test);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interface failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interface %s.\n", interface_test==BMP388_INTERFACE_SPI?"ok":"error");
    
    /* bmp388_set_addr_pin/bmp388_get_addr_pin test */
    bmp388_interface_debug_print("bmp388: bmp388_set_addr_pin/bmp388_get_addr_pin test.\n");
    
    /* set low */
    res = bmp388_set_addr_pin(&gs_handle, BMP388_ADDRESS_ADO_LOW);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set addr pin failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set addr pin low.\n");
    res = bmp388_get_addr_pin(&gs_handle, &addr_pin_test);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get addr pin failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check addr pin %s.\n", addr_pin_test==BMP388_ADDRESS_ADO_LOW?"ok":"error");
    
    /* set high */
    res = bmp388_set_addr_pin(&gs_handle, BMP388_ADDRESS_ADO_HIGH);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set addr pin failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set addr pin high.\n");
    res = bmp388_get_addr_pin(&gs_handle, &addr_pin_test);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get addr pin failed.\n");
       
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check addr pin %s.\n", addr_pin_test==BMP388_ADDRESS_ADO_HIGH?"ok":"error");
    
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
    
    /* bmp388_set_fifo_watermark/bmp388_get_fifo_watermark test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_watermark/bmp388_get_fifo_watermark test.\n");
    fifo_watermark_in = rand()%256 + 256;
    res = bmp388_set_fifo_watermark(&gs_handle, fifo_watermark_in);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo watermark %d.\n", fifo_watermark_in);
    res = bmp388_get_fifo_watermark(&gs_handle, (uint16_t *)&fifo_watermark_out);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo watermark %s.\n", fifo_watermark_out==fifo_watermark_in?"ok":"error");
    
    /* bmp388_set_fifo/bmp388_get_fifo test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo/bmp388_get_fifo test.\n");
    
    /* enable */
    res = bmp388_set_fifo(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo enable.\n");
    res = bmp388_get_fifo(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_fifo(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo disable.\n");
    res = bmp388_get_fifo(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_fifo_stop_on_full/bmp388_get_fifo_stop_on_full test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_stop_on_full/bmp388_get_fifo_stop_on_full test.\n");
    
    /* enable */
    res = bmp388_set_fifo_stop_on_full(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo stop on full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo stop on full enable.\n");
    res = bmp388_get_fifo_stop_on_full(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo stop on full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo stop on full %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_fifo_stop_on_full(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo stop on full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo stop on full disable.\n");
    res = bmp388_get_fifo_stop_on_full(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo stop on full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo stop on full %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_fifo_sensortime_on/bmp388_get_fifo_sensortime_on test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_sensortime_on/bmp388_get_fifo_sensortime_on test.\n");
    
    /* enable */
    res = bmp388_set_fifo_sensortime_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo sensor time on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo sensor time on enable.\n");
    res = bmp388_get_fifo_sensortime_on(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo sensor time on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo sensor time on %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_fifo_sensortime_on(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo sensor time on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo sensor time on disable.\n");
    res = bmp388_get_fifo_sensortime_on(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo sensor time on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo sensor time on %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_fifo_pressure_on/bmp388_get_fifo_pressure_on test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_pressure_on/bmp388_get_fifo_pressure_on test.\n");
    
    /* enable */
    res = bmp388_set_fifo_pressure_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo pressure on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo pressure on enable.\n");
    res = bmp388_get_fifo_pressure_on(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo pressure on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo pressure on %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_fifo_pressure_on(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo pressure on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo pressure on disable.\n");
    res = bmp388_get_fifo_pressure_on(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo pressure on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo pressure on %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_fifo_temperature_on/bmp388_get_fifo_temperature_on test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_temperature_on/bmp388_get_fifo_temperature_on test.\n");
    
    /* enable */
    res = bmp388_set_fifo_temperature_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo temperature on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo temperature on enable.\n");
    res = bmp388_get_fifo_temperature_on(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo temperature on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo temperature on %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_fifo_temperature_on(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo temperature on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo temperature on disable.\n");
    res = bmp388_get_fifo_temperature_on(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo temperature on failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo temperature on %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_fifo_subsampling/bmp388_get_fifo_subsampling test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_subsampling/bmp388_get_fifo_subsampling test.\n");
    subsampling_in = rand()%7;
    res = bmp388_set_fifo_subsampling(&gs_handle, subsampling_in);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo subsampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo subsampling %d.\n", subsampling_in);
    res = bmp388_get_fifo_subsampling(&gs_handle, (uint8_t *)&subsampling_out);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo subsampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo subsampling on %s.\n", subsampling_in==subsampling_out?"ok":"error");
    
    /* bmp388_set_fifo_data_source/bmp388_get_fifo_data_source test */
    bmp388_interface_debug_print("bmp388: bmp388_set_fifo_data_source/bmp388_get_fifo_data_source test.\n");
    
    /* set unfiltered */
    res = bmp388_set_fifo_data_source(&gs_handle, BMP388_FIFO_DATA_SOURCE_UNFILTERED);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo data source failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo data source unfiltered.\n");
    res = bmp388_get_fifo_data_source(&gs_handle, (bmp388_fifo_data_source_t *)&source);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo data source failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo data source %s.\n", source==BMP388_FIFO_DATA_SOURCE_UNFILTERED?"ok":"error");
    
    /* set filtered */
    res = bmp388_set_fifo_data_source(&gs_handle, BMP388_FIFO_DATA_SOURCE_FILTERED);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set fifo data source failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set fifo data source filtered.\n");
    res = bmp388_get_fifo_data_source(&gs_handle, (bmp388_fifo_data_source_t *)&source);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo data source failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check fifo data source %s.\n", source==BMP388_FIFO_DATA_SOURCE_FILTERED?"ok":"error");
    
    /* bmp388_set_interrupt_pin_type/bmp388_get_interrupt_pin_type test */
    bmp388_interface_debug_print("bmp388: bmp388_set_interrupt_pin_type/bmp388_get_interrupt_pin_type test.\n");
    
    /* set push-pull */
    res = bmp388_set_interrupt_pin_type(&gs_handle, BMP388_INTERRUPT_PIN_TYPE_PUSH_PULL);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt pin type failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt pin type push pull.\n");
    res = bmp388_get_interrupt_pin_type(&gs_handle, (bmp388_interrupt_pin_type_t *)&pin_type);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt pin type failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt pin type %s.\n", pin_type==BMP388_INTERRUPT_PIN_TYPE_PUSH_PULL?"ok":"error");
    
    /* set open drain */
    res = bmp388_set_interrupt_pin_type(&gs_handle, BMP388_INTERRUPT_PIN_TYPE_OPEN_DRAIN);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt pin type failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt pin type open drain.\n");
    res = bmp388_get_interrupt_pin_type(&gs_handle, (bmp388_interrupt_pin_type_t *)&pin_type);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt pin type failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt pin type %s.\n", pin_type==BMP388_INTERRUPT_PIN_TYPE_OPEN_DRAIN?"ok":"error");
    
    /* bmp388_set_interrupt_active_level/bmp388_get_interrupt_active_level test */
    bmp388_interface_debug_print("bmp388: bmp388_set_interrupt_active_level/bmp388_get_interrupt_active_level test.\n");
    
    /* set lower */
    res = bmp388_set_interrupt_active_level(&gs_handle, BMP388_INTERRUPT_ACTIVE_LEVEL_LOWER);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt active level failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt active level lower.\n");
    res = bmp388_get_interrupt_active_level(&gs_handle, (bmp388_interrupt_active_level_t *)&level);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt active level failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt active level %s.\n", level==BMP388_INTERRUPT_ACTIVE_LEVEL_LOWER?"ok":"error");
    
    /* set higher */
    res = bmp388_set_interrupt_active_level(&gs_handle, BMP388_INTERRUPT_ACTIVE_LEVEL_HIGHER);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt active level failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt active level higher.\n");
    res = bmp388_get_interrupt_active_level(&gs_handle, (bmp388_interrupt_active_level_t *)&level);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt active level failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt active level %s.\n", level==BMP388_INTERRUPT_ACTIVE_LEVEL_HIGHER?"ok":"error");
    
    /* bmp388_set_latch_interrupt_pin_and_interrupt_status/bmp388_get_latch_interrupt_pin_and_interrupt_status test */
    bmp388_interface_debug_print("bmp388: bmp388_set_latch_interrupt_pin_and_interrupt_status/bmp388_get_latch_interrupt_pin_and_interrupt_status test.\n");
    
    /* enable */
    res = bmp388_set_latch_interrupt_pin_and_interrupt_status(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set latch interrupt pin and interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set latch interrupt pin and interrupt status enable.\n");
    res = bmp388_get_latch_interrupt_pin_and_interrupt_status(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get latch interrupt pin and interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check latch interrupt pin and interrupt status %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_latch_interrupt_pin_and_interrupt_status(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set latch interrupt pin and interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set latch interrupt pin and interrupt status disable.\n");
    res = bmp388_get_latch_interrupt_pin_and_interrupt_status(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get latch interrupt pin and interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check latch interrupt pin and interrupt status %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_interrupt_fifo_watermark/bmp388_get_interrupt_fifo_watermark test */
    bmp388_interface_debug_print("bmp388: bmp388_set_interrupt_fifo_watermark/bmp388_get_interrupt_fifo_watermark test.\n");
    
    /* enable */
    res = bmp388_set_interrupt_fifo_watermark(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt fifo watermark enable.\n");
    res = bmp388_get_interrupt_fifo_watermark(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt fifo watermark %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_interrupt_fifo_watermark(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt fifo watermark disable.\n");
    res = bmp388_get_interrupt_fifo_watermark(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt fifo watermark failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt fifo watermark %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_interrupt_fifo_full/bmp388_get_interrupt_fifo_full test */
    bmp388_interface_debug_print("bmp388: bmp388_set_interrupt_fifo_full/bmp388_get_interrupt_fifo_full test.\n");
    
    /* enable */
    res = bmp388_set_interrupt_fifo_full(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt fifo full enable.\n");
    res = bmp388_get_interrupt_fifo_full(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt fifo full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt fifo full %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_interrupt_fifo_full(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt fifo full disable.\n");
    res = bmp388_get_interrupt_fifo_full(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt fifo full failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt fifo full %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_interrupt_data_ready/bmp388_get_interrupt_fifo_data_ready test */
    bmp388_interface_debug_print("bmp388: bmp388_set_interrupt_data_ready/bmp388_get_interrupt_fifo_data_ready test.\n");
    
    /* enable */
    res = bmp388_set_interrupt_data_ready(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt data ready failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt data ready enable.\n");
    res = bmp388_get_interrupt_data_ready(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt data ready failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt data ready %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_interrupt_data_ready(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set interrupt data ready failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set interrupt data ready disable.\n");
    res = bmp388_get_interrupt_data_ready(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt data ready failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check interrupt data ready %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_spi_wire/bmp388_get_spi_wire test */
    bmp388_interface_debug_print("bmp388: bmp388_set_spi_wire/bmp388_get_spi_wire test.\n");
    
    /* set 4 wire */
    res = bmp388_set_spi_wire(&gs_handle, BMP388_SPI_WIRE_4);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set spi wire failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set spi 4 wire.\n");
    res = bmp388_get_spi_wire(&gs_handle, (bmp388_spi_wire_t *)&wire);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get spi wire failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check spi wire %s.\n", wire==BMP388_SPI_WIRE_4?"ok":"error");
    if (interface == BMP388_INTERFACE_IIC)
    {
        /* set 3 wire */
        res = bmp388_set_spi_wire(&gs_handle, BMP388_SPI_WIRE_3);
        if (res != 0)
        {
            bmp388_interface_debug_print("bmp388: set spi wire failed.\n");
            (void)bmp388_deinit(&gs_handle);
            
            return 1;
        }
        bmp388_interface_debug_print("bmp388: set spi 3 wire.\n");
        res = bmp388_get_spi_wire(&gs_handle, (bmp388_spi_wire_t *)&wire);
        if (res != 0)
        {
            bmp388_interface_debug_print("bmp388: get spi wire failed.\n");
            (void)bmp388_deinit(&gs_handle);
            
            return 1;
        }
        bmp388_interface_debug_print("bmp388: check spi wire %s.\n", wire==BMP388_SPI_WIRE_3?"ok":"error");
    }
    
    /* bmp388_set_iic_watchdog_timer/bmp388_get_iic_watchdog_timer test */
    bmp388_interface_debug_print("bmp388: bmp388_set_iic_watchdog_timer/bmp388_get_iic_watchdog_timer test.\n");
    
    /* enable */
    res = bmp388_set_iic_watchdog_timer(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog timer failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set iic watchdog timer enable.\n");
    res = bmp388_get_iic_watchdog_timer(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get iic watchdog timer failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check iic watchdog timer %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* disable */
    res = bmp388_set_iic_watchdog_timer(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog timer failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set iic watchdog timer disable.\n");
    res = bmp388_get_iic_watchdog_timer(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get iic watchdog timer failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check iic watchdog timer %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* bmp388_set_iic_watchdog_period/bmp388_get_iic_watchdog_period test */
    bmp388_interface_debug_print("bmp388: bmp388_set_iic_watchdog_period/bmp388_get_iic_watchdog_period test.\n");
    
    /* set 1.25ms period */
    res = bmp388_set_iic_watchdog_period(&gs_handle, BMP388_IIC_WATCHDOG_PERIOD_1P25_MS);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog period failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set iic watchdog period 1.25ms.\n");
    res = bmp388_get_iic_watchdog_period(&gs_handle, (bmp388_iic_watchdog_period_t *)&period);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get iic watchdog period failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check iic watchdog period %s.\n", period==BMP388_IIC_WATCHDOG_PERIOD_1P25_MS?"ok":"error");
    
    /* set 40ms period */
    res = bmp388_set_iic_watchdog_period(&gs_handle, BMP388_IIC_WATCHDOG_PERIOD_40_MS);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog period failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set iic watchdog period 40ms.\n");
    res = bmp388_get_iic_watchdog_period(&gs_handle, (bmp388_iic_watchdog_period_t *)&period);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get iic watchdog period failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check iic watchdog period %s.\n", period==BMP388_IIC_WATCHDOG_PERIOD_40_MS?"ok":"error");
    
    /* bmp388_set_pressure/bmp388_get_pressure test */
    bmp388_interface_debug_print("bmp388: bmp388_set_pressure/bmp388_get_pressure test.\n");
    
    /* disable */
    res = bmp388_set_pressure(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure disable.\n");
    res = bmp388_get_pressure(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* enable */
    res = bmp388_set_pressure(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure enable.\n");
    res = bmp388_get_pressure(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* bmp388_set_temperature/bmp388_get_temperature test */
    bmp388_interface_debug_print("bmp388: bmp388_set_temperature/bmp388_get_temperature test.\n");
    
    /* disable */
    res = bmp388_set_temperature(&gs_handle, BMP388_BOOL_FALSE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature disable.\n");
    res = bmp388_get_temperature(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature %s.\n", enable==BMP388_BOOL_FALSE?"ok":"error");
    
    /* enable */
    res = bmp388_set_temperature(&gs_handle, BMP388_BOOL_TRUE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature enable.\n");
    res = bmp388_get_temperature(&gs_handle, (bmp388_bool_t *)&enable);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature %s.\n", enable==BMP388_BOOL_TRUE?"ok":"error");
    
    /* bmp388_set_mode/bmp388_get_mode test */
    bmp388_interface_debug_print("bmp388: bmp388_set_mode/bmp388_get_mode test.\n");
    
    /* sleep */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_SLEEP_MODE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set mode sleep.\n");
    res = bmp388_get_mode(&gs_handle, (bmp388_mode_t *)&mode);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check mode %s.\n", mode==BMP388_MODE_SLEEP_MODE?"ok":"error");
    
    /* normal mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_NORMAL_MODE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set mode normal mode.\n");
    res = bmp388_get_mode(&gs_handle, (bmp388_mode_t *)&mode);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check mode %s.\n", mode==BMP388_MODE_NORMAL_MODE?"ok":"error");
    
    /* set forced mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_SLEEP_MODE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_delay_ms(50);
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_FORCED_MODE);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set mode forced mode.\n");
    res = bmp388_get_mode(&gs_handle, (bmp388_mode_t *)&mode);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get mode failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check mode %s.\n", mode==BMP388_MODE_FORCED_MODE?"ok":"error"); 
    
    /* bmp388_set_pressure_oversampling/bmp388_get_pressure_oversampling test */
    bmp388_interface_debug_print("bmp388: bmp388_set_pressure_oversampling/bmp388_get_pressure_oversampling test.\n");
    
    /* set oversampling x1 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x1);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure oversampling x1.\n");
    res = bmp388_get_pressure_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x1?"ok":"error");
    
    /* set oversampling x2 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x2);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure oversampling x2.\n");
    res = bmp388_get_pressure_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x2?"ok":"error");
    
    /* set oversampling x4 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x4);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure oversampling x4.\n");
    res = bmp388_get_pressure_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x4?"ok":"error");
    
    /* set oversampling x8 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x8);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure oversampling x8.\n");
    res = bmp388_get_pressure_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x8?"ok":"error");
    
    /* set oversampling x16 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x16);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure oversampling x16.\n");
    res = bmp388_get_pressure_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x16?"ok":"error");
    
    /* set oversampling x32 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x32);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set pressure oversampling x32.\n");
    res = bmp388_get_pressure_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get pressure oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check pressure oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x32?"ok":"error");
    
    /* bmp388_set_temperature_oversampling/bmp388_get_temperature_oversampling test */
    bmp388_interface_debug_print("bmp388: bmp388_set_temperature_oversampling/bmp388_get_temperature_oversampling test.\n");
    
    /* oversampling x1 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x1);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature oversampling x1.\n");
    res = bmp388_get_temperature_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x1?"ok":"error");  
    
    /* set oversampling x2 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x2);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature oversampling x2.\n");
    res = bmp388_get_temperature_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x2?"ok":"error");
    
    /* set oversampling x4 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x4);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature oversampling x4.\n");
    res = bmp388_get_temperature_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x4?"ok":"error");
    
    /* set oversampling x8 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x8);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature oversampling x8.\n");
    res = bmp388_get_temperature_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x8?"ok":"error");
    
    /* set oversampling x16 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x16);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature oversampling x16.\n");
    res = bmp388_get_temperature_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x16?"ok":"error");
    
    /* set oversampling x32 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x32);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set temperature oversampling x32.\n");
    res = bmp388_get_temperature_oversampling(&gs_handle, (bmp388_oversampling_t *)&oversampling);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get temperature oversampling failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check temperature oversampling %s.\n", oversampling==BMP388_OVERSAMPLING_x32?"ok":"error");
    
    /* bmp388_set_odr/bmp388_get_odr test */
    bmp388_interface_debug_print("bmp388: bmp388_set_odr/bmp388_get_odr test.\n");
    
    /* set odr 200Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_200_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 200Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_200_HZ?"ok":"error");
    
    /* set odr 100Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_100_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 100Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_100_HZ?"ok":"error");
    
    /* set odr 50Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_50_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 50Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_50_HZ?"ok":"error");
    
    /* set odr 25Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_25_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 25Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_25_HZ?"ok":"error");
    
    /* set odr 12.5Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_12P5_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 12.5Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_12P5_HZ?"ok":"error");
    
    /* set odr 6.25Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_6P25_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 6.25Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_6P25_HZ?"ok":"error");
    
    /* set odr 3.1Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_3P1_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 3.1Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_3P1_HZ?"ok":"error");
    
    /* set odr 1.5Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_1P5_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 1.5Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_1P5_HZ?"ok":"error");
    
    /* set odr 0.78Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P78_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.78Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P78_HZ?"ok":"error");
    
    /* set odr 0.39Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P39_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.39Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P39_HZ?"ok":"error");
    
    /* set odr 0.2Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P2_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.2Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P2_HZ?"ok":"error");
    
    /* set odr 0.1Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P1_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.1Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P1_HZ?"ok":"error");
    
    /* set odr 0.05Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P05_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.05Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P05_HZ?"ok":"error");
    
    /* set odr 0.02Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P02_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.02Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P02_HZ?"ok":"error");
    
    /* set odr 0.01Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P01_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.01Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P01_HZ?"ok":"error");
    
    /* set odr 0.006Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P006_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.006Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P006_HZ?"ok":"error");
    
    /* set odr 0.003Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P003_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.003Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P003_HZ?"ok":"error");
    
    /* set odr 0.0015Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_0P0015_HZ);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set odr 0.0015Hz.\n");
    res = bmp388_get_odr(&gs_handle, (bmp388_odr_t *)&odr);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get odr failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check odr %s.\n", odr==BMP388_ODR_0P0015_HZ?"ok":"error");
    
    /* bmp388_set_filter_coefficient/bmp388_get_filter_coefficient test */
    bmp388_interface_debug_print("bmp388: bmp388_set_filter_coefficient/bmp388_get_filter_coefficient test.\n");
    
    /* set coefficient 0 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_0);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 0.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_0?"ok":"error");
    
    /* set coefficient 1 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_1);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 1.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_1?"ok":"error");
    
    /* set coefficient 3 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_3);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 3.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_3?"ok":"error");
    
    /* set coefficient 7 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_7);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 7.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_7?"ok":"error");
    
    /* set coefficient 15 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_15);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 15.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_15?"ok":"error");
    
    /* set coefficient 31 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_31);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 31.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_31?"ok":"error");
    
    /* set coefficient 63 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_63);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 63.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_63?"ok":"error");
    
    /* set coefficient 127 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_127);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: set filter coefficient 127.\n");
    res = bmp388_get_filter_coefficient(&gs_handle, (bmp388_filter_coefficient_t *)&coef);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get filter coefficient failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: check filter coefficient %s.\n", coef==BMP388_FILTER_COEFFICIENT_127?"ok":"error");
    
    /* bmp388_get_error */
    bmp388_interface_debug_print("bmp388: bmp388_get_error.\n");
    res = bmp388_get_error(&gs_handle, (uint8_t *)&err);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get err failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: err is 0x%02X.\n", (uint8_t)err);
    
    /* bmp388_get_status */
    bmp388_interface_debug_print("bmp388: bmp388_get_status.\n");
    res = bmp388_get_status(&gs_handle, (uint8_t *)&status);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: status is 0x%02X.\n", (uint8_t)status);
    
    /* bmp388_get_sensortime */
    bmp388_interface_debug_print("bmp388: bmp388_get_sensortime.\n");
    res = bmp388_get_sensortime(&gs_handle, (uint32_t *)&sensortime);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get sensor time failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: sensor time is 0x%06X.\n", (uint32_t)sensortime);
    
    /* bmp388_get_event */
    bmp388_interface_debug_print("bmp388: bmp388_get_event.\n");
    res = bmp388_get_event(&gs_handle, &event);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get event failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: event is %s.\n", event==BMP388_EVENT_NONE?"none":"power up or softrest");
    
    /* bmp388_get_interrupt_status */
    bmp388_interface_debug_print("bmp388: bmp388_get_interrupt_status.\n");
    res = bmp388_get_interrupt_status(&gs_handle, (uint8_t *)&status);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get interrupt status failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: interrupt status is 0x%02X.\n", (uint8_t)status);
    
    /* bmp388_get_fifo_length */
    bmp388_interface_debug_print("bmp388: bmp388_get_fifo_length.\n");
    res = bmp388_get_fifo_length(&gs_handle, (uint16_t *)&length);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo length failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: get fifo length is 0x%04X.\n", (uint16_t)length);
    
    /* bmp388_get_fifo_data */
    bmp388_interface_debug_print("bmp388: bmp388_get_fifo_data.\n");
    res = bmp388_get_fifo_data(&gs_handle, (uint8_t *)&data, 1);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: get fifo data failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: get fifo data is 0x%04X.\n", (uint8_t)data);
    
    /* bmp388_flush_fifo */
    bmp388_interface_debug_print("bmp388: bmp388_flush_fifo.\n");
    res = bmp388_flush_fifo(&gs_handle);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: flush fifo failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: flush fifo %s.\n", res?"error":"ok");
    
    /* bmp388_extmode_en_middle */
    bmp388_interface_debug_print("bmp388: bmp388_extmode_en_middle.\n");
    res = bmp388_extmode_en_middle(&gs_handle);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: extmode en middle failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: extmode en middle %s.\n", res?"error":"ok");
    
    /* bmp388_softreset */
    bmp388_interface_debug_print("bmp388: bmp388_softreset.\n");
    res = bmp388_softreset(&gs_handle);
    if (res != 0)
    {
        bmp388_interface_debug_print("bmp388: bmp388 soft reset failed.\n");
        (void)bmp388_deinit(&gs_handle);
        
        return 1;
    }
    bmp388_interface_debug_print("bmp388: soft reset %s.\n", res?"error":"ok");
    
    /* finish register test */
    bmp388_interface_debug_print("bmp388: finish register test.\n");
    (void)bmp388_deinit(&gs_handle);
    
    return 0;
}
