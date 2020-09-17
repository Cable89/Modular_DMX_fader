#include <Wire.h>
#include <MIDIUSB.h>


void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  //Serial.begin(9600);  // start serial for output
  //Serial.println("Serial.begin");
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

uint8_t val_buffer[4];
uint8_t prev_val[4];

void loop() {
  Wire.requestFrom(0x10, 4);    // request 4 bytes from slave device #16
  unsigned int i = 0;
  while (Wire.available()) { // slave may send less than requested
    uint8_t c = Wire.read(); // receive a byte
    if(i < 3){
      val_buffer[i] = c/2; // DMX module sends one byte, MIDI takes 7bits
    }
    if(i == 3){
      val_buffer[i] = c;
    }
    //Serial.print("I2C:");
    //Serial.print(c, DEC);         // print the character
    //Serial.println();
    i++;
  }
  for(int i=0; i<4; i++){
    if(val_buffer[i] != prev_val[i]){
      if(i == 3){
        for(int button=0; button<3; button++){
          if( (val_buffer[i] & (1 << button)) != (prev_val[i] & (1 << button)) ){
            if (val_buffer[i] & (1 << button)){
              noteOn(button, 42, 127);
            } else {
              noteOff(button, 42, 127);
            }
          }
        }
      } else {
        controlChange(i, 7, val_buffer[i]);
      }
      prev_val[i] = val_buffer[i];
    }
  }
  MidiUSB.flush();
  delay(1);
}
