// Dangaya Driver - Wheels
#define IN_Speed_Left 3   // to control the speed of the motor  (110 - 255)
#define INA_left 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_left 
#define IN_Speed_Right 6    
#define INA_right 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_right   

//Dangaya Driver - Weapons
#define IN_Speed_Weapon_Front 3   // to control the speed of the motor  (110 - 255)
#define INA_Weapon_Front 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_Weapon_Front 
#define IN_Speed_Weapon_Back 6   
#define INA_Weapon_Back 2   // to control the direction of the motor (10 - FW, 01 - BW, 00 - coast, 11- Break)
#define INB_Weapon_Back  


int LMotorSpeed = 85;
int RMotorSpeed = 105; 


void forward();
void backward();
void turn_left();
void turn_right();
void motor_speed();


void setup() {
  // put your setup code here, to run once:
  pinMode(IN_Speed_Left, OUTPUT);
  pinMode(INA_left, OUTPUT);
  pinMode(INB_left, OUTPUT);

  pinMode(IN_Speed_Right, OUTPUT);
  pinMode(INA_Right, OUTPUT);
  pinMode(INB_Right, OUTPUT);

  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INA_right, HIGH);

  analogWrite(IN_Speed_Left, 255);
  analogWrite(IN_Speed_Right, 255);

  pinMode(IN_Speed_Weapon_Front, OUTPUT);
  pinMode(INA_Weapon_Front, OUTPUT);
  pinMode(INB_Weapon_Front, OUTPUT);

  pinMode(IN_Speed_Weapon_Back, OUTPUT);
  pinMode(INA_Weapon_Back, OUTPUT);
  pinMode(INB_Weapon_Back, OUTPUT);

  ////////////////////
  digitalWrite(INA_Weapon_Front, HIGH);   // Roller rolls at all times
  digitalWrite(INB_Weapon_Front, LOW);
  analogWrite(IN_Speed_Weapon_Front, 255);
  ///////////////////

  digitalWrite(INA_Weapon_Back, HIGH);
  digitalWrite(INB_Weapon_Back, HIGH);

  analogWrite(IN_Speed_Weapon_Back, 255);
  delay(500);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void forward()
{
  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, LOW);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INB_right, LOW);
  motor_speed();
}

void backward()
{
  digitalWrite(INA_left, LOW);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, LOW);
  digitalWrite(INB_right, HIGH);
  motor_speed();
}

void turn_left()
{
  digitalWrite(INA_left, LOW);
  digitalWrite(INB_left, HIGH);
  digitalWrite(INA_right, HIGH);
  digitalWrite(INB_right, LOW);
  motor_speed();
}

void turn_right()
{
  digitalWrite(INA_left, HIGH);
  digitalWrite(INB_left, LOW);
  digitalWrite(INA_right, LOW);
  digitalWrite(INB_right, HIGH);
  motor_speed();
}

void motor_speed()
{   
    analogWrite(EN_Speed_Left, LMotorSpeed);
    analogWrite(EN_Speed_Right7, RMotorSpeed);
}

