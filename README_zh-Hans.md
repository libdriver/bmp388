[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BMP388

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/bmp388/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

BMP388是一款成熟的带有压力和温度测量的数字传感器。传感器1Hz、3.4uA的测量模式可以使其工作在诸多电池驱动的设备，例如手机、GPS或者手表。BMP388可被用在飞行玩具、无人机、手机平板GPS、导航系统、便携式健康设备、室内监测和手表等。

LibDriver BMP388是LibDriver推出的BMP388全功能驱动，该驱动提供压强温度连续读取、压强温度单次读取、中断读取和FIFO采集等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
    - [example interrupt](#example-interrupt)
    - [example fifo](#example-fifo)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver BMP388的源文件。

/interface目录包含了LibDriver BMP388与平台无关的IIC、SPI总线模板。

/test目录包含了LibDriver BMP388驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver BMP388编程范例。

/doc目录包含了LibDriver BMP388离线文档。

/datasheet目录包含了BMP388数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC、SPI总线模板，完成指定平台的IIC、SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_bmp388_basic.h"

uint8_t res;
uint8_t i;
float temperature_c;
float pressure_pa;

res = bmp388_basic_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    bmp388_interface_delay_ms(1000);
    res = bmp388_basic_read((float *)&temperature_c, (float *)&pressure_pa);
    if (res != 0)
    {
        (void)bmp388_basic_deinit();

        return 1;
    }
    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", temperature_c);
    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", pressure_pa);

    ...
        
}

...

(void)bmp388_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_bmp388_shot.h"

uint8_t res;
uint8_t i;
float temperature_c;
float pressure_pa;

res = bmp388_shot_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    bmp388_interface_delay_ms(1000);
    res = bmp388_shot_read((float *)&temperature_c, (float *)&pressure_pa);
    if (res != 0)
    {
        (void)bmp388_shot_deinit();

        return 1;
    }
    bmp388_interface_debug_print("bmp388: temperature is %0.2fC.\n", temperature_c);
    bmp388_interface_debug_print("bmp388: pressure is %0.2fPa.\n", pressure_pa);
    
    ...
    
}

...

(void)bmp388_shot_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_bmp388_interrupt.h"

uint8_t res;
uint16_t i, timeout;
uint8_t gs_data_ready_flag;
float gs_temperature_c;
float gs_pressure_pa;

void bmp388_interrupt_receive_callback(uint8_t type)
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
            if (bmp388_interrupt_read((float *)&gs_temperature_c, (float *)&gs_pressure_pa) != 0)
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

res = gpio_interrupt_init();
if (res != 0)
{
    return 1;
}
res = bmp388_interrupt_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW, bmp388_interrupt_receive_callback);
if (res != 0)
{
    (void)gpio_interrupt_deinit();

    return 1;
}

...

gs_data_ready_flag = 0;
timeout = 5000;
for (i = 0; i < 3; i++)
{
    while (timeout != 0)
    {
        bmp388_interface_delay_ms(100);
        timeout--;
        if (gs_data_ready_flag != 0)
        {
            break;
        }
        if (timeout == 0)
        {
            (void)gpio_interrupt_deinit();
            (void)bmp388_interrupt_deinit();

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

(void)gpio_interrupt_deinit();
(void)bmp388_interrupt_deinit();

return 0;
```

#### example fifo

```C
#include "driver_bmp388_fifo.h"

uint8_t gs_fifo_full_flag;
uint8_t gs_fifo_watermark_flag;
uint16_t i, timeout;
uint8_t gs_buf[512];
bmp388_frame_t gs_frame[256];

void bmp388_fifo_receive_callback(uint8_t type)
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
            if (res != 0)
            {
                bmp388_interface_debug_print("bmp388: fifo read failed.\n");
                
                return;
            }
            for (i = 0; i < frame_len; i++)
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
            uint8_t res;
            uint16_t len;
            uint16_t i, frame_len;
            
            len = 512;
            frame_len = 256;
            res = bmp388_fifo_read(gs_buf, len, (bmp388_frame_t *)gs_frame, (uint16_t *)&frame_len);
            if (res != 0)
            {
                bmp388_interface_debug_print("bmp388: fifo read failed.\n");
                
                return;
            }
            for (i = 0; i < frame_len; i++)
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
}

res = gpio_interrupt_init();
if (res != 0)
{
    return 1;
}
res = bmp388_fifo_init(BMP388_INTERFACE_IIC, BMP388_ADDRESS_ADO_LOW, bmp388_fifo_receive_callback);
if (res != 0)
{
    (void)gpio_interrupt_deinit();

    return 1;
}

...

gs_fifo_watermark_flag = 0;
gs_fifo_full_flag = 0;
timeout = 5000;
for (i = 0; i < 3; i++)
{
    while (timeout != 0)
    {
        bmp388_interface_delay_ms(100);
        timeout--;
        if ((gs_fifo_watermark_flag != 0) || (gs_fifo_full_flag != 0))
        {
            break;
        }
        if (timeout == 0)
        {
            (void)gpio_interrupt_deinit();
            (void)bmp388_fifo_deinit();

            return 1;
        }
    }
    gs_fifo_watermark_flag = 0;
    gs_fifo_full_flag = 0;
    timeout = 5000;
    
    ...
    
}
(void)gpio_interrupt_deinit();
(void)bmp388_fifo_deinit();

...

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/bmp388/index.html](https://www.libdriver.com/docs/bmp388/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。