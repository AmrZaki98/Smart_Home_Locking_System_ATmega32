# Smart_Home_Locking_System_ATmega32

## The code is an implementation of the state flow diagrm shown below
![LockStateMachine](https://user-images.githubusercontent.com/90519613/200644234-de68f074-c6e2-4eb6-a1b8-e9d5e4e35f27.PNG)

### The states of the system are:

1. Locked state: This is the default state, where the door will be locked. (Using a normally closed magnet).
2. Request state: Where the user requests to open the door. In this state, the "Enter password" message is displayed on the LCD. Any number written by the user while in the "Request" state will be written in the password buffer to be compared with the password writen in the EEPROM. While in this state, the user can clear the password written and starts writing again. After the user presses "Enter", the password buffer will be compared with the password in the EEPROM.
3. Unlocked state: In case the password is written correctly by the user, the system will go to the unlocked state. In this state, the magnet will be off, and the door could be opened.
4. Update password: In case the user wants to update the password stored in the EEPROM, the system will enter this state. This is a parent state having two smaller ones in it:
      * The First password state: This is the one entered when a change password request is made. In this state, the user needs to enter the new password.
      * The second password state: After the user enters the new password, they need to verify it by typing it again. This state is responsible to request the password verfication.


### Notes:
 * Any message displayed has a content, which is a string required to be printed on the LCD, and a time out, which is the time between displaying the message on the screen and clearing it.
 * The system has two tasks:
     * LCD display task:  Take any message in the display queue and calls the display manager APIs to print it on the LCD
     * SecurityStateMachine: This task implements the state flow above to control the magnet and the LCD display by calling the appropriate APIs.
 * The tasks of the system are scheduled using freeRTOS.
