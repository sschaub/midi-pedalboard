# Arduino USB Midi Pedalboard Encoder

This utility is compatible with Arduino models that support serial over USB, such as the Leonardo.
It requires the [MIDIUSB](https://www.arduino.cc/reference/en/libraries/midiusb/) library.

- Edit the `SCAN_PINS` to be the Arduino port numbers
  wired to the pedalboard matrix row pins, and `WRITE_PINS` to be the
  Arduino port numbers wired to the pedalboard matrix column pins. 
- Edit `midiMatrix` using the matrix data obtained with the `creatematrix` utility
- Set `channel` to the desired Midi output channel. Note that the output channel
  you specify here should be one less than the desired Midi channel. So if you assign
  `channel = 0`, the output will be on Midi channel 1.

