### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

SPI Pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

GPIO Pin: INT PB0.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. BMP388

#### 3.1 Command Instruction

1. Show bmp388 chip and driver information.

   ```shell
   bmp388 (-i | --information)
   ```

2. Show bmp388 help.

   ```shell
   bmp388 (-h | --help)
   ```

3. Show bmp388 pin connections of the current board.

   ```shell
   bmp388 (-p | --port)
   ```

4. Run bmp388 register test.

   ```shell
   bmp388 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
   ```

5. Run bmp388 read test, num means the test times. 

   ```shell
   bmp388 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

6. Run bmp388 interrupt test, num means the test times.

   ```shell
   bmp388 (-t int | --test=int) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

7. Run bmp388 fifo test, num means the test times.

   ```shell
   bmp388 (-t fifo | --test=fifo) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

8. Run bmp388 read function, num means the read times. 

   ```shell
   bmp388 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

9. Run bmp388 shot function, num means the read times.

   ```shell
   bmp388 (-e shot | --example=shot) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
   ```

10. Run bmp388 interrupt function, num means the read times.

    ```shell
    bmp388 (-e int | --example=int) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
    ```

11. Run bmp388 fifo function, num means the read times.

    ```shell
    bmp388 (-e fifo | --example=fifo) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
    ```

#### 3.2 Command Example

```shell
bmp388 -i

bmp388: chip is Bosch BMP388.
bmp388: manufacturer is Bosch.
bmp388: interface is IIC SPI.
bmp388: driver version is 2.0.
bmp388: min supply voltage is 1.6V.
bmp388: max supply voltage is 3.6V.
bmp388: max current is 0.80mA.
bmp388: max temperature is 85.0C.
bmp388: min temperature is -40.0C.
```

```shell
bmp388 -p

bmp388: SPI interface SCK connected to GPIOA PIN5.
bmp388: SPI interface MISO connected to GPIOA PIN6.
bmp388: SPI interface MOSI connected to GPIOA PIN7.
bmp388: SPI interface CS connected to GPIOA PIN4.
bmp388: IIC interface SCL connected to GPIOB PIN8.
bmp388: IIC interface SDA connected to GPIOB PIN9.
bmp388: INT connected to GPIOB PIN0.
```

