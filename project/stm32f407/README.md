### 1. Chip

#### 1.1 Chip Info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

spi pin: SCK/MISO/MOSI/CS  PA5/PA6/PA7/PA4.

gpio pin: INT PB0.

### 2. Shell

#### 2.1 Shell Parameter

baud rate: 115200.

data bits : 8.

stop bits: 1.

parity: none.

flow control: none.

### 3. BMP388

#### 3.1 Command Instruction

​          bmp388 is a basic command which can test all bmp388 driver function:

​           -i        show bmp388 chip and driver information.

​           -h       show bmp388 help.

​           -p       show bmp388 pin connections of the current board.

​           -t (reg (-iic | -spi) -a (0 | 1) | read <times> (-iic | -spi) -a (0 | 1)  | int  <times> (-iic | -spi) -a (0 | 1) | fifo  <times> (-iic | -spi) -a (0 | 1))

​           -t reg (-iic | -spi) -a (0 | 1)        run bmp388 register test. 

​           -t read <times> (-iic | -spi) -a (0 | 1)        run bmp388 read test. times means the test times. 

​           -t int <times> (-iic | -spi) -a (0 | 1)        run bmp388 interrupt test. times means the test times. 

​           -t fifo <times> (-iic | -spi) -a (0 | 1)        run bmp388 fifo test. times means the test times. 

​           -c (read <times> (-iic | -spi) -a (0 | 1) | shot <times> (-iic | -spi) -a (0 | 1) | int <times> (-iic | -spi) -a (0 | 1) | fifo <times> (-iic | -spi) -a (0 | 1) )

​           -c read <times> (-iic | -spi) -a (0 | 1)        run bmp388 read function. times means the read times. 

​           -c shot <times> (-iic | -spi) -a (0 | 1)        run bmp388 shot function. times means the read times. 

​           -c int <times> (-iic | -spi) -a (0 | 1)        run bmp388 interrupt function. times means the read times. 

​           -c fifo <times> (-iic | -spi) -a (0 | 1)        run bmp388 fifo function. times means the read times. 

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
bmp388 -t reg -spi -a 0

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
bmp388: check mode ok.
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
bmp388: sensortime is 0x001E66.
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
bmp388 -t read 3 -spi -a 0

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
bmp388: temperature is 27.14c.
bmp388: pressure is 102571.11pa.
bmp388: temperature is 27.14c.
bmp388: pressure is 102570.99pa.
bmp388: temperature is 27.14c.
bmp388: pressure is 102570.83pa.
bmp388: normal mode read test.
bmp388: temperature is 27.36c.
bmp388: pressure is 102556.73pa.
bmp388: temperature is 27.39c.
bmp388: pressure is 102555.52pa.
bmp388: temperature is 27.41c.
bmp388: pressure is 102555.84pa.
bmp388: finish read test.
```

```shell
bmp388 -t int 3 -spi -a 0

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
bmp388: temperature is 27.42c.
bmp388: pressure is 102560.72pa.
bmp388: temperature is 27.53c.
bmp388: pressure is 102556.27pa.
bmp388: temperature is 27.54c.
bmp388: pressure is 102555.51pa.
bmp388: finish interrupt test.
```

```shell
bmp388 -t fifo 3 -spi -a 0

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
bmp388 -c read 3 -spi -a 0

bmp388: 1/3.
bmp388: temperature is 28.03C.
bmp388: pressure is 102563.48Pa.
bmp388: 2/3.
bmp388: temperature is 28.07C.
bmp388: pressure is 102562.90Pa.
bmp388: 3/3.
bmp388: temperature is 28.08C.
bmp388: pressure is 102562.76Pa.
```

```shell
bmp388 -c shot 3 -spi -a 0

bmp388: 1/3.
bmp388: temperature is 27.76C.
bmp388: pressure is 102577.23Pa.
bmp388: 2/3.
bmp388: temperature is 27.76C.
bmp388: pressure is 102577.16Pa.
bmp388: 3/3.
bmp388: temperature is 27.76C.
bmp388: pressure is 102577.59Pa.
```

```shell
bmp388 -c int 3 -spi -a 0

bmp388: 1/3.
bmp388: temperature is 27.24C.
bmp388: pressure is 102567.33Pa.
bmp388: 2/3.
bmp388: temperature is 27.27C.
bmp388: pressure is 102565.65Pa.
bmp388: 3/3.
bmp388: temperature is 27.33C.
bmp388: pressure is 102561.62Pa.
```

```shell
bmp388 -c fifo 3 -spi -a 0

