# Arduino Midi Pedalboard Encoder

This Arduino utility encodes matrix-style organ pedalboards to Midi data. It
is compatible with most Arduino models. It is designed to be used with
an Arduino that has a Midi port connected to the Arduino's serial
output pin. I have tested it with Arduino Mega and Leonardo models.

Configure it as follows:

- Edit the `SCAN_PINS` to be the Arduino port numbers
  wired to the pedalboard matrix row pins, and `WRITE_PINS` to be the
  Arduino port numbers wired to the pedalboard matrix column pins. 
- Edit `midiMatrix` using the matrix data obtained with the `creatematrix` utility
- Set `channel` to the desired Midi output channel. Note that the output channel
  you specify here should be one less than the desired Midi channel. So if you assign
  `channel = 0`, the output will be on Midi channel 1.