```shell
bmp388 -t reg --addr=0 --interface=iic

bmp388: chip is Bosch BMP388.
bmp388: manufacturer is Bosch.
bmp388: interface is IIC SPI.
bmp388: driver version is 2.0.
bmp388: min supply voltage is 1.6V.
bmp388: max supply voltage is 3.6V.
bmp388: max current is 0.80mA.
bmp388: max temperature is 85.0C.
bmp388: min temperature is -40.0C.
bmp388: start register test.
bmp388: bmp388_set_interface/bmp388_get_interface test.
bmp388: set interface iic.
bmp388: check interface ok.
bmp388: set interface spi.
bmp388: check interface ok.
bmp388: bmp388_set_addr_pin/bmp388_get_addr_pin test.
bmp388: set addr pin low.
bmp388: check addr pin ok.
bmp388: set addr pin high.
bmp388: check addr pin ok.
bmp388: bmp388_set_fifo_watermark/bmp388_get_fifo_watermark test.
bmp388: set fifo watermark 432.
bmp388: check fifo watermark ok.
bmp388: bmp388_set_fifo/bmp388_get_fifo test.
bmp388: set fifo enable.
bmp388: check fifo ok.
bmp388: set fifo disable.
bmp388: check fifo ok.
bmp388: bmp388_set_fifo_stop_on_full/bmp388_get_fifo_stop_on_full test.
bmp388: set fifo stop on full enable.
bmp388: check fifo stop on full ok.
bmp388: set fifo stop on full disable.
bmp388: check fifo stop on full ok.
bmp388: bmp388_set_fifo_sensortime_on/bmp388_get_fifo_sensortime_on test.
bmp388: set fifo sensortime on enable.
bmp388: check fifo sensortime on ok.
bmp388: set fifo sensortime on disable.
bmp388: check fifo sensortime on ok.
bmp388: bmp388_set_fifo_pressure_on/bmp388_get_fifo_pressure_on test.
bmp388: set fifo pressure on enable.
bmp388: check fifo pressure on ok.
bmp388: set fifo pressure on disable.
bmp388: check fifo pressure on ok.
bmp388: bmp388_set_fifo_temperature_on/bmp388_get_fifo_temperature_on test.
bmp388: set fifo temperature on enable.
bmp388: check fifo temperature on ok.
bmp388: set fifo temperature on disable.
bmp388: check fifo temperature on ok.
bmp388: bmp388_set_fifo_subsampling/bmp388_get_fifo_subsampling test.
bmp388: set fifo subsampling 4.
bmp388: check fifo subsampling on ok.
bmp388: bmp388_set_fifo_data_source/bmp388_get_fifo_data_source test.
bmp388: set fifo data source unfiltered.
bmp388: check fifo data source ok.
bmp388: set fifo data source filtered.
bmp388: check fifo data source ok.
bmp388: bmp388_set_interrupt_pin_type/bmp388_get_interrupt_pin_type test.
bmp388: set interrupt pin type push pull.
bmp388: check interrupt pin type ok.
bmp388: set interrupt pin type open drain.
bmp388: check interrupt pin type ok.
bmp388: bmp388_set_interrupt_active_level/bmp388_get_interrupt_active_level test.
bmp388: set interrupt active level lower.
bmp388: check interrupt active level ok.
bmp388: set interrupt active level higher.
bmp388: check interrupt active level ok.
bmp388: bmp388_set_latch_interrupt_pin_and_interrupt_status/bmp388_get_latch_interrupt_pin_and_interrupt_status test.
bmp388: set latch interrupt pin and interrupt status enable.
bmp388: check latch interrupt pin and interrupt status ok.
bmp388: set latch interrupt pin and interrupt status disable.
bmp388: check latch interrupt pin and interrupt status ok.
bmp388: bmp388_set_interrupt_fifo_watermark/bmp388_get_interrupt_fifo_watermark test.
bmp388: set interrupt fifo watermark enable.
bmp388: check interrupt fifo watermark ok.
bmp388: set interrupt fifo watermark disable.
bmp388: check interrupt fifo watermark ok.
bmp388: bmp388_set_interrupt_fifo_full/bmp388_get_interrupt_fifo_full test.
bmp388: set interrupt fifo full enable.
bmp388: check interrupt fifo full ok.
bmp388: set interrupt fifo full disable.
bmp388: check interrupt fifo full ok.
bmp388: bmp388_set_interrupt_data_ready/bmp388_get_interrupt_fifo_data_ready test.
bmp388: set interrupt data ready enable.
bmp388: check interrupt data ready ok.
bmp388: set interrupt data ready disable.
bmp388: check interrupt data ready ok.
bmp388: bmp388_set_spi_wire/bmp388_get_spi_wire test.
bmp388: set spi 4 wire.
bmp388: check spi wire ok.
bmp388: set spi 3 wire.
bmp388: check spi wire ok.
bmp388: bmp388_set_iic_watchdog_timer/bmp388_get_iic_watchdog_timer test.
bmp388: set iic watchdog timer enable.
bmp388: check iic watchdog timer ok.
bmp388: set iic watchdog timer disable.
bmp388: check iic watchdog timer ok.
bmp388: bmp388_set_iic_watchdog_period/bmp388_get_iic_watchdog_period test.
bmp388: set iic watchdog period 1.25ms.
bmp388: check iic watchdog period ok.
bmp388: set iic watchdog period 40ms.
bmp388: check iic watchdog period ok.
bmp388: bmp388_set_pressure/bmp388_get_pressure test.
bmp388: set pressure disable.
bmp388: check pressure ok.
bmp388: set pressure enable.
bmp388: check pressure ok.
bmp388: bmp388_set_temperature/bmp388_get_temperature test.
bmp388: set temperature disable.
bmp388: check temperature ok.
bmp388: set temperature enable.
bmp388: check temperature ok.
bmp388: bmp388_set_mode/bmp388_get_mode test.
bmp388: set mode sleep.
bmp388: check mode ok.
bmp388: set mode normal mode.
bmp388: check mode ok.
bmp388: set mode forced mode.
bmp388: check mode error.
bmp388: bmp388_set_pressure_oversampling/bmp388_get_pressure_oversampling test.
bmp388: set pressure oversampling x1.
bmp388: check pressure oversampling ok.
bmp388: set pressure oversampling x2.
bmp388: check pressure oversampling ok.
bmp388: set pressure oversampling x4.
bmp388: check pressure oversampling ok.
bmp388: set pressure oversampling x8.
bmp388: check pressure oversampling ok.
bmp388: set pressure oversampling x16.
bmp388: check pressure oversampling ok.
bmp388: set pressure oversampling x32.
bmp388: check pressure oversampling ok.
bmp388: bmp388_set_temperature_oversampling/bmp388_get_temperature_oversampling test.
bmp388: set temperature oversampling x1.
bmp388: check temperature oversampling ok.
bmp388: set temperature oversampling x2.
bmp388: check temperature oversampling ok.
bmp388: set temperature oversampling x4.
bmp388: check temperature oversampling ok.
bmp388: set temperature oversampling x8.
bmp388: check temperature oversampling ok.
bmp388: set temperature oversampling x16.
bmp388: check temperature oversampling ok.
bmp388: set temperature oversampling x32.
bmp388: check temperature oversampling ok.
bmp388: bmp388_set_odr/bmp388_get_odr test.
bmp388: set odr 200Hz.
bmp388: check odr ok.
bmp388: set odr 100Hz.
bmp388: check odr ok.
bmp388: set odr 50Hz.
bmp388: check odr ok.
bmp388: set odr 25Hz.
bmp388: check odr ok.
bmp388: set odr 12.5Hz.
bmp388: check odr ok.
bmp388: set odr 6.25Hz.
bmp388: check odr ok.
bmp388: set odr 3.1Hz.
bmp388: check odr ok.
bmp388: set odr 1.5Hz.
bmp388: check odr ok.
bmp388: set odr 0.78Hz.
bmp388: check odr ok.
bmp388: set odr 0.39Hz.
bmp388: check odr ok.
bmp388: set odr 0.2Hz.
bmp388: check odr ok.
bmp388: set odr 0.1Hz.
bmp388: check odr ok.
bmp388: set odr 0.05Hz.
bmp388: check odr ok.
bmp388: set odr 0.02Hz.
bmp388: check odr ok.
bmp388: set odr 0.01Hz.
bmp388: check odr ok.
bmp388: set odr 0.006Hz.
bmp388: check odr ok.
bmp388: set odr 0.003Hz.
bmp388: check odr ok.
bmp388: set odr 0.0015Hz.
bmp388: check odr ok.
bmp388: bmp388_set_filter_coefficient/bmp388_get_filter_coefficient test.
bmp388: set filter coefficient 0.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 1.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 3.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 7.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 15.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 31.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 63.
bmp388: check filter coefficient ok.
bmp388: set filter coefficient 127.
bmp388: check filter coefficient ok.
bmp388: bmp388_get_error.
bmp388: err is 0x00.
bmp388: bmp388_get_status.
bmp388: status is 0x70.
bmp388: bmp388_get_sensortime.
bmp388: sensortime is 0x0025B5.
bmp388: bmp388_get_event.
bmp388: event is power up or softrest.
bmp388: bmp388_get_interrupt_status.
bmp388: interrupt status is 0x08.
bmp388: bmp388_get_fifo_length.
bmp388: get fifo length is 0x0000.
bmp388: bmp388_get_fifo_data.
bmp388: get fifo data is 0x0080.
bmp388: bmp388_flush_fifo.
bmp388: flush fifo ok.
bmp388: bmp388_extmode_en_middle.
bmp388: extmode en middle ok.
bmp388: bmp388_softreset.
bmp388: softreset ok.
bmp388: finish register test.
```

