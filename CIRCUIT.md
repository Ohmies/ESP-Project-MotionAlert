# Circuit Diagram

## ESP32 to PIR Sensor Connection

```
ESP32 DevKit               PIR Sensor (HC-SR501)
+----------+               +------------------+
|          |               |                  |
|     3.3V |<------------->| VCC              |
|      GND |<------------->| GND              |
|    GPIO4 |<------------->| OUT              |
|          |               |                  |
+----------+               +------------------+
```

## Detailed Pin Mapping

| ESP32 Pin | PIR Pin | Wire Color (Suggested) | Function |
|-----------|---------|------------------------|----------|
| 3.3V      | VCC     | Red                    | Power Supply |
| GND       | GND     | Black                  | Ground |
| GPIO4     | OUT     | Yellow/Orange          | Signal Output |

## PIR Sensor Settings

The HC-SR501 PIR sensor has two potentiometers:

### Sensitivity Adjustment (Sx)
- **Clockwise**: Increase sensitivity (up to 7 meters)
- **Counter-clockwise**: Decrease sensitivity (down to 3 meters)

### Time Delay Adjustment (Tx)
- **Clockwise**: Increase delay time (up to 300 seconds)
- **Counter-clockwise**: Decrease delay time (down to 5 seconds)

## Jumper Settings

The PIR sensor has a jumper that controls the trigger mode:

- **H Position**: Repeatable trigger mode (recommended for this project)
- **L Position**: Single trigger mode

## Power Requirements

- **ESP32**: 3.3V - 5V (can be powered via USB or external supply)
- **PIR Sensor**: 4.5V - 20V (typically 5V)
- **Current Consumption**: ~65mA (ESP32) + ~50µA (PIR standby)

## Optional Components

### Pull-up Resistor
- A 10kΩ pull-up resistor can be added between GPIO4 and 3.3V for more stable readings
- ESP32 has internal pull-up resistors, so this is usually not necessary

### LED Indicator
- Connect an LED with 220Ω resistor to GPIO2 for visual motion indication
- Anode to GPIO2, Cathode to GND through resistor

### Breadboard Layout Example

```
Breadboard Layout:
+-----+-----+-----+-----+-----+
|     | VCC | GND | OUT |     |
| PIR +-----+-----+-----+     |
|     |  R  |  B  |  Y  |     |
+-----+--|--+--|--+--|--+-----+
         |     |     |
      3.3V   GND   GPIO4
         |     |     |
    +----+-----+-----+----+
    |    ESP32 DevKit     |
    +--------------------+
```

## Safety Notes

- Always connect GND first, then VCC, then signal pins
- Double-check connections before powering on
- Use appropriate wire gauge for power connections
- Keep connections as short as possible to reduce noise
