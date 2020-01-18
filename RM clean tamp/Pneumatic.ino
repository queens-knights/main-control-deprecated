String num;
int Relay[4] = {6,7,8,9};
void setup() {
  // put your setup code here, to run once:
int z =0;

while(z<4)
{
  pinMode(Relay[z], OUTPUT);    //initialize all relays to low, writing high is low relay
  digitalWrite(Relay[z], HIGH);
  z++;
}
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  if(i ==4)
  {
    i=0;
  }
  digitalWrite(Relay[i], LOW); //test stuff
  delay(1000);
  digitalWrite(Relay[i], HIGH);
   delay(1000);
   i++;
   */

int i =0;
if( Serial.available()==4)  //once received 4 digit serial
{
  num = Serial.readString();
  Serial.println(num);
  while(i<4)
  {
    if (num[i] == '1')  //going through characters in serial string if 1 turn on else off
    {
    digitalWrite(Relay[i], LOW);
    }
    else
    {
    digitalWrite(Relay[i], HIGH);
    }
     i++;
  }
  
}

}