```shell
bmp388 -t read --addr=0 --interface=iic --times=3

bmp388: chip is Bosch BMP388.
bmp388: manufacturer is Bosch.
bmp388: interface is IIC SPI.
bmp388: driver version is 2.0.
bmp388: min supply voltage is 1.6V.
bmp388: max supply voltage is 3.6V.
bmp388: max current is 0.80mA.
bmp388: max temperature is 85.0C.
bmp388: min temperature is -40.0C.
bmp388: start read test.
bmp388: forced mode read test.
bmp388: temperature is 26.94C.
bmp388: pressure is 102993.07Pa.
bmp388: temperature is 26.94C.
bmp388: pressure is 102993.07Pa.
bmp388: temperature is 26.94C.
bmp388: pressure is 102993.20Pa.
bmp388: normal mode read test.
bmp388: temperature is 27.04C.
bmp388: pressure is 102982.96Pa.
bmp388: temperature is 27.11C.
bmp388: pressure is 102976.89Pa.
bmp388: temperature is 27.15C.
bmp388: pressure is 102974.42Pa.
bmp388: finish read test.
```

```shell
bmp388 -t int --addr=0 --interface=iic --times=3

bmp388: chip is Bosch BMP388.
bmp388: manufacturer is Bosch.
bmp388: interface is IIC SPI.
bmp388: driver version is 2.0.
bmp388: min supply voltage is 1.6V.
bmp388: max supply voltage is 3.6V.
bmp388: max current is 0.80mA.
bmp388: max temperature is 85.0C.
bmp388: min temperature is -40.0C.
bmp388: start interrupt test.
bmp388: temperature is 28.40C.
bmp388: pressure is 103012.95Pa.
bmp388: temperature is 28.53C.
bmp388: pressure is 103002.73Pa.
bmp388: temperature is 28.58C.
bmp388: pressure is 103000.25Pa.
bmp388: finish interrupt test.
```

