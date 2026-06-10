# I2C LCD Address Guide

## Overview

Most 16x2 and 20x4 LCD modules with an I2C backpack use a PCF8574 I/O expander to communicate with a microcontroller over the I2C bus.

Many tutorials use the default I2C address and do not explain that the address can be changed using the A0, A1, and A2 address selection pads available on the back of the I2C backpack. By modifying these address bits, multiple LCD modules can share the same SDA and SCL lines and operate independently using a single microcontroller.

This repository documents the address modification process, explains how the address is generated, and provides Arduino examples for detecting and using multiple LCDs on the same I2C bus.

---

## Motivation

While experimenting with I2C LCD modules, I found that most resources focus only on the default address and rarely explain how the address selection pads work. This project was created to document the address combinations available on a typical PCF8574 LCD backpack and demonstrate how multiple LCD modules can be connected and controlled simultaneously.

---

## Features

- Explanation of PCF8574 address selection
- Address mapping for A0, A1, and A2 combinations
- Hardware modification guide
- I2C scanner example
- Automatic LCD address detection
- Multiple LCD operation on a single I2C bus
- Arduino Nano compatible examples

---

## Hardware Required

- Arduino Nano (or any compatible Arduino board)
- 16x2 or 20x4 LCD with I2C backpack
- Jumper wires
- USB cable
- Soldering iron
- Solder

---

## Understanding the I2C Backpack

The LCD itself is not an I2C device.

The small board attached to the back of the LCD contains a PCF8574 I/O expander. This chip converts I2C commands into the parallel signals required by the LCD.

The PCF8574 provides three configurable address bits:

- A0
- A1
- A2

These three bits determine the final I2C address of the module.

Since there are three configurable bits, there are:

2³ = 8 possible address combinations

This allows up to eight LCD modules to share the same SDA and SCL lines while being individually addressed by the microcontroller.

---

## Address Logic

The PCF8574 address format is:

```text
0100 A2 A1 A0
```

The first four bits are fixed by the device.

The last three bits are controlled by the A0, A1, and A2 solder pads on the I2C backpack.

On many commonly available LCD backpacks:

- Open pad = Logic 1
- Shorted pad = Logic 0

The default configuration is usually:

```text
A2 = 1
A1 = 1
A0 = 1
```

Which results in:

```text
0100111 = 0x27
```

Changing the state of A0, A1, and A2 changes the final address.

---

## Address Mapping

The following table is based on a commonly used PCF8574 I2C LCD backpack.

| A2 | A1 | A0 | I2C Address |
|----|----|----|-------------|
| 1 | 1 | 1 | 0x27 |
| 1 | 1 | 0 | 0x26 |
| 1 | 0 | 1 | 0x25 |
| 1 | 0 | 0 | 0x24 |
| 0 | 1 | 1 | 0x23 |
| 0 | 1 | 0 | 0x22 |
| 0 | 0 | 1 | 0x21 |
| 0 | 0 | 0 | 0x20 |

**Note:** Address mapping may vary depending on the PCF8574 variant used on the module. Always verify the address using an I2C scanner after making modifications.

---

## Modifying the Address

Locate the address selection pads on the back of the I2C backpack.

The pads are usually labelled:

```text
A0
A1
A2
```

Creating a solder bridge across a pad changes the corresponding address bit.

Examples:

| Modification | Resulting Address |
|-------------|------------------|
| Default | 0x27 |
| A0 Shorted | 0x26 |
| A1 Shorted | 0x25 |
| A2 Shorted | 0x23 |
| A0 + A1 Shorted | 0x24 |
| A0 + A2 Shorted | 0x22 |
| A1 + A2 Shorted | 0x21 |
| A0 + A1 + A2 Shorted | 0x20 |

Verify the new address using the scanner example provided in this repository.

---

## Arduino Nano Connections

| Arduino Nano | LCD I2C Backpack |
|-------------|------------------|
| 5V | VCC |
| GND | GND |
| A4 | SDA |
| A5 | SCL |

---

## Finding the I2C Address

The repository contains an I2C scanner example that scans the bus and displays all detected I2C devices through the Serial Monitor.

Example output:

```text
I2C Scanner
Device found at 0x27
```

After modifying the address:

```text
I2C Scanner
Device found at 0x26
```

---

## Displaying the Address on the LCD

The repository also includes an example that:

1. Scans the I2C bus
2. Detects the LCD address
3. Initializes the LCD
4. Displays the detected address on the LCD

Example display:

```text
LCD Address:
0x27
```

---

## Using Multiple LCDs

Multiple LCD modules can be connected in parallel on the same I2C bus.

Example configuration:

| LCD | Address |
|------|---------|
| LCD 1 | 0x27 |
| LCD 2 | 0x26 |
| LCD 3 | 0x25 |

All modules share:

```text
SDA
SCL
VCC
GND
```

The microcontroller communicates with each LCD using its unique address.

Example:

```cpp
LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x26, 16, 2);
LiquidCrystal_I2C lcd3(0x25, 16, 2);
```

Each LCD can display different information while using the same I2C bus.

---
## Limitations

The I2C scanner detects all devices connected to the I2C bus.

For example:

| Device | Address |
|----------|---------|
| LCD | 0x27 |
| OLED Display | 0x3C |
| RTC Module | 0x68 |

If multiple I2C device types are connected, the scanner will detect all of them. The example sketches assume that the detected devices are LCD modules.

---

## Tested Configuration

- Arduino Nano
- Arduino Uno
- 16x2 LCD
- PCF8574 I2C Backpack
- Arduino IDE 2.x

---

## License

This project is provided for educational and learning purposes. Feel free to use, modify, and distribute it.

---

## Author

This repository was created to document and demonstrate how the A0, A1, and A2 address selection pads on a PCF8574 I2C LCD backpack can be used to generate multiple unique addresses and operate several LCD modules on the same I2C bus.
