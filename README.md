# HC-12_monitor
This Arduino code allows you to remotely change the HC-12 device. 
**Remote Device Status and AT Command Control - HC12 Readme**

To monitor the status of remote devices using HC12, follow these steps:

1. Connect to one of the HC12 devices.
2. Check the status of a remote device by entering: `check deviceName`

   Replace `deviceName` with the name of the remote device you want to check.

3. Change the monitored device by entering: `change deviceName`

   Replace `deviceName` with the new name of the remote device you want to monitor.

For remotely sending AT commands, utilize the following format:

`config deviceName ATcommand`

Replace `deviceName` with the name of the target device and `ATcommand` with the specific AT command you wish to execute remotely.

**Examples of AT Commands:**

- `AT` - Test command. It should return "OK" if the AT interface is enabled.
- `AT+B57600` - Set serial port baud rate to 57600bps.
- `AT+C002` - Set radio channel to 433.8MHz.
- `AT+FUx` - Set device mode: FU1, FU2, FU3, or FU4.
- `AT+P2` - Set device transmitting power to 2dBm (1.6mW).

**Maximum Range for Different Baud Rates:**

- 1200bps ~ 1000m
- 2400bps ~ 1000m
- 4800bps ~ 500m
- 9600bps ~ 500m
- 19200bps ~ 250m
- 38400bps ~ 250m
- 57600bps ~ 100m
- 115200bps ~ 100m

**Transmitting Power Settings:**
- `AT+Px` - Set transmitting power of module, x is optional from 1 to 8
| Power Level (x) | Transmitter Power (dBm) |
|-----------------|-------------------------|
| 1               | -1 dBm                  |
| 2               | 2 dBm                   |
| 3               | 5 dBm                   |
| 4               | 8 dBm                   |
| 5               | 11 dBm                  |
| 6               | 14 dBm                  |
| 7               | 14 dBm                  |
| 8               | 20 dBm                  |

**Other Useful Commands:**

- `AT+RX` - Retrieve all parameters: mode, channel, baud rate, and power.
- `AT+V` - Retrieve module version.
- `AT+DEFAULT` - Reset module parameters to default settings.

These commands provide you with a convenient way to monitor remote devices and remotely manage them using the HC12 module. Make sure to refer to the device documentation for a comprehensive list of available AT commands and functionalities.
