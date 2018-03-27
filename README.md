# smartTrollyUsingRFID
The main of this project is to add or remove the products to the trolly with RFID cards, the amount of a particular product and total amount shown on display.

FOLLOW THESE STEPS TO UNDERSTAND THE PROJECT
Step01:
First install the arduino software which is provided in the software folder
Step02:
Install the RC-522 library in the arduino software (goto sketch>include
libraries> manage libraries >search rc-522
Step03:
First understand the block diagram and circuit diagram which are in the
cktDiag folder
Step04:
Open the code(rfidFirm.ino) provided in the firmware folder.
Compare the pin mapping between ckt diagram to the code.
Step05:
Make changes if any. Connect the arduino to the computer through a usb
cable. Upload the code into the arduino (before this select the proper
board and communication port. Go to tools > boards> select arduino-uno,
tools > com port >Select your arduino port )
Step06:
Functionality:
The RFID reader always active that can scan a card at a time. It reads
the id card then, based on the uniq id of the card the Item will be shown on
the screen(which is pre programmed_the uniq id and the information in the
card can be programmed by us). The amount and names are
preprogrammed so the applicable amount will be added or substracted
from the total amount with respect to switch provided physically.
For every card reading the buzzer activated for 100 milliseconds.
Step07:
Error Message:
If the removing item is not a part of added items then the total sum
will be wrong then the display shows wrong item error message.
Step08:
ERRORS:
PLEASE don’t remove the card from the reader shortly, it may
crashes the process.If it happened then just press the reset button on the
arduino.
 Step09:
I mapped arduino pins differently (I changed the pcb connections also for
the proper arrangement of modules but you can understand the circuit by seeing
circuit diagram)
