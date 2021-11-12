
// Connect ESP32 to Modules
int SER_Pin = 21;   //pin 14 on the 75HC595
int RCLK_Pin = 23;  //pin 12 on the 75HC595h
int SRCLK_Pin = 22; //pin 11 on the 75HC595

// Wifi Details

#include "headers.h"   //all misc. headers and functions
#include "MQTTFuncs.h" //MQTT related functions

// char ssid[] = "SKY9C5DC"; // Your Wi-Fi Credentials
// char pass[] = "UTWVDVFS";

char ssid[] = "3STechLabs"; // Your Wi-Fi Credentials
char pass[] = "%@3stech@nauman%";

TaskHandle_t Twitter;
Neotimer twitterGetTimer = Neotimer(2000); // Set timer's preset

String message = "HELLO"; // This is the message that will be displayed
//How many of the shift registers - change this
#define number_of_74hc595s 1

//Number of pins per shift register
#define numOfRegisterPins number_of_74hc595s * 8
boolean registers[numOfRegisterPins];

//set all register pins to LOW
void loopFunction(void *pvParameters);
void clearRegisters()
{
  for (int i = numOfRegisterPins - 1; i >= 0; i--)
  {
    registers[i] = LOW;
  }
}

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters()
{
  digitalWrite(RCLK_Pin, LOW);
  for (int i = numOfRegisterPins - 1; i >= 0; i--)
  {
    digitalWrite(SRCLK_Pin, LOW);
    int val = registers[i];
    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value)
{
  registers[index] = value;
}

////////////////////////////////////////////////////////////////////
//declare variables for the motor pins
int motorPin1 = 0; // Blue   - 28BYJ48 pin 1
int motorPin2 = 1; // Pink   - 28BYJ48 pin 2
int motorPin3 = 2; // Yellow - 28BYJ48 pin 3
int motorPin4 = 3; // Orange - 28BYJ48 pin 4

int motorPin5 = 4; // Blue   - 28BYJ48 pin 1
int motorPin6 = 5; // Pink   - 28BYJ48 pin 2
int motorPin7 = 6; // Yellow - 28BYJ48 pin 3
int motorPin8 = 7; // Orange - 28BYJ48 pin 4

int motorPin9 = 8;   // Blue   - 28BYJ48 pin 1
int motorPin10 = 9;  // Pink   - 28BYJ48 pin 2
int motorPin11 = 10; // Yellow - 28BYJ48 pin 3
int motorPin12 = 11; // Orange - 28BYJ48 pin 4

int motorPin13 = 12; // Blue   - 28BYJ48 pin 1
int motorPin14 = 13; // Pink   - 28BYJ48 pin 2
int motorPin15 = 14; // Yellow - 28BYJ48 pin 3
int motorPin16 = 15; // Orange - 28BYJ48 pin 4

int motorPin17 = 16; // Blue   - 28BYJ48 pin 1
int motorPin18 = 17; // Pink   - 28BYJ48 pin 2
int motorPin19 = 18; // Yellow - 28BYJ48 pin 3
int motorPin20 = 19; // Orange - 28BYJ48 pin 4

int motorPin21 = 20; // Blue   - 28BYJ48 pin 1
int motorPin22 = 21; // Pink   - 28BYJ48 pin 2
int motorPin23 = 22; // Yellow - 28BYJ48 pin 3
int motorPin24 = 23; // Orange - 28BYJ48 pin 4

int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int s8;
int s9;
int s10;
int s11;
int s12;

int m1;
int m2;
int m3;
int m4;
int m5;
int m6;
int m7;
int m8;
int m9;
int m10;
int m11;
int m12;

int r1;
int r2;
int r3;
int r4;
int r5;
int r6;
int r7;
int r8;
int r9;
int r10;
int r11;
int r12;

//////////////////////////////////////////////////////////////////////////////
void connectToWiFi()
{
  int TryCount = 0;
  //log_i( "connect to wifi" );
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    TryCount++;

    
    Serial.print(".");
    delay(1000);
    if (TryCount == 20)
    {
      ESP.restart();
    }
  }
  // WiFi.onEvent( WiFiEvent );
}
void setup()
{

  Serial.begin(9600);

  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

  //reset all register pins
  clearRegisters();
  writeRegisters();

  // Connect to WIFI
  Serial.print("Connecting to ");
  connectToWiFi();
  Serial.println("WiFi connected");
  mqttConnect(); //start mqtt

  xTaskCreatePinnedToCore(
      loopFunction, /* Task function. */
      "Twitter",    /* name of task. */
      10000,        /* Stack size of task */
      NULL,         /* parameter of the task */
      1,            /* priority of the task */
      &Twitter,     /* Task handle to keep track of created task */
      1);
  delay(500);
  setHashTag("football"); //to set the hastag
}

