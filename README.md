[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver BMP388

[![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/bmp388/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The BMP388 is a digital sensor with pressure and temperature measurement based on proven sensing principles.The sensor module is housed in an extremely compact 10-pin metal-lid LGA package with a footprint only 2.0 x 2.0 mm2 and max 0.8 mm package height. Its small dimensions and its low power consumption of 3.4 uA@1Hz allow the implementation in battery driven devices such as mobile phones ,GPS modules or watches.

LibDriver BMP388 is a full function driver of BMP388 launched by LibDriver.It provides continuous reading of pressure and temperature, single reading of pressure and temperature, interrupt reading, FIFO acquisition and other functions.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example match](#example-match)
    - [example alarm](#example-alarm)
    - [example search](#example-search)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver BMP388 source files.

/interface includes LibDriver BMP388 IIC, SPI platform independent template。

/test includes LibDriver BMP388 driver test code and this code can test the chip necessary function simply。

/example includes LibDriver BMP388 sample code.

/doc includes LibDriver BMP388 offline document.

/datasheet includes BMP388 datasheet。

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

### Install

Reference /interface IIC, SPI platform independent template and finish your platform IIC, SPI driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

```C
uint8_t res;
uint8_t i;
float temperature_c;
float pressure_pa;

res = bmp388_basic_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW);
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    bmp388_interface_delay_ms(1000);
    res = bmp388_basic_read((float *)&temperature_c, (float *)&pressure_pa);
    if (res)
    {
        bmp388_basic_deinit();

        return 1;
    }
    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", temperature_c);
    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", pressure_pa);

    ...
        
}

...

bmp388_basic_deinit();

return 0;
```

#### example shot

```C
uint8_t res;
uint8_t i;
float temperature_c;
float pressure_pa;

res = bmp388_shot_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW);
if (res)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    bmp388_interface_delay_ms(1000);
    res = bmp388_shot_read((float *)&temperature_c, (float *)&pressure_pa);
    if (res)
    {
        bmp388_shot_deinit();

        return 1;
    }
    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", temperature_c);
    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", pressure_pa);
    
    ...
    
}

...

bmp388_shot_deinit();

return 0;
```

#### example interrupt

```C
uint8_t res;
uint16_t i, timeout;
uint8_t gs_data_ready_flag;
float gs_temperature_c;
float gs_pressure_pa;

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

res = gpio_interrupt_init();
if (res)
{
    return 1;
}
res = bmp388_interrupt_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW, bmp388_interface_interrupt_receive_callback);
if (res)
{
    gpio_interrupt_deinit();

    return 1;
}

...

gs_data_ready_flag = 0;
timeout = 5000;
for (i = 0; i < 3; i++)
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
            gpio_interrupt_deinit();
            bmp388_interrupt_deinit();

            return 1;
        }
    }
    gs_data_ready_flag = 0;
    timeout = 5000;
    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", gs_temperature_c);
    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", gs_pressure_pa);
    
    ...
    
}

...

gpio_interrupt_deinit();
bmp388_interrupt_deinit();

return 0;
```

#### example fifo

```C
uint8_t gs_fifo_full_flag;
uint8_t gs_fifo_watermark_flag;
uint16_t i, timeout;
uint8_t gs_buf[512];
bmp388_frame_t gs_frame[256];

uint8_t bmp388_interface_fifo_receive_callback(uint8_t type)
{
    switch (type)
    {
        case BMP388_INTERRUPT_STATUS_FIFO_WATERMARK :
        {
            uint8_t res;
            uint16_t len;
            uint16_t i, frame_len;
            
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

res = gpio_interrupt_init();
if (res)
{
    return 1;
}
res = bmp388_fifo_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW, bmp388_interface_fifo_receive_callback);
if (res)
{
    gpio_interrupt_deinit();

    return 1;
}

...

gs_fifo_watermark_flag = 0;
gs_fifo_full_flag = 0;
timeout = 5000;
for (i = 0; i < 3; i++)
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
            gpio_interrupt_deinit();
            bmp388_fifo_deinit();

            return 1;
        }
    }
    gs_fifo_watermark_flag = 0;
    gs_fifo_full_flag = 0;
    timeout = 5000;
    
    ...
    
}
gpio_interrupt_deinit();
bmp388_fifo_deinit();

...

return 0;
```

### Document

Online documents: https://www.libdriver.com/docs/bmp388/index.html

Offline documents: /doc/html/index.html

### Contributing

Please sent an e-mail to lishifenging@outlook.com

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com