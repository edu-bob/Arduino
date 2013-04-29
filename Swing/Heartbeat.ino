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
// This structure defines the actions, delay, and transitions for each state
//
struct {
  int onoff;
  unsigned long waitTime;
  int nextState;
} Cycle[] = {
  {1, 120, 1},
  {0, 180, 2},
  {1, 80, 3},
  {0, 600, 0}
};

void Heartbeat::setup()
{
  pinMode(PIN_HEARTBEAT, OUTPUT);
  state = 0;
  nextTime = millis();
}

void Heartbeat::loop()
{
  if ( millis() < nextTime ) return;
  digitalWrite(PIN_HEARTBEAT, Cycle[state].onoff);
  nextTime += Cycle[state].waitTime;
  state = Cycle[state].nextState;
}