void loopFunction(void *pvParameters)
{
  mqttClient.setKeepAlive( 90 );

  for (;;)
  {
    // message = getLastTweet(); //returns a string of latest tweet of the set hashtag
    if ((wclient.connected()) && (WiFi.status() == WL_CONNECTED))
    {
      // if (twitterGetTimer.repeat())
      // {
      Serial.println(getLastTweet());
      //}
      if (!mqttClient.connected())
      {
        reconnect();
      }
      mqttClient.loop();
    }
    else if (!(WiFi.status() == WL_CONNECTED))
    {
      //connect to wifi then connect to mqtt here
      WiFi.disconnect();
      connectToWiFi();
    }
    if (WiFi.status() == WL_IDLE_STATUS)
    {
      ESP.restart();

      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);
    // delay(50);
  }
}
//////////////////////////////////////////////////////////////////////////////
void loop()
{

  s1 = toupper(message[0]) - '@';
  s2 = toupper(message[1]) - '@';
  s3 = toupper(message[2]) - '@';
  s4 = toupper(message[3]) - '@';
  s5 = toupper(message[4]) - '@';
  s6 = toupper(message[5]) - '@';
  s7 = toupper(message[6]) - '@';
  s8 = toupper(message[7]) - '@';
  s9 = toupper(message[8]) - '@';
  s10 = toupper(message[9]) - '@';
  s11 = toupper(message[10]) - '@';
  s12 = toupper(message[11]) - '@';

  s1 = (s1 * 102.4 + 4) / 8;
  s2 = (s2 * 102.4 + 4) / 8;
  s3 = (s3 * 102.4 + 4) / 8;
  s4 = (s4 * 102.4 + 4) / 8;
  s5 = (s5 * 102.4 + 4) / 8;
  s6 = (s6 * 102.4 + 4) / 8;
  s7 = (s7 * 102.4 + 4) / 8;
  s8 = (s8 * 102.4 + 4) / 8;
  s9 = (s9 * 102.4 + 4) / 8;
  s10 = (s10 * 102.4 + 4) / 8;
  s11 = (s11 * 102.4 + 4) / 8;
  s12 = (s12 * 102.4 + 4) / 8;

  m1 = s1 * 8;
  m2 = s2 * 8;
  m3 = s3 * 8;
  m4 = s4 * 8;
  m5 = s5 * 8;
  m6 = s6 * 8;
  m7 = s7 * 8;
  m8 = s8 * 8;
  m9 = s9 * 8;
  m10 = s10 * 8;
  m11 = s11 * 8;
  m12 = s12 * 8;

  r1 = 4096 - m1;
  r2 = 4096 - m2;
  r3 = 4096 - m3;
  r4 = 4096 - m4;
  r5 = 4096 - m5;
  r6 = 4096 - m6;
  r7 = 4096 - m7;
  r8 = 4096 - m8;
  r9 = 4096 - m9;
  r10 = 4096 - m10;
  r11 = 4096 - m11;
  r12 = 4096 - m12;

  if (message.length() < 12)
  {
    m12 = 4096;
    r12 = 0;
  }
  if (message.length() < 11)
  {
    m11 = 4096;
    r11 = 0;
  }
  if (message.length() < 10)
  {
    m10 = 4096;
    r10 = 0;
  }
  if (message.length() < 9)
  {
    m9 = 4096;
    r9 = 0;
  }
  if (message.length() < 8)
  {
    m8 = 4096;
    r8 = 0;
  }
  if (message.length() < 7)
  {
    m7 = 4096;
    r7 = 0;
  }
  if (message.length() < 6)
  {
    m6 = 4096;
    r6 = 0;
  }
  if (message.length() < 5)
  {
    m5 = 4096;
    r5 = 0;
  }
  if (message.length() < 4)
  {
    m4 = 4096;
    r4 = 0;
  }
  if (message.length() < 3)
  {
    m3 = 4096;
    r3 = 0;
  }
  if (message.length() < 2)
  {
    m2 = 4096;
    r2 = 0;
  }
  if (message.length() < 1)
  {
    m1 = 4096;
    r1 = 0;
  }

  move_step();
}