```shell
bmp388 -t fifo --addr=0 --interface=iic --times=3

bmp388: chip is Bosch BMP388.
bmp388: manufacturer is Bosch.
bmp388: interface is IIC SPI.
bmp388: driver version is 2.0.
bmp388: min supply voltage is 1.6V.
bmp388: max supply voltage is 3.6V.
bmp388: max current is 0.80mA.
bmp388: max temperature is 85.0C.
bmp388: min temperature is -40.0C.
bmp388: start fifo test.
bmp388: fifo watermark test.
bmp388: read fifo with length 265.
bmp388: read fifo with length 263.
bmp388: read fifo with length 263.
bmp388: fifo full test.
bmp388: clear fifo with length 508.
bmp388: fifo parse success and total frame is 145.
bmp388: clear fifo with length 508.
bmp388: fifo parse success and total frame is 145.
bmp388: clear fifo with length 508.
bmp388: fifo parse success and total frame is 145.
bmp388: finish fifo test.
```

```shell
bmp388 -e read --addr=0 --interface=iic --times=3

bmp388: 1/3.
bmp388: temperature is 27.05C.
bmp388: pressure is 102983.25Pa.
bmp388: 2/3.
bmp388: temperature is 27.12C.
bmp388: pressure is 102976.95Pa.
bmp388: 3/3.
bmp388: temperature is 27.16C.
bmp388: pressure is 102974.87Pa.
```

