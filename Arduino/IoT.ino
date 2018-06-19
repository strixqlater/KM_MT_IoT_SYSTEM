#include <SoftwareSerial.h> // SofrwareSerial 사용을 위한 라이브러리
#include <LiquidCrystal.h> // LCD 사용을 위한 라이브러리
#include <DHT.h> // 온습도 센서 사용을 위한 라이브러리

#define SSID "Exynos8890" // 연결 할 AP의 SSID
#define PASS "icnxkmaster" // 연결 할 AP의 Password
#define DST_IP "strixqlater.iptime.org" //서버 측 주소 값
#define dhtPin 7 // 온습도 센서 Data Pin
#define dustPin A7 // 미세먼지 센서 Analog Pin
#define dustLed 2 // 미세먼지 센서 LED Pin

SoftwareSerial dbgSerial(10, 11); // ESP8266 소프트웨어 시리얼 통신을 위한 Rx, Tx 설정
LiquidCrystal lcd(48, 49, 50, 51, 52, 53);
DHT dht(dhtPin, DHT11); // 온습도 센서 초기화

int temp; // 온도 변수 선언
int humid; // 습도 변수 선언

float dustVal = 0; // 미세먼지 Analog 데이터 값 저장 변수 선언
float dustDensity = 0; // 미세먼지 측정값 변수 선언
int delayTime = 280; // 미세먼지 측정 시 LED 꺼짐 시간
int delayTime2 = 40; // 미세먼지 측정 시 LED 켜짐 시간
float offTime = 9680; // 미세먼지 측정 대기 시간

void setup() {
  Serial.begin(9600); // 시리얼 포트 초기화
  Serial.setTimeout(5000); // 시리얼 포트 타임아웃 설정  
  dbgSerial.begin(9600); // ESP8266 포트 초기화
  lcd.begin(16, 2); // LCD 모듈 초기화
  pinMode(dustLed, OUTPUT); // 미세먼지 센서 LED 초기화

  Serial.println("ESP8266");
  Serial.println("connecting...");

  lcd.home();
  lcd.clear();
  lcd.print("Initializing...");
  lcd.setCursor(0, 1);
  lcd.print("@codegazer");

  // ESP8266 모듈을 이용하여 AP 연결
  boolean connected = false;
  for(int i = 0; i < 10; i++) {
    if(connectWiFi()) {
      connected = true;
      break;
    }
  }

  if(!connected) {
    while(1);
  }
  delay(5000);

  dbgSerial.println("AT+CIPMUX=0");
}

// 센서 값을 서버 측으로 전송 함수
void DataToServer() {
  temp = dht.readTemperature(); // 온도 측정
  humid = dht.readHumidity(); // 습도 측정

  //미세먼지 측정
  digitalWrite(dustLed,LOW);
  delayMicroseconds(delayTime);
  dustVal = analogRead(dustPin);
  delayMicroseconds(delayTime2);
  digitalWrite(dustLed,HIGH);
  delayMicroseconds(offTime);
  dustDensity = 0.17*(dustVal*0.0049)-0.1;
  
  // 서버와의 연결 시도
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  Serial.println(cmd);
  dbgSerial.println(cmd);

  // TCP 연결 오류 체크
  if(dbgSerial.find("Error")) {
    Serial.println("TCP connect error");
    return;
  }

  // 서버 측으로 센서에서 받아온 정보를 전송
  cmd = "GET /data.php?temp=";
  cmd += temp;
  cmd += "&humid=";
  cmd += humid;
  cmd += "&dust=";
  cmd += dustDensity;
  cmd += "\r\n";
  dbgSerial.print("AT+CIPSEND=");
  dbgSerial.println(cmd.length());

  Serial.println(cmd);

  // 서버 측으로 센서 정보 전송 성공
  if(dbgSerial.find(">")) {
    Serial.print(">");
  }

  // 서버 측으로 센서 정보 전송 실패
  else {
    dbgSerial.println("AP+CIPCLOSE");
    Serial.println("connection timeout!");
    delay(1000);
    return;
  }

  dbgSerial.print(cmd);
  delay(2000);

  while(Serial.available()) {
    char c = Serial.read();
    dbgSerial.write(c);
    if(c == '\r') dbgSerial.print('\n');
  }
  Serial.println(" OK");
  delay(1000);
}

// 센서의 정보를 LCD로 출력하는 함수
void lcdPrint() {
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("'C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humid);
  lcd.print("%");
  lcd.setCursor(15, 1);
  lcd.blink();
}

void loop() {
  Serial.println("Requesting sensor data...");
  DataToServer();
  lcdPrint();
}

// ESP8266 모듈의 AP 연결 함수
boolean connectWiFi()  
{  
  //dbgSerial.println("AT+CWMODE=1");
   
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  dbgSerial.println(cmd);
  Serial.println(cmd);
  delay(3000);

  //AP 연결 성공 시 해당 문자열 출력
  if(dbgSerial.find("OK")) {
    Serial.println("OK, AP connect successfully.");
    return true;
  }

  // AP 연결 실패 시 해당 문자열 출력
  else {
    Serial.println("Error, AP connect failed.");
    return false;
  }
}
