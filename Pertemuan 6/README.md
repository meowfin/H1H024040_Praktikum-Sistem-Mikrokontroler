# 6.5.4 Pertanyaan Praktikum
## 1. Jelaskan proses bagaimana tombol dapat mengubah kondisi LED menggunakan interrupt! 
Pada percobaan ini, push button digunakan sebagai input interrupt dan LED digunakan sebagai output indikator. Sistem bekerja dengan memanfaatkan external interrupt pada pin digital 2 Arduino Uno. Ketika tombol ditekan, terjadi perubahan logika tegangan pada pin interrupt sehingga mikrokontroler langsung menghentikan sementara program utama dan menjalankan ISR (Interrupt Service Routine).

Pada program yang digunakan, variabel ```ledState``` menyimpan kondisi LED. Ketika interrupt aktif, ISR akan dijalankan dan variabel ```ledState``` diubah menjadi kebalikan dari kondisi sebelumnya menggunakan operator logika NOT (!). Setelah ISR selesai dijalankan, program utama kembali berjalan dan fungsi ```digitalWrite()``` akan menyesuaikan kondisi LED berdasarkan nilai terbaru dari variabel tersebut.

Berdasarkan hasil percobaan, LED berhasil berubah kondisi setiap kali tombol ditekan. Sistem menunjukkan respon yang cepat karena interrupt bekerja secara langsung tanpa polling terus menerus. Hal ini membuktikan bahwa interrupt lebih efisien dibanding metode polling pada sistem embedded modern.
## 2. Apa fungsi attachInterrupt() pada program tersebut? 
Fungsi ```attachInterrupt()``` digunakan untuk menghubungkan pin interrupt dengan ISR tertentu agar mikrokontroler dapat menjalankan fungsi ISR ketika terjadi event interrupt. Pada program praktikum, fungsi ini digunakan untuk menentukan:

1. Pin interrupt yang digunakan
    
2. Fungsi ISR yang akan dijalankan
    
3. Mode interrupt yang digunakan

Contoh penggunaan:
```cpp
attachInterrupt(
 digitalPinToInterrupt(2),
 tombolInterrupt,
 FALLING
);
```
Penjelasan:

- digitalPinToInterrupt(2) digunakan untuk menentukan bahwa interrupt berada pada pin 2 Arduino Uno.
  
- tombolInterrupt merupakan nama ISR yang akan dijalankan ketika interrupt terjadi.
  
- FALLING menunjukkan bahwa interrupt aktif ketika sinyal berubah dari HIGH ke LOW.

Tanpa fungsi ```attachInterrupt()```, Arduino tidak dapat mengetahui ISR mana yang harus dijalankan ketika interrupt terjadi. Oleh karena itu fungsi ini sangat penting dalam implementasi external interrupt.
## 3. Mengapa pada ISR tidak disarankan menggunakan delay() dan Serial.print()?
ISR harus dibuat sesingkat dan sesederhana mungkin karena selama ISR berjalan, program utama akan dihentikan sementara. Penggunaan fungsi ```delay()``` di dalam ISR tidak disarankan karena fungsi tersebut akan menghentikan sistem selama waktu tertentu sehingga seluruh proses lain ikut tertunda.

Sebagai contoh, jika ISR menggunakan ```delay(1000)```, maka sistem akan berhenti selama satu detik setiap interrupt terjadi. Kondisi ini dapat menyebabkan sistem menjadi lambat dan tidak responsif.

Selain itu, penggunaan ```Serial.print()``` di dalam ISR juga tidak disarankan karena proses komunikasi serial membutuhkan waktu relatif lama. Ketika ISR terlalu lama berjalan, interrupt lain dapat tertunda sehingga sistem menjadi tidak stabil.
## 4. Apa fungsi keyword volatile pada variabel ledState? 
Keyword ```volatile``` digunakan untuk memberi tahu compiler bahwa nilai variabel dapat berubah sewaktu-waktu di luar alur normal program, misalnya akibat interrupt. Pada praktikum ini, variabel ```ledState``` digunakan bersama antara ISR dan program utama sehingga perlu menggunakan keyword ```volatile```.

Contoh deklarasi:
```cpp
volatile bool ledState = false;
```
Tanpa penggunaan volatile, compiler dapat melakukan optimasi yang menyebabkan perubahan nilai variabel pada ISR tidak terbaca dengan benar oleh program utama. Akibatnya kondisi LED dapat menjadi tidak sesuai dengan yang diharapkan.

Dengan menggunakan volatile, sistem akan selalu membaca nilai terbaru dari variabel sehingga sinkronisasi antara ISR dan program utama tetap terjaga.
## 5. Pada percobaan digunakan mode interrupt FALLING. Modifikasikan program menggunakan mode interrupt lain (RISING, CHANGE, atau LOW) kemudian: 
## • Jelaskan perbedaan cara kerja masing-masing mode interrupt tersebut 
## • Analisis perubahan perilaku LED yang terjadi pada setiap mode 
## • Sertakan source code dan penjelasan program dalam bentuk README.md 
### A. Mode RISING
Mode ```RISING``` akan aktif ketika terjadi perubahan logika dari LOW ke HIGH. Pada push button, interrupt akan terjadi ketika tombol dilepas jika menggunakan konfigurasi tertentu.