```shell
bmp388 -e shot --addr=0 --interface=iic --times=3

bmp388: 1/3.
bmp388: temperature is 26.93C.
bmp388: pressure is 102994.28Pa.
bmp388: 2/3.
bmp388: temperature is 26.93C.
bmp388: pressure is 102994.32Pa.
bmp388: 3/3.
bmp388: temperature is 26.93C.
bmp388: pressure is 102994.31Pa.
```

```shell
bmp388 -e int --addr=0 --interface=iic --times=3

bmp388: 1/3.
bmp388: temperature is 26.93C.
bmp388: pressure is 102997.63Pa.
bmp388: 2/3.
bmp388: temperature is 26.94C.
bmp388: pressure is 102997.09Pa.
bmp388: 3/3.
bmp388: temperature is 26.96C.
bmp388: pressure is 102994.97Pa.
```

```shell
bmp388 -e fifo --addr=0 --interface=iic --times=3

bmp388: fifo 1/1.
bmp388: sensortime is 74180.
bmp388: fifo 1/75.
bmp388: temperature is 26.96C.
bmp388: fifo 2/75.
bmp388: pressure is 102971.79Pa.
bmp388: fifo 3/75.
bmp388: temperature is 26.97C.
bmp388: fifo 4/75.
bmp388: pressure is 102971.60Pa.
bmp388: fifo 5/75.
bmp388: temperature is 26.97C.
bmp388: fifo 6/75.
bmp388: pressure is 102971.44Pa.
bmp388: fifo 7/75.
bmp388: temperature is 26.97C.
bmp388: fifo 8/75.
bmp388: pressure is 102971.32Pa.
bmp388: fifo 9/75.
bmp388: temperature is 26.97C.
bmp388: fifo 10/75.
bmp388: pressure is 102971.25Pa.
bmp388: fifo 11/75.
bmp388: temperature is 26.98C.
bmp388: fifo 12/75.
bmp388: pressure is 102971.09Pa.
bmp388: fifo 13/75.
bmp388: temperature is 26.98C.
bmp388: fifo 14/75.
bmp388: pressure is 102970.90Pa.
bmp388: fifo 15/75.
bmp388: temperature is 26.98C.
bmp388: fifo 16/75.
bmp388: pressure is 102970.79Pa.
bmp388: fifo 17/75.
bmp388: temperature is 26.98C.
bmp388: fifo 18/75.
bmp388: pressure is 102970.57Pa.
bmp388: fifo 19/75.
bmp388: temperature is 26.98C.
bmp388: fifo 20/75.
bmp388: pressure is 102970.46Pa.
bmp388: fifo 21/75.
bmp388: temperature is 26.98C.
bmp388: fifo 22/75.
bmp388: pressure is 102970.30Pa.
bmp388: fifo 23/75.
bmp388: temperature is 26.98C.
bmp388: fifo 24/75.
bmp388: pressure is 102970.28Pa.
bmp388: fifo 25/75.
bmp388: temperature is 26.98C.
bmp388: fifo 26/75.
bmp388: pressure is 102970.09Pa.
bmp388: fifo 27/75.
bmp388: temperature is 26.99C.
bmp388: fifo 28/75.
bmp388: pressure is 102970.06Pa.
bmp388: fifo 29/75.
bmp388: temperature is 26.99C.
bmp388: fifo 30/75.
bmp388: pressure is 102970.00Pa.
bmp388: fifo 31/75.
bmp388: temperature is 26.99C.
bmp388: fifo 32/75.
bmp388: pressure is 102969.81Pa.
bmp388: fifo 33/75.
bmp388: temperature is 26.99C.
bmp388: fifo 34/75.
bmp388: pressure is 102969.84Pa.
bmp388: fifo 35/75.
bmp388: temperature is 26.99C.
bmp388: fifo 36/75.
bmp388: pressure is 102969.79Pa.
bmp388: fifo 37/75.
bmp388: temperature is 26.99C.
bmp388: fifo 38/75.
bmp388: pressure is 102969.82Pa.
bmp388: fifo 39/75.
bmp388: temperature is 26.99C.
bmp388: fifo 40/75.
bmp388: pressure is 102969.81Pa.
bmp388: fifo 41/75.
bmp388: temperature is 27.00C.
bmp388: fifo 42/75.
bmp388: pressure is 102969.67Pa.
bmp388: fifo 43/75.
bmp388: temperature is 27.00C.
bmp388: fifo 44/75.
bmp388: pressure is 102969.67Pa.
bmp388: fifo 45/75.
bmp388: temperature is 27.00C.
bmp388: fifo 46/75.
bmp388: pressure is 102969.60Pa.
bmp388: fifo 47/75.
bmp388: temperature is 27.00C.
bmp388: fifo 48/75.
bmp388: pressure is 102969.69Pa.
bmp388: fifo 49/75.
bmp388: temperature is 27.00C.
bmp388: fifo 50/75.
bmp388: pressure is 102969.66Pa.
bmp388: fifo 51/75.
bmp388: temperature is 27.00C.
bmp388: fifo 52/75.
bmp388: pressure is 102969.53Pa.
bmp388: fifo 53/75.
bmp388: temperature is 27.00C.
bmp388: fifo 54/75.
bmp388: pressure is 102969.44Pa.
bmp388: fifo 55/75.
bmp388: temperature is 27.00C.
bmp388: fifo 56/75.
bmp388: pressure is 102969.41Pa.
bmp388: fifo 57/75.
bmp388: temperature is 27.00C.
bmp388: fifo 58/75.
bmp388: pressure is 102969.28Pa.
bmp388: fifo 59/75.
bmp388: temperature is 27.00C.
bmp388: fifo 60/75.
bmp388: pressure is 102969.16Pa.
bmp388: fifo 61/75.
bmp388: temperature is 27.00C.
bmp388: fifo 62/75.
bmp388: pressure is 102969.08Pa.
bmp388: fifo 63/75.
bmp388: temperature is 27.00C.
bmp388: fifo 64/75.
bmp388: pressure is 102969.01Pa.
bmp388: fifo 65/75.
bmp388: temperature is 27.01C.
bmp388: fifo 66/75.
bmp388: pressure is 102969.18Pa.
bmp388: fifo 67/75.
bmp388: temperature is 27.01C.
bmp388: fifo 68/75.
bmp388: pressure is 102969.24Pa.
bmp388: fifo 69/75.
bmp388: temperature is 27.01C.
bmp388: fifo 70/75.
bmp388: pressure is 102969.13Pa.
bmp388: fifo 71/75.
bmp388: temperature is 27.01C.
bmp388: fifo 72/75.
bmp388: pressure is 102969.01Pa.
bmp388: fifo 73/75.
bmp388: temperature is 27.01C.
bmp388: fifo 74/75.
bmp388: pressure is 102968.86Pa.
bmp388: fifo 75/75.
bmp388: sensortime is 149746.
bmp388: fifo 1/11.
bmp388: temperature is 27.01C.
bmp388: fifo 2/11.
bmp388: pressure is 102968.86Pa.
bmp388: fifo 3/11.
bmp388: temperature is 27.01C.
bmp388: fifo 4/11.
bmp388: pressure is 102968.97Pa.
bmp388: fifo 5/11.
bmp388: temperature is 27.01C.
bmp388: fifo 6/11.
bmp388: pressure is 102968.88Pa.
bmp388: fifo 7/11.
bmp388: temperature is 27.01C.
bmp388: fifo 8/11.
bmp388: pressure is 102968.73Pa.
bmp388: fifo 9/11.
bmp388: temperature is 27.01C.
bmp388: fifo 10/11.
bmp388: pressure is 102968.57Pa.
bmp388: fifo 11/11.
bmp388: sensortime is 161386.
bmp388: fifo 1/75.
bmp388: temperature is 27.01C.
bmp388: fifo 2/75.
bmp388: pressure is 102968.63Pa.
bmp388: fifo 3/75.
bmp388: temperature is 27.01C.
bmp388: fifo 4/75.
bmp388: pressure is 102968.59Pa.
bmp388: fifo 5/75.
bmp388: temperature is 27.01C.
bmp388: fifo 6/75.
bmp388: pressure is 102968.59Pa.
bmp388: fifo 7/75.
bmp388: temperature is 27.01C.
bmp388: fifo 8/75.
bmp388: pressure is 102968.48Pa.
bmp388: fifo 9/75.
bmp388: temperature is 27.01C.
bmp388: fifo 10/75.
bmp388: pressure is 102968.54Pa.
bmp388: fifo 11/75.
bmp388: temperature is 27.01C.
bmp388: fifo 12/75.
bmp388: pressure is 102968.57Pa.
bmp388: fifo 13/75.
bmp388: temperature is 27.02C.
bmp388: fifo 14/75.
bmp388: pressure is 102968.61Pa.
bmp388: fifo 15/75.
bmp388: temperature is 27.02C.
bmp388: fifo 16/75.
bmp388: pressure is 102968.55Pa.
bmp388: fifo 17/75.
bmp388: temperature is 27.02C.
bmp388: fifo 18/75.
bmp388: pressure is 102968.34Pa.
bmp388: fifo 19/75.
bmp388: temperature is 27.02C.
bmp388: fifo 20/75.
bmp388: pressure is 102968.21Pa.
bmp388: fifo 21/75.
bmp388: temperature is 27.02C.
bmp388: fifo 22/75.
bmp388: pressure is 102968.24Pa.
bmp388: fifo 23/75.
bmp388: temperature is 27.02C.
bmp388: fifo 24/75.
bmp388: pressure is 102968.31Pa.
bmp388: fifo 25/75.
bmp388: temperature is 27.02C.
bmp388: fifo 26/75.
bmp388: pressure is 102968.32Pa.
bmp388: fifo 27/75.
bmp388: temperature is 27.02C.
bmp388: fifo 28/75.
bmp388: pressure is 102968.30Pa.
bmp388: fifo 29/75.
bmp388: temperature is 27.02C.
bmp388: fifo 30/75.
bmp388: pressure is 102968.26Pa.
bmp388: fifo 31/75.
bmp388: temperature is 27.02C.
bmp388: fifo 32/75.
bmp388: pressure is 102968.31Pa.
bmp388: fifo 33/75.
bmp388: temperature is 27.02C.
bmp388: fifo 34/75.
bmp388: pressure is 102968.44Pa.
bmp388: fifo 35/75.
bmp388: temperature is 27.02C.
bmp388: fifo 36/75.
bmp388: pressure is 102968.38Pa.
bmp388: fifo 37/75.
bmp388: temperature is 27.02C.
bmp388: fifo 38/75.
bmp388: pressure is 102968.45Pa.
bmp388: fifo 39/75.
bmp388: temperature is 27.02C.
bmp388: fifo 40/75.
bmp388: pressure is 102968.44Pa.
bmp388: fifo 41/75.
bmp388: temperature is 27.02C.
bmp388: fifo 42/75.
bmp388: pressure is 102968.45Pa.
bmp388: fifo 43/75.
bmp388: temperature is 27.02C.
bmp388: fifo 44/75.
bmp388: pressure is 102968.43Pa.
bmp388: fifo 45/75.
bmp388: temperature is 27.02C.
bmp388: fifo 46/75.
bmp388: pressure is 102968.43Pa.
bmp388: fifo 47/75.
bmp388: temperature is 27.02C.
bmp388: fifo 48/75.
bmp388: pressure is 102968.48Pa.
bmp388: fifo 49/75.
bmp388: temperature is 27.02C.
bmp388: fifo 50/75.
bmp388: pressure is 102968.42Pa.
bmp388: fifo 51/75.
bmp388: temperature is 27.02C.
bmp388: fifo 52/75.
bmp388: pressure is 102968.49Pa.
bmp388: fifo 53/75.
bmp388: temperature is 27.02C.
bmp388: fifo 54/75.
bmp388: pressure is 102968.50Pa.
bmp388: fifo 55/75.
bmp388: temperature is 27.02C.
bmp388: fifo 56/75.
bmp388: pressure is 102968.45Pa.
bmp388: fifo 57/75.
bmp388: temperature is 27.02C.
bmp388: fifo 58/75.
bmp388: pressure is 102968.48Pa.
bmp388: fifo 59/75.
bmp388: temperature is 27.03C.
bmp388: fifo 60/75.
bmp388: pressure is 102968.46Pa.
bmp388: fifo 61/75.
bmp388: temperature is 27.03C.
bmp388: fifo 62/75.
bmp388: pressure is 102968.51Pa.
bmp388: fifo 63/75.
bmp388: temperature is 27.03C.
bmp388: fifo 64/75.
bmp388: pressure is 102968.56Pa.
bmp388: fifo 65/75.
bmp388: temperature is 27.03C.
bmp388: fifo 66/75.
bmp388: pressure is 102968.45Pa.
bmp388: fifo 67/75.
bmp388: temperature is 27.03C.
bmp388: fifo 68/75.
bmp388: pressure is 102968.48Pa.
bmp388: fifo 69/75.
bmp388: temperature is 27.03C.
bmp388: fifo 70/75.
bmp388: pressure is 102968.49Pa.
bmp388: fifo 71/75.
bmp388: temperature is 27.03C.
bmp388: fifo 72/75.
bmp388: pressure is 102968.52Pa.
bmp388: fifo 73/75.
bmp388: temperature is 27.03C.
bmp388: fifo 74/75.
bmp388: pressure is 102968.53Pa.
bmp388: fifo 75/75.
bmp388: sensortime is 235762.
bmp388: fifo 1/11.
bmp388: temperature is 27.03C.
bmp388: fifo 2/11.
bmp388: pressure is 102968.59Pa.
bmp388: fifo 3/11.
bmp388: temperature is 27.03C.
bmp388: fifo 4/11.
bmp388: pressure is 102968.58Pa.
bmp388: fifo 5/11.
bmp388: temperature is 27.03C.
bmp388: fifo 6/11.
bmp388: pressure is 102968.61Pa.
bmp388: fifo 7/11.
bmp388: temperature is 27.03C.
bmp388: fifo 8/11.
bmp388: pressure is 102968.45Pa.
bmp388: fifo 9/11.
bmp388: temperature is 27.03C.
bmp388: fifo 10/11.
bmp388: pressure is 102968.41Pa.
bmp388: fifo 11/11.
bmp388: sensortime is 247405.
bmp388: finish fifo read.
```

```shell
bmp388 -h

Usage:
  bmp388 (-i | --information)
  bmp388 (-h | --help)
  bmp388 (-p | --port)
  bmp388 (-t reg | --test=reg) [--addr=<0 | 1>] [--interface=<iic | spi>]
  bmp388 (-t read | --test=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bmp388 (-t int | --test=int) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bmp388 (-t fifo | --test=fifo) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bmp388 (-e read | --example=read) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bmp388 (-e shot | --example=shot) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bmp388 (-e int | --example=int) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]
  bmp388 (-e fifo | --example=fifo) [--addr=<0 | 1>] [--interface=<iic | spi>] [--times=<num>]

Options:
      --addr=<0 | 1>                 Set the chip iic address.([default: 0])
  -e <read | shot | int | fifo>, --example=<read | shot | int | fifo>
                                     Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --interface=<iic | spi>        Set the chip interface.([default: iic])
  -p, --port                         Display the pin connections of the current board.
  -t <reg | read | int | fifo>, --test=<reg | read | int | fifo>
                                     Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

