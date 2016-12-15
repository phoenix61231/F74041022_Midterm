#include <Ultrasonic.h>

#define front_trig 11
#define front_echo 2
#define left_trig 7
#define left_echo 8 
#define right_trig 3
#define right_echo 4
#define motor_right_back 5
#define motor_right_for 6
#define motor_left_back 9
#define motor_left_for 10

#define front_r_dir 5
#define front_l_dir 4
#define left_dir 1
#define right_dir 2
#define worst_situa 3


Ultrasonic front(front_trig,front_echo);
Ultrasonic left(left_trig,left_echo);
Ultrasonic right(right_trig,right_echo);

int v=80,last_cross;
float front_dis,right_dis,left_dis; 
bool back=false,front_sta,left_sta,right_sta;

void setup() {
  Serial.begin(9600);
  pinMode(motor_right_back,OUTPUT);
  pinMode(motor_right_for,OUTPUT);
  pinMode(motor_left_back,OUTPUT);
  pinMode(motor_left_for,OUTPUT); 
  analogWrite(motor_right_for,0);
  analogWrite(motor_right_back,0);
  analogWrite(motor_left_for,0);
  analogWrite(motor_left_back,0);
}

void loop() {
  long front_sec = front.timing(),left_sec = left.timing(),right_sec = right.timing();
  front_dis = front.convert(front_sec, Ultrasonic::CM);
  left_dis = left.convert(left_sec, Ultrasonic::CM);
  right_dis = right.convert(right_sec,Ultrasonic::CM);

  if(front_dis<=10){    front_sta = false;  }
     else{    front_sta = true;  }
  if(left_dis>=30){    left_sta = true;  }
     else{    left_sta = false;  } 
  if(right_dis>=30){    right_sta = true;  }
     else{    right_sta =false;  }

  //new
  if(front_dis>1000){
    analogWrite(motor_left_back,v);
    analogWrite(motor_right_back,v);
    delay(200);
    analogWrite(motor_left_back,0);
    analogWrite(motor_right_back,0);
    front_sta = false;    
  }
  
  if(back == false){
    if(left_dis<8){
      analogWrite(motor_right_back,v);
      delay(200);
      analogWrite(motor_right_back,0);
      delay(250);
    }
    else if(right_dis<8){
      analogWrite(motor_left_back,v);
      delay(200);
      analogWrite(motor_left_back,0);
      delay(250);
    }
    switch(front_sta){
      case true:
        switch(left_sta){
          case true:
            switch(right_sta){
              case true:
                //worst situation                                                
                break;
              case false:
                /*analogWrite(motor_right_for,v);
                delay(650);
                analogWrite(motor_right_for,0);
                delay(500);
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(1500);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);*/
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(100);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);
                last_cross=front_l_dir;                                     
                break;
            }
            break;
          case false:
            switch(right_sta){
              case true:               
                /*analogWrite(motor_left_for,v);
                delay(650);
                analogWrite(motor_left_for,0);
                delay(500);
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(1000);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);*/
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(100);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);
                last_cross=front_r_dir ;                                                                   
                break;      
              case false:
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(200);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);                              
                break;
            }
            break;          
        }        
        break;        
      case false:
        switch(left_sta){
          case true:
            switch(right_sta){
              case true:
                //worst situation      
                analogWrite(motor_left_back,v);
                analogWrite(motor_right_back,v);
                delay(200);
                analogWrite(motor_left_back,0);
                analogWrite(motor_right_back,0);
                         
                analogWrite(motor_right_for,v);
                delay(650);
                analogWrite(motor_right_for,0);
                delay(500);
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(1000);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);                
                last_cross=worst_situa;                               
                break;
              case false:
                analogWrite(motor_left_back,v);
                analogWrite(motor_right_back,v);
                delay(200);
                analogWrite(motor_left_back,0);
                analogWrite(motor_right_back,0);
                
                analogWrite(motor_right_for,v);
                delay(650);
                analogWrite(motor_right_for,0);
                delay(500);
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(1000);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);                                                                     
                break;
            }
            break;
          case false:
            switch(right_sta){
              case true:
                analogWrite(motor_left_back,v);
                analogWrite(motor_right_back,v);
                delay(200);
                analogWrite(motor_left_back,0);
                analogWrite(motor_right_back,0);
              
                analogWrite(motor_left_for,v);
                delay(650);
                analogWrite(motor_left_for,0);
                delay(500);
                analogWrite(motor_right_for,v);
                analogWrite(motor_left_for,v);
                delay(1000);
                analogWrite(motor_right_for,0);
                analogWrite(motor_left_for,0);
                break;      
              case false:
                back=true;                              
                break;
            }
            break;          
        }
        break;
    }
       
  }
  else{
    if(left_dis<8){
      analogWrite(motor_left_for,v);
      delay(200);
      analogWrite(motor_left_for,0);
      delay(500);
      }
    else if(right_dis<8){
      analogWrite(motor_right_for,v);
      delay(200);
      analogWrite(motor_right_for,0);
      delay(500);
    }
    if(left_sta!=false || right_sta!=false){
      switch(last_cross){
        case 0:
          analogWrite(motor_right_for,v);
          delay(650);
          analogWrite(motor_right_for,0);
          delay(500);
          //
          analogWrite(motor_right_for,v);
          analogWrite(motor_left_for,v);
          delay(1000);
          analogWrite(motor_right_for,0);
          analogWrite(motor_left_for,0);
          break;
        case 2:
          analogWrite(motor_left_back,v);
          delay(650);
          analogWrite(motor_left_back,0);
          delay(500);
          //
          analogWrite(motor_right_for,v);
          analogWrite(motor_left_for,v);
          delay(1000);
          analogWrite(motor_right_for,0);
          analogWrite(motor_left_for,0);
          break;
        case 3:          
          analogWrite(motor_right_back,v);          
          analogWrite(motor_left_for,v);
          delay(650);
          analogWrite(motor_right_back,0);          
          analogWrite(motor_left_for,0);
          delay(500);
          //
          analogWrite(motor_right_for,v);
          analogWrite(motor_left_for,v);
          delay(1000);
          analogWrite(motor_right_for,0);
          analogWrite(motor_left_for,0);
          break;
        case 4:
          analogWrite(motor_left_back,v);
          delay(650);
          analogWrite(motor_left_back,0);
          delay(250);
          //
          analogWrite(motor_right_for,v);
          analogWrite(motor_left_for,v);
          delay(1000);
          analogWrite(motor_right_for,0);
          analogWrite(motor_left_for,0);
          break;
        case 5:
          analogWrite(motor_right_back,v);
          delay(650);
          analogWrite(motor_right_back,0);
          delay(250);
          //
          analogWrite(motor_right_for,v);
          analogWrite(motor_left_for,v);
          delay(1000);
          analogWrite(motor_right_for,0);
          analogWrite(motor_left_for,0);        
          break;          
      }
      back=false;
    }
    else{
      analogWrite(motor_right_back,v);
      analogWrite(motor_left_back,v);
      delay(250);
      analogWrite(motor_right_back,0);
      analogWrite(motor_left_back,0);
    }            
  }
  

}
