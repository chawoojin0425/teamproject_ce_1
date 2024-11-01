#include <Servo.h>  // 서보 라이브러리 포함
Servo l, r;       // 왼쪽과 오른쪽 서보 선언

void setup() {
  pinMode(11, OUTPUT);      // 11번 핀을 출력 모드로 설정
  pinMode(7, INPUT_PULLUP); // 7번 핀을 풀업 입력으로 설정
  pinMode(5, INPUT_PULLUP); // 5번 핀을 풀업 입력으로 설정
  
  l.attach(13); // 왼쪽 서보를 13번 핀에 연결
  r.attach(12); // 오른쪽 서보를 12번 핀에 연결

  // 8자 움직임
  dance8_forward(100); // 지그재그로 직진

  l.write(1525);
  r.write(1300);   // 왼쪽 회전
  delay(6050);
  
  dance8_forward(100); // 지그재그로 직진
  
  l.write(1700);
  r.write(1490);
  delay(5700);   // 오른쪽 회전
} 

void loop() {

  int light = analogRead(A0); // 조도 센서 값 읽기

  if(light > 800){
    digitalWrite(11, HIGH); // LED 켜기
    delay(500);
    digitalWrite(11, LOW);  // LED 끄기
    delay(500);
    l.detach(); // 서보 모터와 핀의 연결 해제
    r.detach();
  }

  // 더듬이
  byte wl = digitalRead(5); // 왼쪽 더듬이 (GND - 핀 5)
  byte wr = digitalRead(7); // 오른쪽 더듬이 (GND - 핀 7)
  if ((wl == 0) && (wr == 0)) { // 양쪽 센서가 감지되었을 때
    backward(500);  // 0.5초 동안 후진
    turnRight(400); // 약 60도 우회전
  } else if (wl == 0) { // 왼쪽 센서만 감지되었을 때
    backward(500);  // 0.5초 동안 후진
    turnRight(200); // 약 30도 우회전
  } else if (wr == 0) { // 오른쪽 센서만 감지되었을 때
    backward(500);  // 0.5초 동안 후진
    turnLeft(200);  // 약 30도 좌회전
  } else {
    forward(20);    // 1/50초 동안 전진
  }
}

void forward(int time) {
  l.write(1700);   // 왼쪽 모터 전진
  r.write(1300);   // 오른쪽 모터 전진
  delay(time);     // 설정된 시간 동안 대기
}

void turnLeft(int time) {
  l.write(1300);   // 왼쪽 모터 좌회전
  r.write(1300);   // 오른쪽 모터 좌회전
  delay(time);     // 설정된 시간 동안 대기
}

void turnRight(int time) {
  l.write(1700);   // 왼쪽 모터 우회전
  r.write(1700);   // 오른쪽 모터 우회전
  delay(time);     // 설정된 시간 동안 대기
}

void backward(int time) {
  l.write(1300);   // 왼쪽 모터 후진
  r.write(1700);   // 오른쪽 모터 후진
  delay(time);     // 설정된 시간 동안 대기
}

void dance8_forward(int time){
  for (int i = 0; i < 10; i++){
    l.write(1700);
    r.write(1500);
    delay(time);
    l.write(1500);
    r.write(1300);
    delay(time);
  }
  l.write(1500);
  r.write(1300);
  delay(time);
}