void move_step()
{

  int c1 = 0;
  int c2 = 0;
  int c3 = 0;
  int c4 = 0;
  int c5 = 0;
  int c6 = 0;
  int c7 = 0;
  int c8 = 0;
  int c9 = 0;
  int c10 = 0;
  int c11 = 0;
  int c12 = 0;

  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
  int v4 = 0;
  int v5 = 0;
  int v6 = 0;
  int v7 = 0;
  int v8 = 0;
  int v9 = 0;
  int v10 = 0;
  int v11 = 0;
  int v12 = 0;

  while (c6 < 4096)
  {
    if (c1 < m1)
    {
      setRegisterPin(motorPin1, HIGH);
      setRegisterPin(motorPin2, LOW);
      setRegisterPin(motorPin3, LOW);
      setRegisterPin(motorPin4, LOW);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, HIGH);
      setRegisterPin(motorPin6, LOW);
      setRegisterPin(motorPin7, LOW);
      setRegisterPin(motorPin8, LOW);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, HIGH);
      setRegisterPin(motorPin10, LOW);
      setRegisterPin(motorPin11, LOW);
      setRegisterPin(motorPin12, LOW);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, HIGH);
      setRegisterPin(motorPin14, LOW);
      setRegisterPin(motorPin15, LOW);
      setRegisterPin(motorPin16, LOW);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, HIGH);
      setRegisterPin(motorPin18, LOW);
      setRegisterPin(motorPin19, LOW);
      setRegisterPin(motorPin20, LOW);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, HIGH);
      setRegisterPin(motorPin22, LOW);
      setRegisterPin(motorPin23, LOW);
      setRegisterPin(motorPin24, LOW);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, HIGH);
      setRegisterPin(motorPin2, HIGH);
      setRegisterPin(motorPin3, LOW);
      setRegisterPin(motorPin4, LOW);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, HIGH);
      setRegisterPin(motorPin6, HIGH);
      setRegisterPin(motorPin7, LOW);
      setRegisterPin(motorPin8, LOW);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, HIGH);
      setRegisterPin(motorPin10, HIGH);
      setRegisterPin(motorPin11, LOW);
      setRegisterPin(motorPin12, LOW);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, HIGH);
      setRegisterPin(motorPin14, HIGH);
      setRegisterPin(motorPin15, LOW);
      setRegisterPin(motorPin16, LOW);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, HIGH);
      setRegisterPin(motorPin18, HIGH);
      setRegisterPin(motorPin19, LOW);
      setRegisterPin(motorPin20, LOW);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, HIGH);
      setRegisterPin(motorPin22, HIGH);
      setRegisterPin(motorPin23, LOW);
      setRegisterPin(motorPin24, LOW);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, LOW);
      setRegisterPin(motorPin2, HIGH);
      setRegisterPin(motorPin3, LOW);
      setRegisterPin(motorPin4, LOW);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, LOW);
      setRegisterPin(motorPin6, HIGH);
      setRegisterPin(motorPin7, LOW);
      setRegisterPin(motorPin8, LOW);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, LOW);
      setRegisterPin(motorPin10, HIGH);
      setRegisterPin(motorPin11, LOW);
      setRegisterPin(motorPin12, LOW);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, LOW);
      setRegisterPin(motorPin14, HIGH);
      setRegisterPin(motorPin15, LOW);
      setRegisterPin(motorPin16, LOW);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, LOW);
      setRegisterPin(motorPin18, HIGH);
      setRegisterPin(motorPin19, LOW);
      setRegisterPin(motorPin20, LOW);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, LOW);
      setRegisterPin(motorPin22, HIGH);
      setRegisterPin(motorPin23, LOW);
      setRegisterPin(motorPin24, LOW);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, LOW);
      setRegisterPin(motorPin2, HIGH);
      setRegisterPin(motorPin3, HIGH);
      setRegisterPin(motorPin4, LOW);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, LOW);
      setRegisterPin(motorPin6, HIGH);
      setRegisterPin(motorPin7, HIGH);
      setRegisterPin(motorPin8, LOW);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, LOW);
      setRegisterPin(motorPin10, HIGH);
      setRegisterPin(motorPin11, HIGH);
      setRegisterPin(motorPin12, LOW);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, LOW);
      setRegisterPin(motorPin14, HIGH);
      setRegisterPin(motorPin15, HIGH);
      setRegisterPin(motorPin16, LOW);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, LOW);
      setRegisterPin(motorPin18, HIGH);
      setRegisterPin(motorPin19, HIGH);
      setRegisterPin(motorPin20, LOW);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, LOW);
      setRegisterPin(motorPin22, HIGH);
      setRegisterPin(motorPin23, HIGH);
      setRegisterPin(motorPin24, LOW);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, LOW);
      setRegisterPin(motorPin2, LOW);
      setRegisterPin(motorPin3, HIGH);
      setRegisterPin(motorPin4, LOW);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, LOW);
      setRegisterPin(motorPin6, LOW);
      setRegisterPin(motorPin7, HIGH);
      setRegisterPin(motorPin8, LOW);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, LOW);
      setRegisterPin(motorPin10, LOW);
      setRegisterPin(motorPin11, HIGH);
      setRegisterPin(motorPin12, LOW);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, LOW);
      setRegisterPin(motorPin14, LOW);
      setRegisterPin(motorPin15, HIGH);
      setRegisterPin(motorPin16, LOW);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, LOW);
      setRegisterPin(motorPin18, LOW);
      setRegisterPin(motorPin19, HIGH);
      setRegisterPin(motorPin20, LOW);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, LOW);
      setRegisterPin(motorPin22, LOW);
      setRegisterPin(motorPin23, HIGH);
      setRegisterPin(motorPin24, LOW);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, LOW);
      setRegisterPin(motorPin2, LOW);
      setRegisterPin(motorPin3, HIGH);
      setRegisterPin(motorPin4, HIGH);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, LOW);
      setRegisterPin(motorPin6, LOW);
      setRegisterPin(motorPin7, HIGH);
      setRegisterPin(motorPin8, HIGH);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, LOW);
      setRegisterPin(motorPin10, LOW);
      setRegisterPin(motorPin11, HIGH);
      setRegisterPin(motorPin12, HIGH);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, LOW);
      setRegisterPin(motorPin14, LOW);
      setRegisterPin(motorPin15, HIGH);
      setRegisterPin(motorPin16, HIGH);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, LOW);
      setRegisterPin(motorPin18, LOW);
      setRegisterPin(motorPin19, HIGH);
      setRegisterPin(motorPin20, HIGH);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, LOW);
      setRegisterPin(motorPin22, LOW);
      setRegisterPin(motorPin23, HIGH);
      setRegisterPin(motorPin24, HIGH);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, LOW);
      setRegisterPin(motorPin2, LOW);
      setRegisterPin(motorPin3, LOW);
      setRegisterPin(motorPin4, HIGH);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, LOW);
      setRegisterPin(motorPin6, LOW);
      setRegisterPin(motorPin7, LOW);
      setRegisterPin(motorPin8, HIGH);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, LOW);
      setRegisterPin(motorPin10, LOW);
      setRegisterPin(motorPin11, LOW);
      setRegisterPin(motorPin12, HIGH);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, LOW);
      setRegisterPin(motorPin14, LOW);
      setRegisterPin(motorPin15, LOW);
      setRegisterPin(motorPin16, HIGH);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, LOW);
      setRegisterPin(motorPin18, LOW);
      setRegisterPin(motorPin19, LOW);
      setRegisterPin(motorPin20, HIGH);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, LOW);
      setRegisterPin(motorPin22, LOW);
      setRegisterPin(motorPin23, LOW);
      setRegisterPin(motorPin24, HIGH);
      writeRegisters();
    }
    c6++;
    delay(1);

    if (c1 < m1)
    {
      setRegisterPin(motorPin1, HIGH);
      setRegisterPin(motorPin2, LOW);
      setRegisterPin(motorPin3, LOW);
      setRegisterPin(motorPin4, HIGH);
      writeRegisters();
    }
    c1++;
    if (c2 < m2)
    {
      setRegisterPin(motorPin5, HIGH);
      setRegisterPin(motorPin6, LOW);
      setRegisterPin(motorPin7, LOW);
      setRegisterPin(motorPin8, HIGH);
      writeRegisters();
    }
    c2++;
    if (c3 < m3)
    {
      setRegisterPin(motorPin9, HIGH);
      setRegisterPin(motorPin10, LOW);
      setRegisterPin(motorPin11, LOW);
      setRegisterPin(motorPin12, HIGH);
      writeRegisters();
    }
    c3++;
    if (c4 < m4)
    {
      setRegisterPin(motorPin13, HIGH);
      setRegisterPin(motorPin14, LOW);
      setRegisterPin(motorPin15, LOW);
      setRegisterPin(motorPin16, HIGH);
      writeRegisters();
    }
    c4++;
    if (c5 < m5)
    {
      setRegisterPin(motorPin17, HIGH);
      setRegisterPin(motorPin18, LOW);
      setRegisterPin(motorPin19, LOW);
      setRegisterPin(motorPin20, HIGH);
      writeRegisters();
    }
    c5++;
    if (c6 < m6)
    {
      setRegisterPin(motorPin21, HIGH);
      setRegisterPin(motorPin22, LOW);
      setRegisterPin(motorPin23, LOW);
      setRegisterPin(motorPin24, HIGH);
      writeRegisters();
    }
    c6++;
    delay(1);
  }

  if (c6 = m6)
  {
    clearRegisters();
    writeRegisters();

    delay(3000);

    while (v6 < 4096)
    {

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, HIGH);
        setRegisterPin(motorPin2, LOW);
        setRegisterPin(motorPin3, LOW);
        setRegisterPin(motorPin4, LOW);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, HIGH);
        setRegisterPin(motorPin6, LOW);
        setRegisterPin(motorPin7, LOW);
        setRegisterPin(motorPin8, LOW);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, HIGH);
        setRegisterPin(motorPin10, LOW);
        setRegisterPin(motorPin11, LOW);
        setRegisterPin(motorPin12, LOW);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, HIGH);
        setRegisterPin(motorPin14, LOW);
        setRegisterPin(motorPin15, LOW);
        setRegisterPin(motorPin16, LOW);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, HIGH);
        setRegisterPin(motorPin18, LOW);
        setRegisterPin(motorPin19, LOW);
        setRegisterPin(motorPin20, LOW);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, HIGH);
        setRegisterPin(motorPin22, LOW);
        setRegisterPin(motorPin23, LOW);
        setRegisterPin(motorPin24, LOW);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, HIGH);
        setRegisterPin(motorPin2, HIGH);
        setRegisterPin(motorPin3, LOW);
        setRegisterPin(motorPin4, LOW);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, HIGH);
        setRegisterPin(motorPin6, HIGH);
        setRegisterPin(motorPin7, LOW);
        setRegisterPin(motorPin8, LOW);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, HIGH);
        setRegisterPin(motorPin10, HIGH);
        setRegisterPin(motorPin11, LOW);
        setRegisterPin(motorPin12, LOW);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, HIGH);
        setRegisterPin(motorPin14, HIGH);
        setRegisterPin(motorPin15, LOW);
        setRegisterPin(motorPin16, LOW);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, HIGH);
        setRegisterPin(motorPin18, HIGH);
        setRegisterPin(motorPin19, LOW);
        setRegisterPin(motorPin20, LOW);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, HIGH);
        setRegisterPin(motorPin22, HIGH);
        setRegisterPin(motorPin23, LOW);
        setRegisterPin(motorPin24, LOW);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, LOW);
        setRegisterPin(motorPin2, HIGH);
        setRegisterPin(motorPin3, LOW);
        setRegisterPin(motorPin4, LOW);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, LOW);
        setRegisterPin(motorPin6, HIGH);
        setRegisterPin(motorPin7, LOW);
        setRegisterPin(motorPin8, LOW);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, LOW);
        setRegisterPin(motorPin10, HIGH);
        setRegisterPin(motorPin11, LOW);
        setRegisterPin(motorPin12, LOW);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, LOW);
        setRegisterPin(motorPin14, HIGH);
        setRegisterPin(motorPin15, LOW);
        setRegisterPin(motorPin16, LOW);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, LOW);
        setRegisterPin(motorPin18, HIGH);
        setRegisterPin(motorPin19, LOW);
        setRegisterPin(motorPin20, LOW);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, LOW);
        setRegisterPin(motorPin22, HIGH);
        setRegisterPin(motorPin23, LOW);
        setRegisterPin(motorPin24, LOW);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, LOW);
        setRegisterPin(motorPin2, HIGH);
        setRegisterPin(motorPin3, HIGH);
        setRegisterPin(motorPin4, LOW);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, LOW);
        setRegisterPin(motorPin6, HIGH);
        setRegisterPin(motorPin7, HIGH);
        setRegisterPin(motorPin8, LOW);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, LOW);
        setRegisterPin(motorPin10, HIGH);
        setRegisterPin(motorPin11, HIGH);
        setRegisterPin(motorPin12, LOW);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, LOW);
        setRegisterPin(motorPin14, HIGH);
        setRegisterPin(motorPin15, HIGH);
        setRegisterPin(motorPin16, LOW);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, LOW);
        setRegisterPin(motorPin18, HIGH);
        setRegisterPin(motorPin19, HIGH);
        setRegisterPin(motorPin20, LOW);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, LOW);
        setRegisterPin(motorPin22, HIGH);
        setRegisterPin(motorPin23, HIGH);
        setRegisterPin(motorPin24, LOW);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, LOW);
        setRegisterPin(motorPin2, LOW);
        setRegisterPin(motorPin3, HIGH);
        setRegisterPin(motorPin4, LOW);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, LOW);
        setRegisterPin(motorPin6, LOW);
        setRegisterPin(motorPin7, HIGH);
        setRegisterPin(motorPin8, LOW);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, LOW);
        setRegisterPin(motorPin10, LOW);
        setRegisterPin(motorPin11, HIGH);
        setRegisterPin(motorPin12, LOW);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, LOW);
        setRegisterPin(motorPin14, LOW);
        setRegisterPin(motorPin15, HIGH);
        setRegisterPin(motorPin16, LOW);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, LOW);
        setRegisterPin(motorPin18, LOW);
        setRegisterPin(motorPin19, HIGH);
        setRegisterPin(motorPin20, LOW);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, LOW);
        setRegisterPin(motorPin22, LOW);
        setRegisterPin(motorPin23, HIGH);
        setRegisterPin(motorPin24, LOW);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, LOW);
        setRegisterPin(motorPin2, LOW);
        setRegisterPin(motorPin3, HIGH);
        setRegisterPin(motorPin4, HIGH);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, LOW);
        setRegisterPin(motorPin6, LOW);
        setRegisterPin(motorPin7, HIGH);
        setRegisterPin(motorPin8, HIGH);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, LOW);
        setRegisterPin(motorPin10, LOW);
        setRegisterPin(motorPin11, HIGH);
        setRegisterPin(motorPin12, HIGH);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, LOW);
        setRegisterPin(motorPin14, LOW);
        setRegisterPin(motorPin15, HIGH);
        setRegisterPin(motorPin16, HIGH);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, LOW);
        setRegisterPin(motorPin18, LOW);
        setRegisterPin(motorPin19, HIGH);
        setRegisterPin(motorPin20, HIGH);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, LOW);
        setRegisterPin(motorPin22, LOW);
        setRegisterPin(motorPin23, HIGH);
        setRegisterPin(motorPin24, HIGH);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, LOW);
        setRegisterPin(motorPin2, LOW);
        setRegisterPin(motorPin3, LOW);
        setRegisterPin(motorPin4, HIGH);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, LOW);
        setRegisterPin(motorPin6, LOW);
        setRegisterPin(motorPin7, LOW);
        setRegisterPin(motorPin8, HIGH);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, LOW);
        setRegisterPin(motorPin10, LOW);
        setRegisterPin(motorPin11, LOW);
        setRegisterPin(motorPin12, HIGH);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, LOW);
        setRegisterPin(motorPin14, LOW);
        setRegisterPin(motorPin15, LOW);
        setRegisterPin(motorPin16, HIGH);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, LOW);
        setRegisterPin(motorPin18, LOW);
        setRegisterPin(motorPin19, LOW);
        setRegisterPin(motorPin20, HIGH);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, LOW);
        setRegisterPin(motorPin22, LOW);
        setRegisterPin(motorPin23, LOW);
        setRegisterPin(motorPin24, HIGH);
        writeRegisters();
      }
      v6++;
      delay(1);

      if (v1 < r1)
      {
        setRegisterPin(motorPin1, HIGH);
        setRegisterPin(motorPin2, LOW);
        setRegisterPin(motorPin3, LOW);
        setRegisterPin(motorPin4, HIGH);
        writeRegisters();
      }
      v1++;
      if (v2 < r2)
      {
        setRegisterPin(motorPin5, HIGH);
        setRegisterPin(motorPin6, LOW);
        setRegisterPin(motorPin7, LOW);
        setRegisterPin(motorPin8, HIGH);
        writeRegisters();
      }
      v2++;
      if (v3 < r3)
      {
        setRegisterPin(motorPin9, HIGH);
        setRegisterPin(motorPin10, LOW);
        setRegisterPin(motorPin11, LOW);
        setRegisterPin(motorPin12, HIGH);
        writeRegisters();
      }
      v3++;
      if (v4 < r4)
      {
        setRegisterPin(motorPin13, HIGH);
        setRegisterPin(motorPin14, LOW);
        setRegisterPin(motorPin15, LOW);
        setRegisterPin(motorPin16, HIGH);
        writeRegisters();
      }
      v4++;
      if (v5 < r5)
      {
        setRegisterPin(motorPin17, HIGH);
        setRegisterPin(motorPin18, LOW);
        setRegisterPin(motorPin19, LOW);
        setRegisterPin(motorPin20, HIGH);
        writeRegisters();
      }
      v5++;
      if (v6 < r6)
      {
        setRegisterPin(motorPin21, HIGH);
        setRegisterPin(motorPin22, LOW);
        setRegisterPin(motorPin23, LOW);
        setRegisterPin(motorPin24, HIGH);
        writeRegisters();
      }
      v6++;
      delay(1);
    }

    clearRegisters();
    writeRegisters();

    delay(3000);
  }
}
