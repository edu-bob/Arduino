//
// Heartbeat class, just pulses the PIN_HEARTBEAT output.
// A good use is to flash the pin 13 LED just to let you know the program is running.
//
// States:
// 0 - off, turn on, short delay
// 1 - on, turn off, short delay
// 2 - off, turn on, short delay
// 3 - on, turn off, long delay
//
// Bob Brown
// rlb@openeye.com
//

//
// This structure defines the actions and delay for each state
//
struct {
  int onoff;
  unsigned long waitTime;
} Cycle[] = {
  {1, 120},
  {0, 180},
  {1, 50},
  {0, 600}
};

void Heartbeat::setup(int _pin)
{
  pin = _pin;
  pinMode(pin, OUTPUT);
  state = 0;
  nextTime = millis();
}

void Heartbeat::loop()
{
  if ( millis() < nextTime ) return;
  digitalWrite(pin, Cycle[state].onoff);
  nextTime += Cycle[state].waitTime;
  state = (state+1) % (sizeof Cycle / sizeof Cycle[0]);
}

