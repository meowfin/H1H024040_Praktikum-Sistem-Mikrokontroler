# 3.5.4 Pertanyaan Praktikum
## 1. Jelaskan proses dari input keyboard hingga LED menyala/mati!
Proses komunikasi dimulai saat pengguna menekan tombol pada keyboard di antarmuka Serial Monitor, di mana sistem operasi komputer mengonversi input tersebut menjadi kode ASCII, misalnya karakter '1' yang memiliki nilai hexadesimal 0x31. Data ini kemudian dikirimkan melalui kabel USB dalam bentuk paket serial yang diatur oleh driver USB-to-Serial pada perangkat Arduino. Setelah mencapai mikrokontroler ATmega328P, sinyal tersebut diterima oleh periferal Universal Asynchronous Receiver-Transmitter (UART) dan disimpan sementara di dalam receive buffer hardware. Di dalam kode program, instruksi ```Serial.read()``` mengambil satu byte data dari buffer tersebut untuk diproses oleh CPU. Apabila nilai yang terbaca sesuai dengan logika pembanding (misalnya ```data == '1' ```), mikrokontroler akan memerintahkan unit GPIO untuk mengeluarkan tegangan tinggi (5V) melalui instruksi ```digitalWrite(PIN_LED, HIGH)```, yang kemudian mengalirkan arus listrik menuju LED sehingga perangkat menyala.
## 2. Mengapa digunakan ```Serial.available()``` sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
Fungsi ```Serial.available()``` memainkan peran krusial sebagai penjaga gerbang (gatekeeper) yang memberikan informasi mengenai jumlah byte data yang telah diterima dan siap untuk dibaca di dalam receive buffer. Tanpa penggunaan fungsi ini, instruksi ```Serial.read()``` akan tetap dieksekusi oleh CPU pada setiap siklus ```loop()```, meskipun sebenarnya tidak ada data yang dikirimkan oleh komputer. Jika baris tersebut dihilangkan, ```Serial.read()``` akan mengembalikan nilai -1 (konstanta EOF) secara terus-menerus karena buffer dalam keadaan kosong. Hal ini akan menyebabkan logika percabangan ```if-else``` dalam program memproses data yang tidak valid, yang berujung pada eksekusi perintah yang salah atau munculnya pesan kesalahan "Perintah tidak dikenal" secara berulang-ulang, sehingga mengganggu stabilitas sistem secara keseluruhan.
## 3. Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
```cpp
#include <Arduino.h>

const int PIN_LED = 12;     // Menentukan pin LED
bool modeBlink = false;     // Status mode blink

void setup() {
Serial.begin(9600);       // Memulai komunikasi serial
pinMode(PIN_LED, OUTPUT); // Set pin LED sebagai output
}

void loop() {

    if (Serial.available() > 0) {  // Cek apakah ada data masuk
        char data = Serial.read();   // Baca data dari serial

        if (data == '1') {           
            modeBlink = false;         
            digitalWrite(PIN_LED, HIGH); // LED menyala
        }
        else if (data == '0') {      
            modeBlink = false;         
            digitalWrite(PIN_LED, LOW);  // LED mati
        }
        else if (data == '2') {      
            modeBlink = true;          // Aktifkan mode blink
        }
    }

    if (modeBlink) {               
        digitalWrite(PIN_LED, HIGH); 
        delay(500);                  
        digitalWrite(PIN_LED, LOW);  
        delay(500);                  
    }
}
```
Penjelasan:
- ```modeBlink``` digunakan untuk menyimpan kondisi LED apakah berkedip atau tidak
- Jika menerima '2', LED masuk mode berkedip terus menerus
- Jika menerima '1' atau '0', mode blink dimatikan
- ```delay(500)``` mengatur kecepatan kedipan LED
## 4. Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadap sistem
`delay()` digunakan karena program ini tidak memerlukan multitasking. `delay()` menyebabkan program berhenti sementara selama waktu yang ditentukan, sehingga program tidak dapat melakukan hal lain selama periode tersebut. Namun, karena program ini hanya melakukan satu tugas (mengontrol LED), `delay()` tidak menjadi masalah. Jika program ini memerlukan multitasking, maka `milis()` akan lebih cocok digunakan.
# 3.6.4 Pertanyaan Praktikum
## 1. Jelaskan bagaimana cara kerja komunikasi I2C antara Arduino dan LCD pada rangkaian tersebut!
Komunikasi I2C (Inter-Integrated Circuit) pada rangkaian ini beroperasi berdasarkan arsitektur Master-Slave, di mana Arduino Uno bertindak sebagai Master yang mengendalikan sinkronisasi detak dan aliran data, sementara modul LCD I2C bertindak sebagai Slave. Transmisi data dilakukan melalui dua jalur utama: Serial Data (SDA) untuk pertukaran bit informasi dan Serial Clock (SCL) untuk sinkronisasi waktu. Proses dimulai dengan Master mengirimkan Start Condition diikuti oleh alamat hexadesimal unik periferal (seperti 0x27) untuk mengaktifkan target Slave tertentu tanpa mengganggu perangkat lain di jalur bus yang sama. Setelah koneksi terjalin, data perintah atau karakter dikirimkan secara sekuensial, diakhiri dengan Stop Condition untuk membebaskan jalur bus.
## 2. Apakah pin potensiometer harus seperti itu? Jelaskan yang terjadi apabila pin kiri dan pin kanan tertukar! 
Konfigurasi pin pada potensiometer mengikuti prinsip pembagi tegangan (voltage divider) . Berdasarkan tabel wiring, pin kiri dihubungkan ke GND, pin tengah ke A0 (sebagai sinyal output analog), dan pin kanan ke 5V.
- Apa yang terjadi jika pin kiri dan kanan tertukar? Secara teknis, pertukaran ini tidak akan merusak komponen karena keduanya tetap terhubung ke rel daya. Namun, hal ini akan menyebabkan logika rotasi potensiometer menjadi terbalik (inverse). Jika semula putaran searah jarum jam meningkatkan tegangan (dan nilai ADC), maka setelah ditukar, putaran searah jarum jam justru akan menurunkan tegangan menuju 0V. Hal ini dikarenakan arah gradien resistansi terhadap wiper (pin tengah) mengalami pembalikan referensi polaritas.
## 3. Modifikasi program dengan menggabungkan antara UART dan I2C (keduanya sebagai output) sehingga:
## - Data tidak hanya ditampilkan di LCD tetapi juga di Serial Monitor 
## - Adapun data yang ditampilkan pada Serial Monitor sesuai dengan table berikut: 
<img width="737" height="42" alt="image" src="https://github.com/user-attachments/assets/0cd8d9c0-3a98-43e1-a51c-4253d1e0c6a0" />

