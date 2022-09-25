# Scoreboard

Bob Brown, rlb408, edu-bob

Arduino program for driving a four-digit scoreboard through a RS-232C interface.  
THe scoreboard comprises 7-segment displays. The interface takes line-oriented commands
where the first character is an operator (e.g. "=" means "display number").

Description of modules
- ScoreBoard.ino - main inikt and event loop program, containing the logic of communicating with the host and processing commands
- Digits.ino - logic to set numbers into the 7-segment display
- ModeSwitch.ino - driver for the internal modeswitch, with debouncing logic. The mode switch can be used to run a particular self test
