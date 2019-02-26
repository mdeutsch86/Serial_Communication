long int BAUD_RATE = 115200;
int inByte;  // incoming serial byte
bool is_connected = false; ///< True if the connection with the master is available


enum Command //here are the available commands for communication
  {
    HI = 0,
    RECIEVED = 1,
    ALREADY_CONNECTED =2, 
  };
typedef enum Command Command;



void setup() {
  // start serial port at 9600 bps:
  Serial.begin(BAUD_RATE);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  while(!is_connected)
  {
    write_cmd(HI);
    wait_for_bytes(1, 1000);
    get_messages_from_serial();
  }
}

void loop()
  {
  //get_messages_from_serial();
  }


void write_cmd(enum Command myCmd)
{
  uint8_t* Command = (uint8_t*) &myCmd;
  Serial.write(Command, sizeof(uint8_t));
}

void get_messages_from_serial()
{
  if(Serial.available() > 0)
  {
    // The first byte received is the instruction
    Command cmd_received = read_cmd();

    if(cmd_received == HI)
    {
      digitalWrite(13, HIGH);
      // If the cards haven't say hi, check the connection
      if(!is_connected)
      
      {
        is_connected = true;
        write_cmd(HI);
               
      }
      else
      {
        // If we are already connected do not send "hi" to avoid infinite loop
        write_cmd(ALREADY_CONNECTED);
      }
    }

    write_cmd(RECIEVED); // Confirm the reception
    digitalWrite(12, HIGH);
  }
}

void wait_for_bytes(int num_bytes, unsigned long timeout)
{
  unsigned long startTime = millis();
  //Wait for incoming bytes or exit if timeout
  while ((Serial.available() < num_bytes) && (millis() - startTime < timeout)){}
}

Command read_cmd()
{
  return (Command) Serial.read();
}
