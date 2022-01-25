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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-04-12
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/04/12  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_bmp388_basic.h"
#include "driver_bmp388_shot.h"
#include "driver_bmp388_interrupt.h"
#include "driver_bmp388_fifo.h"
#include "driver_bmp388_register_test.h"
#include "driver_bmp388_read_test.h"
#include "driver_bmp388_interrupt_test.h"
#include "driver_bmp388_fifo_test.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "gpio.h"
#include "shell.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
static uint8_t gs_data_ready_flag;         /**< data ready flag */
static float gs_temperature_c;             /**< temperature data */
static float gs_pressure_pa;               /**< pressure data */
static uint8_t gs_fifo_full_flag;          /**< fifo full flag */
static uint8_t gs_fifo_watermark_flag;     /**< fifo watermark flag */
static uint8_t gs_buf[512];                /**< buffer */
static bmp388_frame_t gs_frame[256];       /**< frame buffer */
uint8_t g_buf[256];                        /**< uart buffer */
uint16_t g_len;                            /**< uart buffer length */
uint8_t (*g_gpio_irq)(void) = NULL;        /**< irq function address */

/**
 * @brief exti 0 irq
 * @note  none
 */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief     gpio exti callback
 * @param[in] pin is the gpio pin
 * @note      none
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
        if (g_gpio_irq)
        {
            g_gpio_irq();
        }
    }
}

/**
 * @brief     interface interrupt receive callback
 * @param[in] type is the interrupt type
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t bmp388_interface_interrupt_receive_callback(uint8_t type)
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
            /* read temperature pressure */
            if (bmp388_interrupt_read((float *)&gs_temperature_c, (float *)&gs_pressure_pa))
            {
                bmp388_interface_debug_print("bmp388: read temperature and pressure failed.\n");
           
                return 1;
            }
            gs_data_ready_flag  = 1;
            
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
 * @brief     interface fifo receive callback
 * @param[in] type is the interrupt type
 * @return    status code
 *            - 0 success
 * @note      none
 */
