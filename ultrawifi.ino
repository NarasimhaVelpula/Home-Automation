
#define ssid "sai"
#define pass "12345678"
#define api "ecourses.aec.edu.in"//website linked
#define bodrate 115200
#define URL "http://" 

int field1=0,field2=0,field3=0,field4=0,field5=0;
String GET1="GET /thub/homeautomation/Public/status.php";//GET command from the server
bool updated;



void setup()
{
  // put your setup code here, to run once:
  
Serial.begin(bodrate);
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
pinMode(11,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(6,OUTPUT);
Serial.println("AT");
delay(1000);


if(Serial.find("OK"))
{
  Serial.println("AT+CWMODE=1");
  delay(5000);
  String cmd="AT+CWJAP=\"";
  cmd+=ssid;
  cmd+="\",\"";
  cmd+=pass;
  cmd+="\"";
  Serial.println(cmd);  
  delay(10000);
  if(Serial.find("OK"))
  {
   Serial.println("Wifi connected"); 
   digitalWrite(6,HIGH);
  }
  else
  {
    Serial.println("WiFi not connected"); 
    digitalWrite(6,LOW);
  }
}
}
void loop() 
{
  // put your main code here, to run repeatedly:
  int data=status_Checker();
  if((field1==1))
  {
    digitalWrite(13,HIGH);
   
  }
  else 
  {
    digitalWrite(13,LOW);
    
  }
  if(field2==1)
  digitalWrite(12,HIGH);
  else
  digitalWrite(12,LOW);
  if(field3==1)
  digitalWrite(11,HIGH);
  else
  digitalWrite(11,LOW);
  if(field4==1)
  digitalWrite(10,HIGH);
  else
  digitalWrite(10,LOW);
  if(field5==1)
  digitalWrite(9,HIGH);
  else
  digitalWrite(9,LOW);
}




  int status_Checker()
  {
  bool updated=host();
  String data;
   String cmd1=GET1;
   cmd1+="\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd1.length());
 delay(1000);
  if(Serial.find(">"))
  
  {
    
    Serial.println(cmd1);
    String data=Serial.readString();
   
    Serial.println(data);//calculate the positions of array that appear on the serial mo;nitor and calculate data positions of the feilds bits in the array and modify the code below

    Serial.println("AT+CIPCLOSE");
    delay(700);
   if(data[102]=='1')//this is an example simmilllary caluclate the field1 data positiion and replace 30 with exacat position
   {
   field1=1;
   }
   else 
   field1=0;
   if(data[131]=='1')
   field2=1;
   else 
   field2='0';
    if(data[160]=='1')
   field3=1;
   else 
   field3='0';
    if(data[189]=='1')
   field4=1;
   else 
   field4='0';
    if(data[218]=='1')
   field5=1;
   else 
   field5='0';
     return(0);
  
  }
 
  }

bool host()
{
  String cmd="AT+CIPSTART=\"TCP\",\"";
  cmd+=api;
  cmd+="\",80";
  
  Serial.println(cmd);
 delay(1000);
  if(Serial.find("Error"))
  {
    host();
  }
  else
  {
    return(0);
  }
}

