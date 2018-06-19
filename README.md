# KM_MT_IoT_SYSTEM
Temp/Humid, Dust measured value upload to server

## 1. 개발 환경 (Development Enviroments)
Arduino Mega 2560, 1602 LCD, ESP8266(ESP-01), DHT11, GP2Y1010AU0F

Odroid XU4, Ubuntu 18.04, NginX 1.14.0, PHP 7.2.5, MySQL 14.14

## 2. 회로 구성 (Circuit Configuration)
./ 폴더 내의 IoT.png, IoT.fzz 를 참조하시시기 바랍니다.
*.fzz 의 파일은 Fritzing 툴을 이용하시면 Open 이 가능합니다.

## 3. 서버 설정 (Setting Server)
이 프로젝트는 우분투 18.04 기반 LEMP 스택 환경에서 작성되었습니다.
기타 APM 환경에서도 작동 할 것으로 생각됩니다만, LEMP 환경이 아닌 다른 곳에서의 작동을 보장하지 않습니다.

웹 서버 기본 설치 된 환경에서 (우분투의 경우, /var/www/html) ./Server 내의 폴더의 파일을 모두 옮겨 주시면 됩니다.

기타 필요한 파일 및 데이터베이스 (head.inc 등) 은 직접 작성해서 파일과 연동 해주시면 되겠습니다.

## 4. 클라이언트 설정 (Setting Client)
이 프로젝트는 Arduino Mega 2560 기반에서 작성 되었습니다.
기타 Uno 등 다른 보드에서의 작동을 보장하지 않습니다.

./Arduino 내의 IoT.ino 파일을 Arduino IDE 에서 Open 해주 신 후 컴파일 해서 사용하시면 되겠습니다.

## 5. 기타 사항 (etc)
기타 궁금하신 점은 codegazer (strixqlater@gmail.com) 으로 문의 바랍니다.
