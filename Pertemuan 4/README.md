# Pertanyaan Praktikum Percobaan 1
## 1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
> Fungsi analogRead() digunakan untuk membaca nilai tegangan analog yang berasal dari potensiometer melalui pin analog Arduino. Pada rangkaian ini, potensiometer menghasilkan tegangan antara 0V sampai 5V tergantung posisi putarannya.
Arduino tidak dapat langsung memproses sinyal analog, sehingga ADC internal akan mengubah tegangan tersebut menjadi nilai digital dengan rentang 0–1023.
## 2. Mengapa diperlukan fungsi map() dalam program tersebut?
> Fungsi map() digunakan untuk mengubah rentang nilai tertentu ke rentang nilai lain. Pada praktikum ini, map() digunakan untuk mengkonversi nilai ADC (0–1023) menjadi sudut servo (misalnya 0–180 derajat) agar sesuai dengan kebutuhan output.
## 3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md
### Program modifikasi
```cpp
#include <Servo.h>

Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int pos = 0;
int val = 0;

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potensioPin);

  pos = map(val, 0, 1023, 30, 150);

  myservo.write(pos);

  Serial.print("ADC Potensio: ");
  Serial.print(val);

  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);

  delay(100);
}
```
### Penjelasan Program
> Perubahan utama terdapat pada bagian:
```cpp
pos = map(val, 0, 1023, 30, 150);
```
> Awalnya servo bergerak dari 0°–180°, kemudian dimodifikasi agar hanya bergerak dari 30°–150°. Artinya:
> - ADC minimum → servo bergerak ke 30°
> - ADC maksimum → servo bergerak ke 150°

> Modifikasi ini dilakukan untuk membatasi pergerakan servo agar tidak bergerak terlalu ekstrem dan mengurangi risiko jitter pada posisi ujung servo.

# Pertanyaan Praktikum Percobaan 2
## 1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!
> LED dapat diatur kecerahannya menggunakan fungsi analogWrite() karena Arduino menghasilkan sinyal PWM (Pulse Width Modulation), yaitu sinyal digital yang dinyalakan dan dimatikan dengan cepat. Kecerahan LED ditentukan oleh duty cycle, yaitu perbandingan lama waktu sinyal HIGH terhadap satu periode. Semakin besar nilai PWM, semakin lama sinyal berada pada kondisi HIGH sehingga tegangan rata-rata yang diterima LED meningkat dan LED terlihat lebih terang.
## 2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
> Nilai ADC memiliki rentang 0–1023 karena menggunakan resolusi 10-bit, sedangkan PWM memiliki rentang 0–255 karena menggunakan resolusi 8-bit. Oleh karena itu, diperlukan proses scaling (menggunakan fungsi map()) untuk menyesuaikan nilai ADC agar dapat digunakan sebagai nilai PWM.
## 3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.
### Program modifikasi
```cpp
#include <Arduino.h>

const int potPin = A0;
const int ledPin = 9;

int nilaiADC = 0;
int pwm = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  nilaiADC = analogRead(potPin);

  pwm = map(nilaiADC, 0, 1023, 0, 255);

  if (pwm >= 50 && pwm <= 200) {
    analogWrite(ledPin, pwm);
  } 
  else {
    analogWrite(ledPin, 0);
  }

  Serial.print("ADC: ");
  Serial.print(nilaiADC);

  Serial.print(" | PWM: ");
  Serial.println(pwm);

  delay(50);
}
```
### Penjelasan program
> Pada program ini ditambahkan struktur percabangan:
```cpp
if (pwm >= 50 && pwm <= 200)
```
> Jika nilai PWM berada pada rentang 50–200: LED menyala

> Jika nilai PWM di bawah 50 atau di atas 200: LED mati

> Tujuan modifikasi ini adalah membatasi LED agar hanya bekerja pada tingkat kecerahan sedang sesuai instruksi praktikum.
