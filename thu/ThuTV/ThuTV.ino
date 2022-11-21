#include <IRremote.h>

const int receiverPin = 8; // chân digital 8 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu
void setup()
{
  Serial.begin(9600);// serial baudrate 9600
  irrecv.enableIRIn(); // start the IR receiver
}
void loop()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    Serial.println(results.value, HEX); // in ra Serial Monitor
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}