### Source Code RISING
```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    RISING
  );
}

void loop() {
  digitalWrite(13, ledState);
}
```
### Analisis Mode RISING
Pada mode ini LED berubah kondisi ketika sinyal berubah dari LOW ke HIGH. Berdasarkan pengamatan, LED cenderung berubah ketika tombol dilepas karena pin kembali ke kondisi HIGH akibat pull-up internal.
### B. Mode CHANGE
Mode CHANGE akan aktif setiap terjadi perubahan logika baik dari HIGH ke LOW maupun LOW ke HIGH.
### Source Code CHANGE
```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    CHANGE
  );
}

void loop() {
  digitalWrite(13, ledState);
}
```
### Analisis Mode CHANGE
Pada mode ini interrupt akan aktif dua kali, yaitu saat tombol ditekan dan saat tombol dilepas. Akibatnya LED dapat berubah kondisi lebih cepat dibanding mode lainnya.
### C. Mode LOW
Mode LOW akan aktif selama pin berada pada kondisi LOW.
### Source Code LOW
```cpp
#include <Arduino.h>

volatile bool ledState = false;

void tombolInterrupt() {
  ledState = !ledState;
}

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(2),
    tombolInterrupt,
    LOW
  );
}

void loop() {
  digitalWrite(13, ledState);
}
```
### Analisis Mode LOW
Pada mode LOW, interrupt akan terus aktif selama tombol ditekan karena pin berada pada kondisi LOW secara terus menerus. Akibatnya LED dapat berkedip sangat cepat atau tidak stabil karena ISR dipanggil berulang kali selama tombol ditekan.
### Penjelasan Program Interrupt
1. Library Arduino
```cpp
#include <Arduino.h>
```
Digunakan untuk memanggil library utama Arduino.

2. Variabel volatile
```cpp
volatile bool ledState = false;
```
Digunakan untuk menyimpan kondisi LED dan dapat berubah akibat interrupt.

3. ISR
```cpp
void tombolInterrupt() {
 ledState = !ledState;
}
```
Digunakan untuk mengubah kondisi LED ketika interrupt terjadi.

4. attachInterrupt()
```cpp
attachInterrupt(
 digitalPinToInterrupt(2),
 tombolInterrupt,
 FALLING
);
```
Menghubungkan interrupt pada pin 2 dengan ISR menggunakan mode ```FALLING```.
# 6.6.4 Pertanyaan Praktikum 
## 1. Jelaskan bagaimana fungsi millis() bekerja pada program tersebut! 
Fungsi ```millis()``` bekerja dengan menghitung waktu sejak Arduino mulai dinyalakan dalam satuan milidetik. Nilai tersebut berasal dari Timer0 internal mikrokontroler dan terus bertambah selama sistem aktif.

Pada program praktikum, ```millis()``` digunakan untuk membaca waktu saat ini kemudian dibandingkan dengan waktu sebelumnya yang tersimpan pada variabel ```previousMillis```. Jika selisih waktunya telah mencapai interval tertentu, maka LED akan berubah kondisi.
## 2. Apa perbedaan utama antara delay() dan millis()?
Fungsi ```delay()``` bekerja dengan menghentikan seluruh proses program selama waktu tertentu sehingga disebut metode blocking. Sebaliknya, ```millis()``` bekerja dengan menghitung waktu tanpa menghentikan program utama sehingga disebut metode non-blocking.
## 3. Mengapa metode millis() disebut non-blocking? 
Metode ```millis()``` disebut non-blocking karena program utama tetap berjalan selama proses penghitungan waktu berlangsung. Arduino masih dapat menjalankan proses lain seperti membaca sensor, menangani interrupt, maupun mengontrol output lainnya secara bersamaan.

Berbeda dengan ```delay()``` yang menghentikan seluruh sistem sementara, ```millis()``` hanya memeriksa apakah interval waktu tertentu telah tercapai. Oleh karena itu metode ini lebih cocok digunakan pada sistem embedded dan real-time modern.
## 4. Modifikasi program agar: 
## • LED pertama berkedip setiap 1 detik 
## • LED kedua berkedip setiap 500 ms 
## • Tanpa menggunakan delay() 
## Berikan penjelasan setiap baris program dalam bentuk README.md. 
```cpp
unsigned long previousMillis[2] = [0, 0]; // menyimpan millis sebelumnya
bool ledState[2] = [2]; // state dari LED

void setup() {
    // Mengatur kedua pin sebagai output
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis(); // Mengambil waktu sekarang

  if(currentMillis - previousMillis[0] >= 1000) { // mengecek jika millis sekarang dikurangi milis sebelumnya dari led 1 lebih dari 1000
    previousMillis[0] = currentMillis; // Mengeset millis menjadi waktu sekarang
    ledState[0] = !ledState[0]; // Toggling state dari led 1
    digitalWrite(13, ledState[0]); // Menyalakan / mematikan led
  }

  if(currentMillis - previousMillis[1] >= 500) { // mengecek jika millis sekarang dikurangi milis sebelumnya dari led 2 lebih dari 500
    previousMillis[1] = currentMillis; // Mengeset millis menjadi waktu sekarang
    ledState[1] = !ledState[1];  // Toggling state dari led 1
    digitalWrite(12, ledState[1]); // Menyalakan atau mematikan led
  }
}
```