bmp388: fifo 1/1.
bmp388: sensortime is 74003.
bmp388: fifo 1/75.
bmp388: temperature is 27.74C.
bmp388: fifo 2/75.
bmp388: pressure is 102544.24Pa.
bmp388: fifo 3/75.
bmp388: temperature is 27.74C.
bmp388: fifo 4/75.
bmp388: pressure is 102544.46Pa.
bmp388: fifo 5/75.
bmp388: temperature is 27.74C.
bmp388: fifo 6/75.
bmp388: pressure is 102544.32Pa.
bmp388: fifo 7/75.
bmp388: temperature is 27.74C.
bmp388: fifo 8/75.
bmp388: pressure is 102544.07Pa.
bmp388: fifo 9/75.
bmp388: temperature is 27.74C.
bmp388: fifo 10/75.
bmp388: pressure is 102544.26Pa.
bmp388: fifo 11/75.
bmp388: temperature is 27.74C.
bmp388: fifo 12/75.
bmp388: pressure is 102543.92Pa.
bmp388: fifo 13/75.
bmp388: temperature is 27.74C.
bmp388: fifo 14/75.
bmp388: pressure is 102544.07Pa.
bmp388: fifo 15/75.
bmp388: temperature is 27.74C.
bmp388: fifo 16/75.
bmp388: pressure is 102544.20Pa.
bmp388: fifo 17/75.
bmp388: temperature is 27.74C.
bmp388: fifo 18/75.
bmp388: pressure is 102544.71Pa.
bmp388: fifo 19/75.
bmp388: temperature is 27.74C.
bmp388: fifo 20/75.
bmp388: pressure is 102544.90Pa.
bmp388: fifo 21/75.
bmp388: temperature is 27.74C.
bmp388: fifo 22/75.
bmp388: pressure is 102545.38Pa.
bmp388: fifo 23/75.
bmp388: temperature is 27.74C.
bmp388: fifo 24/75.
bmp388: pressure is 102545.42Pa.
bmp388: fifo 25/75.
bmp388: temperature is 27.74C.
bmp388: fifo 26/75.
bmp388: pressure is 102544.96Pa.
bmp388: fifo 27/75.
bmp388: temperature is 27.74C.
bmp388: fifo 28/75.
bmp388: pressure is 102544.51Pa.
bmp388: fifo 29/75.
bmp388: temperature is 27.74C.
bmp388: fifo 30/75.
bmp388: pressure is 102544.64Pa.
bmp388: fifo 31/75.
bmp388: temperature is 27.75C.
bmp388: fifo 32/75.
bmp388: pressure is 102544.95Pa.
bmp388: fifo 33/75.
bmp388: temperature is 27.75C.
bmp388: fifo 34/75.
bmp388: pressure is 102544.76Pa.
bmp388: fifo 35/75.
bmp388: temperature is 27.75C.
bmp388: fifo 36/75.
bmp388: pressure is 102544.40Pa.
bmp388: fifo 37/75.
bmp388: temperature is 27.75C.
bmp388: fifo 38/75.
bmp388: pressure is 102544.09Pa.
bmp388: fifo 39/75.
bmp388: temperature is 27.75C.
bmp388: fifo 40/75.
bmp388: pressure is 102543.14Pa.
bmp388: fifo 41/75.
bmp388: temperature is 27.75C.
bmp388: fifo 42/75.
bmp388: pressure is 102543.49Pa.
bmp388: fifo 43/75.
bmp388: temperature is 27.75C.
bmp388: fifo 44/75.
bmp388: pressure is 102544.12Pa.
bmp388: fifo 45/75.
bmp388: temperature is 27.75C.
bmp388: fifo 46/75.
bmp388: pressure is 102544.66Pa.
bmp388: fifo 47/75.
bmp388: temperature is 27.75C.
bmp388: fifo 48/75.
bmp388: pressure is 102544.75Pa.
bmp388: fifo 49/75.
bmp388: temperature is 27.75C.
bmp388: fifo 50/75.
bmp388: pressure is 102544.75Pa.
bmp388: fifo 51/75.
bmp388: temperature is 27.75C.
bmp388: fifo 52/75.
bmp388: pressure is 102544.89Pa.
bmp388: fifo 53/75.
bmp388: temperature is 27.75C.
bmp388: fifo 54/75.
bmp388: pressure is 102545.13Pa.
bmp388: fifo 55/75.
bmp388: temperature is 27.75C.
bmp388: fifo 56/75.
bmp388: pressure is 102545.30Pa.
bmp388: fifo 57/75.
bmp388: temperature is 27.76C.
bmp388: fifo 58/75.
bmp388: pressure is 102545.94Pa.
bmp388: fifo 59/75.
bmp388: temperature is 27.76C.
bmp388: fifo 60/75.
bmp388: pressure is 102545.20Pa.
bmp388: fifo 61/75.
bmp388: temperature is 27.76C.
bmp388: fifo 62/75.
bmp388: pressure is 102545.24Pa.
bmp388: fifo 63/75.
bmp388: temperature is 27.76C.
bmp388: fifo 64/75.
bmp388: pressure is 102545.43Pa.
bmp388: fifo 65/75.
bmp388: temperature is 27.76C.
bmp388: fifo 66/75.
bmp388: pressure is 102545.28Pa.
bmp388: fifo 67/75.
bmp388: temperature is 27.76C.
bmp388: fifo 68/75.
bmp388: pressure is 102545.37Pa.
bmp388: fifo 69/75.
bmp388: temperature is 27.76C.
bmp388: fifo 70/75.
bmp388: pressure is 102545.12Pa.
bmp388: fifo 71/75.
bmp388: temperature is 27.76C.
bmp388: fifo 72/75.
bmp388: pressure is 102545.15Pa.
bmp388: fifo 73/75.
bmp388: temperature is 27.76C.
bmp388: fifo 74/75.
bmp388: pressure is 102545.09Pa.
bmp388: fifo 75/75.
bmp388: sensortime is 149593.
bmp388: fifo 1/9.
bmp388: temperature is 27.76C.
bmp388: fifo 2/9.
bmp388: pressure is 102545.64Pa.
bmp388: fifo 3/9.
bmp388: temperature is 27.77C.
bmp388: fifo 4/9.
bmp388: pressure is 102545.91Pa.
bmp388: fifo 5/9.
bmp388: temperature is 27.77C.
bmp388: fifo 6/9.
bmp388: pressure is 102545.67Pa.
bmp388: fifo 7/9.
bmp388: temperature is 27.77C.
bmp388: fifo 8/9.
bmp388: pressure is 102546.00Pa.
bmp388: fifo 9/9.
bmp388: sensortime is 158375.
bmp388: fifo 1/75.
bmp388: temperature is 27.76C.
bmp388: fifo 2/75.
bmp388: pressure is 102545.72Pa.
bmp388: fifo 3/75.
bmp388: temperature is 27.77C.
bmp388: fifo 4/75.
bmp388: pressure is 102545.95Pa.
bmp388: fifo 5/75.
bmp388: temperature is 27.77C.
bmp388: fifo 6/75.
bmp388: pressure is 102545.63Pa.
bmp388: fifo 7/75.
bmp388: temperature is 27.77C.
bmp388: fifo 8/75.
bmp388: pressure is 102545.56Pa.
bmp388: fifo 9/75.
bmp388: temperature is 27.77C.
bmp388: fifo 10/75.
bmp388: pressure is 102545.54Pa.
bmp388: fifo 11/75.
bmp388: temperature is 27.77C.
bmp388: fifo 12/75.
bmp388: pressure is 102545.30Pa.
bmp388: fifo 13/75.
bmp388: temperature is 27.77C.
bmp388: fifo 14/75.
bmp388: pressure is 102545.71Pa.
bmp388: fifo 15/75.
bmp388: temperature is 27.77C.
bmp388: fifo 16/75.
bmp388: pressure is 102546.06Pa.
bmp388: fifo 17/75.
bmp388: temperature is 27.77C.
bmp388: fifo 18/75.
bmp388: pressure is 102546.06Pa.
bmp388: fifo 19/75.
bmp388: temperature is 27.77C.
bmp388: fifo 20/75.
bmp388: pressure is 102546.33Pa.
bmp388: fifo 21/75.
bmp388: temperature is 27.77C.
bmp388: fifo 22/75.
bmp388: pressure is 102546.18Pa.
bmp388: fifo 23/75.
bmp388: temperature is 27.77C.
bmp388: fifo 24/75.
bmp388: pressure is 102546.64Pa.
bmp388: fifo 25/75.
bmp388: temperature is 27.77C.
bmp388: fifo 26/75.
bmp388: pressure is 102546.66Pa.
bmp388: fifo 27/75.
bmp388: temperature is 27.77C.
bmp388: fifo 28/75.
bmp388: pressure is 102545.98Pa.
bmp388: fifo 29/75.
bmp388: temperature is 27.77C.
bmp388: fifo 30/75.
bmp388: pressure is 102546.31Pa.
bmp388: fifo 31/75.
bmp388: temperature is 27.78C.
bmp388: fifo 32/75.
bmp388: pressure is 102546.63Pa.
bmp388: fifo 33/75.
bmp388: temperature is 27.78C.
bmp388: fifo 34/75.
bmp388: pressure is 102546.66Pa.
bmp388: fifo 35/75.
bmp388: temperature is 27.78C.
bmp388: fifo 36/75.
bmp388: pressure is 102546.90Pa.
bmp388: fifo 37/75.
bmp388: temperature is 27.78C.
bmp388: fifo 38/75.
bmp388: pressure is 102546.52Pa.
bmp388: fifo 39/75.
bmp388: temperature is 27.77C.
bmp388: fifo 40/75.
bmp388: pressure is 102545.66Pa.
bmp388: fifo 41/75.
bmp388: temperature is 27.77C.
bmp388: fifo 42/75.
bmp388: pressure is 102545.67Pa.
bmp388: fifo 43/75.
bmp388: temperature is 27.78C.
bmp388: fifo 44/75.
bmp388: pressure is 102546.13Pa.
bmp388: fifo 45/75.
bmp388: temperature is 27.78C.
bmp388: fifo 46/75.
bmp388: pressure is 102546.42Pa.
bmp388: fifo 47/75.
bmp388: temperature is 27.78C.
bmp388: fifo 48/75.
bmp388: pressure is 102546.42Pa.
bmp388: fifo 49/75.
bmp388: temperature is 27.78C.
bmp388: fifo 50/75.
bmp388: pressure is 102546.53Pa.
bmp388: fifo 51/75.
bmp388: temperature is 27.78C.
bmp388: fifo 52/75.
bmp388: pressure is 102546.40Pa.
bmp388: fifo 53/75.
bmp388: temperature is 27.78C.
bmp388: fifo 54/75.
bmp388: pressure is 102546.28Pa.
bmp388: fifo 55/75.
bmp388: temperature is 27.78C.
bmp388: fifo 56/75.
bmp388: pressure is 102546.41Pa.
bmp388: fifo 57/75.
bmp388: temperature is 27.78C.
bmp388: fifo 58/75.
bmp388: pressure is 102546.38Pa.
bmp388: fifo 59/75.
bmp388: temperature is 27.78C.
bmp388: fifo 60/75.
bmp388: pressure is 102546.92Pa.
bmp388: fifo 61/75.
bmp388: temperature is 27.78C.
bmp388: fifo 62/75.
bmp388: pressure is 102546.47Pa.
bmp388: fifo 63/75.
bmp388: temperature is 27.78C.
bmp388: fifo 64/75.
bmp388: pressure is 102546.49Pa.
bmp388: fifo 65/75.
bmp388: temperature is 27.78C.
bmp388: fifo 66/75.
bmp388: pressure is 102546.20Pa.
bmp388: fifo 67/75.
bmp388: temperature is 27.78C.
bmp388: fifo 68/75.
bmp388: pressure is 102546.26Pa.
bmp388: fifo 69/75.
bmp388: temperature is 27.78C.
bmp388: fifo 70/75.
bmp388: pressure is 102546.20Pa.
bmp388: fifo 71/75.
bmp388: temperature is 27.78C.
bmp388: fifo 72/75.
bmp388: pressure is 102545.98Pa.
bmp388: fifo 73/75.
bmp388: temperature is 27.78C.
bmp388: fifo 74/75.
bmp388: pressure is 102546.12Pa.
bmp388: fifo 75/75.
bmp388: sensortime is 233561.
bmp388: fifo 1/9.
bmp388: temperature is 27.78C.
bmp388: fifo 2/9.
bmp388: pressure is 102545.81Pa.
bmp388: fifo 3/9.
bmp388: temperature is 27.78C.
bmp388: fifo 4/9.
bmp388: pressure is 102546.12Pa.
bmp388: fifo 5/9.
bmp388: temperature is 27.78C.
bmp388: fifo 6/9.
bmp388: pressure is 102545.91Pa.
bmp388: fifo 7/9.
bmp388: temperature is 27.79C.
bmp388: fifo 8/9.
bmp388: pressure is 102546.22Pa.
bmp388: fifo 9/9.
bmp388: sensortime is 242347.
bmp388: finish fifo read.
```

```shell
bmp388 -h

bmp388 -i
	show bmp388 chip and driver information.
bmp388 -h
	show bmp388 help.
bmp388 -p
	show bmp388 pin connections of the current board.
bmp388 -t reg (-iic | -spi) -a (0 | 1)
	run bmp388 register test.
bmp388 -t read <times> (-iic | -spi) -a (0 | 1)
	run bmp388 read test.times means the test times.
bmp388 -t int <times> (-iic | -spi) -a (0 | 1)
	run bmp388 interrupt test.times means the test times.
bmp388 -t fifo <times> (-iic | -spi) -a (0 | 1)
	run bmp388 fifo test.times means the test times.
bmp388 -c read <times> (-iic | -spi) -a (0 | 1)
	run bmp388 read function.times means the read times.
bmp388 -c shot <times> (-iic | -spi) -a (0 | 1)
	run bmp388 shot function.times means the read times.
bmp388 -c int <times> (-iic | -spi) -a (0 | 1)
	run bmp388 interrupt function.times means the read times.
bmp388 -c fifo <times> (-iic | -spi) -a (0 | 1)
	run bmp388 fifo function.times means the read times.
```

