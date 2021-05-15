/** Copyright(C) LibDriver 2015-2021
  * Author: LiShifeng
  * Version: 2.0.0
  */

#include <driver_bmp388_fifo_test.h>

static bmp388_handle_t gs_handle;
static uint8_t gs_fifo_full_flag;
static uint8_t gs_fifo_watermark_flag;
static uint8_t gs_buf[512];
static bmp388_frame_t gs_frame[256];

/**
 * @brief  fifo test irq handler
 * @return status code
 *         - 0 success
 *         - 1 run failed
 * @note   none
 */
uint8_t bmp388_interface_fifo_test_irq_handler(void)
{
    /* run irq handler */
    if (bmp388_irq_handler(&gs_handle))
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
 * @return    status code
 *            - 0 success
 * @note      none
 */
static uint8_t _bmp388_interface_test_receive_callback(uint8_t type)
{
    switch (type)
    {
        case BMP388_INTERRUPT_STATUS_FIFO_WATERMARK :
        {
            if (gs_fifo_watermark_flag == 0)
            {
                volatile uint16_t len;
                
                len = 512;
                /* read fifo */
                if (bmp388_read_fifo(&gs_handle, (uint8_t *)gs_buf, (uint16_t *)&len))
                {
                    bmp388_interface_debug_print("bmp388: read fifo failed.\n");
               
                    return 1;
                }
                bmp388_interface_debug_print("bmp388: read fifo with length %d.\n", len);
                gs_fifo_watermark_flag = 1;
            }
            
            break;
        }
        case BMP388_INTERRUPT_STATUS_FIFO_FULL :
        {
            volatile uint16_t len;
            volatile uint16_t frame_len;
            
            len = 512;
            /* read fifo */
            if (bmp388_read_fifo(&gs_handle, (uint8_t *)gs_buf, (uint16_t *)&len))
            {
                bmp388_interface_debug_print("bmp388: read fifo failed.\n");
           
                return 1;
            }
            if (len > 4)
            {
                bmp388_interface_debug_print("bmp388: clear fifo with length %d.\n", len); 
                frame_len = 256;
                
                /* parse fifo */
                if (bmp388_fifo_parse(&gs_handle, (uint8_t *)gs_buf, len, (bmp388_frame_t *)gs_frame, (uint16_t *)&frame_len))
                {
                    bmp388_interface_debug_print("bmp388: fifo parse failed.\n");
               
                    return 1;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: fifo parse success and total frame is %d.\n", frame_len);
                }
            }
            gs_fifo_full_flag = 1;
            
            break;
        }
        case BMP388_INTERRUPT_STATUS_DATA_READY :
        {
            break;
        }
        default :
        {
            break;
        }
    }
    
    return 0;
}

/**
 * @brief     fifo test
 * @param[in] interface is the chip interface
 * @param[in] addr_pin is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t bmp388_fifo_test(bmp388_interface_t interface, bmp388_address_t addr_pin, uint32_t times)
{
    volatile uint8_t res;
    volatile uint32_t i;
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
    DRIVER_BMP388_LINK_RECEIVE_CALLBACK(&gs_handle, _bmp388_interface_test_receive_callback);
    
    /* bmp388 info */
    res = bmp388_info(&info);
    if (res)
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
        bmp388_interface_debug_print("bmp388: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
        bmp388_interface_debug_print("bmp388: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        bmp388_interface_debug_print("bmp388: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        bmp388_interface_debug_print("bmp388: max current is %0.2fmA.\n", info.max_current_ma);
        bmp388_interface_debug_print("bmp388: max temperature is %0.1fC.\n", info.temperature_max);
        bmp388_interface_debug_print("bmp388: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start fifo test */
    bmp388_interface_debug_print("bmp388: start fifo test.\n");
    
    /* set interface */
    res = bmp388_set_interface(&gs_handle, interface);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set interface failed.\n");
       
        return 1;
    }
    
    /* set addr pin */
    res = bmp388_set_addr_pin(&gs_handle, addr_pin);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set addr pin failed.\n");
       
        return 1;
    }
    
    /* bmp388 init */
    res = bmp388_init(&gs_handle);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: init failed.\n");
       
        return 1;
    }
    
    /* set spi wire 4 */
    res = bmp388_set_spi_wire(&gs_handle, BMP388_SPI_WIRE_4);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set spi wire failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable iic watchdog timer */
    res = bmp388_set_iic_watchdog_timer(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog timer failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set iic watchdog period 40 ms */
    res = bmp388_set_iic_watchdog_period(&gs_handle, BMP388_IIC_WATCHDOG_PERIOD_40_MS);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set iic watchdog period failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable fifo */
    res = bmp388_set_fifo(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable fifo stop on full */
    res = bmp388_set_fifo_stop_on_full(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo stop on full failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set fifo watermark 256 */
    res = bmp388_set_fifo_watermark(&gs_handle, 256);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo watermark failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable fifo sensortime on */
    res = bmp388_set_fifo_sensortime_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo sensortime on failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    res = bmp388_set_fifo_pressure_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo sensortime on failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    res = bmp388_set_fifo_temperature_on(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo temperature on failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    res = bmp388_set_fifo_subsampling(&gs_handle, 0);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo subsampling failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    res = bmp388_set_fifo_data_source(&gs_handle, BMP388_FIFO_DATA_SOURCE_FILTERED);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo data source failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set interrupt pin type push pull */
    res = bmp388_set_interrupt_pin_type(&gs_handle, BMP388_INTERRUPT_PIN_TYPE_PUSH_PULL);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set interrupt pin type failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set interrupt active level higher */
    res = bmp388_set_interrupt_active_level(&gs_handle, BMP388_INTERRUPT_ACTIVE_LEVEL_HIGHER);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set interrupt active level failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable latch interrupt pin and interrupt status */
    res = bmp388_set_latch_interrupt_pin_and_interrupt_status(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set set latch interrupt pin and interrupt status failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable interrupt fifo watermark */
    res = bmp388_set_interrupt_fifo_watermark(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo watermark failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable interrupt fifo full */
    res = bmp388_set_interrupt_fifo_full(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set interrupt fifo full failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* disable interrupt data ready */
    res = bmp388_set_interrupt_data_ready(&gs_handle, BMP388_BOOL_FALSE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set interrupt data ready failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable pressure */
    res = bmp388_set_pressure(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set pressure failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* enable temperature */
    res = bmp388_set_temperature(&gs_handle, BMP388_BOOL_TRUE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set temperature failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set pressure oversampling x32 */
    res = bmp388_set_pressure_oversampling(&gs_handle, BMP388_OVERSAMPLING_x32);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set pressure oversampling failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set temperature oversampling x2 */
    res = bmp388_set_temperature_oversampling(&gs_handle, BMP388_OVERSAMPLING_x2);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set temperature oversampling failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set odr 12.5Hz */
    res = bmp388_set_odr(&gs_handle, BMP388_ODR_12P5_HZ);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set odr failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set filter coefficient 15 */
    res = bmp388_set_filter_coefficient(&gs_handle, BMP388_FILTER_COEFFICIENT_15);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set filter coefficient failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set normal mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_NORMAL_MODE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* fifo watermark test */
    bmp388_interface_debug_print("bmp388: fifo watermark test.\n");
    for (i=0; i<times; i++)
    {
        volatile uint32_t num;
        
        gs_fifo_watermark_flag = 0;
        num = 0;
        while(gs_fifo_watermark_flag == 0)
        {
            num++;
            if (num > 5000)
            {
                bmp388_interface_debug_print("bmp388: fifo interrupt failed.\n");
                bmp388_deinit(&gs_handle); 
                
                return 1;
            }
            bmp388_interface_delay_ms(1);
        }
    }
    
    /* fifo full test */
    bmp388_interface_debug_print("bmp388: fifo full test.\n");
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_SLEEP_MODE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    bmp388_interface_delay_ms(10);
    
    /* set fifo watermark 512 */
    res = bmp388_set_fifo_watermark(&gs_handle, 512);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set fifo watermark failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* set normal mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_NORMAL_MODE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    for (i=0; i<times; i++)
    {
        volatile uint32_t num;
        
        gs_fifo_watermark_flag = 2;
        gs_fifo_full_flag = 0;
        num = 0;
        while (gs_fifo_full_flag == 0)
        {
            num++;
            if (num > 5000)
            {
                bmp388_interface_debug_print("bmp388: fifo interrupt failed.\n");
                bmp388_deinit(&gs_handle); 
                
                return 1;
            }
            bmp388_interface_delay_ms(1);
        }
    }
    
    /* set sleep mode */
    res = bmp388_set_mode(&gs_handle, BMP388_MODE_SLEEP_MODE);
    if (res)
    {
        bmp388_interface_debug_print("bmp388: set mode failed.\n");
        bmp388_deinit(&gs_handle); 
        
        return 1;
    }
    
    /* finish fifo test */
    bmp388_interface_debug_print("bmp388: finish fifo test.\n");
    bmp388_deinit(&gs_handle); 
    
    return 0;
}
