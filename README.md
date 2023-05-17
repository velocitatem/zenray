# Zenray

*BRIGHTEN YOUR MIND*

A portable light therapy device that uses researched frequencies to lessen users' anxiety, depression and insomnia symptoms. We will use a device consisting of 9-12 white led lights, controlled by arduino and program 2-3 presets for our MVP that focus on different areas (amusement and stress relief, insomnia relief). The programmes will be based on extensive research in the area that has been carried out since the 70s, our unique selling point is that the device is affordable and portable (similar solutions cost up to 2000 euros on the market right now and are tedious to set up), possibly syncable with music.



## Components

All the components in a table:
| Component           | Quantity |
|---------------------|----------|
| MAX72xx             | 2        |
| Red LED             | 1        |
| Yellow LED          | 1        |
| $1k\omega$ Resistor | 3        |
| Photo-resistor      | 1        |
| NPN Transistor      | 1        |
| Jumper Buses        | 25       |
| Simple Jumpers      | 10       |
| Breadboards         | 1-2      |
| Cardboard Headset   | 1        |
| ESP 32              | 1        |

**Total Cost:** ~38 Euros

## Circuit Diagrams
![arduino](./circuit_ard.svg)

![led](./circuit_led.svg)

## Code

All the necessary code to flash is in `program.ino`. Once you flash the code, you should check the *serial console* for the connection IP. Then you can connect to the device via the browser and navigate to the `/` endpoint to see the main page. All will be explained there.