## Tampilan jika potensiometer dalam kondisi diputar paling kiri  
## - ADC: 0  0% | setCursor(0, 0) dan Bar (level) | setCursor(0, 1) 
## - Berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Inisialisasi LCD pada alamat 0x27 dengan ukuran 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
  Serial.begin(9600); // Inisialisasi UART
  lcd.init();         // Inisialisasi I2C LCD
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);              // Membaca nilai ADC (0-1023)
  float volt = (nilai / 1023.0) * 5.0;         // Konversi ke Tegangan
  int persen = map(nilai, 0, 1023, 0, 100);    // Konversi ke Persentase
  int panjangBar = map(nilai, 0, 1023, 0, 16); // Konversi ke skala bar LCD

  // Output ke Serial Monitor (UART)
  Serial.print("ADC: "); Serial.print(nilai);
  Serial.print(" Volt: "); Serial.print(volt, 2); Serial.print(" V ");
  Serial.print("Persen: "); Serial.print(persen); Serial.println("%");

  // Output ke LCD (I2C) - Baris 1
  lcd.setCursor(0, 0);
  lcd.print("ADC:"); lcd.print(nilai);
  lcd.print(" "); lcd.print(persen); lcd.print("%   ");

  // Output ke LCD (I2C) - Baris 2 (Level Bar)
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) lcd.print((char)255); // Karakter blok penuh
    else lcd.print(" ");                      // Karakter kosong
  }

  delay(200); // Jeda sampling untuk stabilitas pembacaan
}
```
Penjelasan:
- Konversi Skala: Program menggunakan perhitungan manual untuk Voltase dan fungsi `map()` untuk membagi nilai ADC ke dalam skala persentase (0-100) dan panjang bar (0-16 karakter) agar sesuai dengan dimensi LCD.
- Sinkronisasi Output: Data diproses sekali di CPU, kemudian dikirimkan secara berurutan ke unit periferal USART (UART) dan unit periferal TWI (I2C) tanpa adanya blocking antar protokol.
- Manajemen Tampilan: Instruksi `lcd.print("   ")` setelah nilai ADC berfungsi untuk membersihkan sisa karakter lama jika nilai baru memiliki jumlah digit yang lebih sedikit, guna menghindari glitch visual pada layar.
## 4. Lengkapi table berikut berdasarkan pengamatan pada Serial Monitor 
<img width="732" height="179" alt="image" src="https://github.com/user-attachments/assets/c5f3ae3f-9704-4a6c-9cde-fe70c500dcf8" />

Jawab:
<img width="1049" height="228" alt="image" src="https://github.com/user-attachments/assets/21611b22-53de-4981-bdf8-3b41a7bbd3e4" />