uint8_t bmp388_interface_fifo_receive_callback(uint8_t type)
{
    switch (type)
    {
        case BMP388_INTERRUPT_STATUS_FIFO_WATERMARK :
        {
            volatile uint8_t res;
            volatile uint16_t len;
            volatile uint16_t i, frame_len;
            
            len = 512;
            frame_len = 256;
            res = bmp388_fifo_read(gs_buf, len, (bmp388_frame_t *)gs_frame, (uint16_t *)&frame_len);
            if (res)
            {
                bmp388_interface_debug_print("bmp388: fifo read failed.\n");
                
                return 1;
            }
            for (i=0; i<frame_len; i++)
            {
                if (gs_frame[i].type == BMP388_FRAME_TYPE_TEMPERATURE)
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", gs_frame[i].data);
                }
                else if (gs_frame[i].type == BMP388_FRAME_TYPE_PRESSURE)
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", gs_frame[i].data);
                }
                else if (gs_frame[i].type == BMP388_FRAME_TYPE_SENSORTIME)
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: sensortime is %d.\n", gs_frame[i].raw);
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: unknow type.\n");
                }
            }
            gs_fifo_watermark_flag = 1;
            
            break;
        }
        case BMP388_INTERRUPT_STATUS_FIFO_FULL :
        {
            volatile uint8_t res;
            volatile uint16_t len;
            volatile uint16_t i, frame_len;
            
            len = 512;
            frame_len = 256;
            res = bmp388_fifo_read(gs_buf, len, (bmp388_frame_t *)gs_frame, (uint16_t *)&frame_len);
            if (res)
            {
                bmp388_interface_debug_print("bmp388: fifo read failed.\n");
                
                return 1;
            }
            for (i=0; i<frame_len; i++)
            {
                if (gs_frame[i].type == BMP388_FRAME_TYPE_TEMPERATURE)
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", gs_frame[i].data);
                }
                else if (gs_frame[i].type == BMP388_FRAME_TYPE_PRESSURE)
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", gs_frame[i].data);
                }
                else if (gs_frame[i].type == BMP388_FRAME_TYPE_SENSORTIME)
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: sensortime is %d.\n", gs_frame[i].raw);
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: fifo %d/%d.\n", i+1, frame_len);
                    bmp388_interface_debug_print("bmp388: unknow type.\n");
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
 * @brief     bmp388 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t bmp388(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            bmp388_info_t info;
            
            /* print bmp388 info */
            bmp388_info(&info);
            bmp388_interface_debug_print("bmp388: chip is %s.\n", info.chip_name);
            bmp388_interface_debug_print("bmp388: manufacturer is %s.\n", info.manufacturer_name);
            bmp388_interface_debug_print("bmp388: interface is %s.\n", info.interface);
            bmp388_interface_debug_print("bmp388: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            bmp388_interface_debug_print("bmp388: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            bmp388_interface_debug_print("bmp388: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            bmp388_interface_debug_print("bmp388: max current is %0.2fmA.\n", info.max_current_ma);
            bmp388_interface_debug_print("bmp388: max temperature is %0.1fC.\n", info.temperature_max);
            bmp388_interface_debug_print("bmp388: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            bmp388_interface_debug_print("bmp388: SPI interface SCK connected to GPIOA PIN5.\n");
            bmp388_interface_debug_print("bmp388: SPI interface MISO connected to GPIOA PIN6.\n");
            bmp388_interface_debug_print("bmp388: SPI interface MOSI connected to GPIOA PIN7.\n");
            bmp388_interface_debug_print("bmp388: SPI interface CS connected to GPIOA PIN4.\n");
            bmp388_interface_debug_print("bmp388: IIC interface SCL connected to GPIOB PIN8.\n");
            bmp388_interface_debug_print("bmp388: IIC interface SDA connected to GPIOB PIN9.\n");
            bmp388_interface_debug_print("bmp388: INT connected to GPIOB PIN0.\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show bmp388 help */
            
            help:
            
            bmp388_interface_debug_print("bmp388 -i\n\tshow bmp388 chip and driver information.\n");
            bmp388_interface_debug_print("bmp388 -h\n\tshow bmp388 help.\n");
            bmp388_interface_debug_print("bmp388 -p\n\tshow bmp388 pin connections of the current board.\n");
            bmp388_interface_debug_print("bmp388 -t reg (-iic | -spi) -a (0 | 1)\n\trun bmp388 register test.\n");
            bmp388_interface_debug_print("bmp388 -t read <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 read test.times means the test times.\n");
            bmp388_interface_debug_print("bmp388 -t int <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 interrupt test.times means the test times.\n");
            bmp388_interface_debug_print("bmp388 -t fifo <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 fifo test.times means the test times.\n");
            bmp388_interface_debug_print("bmp388 -c read <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 read function.times means the read times.\n");
            bmp388_interface_debug_print("bmp388 -c shot <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 shot function.times means the read times.\n");
            bmp388_interface_debug_print("bmp388 -c int <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 interrupt function.times means the read times.\n");
            bmp388_interface_debug_print("bmp388 -c fifo <times> (-iic | -spi) -a (0 | 1)\n\trun bmp388 fifo function.times means the read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                volatile uint8_t res;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[3]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                }
                else if (strcmp("-spi", argv[3]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 1;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                res = bmp388_register_test(interface, addr_pin);
                if (res)
                {
                    return 1;
                }
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 7)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                res = bmp388_read_test(interface, addr_pin, atoi(argv[3]));
                if (res)
                {
                    return 1;
                }
                
                return 0;
            }
            /* interrupt test */
            else if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                res = gpio_interrupt_init();
                if (res)
                {
                    return 1;
                }
                g_gpio_irq = bmp388_interrupt_test_irq_handler;
                res = bmp388_interrupt_test(interface, addr_pin, atoi(argv[3]));
                if (res)
                {
                    g_gpio_irq = NULL;
                    gpio_interrupt_deinit();
                    
                    return 1;
                }
                g_gpio_irq = NULL;
                gpio_interrupt_deinit();
                
                return 0;
            }
            /* fifo test */
            else if (strcmp("fifo", argv[2]) == 0)
            {
                volatile uint8_t res;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                    bmp388_interface_debug_print("bmp388: fifo test can only run in spi interface.\n");
                    
                    return 1;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                res = gpio_interrupt_init();
                if (res)
                {
                    return 1;
                }
                g_gpio_irq = bmp388_fifo_test_irq_handler;
                res = bmp388_fifo_test(interface, addr_pin, atoi(argv[3]));
                if (res)
                {
                    g_gpio_irq = NULL;
                    gpio_interrupt_deinit();
                    
                    return 1;
                }
                g_gpio_irq = NULL;
                gpio_interrupt_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times, i;
                volatile float temperature_c;
                volatile float pressure_pa;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                res = bmp388_basic_init(interface, addr_pin);
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    bmp388_interface_delay_ms(1000);
                    res = bmp388_basic_read((float *)&temperature_c, (float *)&pressure_pa);
                    if (res)
                    {
                        bmp388_basic_deinit();
                        
                        return 1;
                    }
                    bmp388_interface_debug_print("bmp388: %d/%d.\n", i+1, times);
                    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", temperature_c);
                    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", pressure_pa);
                }
                bmp388_basic_deinit();
                
                return 0;
            }
            /* shot function */
            else if (strcmp("shot", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times, i;
                volatile float temperature_c;
                volatile float pressure_pa;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                res = bmp388_shot_init(interface, addr_pin);
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    bmp388_interface_delay_ms(1000);
                    res = bmp388_shot_read((float *)&temperature_c, (float *)&pressure_pa);
                    if (res)
                    {
                        bmp388_shot_deinit();
                        
                        return 1;
                    }
                    bmp388_interface_debug_print("bmp388: %d/%d.\n", i+1, times);
                    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", temperature_c);
                    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", pressure_pa);
                }
                bmp388_shot_deinit();
               
                return 0;
            }
            /* interrupt function */
            else if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times, i, timeout;;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                g_gpio_irq = bmp388_interrupt_irq_handler;
                res = gpio_interrupt_init();
                if (res)
                {
                    return 1;
                }
                res = bmp388_interrupt_init(interface, addr_pin, bmp388_interface_interrupt_receive_callback);
                if (res)
                {
                    g_gpio_irq = NULL;
                    gpio_interrupt_deinit();
                    
                    return 1;
                }
                times = atoi(argv[3]);
                gs_data_ready_flag = 0;
                timeout = 5000;
                for (i=0; i<times; i++)
                {
                    while (timeout)
                    {
                        bmp388_interface_delay_ms(100);
                        timeout--;
                        if (gs_data_ready_flag)
                        {
                            break;
                        }
                        if (timeout == 0)
                        {
                            g_gpio_irq = NULL;
                            gpio_interrupt_deinit();
                            bmp388_interrupt_deinit();
                            
                            return 1;
                        }
                    }
                    gs_data_ready_flag = 0;
                    timeout = 5000;
                    bmp388_interface_debug_print("bmp388: %d/%d.\n", i+1, times);
                    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", gs_temperature_c);
                    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", gs_pressure_pa);
                }
                g_gpio_irq = NULL;
                gpio_interrupt_deinit();
                bmp388_interrupt_deinit();
               
                return 0;
            }
            /* fifo function */
            else if (strcmp("fifo", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times, i, timeout;;
                bmp388_address_t addr_pin;
                bmp388_interface_t interface;
                
                if (strcmp("-iic", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_IIC;
                    bmp388_interface_debug_print("bmp388: fifo test can only run in spi interface.\n");
                    
                    return 5;
                }
                else if (strcmp("-spi", argv[4]) == 0)
                {
                    interface = BMP388_INTERFACE_SPI;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: interface is invalid.\n");
                    
                    return 5;
                }
                if (strcmp("-a", argv[5]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_LOW;
                }
                else if (strcmp("1", argv[6]) == 0)
                {
                    addr_pin = BMP388_ADDRESS_ADO_HIGH;
                }
                else
                {
                    bmp388_interface_debug_print("bmp388: address is invalid.\n");
                    
                    return 5;
                }
                g_gpio_irq = bmp388_fifo_irq_handler;
                res = gpio_interrupt_init();
                if (res)
                {
                    return 1;
                }
                res = bmp388_fifo_init(interface, addr_pin, bmp388_interface_fifo_receive_callback);
                if (res)
                {
                    g_gpio_irq = NULL;
                    gpio_interrupt_deinit();
                    
                    return 1;
                }
                times = atoi(argv[3]);
                gs_fifo_watermark_flag = 0;
                gs_fifo_full_flag = 0;
                timeout = 5000;
                for (i=0; i<times; i++)
                {
                    while (timeout)
                    {
                        bmp388_interface_delay_ms(100);
                        timeout--;
                        if (gs_fifo_watermark_flag || gs_fifo_full_flag)
                        {
                            break;
                        }
                        if (timeout == 0)
                        {
                            g_gpio_irq = NULL;
                            gpio_interrupt_deinit();
                            bmp388_fifo_deinit();
                            
                            return 1;
                        }
                    }
                    gs_fifo_watermark_flag = 0;
                    gs_fifo_full_flag = 0;
                    timeout = 5000;
                }
                bmp388_interface_debug_print("bmp388: finish fifo read.\n");
                g_gpio_irq = NULL;
                gpio_interrupt_deinit();
                bmp388_fifo_deinit();
               
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    volatile uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart1 init */
    uart1_init(115200);
    
    /* shell init && register bmp388 fuction */
    shell_init();
    shell_register("bmp388", bmp388);
    uart1_print("bmp388: welcome to libdriver bmp388.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart1_read(g_buf, 256);
        if (g_len)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart1_print("bmp388: run failed.\n");
            }
            else if (res == 2)
            {
                uart1_print("bmp388: unknow command.\n");
            }
            else if (res == 3)
            {
                uart1_print("bmp388: length is too long.\n");
            }
            else if (res == 4)
            {
                uart1_print("bmp388: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart1_print("bmp388: param is invalid.\n");
            }
            else
            {
                uart1_print("bmp388: unknow status code.\n");
            }
            uart1_flush();
        }
        delay_ms(100);
    }
}
