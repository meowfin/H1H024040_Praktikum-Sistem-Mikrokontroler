# 1.5.4 Pertanyaan Praktikum: 
## 1. Pada kondisi apa program masuk ke blok if? 
Program masuk ke blok if ketika nilai timeDelay <= 100.
## 2. Pada kondisi apa program masuk ke blok else? 
Program masuk ke blok else ketika timeDelay > 100.
## 3. Apa fungsi dari perintah delay(timeDelay)? 
- Mengatur jeda waktu LED menyala atau mati
- Menentukan kecepatan kedipan LED
- Semakin besar nilai delay → LED semakin lambat
- Semakin kecil nilai delay → LED semakin cepat
## 4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan di setiap baris kodenya dalam bentuk README.md! 
```c
int ledPin = 6; // Menentukan pin LED pada Arduino
int timeDelay = 1000; // Nilai awal delay (kedip lambat)

void setup() {
  pinMode(ledPin, OUTPUT);
} // Mengatur pin LED sebagai output

void loop() { // Program berjalan terus menerus
  digitalWrite(ledPin, HIGH); // LED menyala
  delay(timeDelay); // Menunggu sesuai delay

  digitalWrite(ledPin, LOW); // LED mati
  delay(timeDelay); // Menunggu sesuai delay

  if (timeDelay > 300) { // Kondisi saat LED masih lambat menuju cepat 
    timeDelay -= 100;   // mempercepat kedipan
  } 
  else if (timeDelay > 100) { // Kondisi transisi ke kecepatan sedang
    timeDelay -= 50;    // Perubahan lebih halus
  } 
  else { // Kondisi ketika sudah sangat cepat
    digitalWrite(ledPin, LOW); // LED dimatikan
    delay(2000);        // Jeda sebelum reset
    timeDelay = 1000;   // Reset ke kondisi awal
  }
}
```
# 1.6.4 Pertanyaan Praktikum
## 1. Gambarkan rangkaian schematic 5 LED running yang digunakan pada percobaan! 
<img width="926" height="719" alt="Screenshot 2026-04-07 100843" src="https://github.com/user-attachments/assets/cd325512-3401-46e0-a588-5bd3590ba7a2" />

## 2. Jelaskan bagaimana program membuat efek LED berjalan dari kiri ke kanan!
Efek ini dibuat menggunakan perulangan:

```c
for (int ledPin = 2; ledPin < 8; ledPin++)
```
Penjelasan: Variabel ledPin dimulai dari pin kecil (2), Setiap iterasi bertambah (ledPin++), LED menyala satu per satu dari kiri ke kanan
## 3. Jelaskan bagaimana program membuat LED kembali dari kanan ke kiri! 
Efek ini dibuat dengan:
```c
for (int ledPin = 7; ledPin >= 2; ledPin--)
```
Penjelasan: Perulangan dimulai dari pin besar (7), Nilai berkurang (ledPin--), LED menyala dari kanan ke kiri
## 4. Buatkan program agar LED menyala tiga LED kanan dan tiga LED kiri secara bergantian dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
```c
int timer = 200; //Mengatur kecepatan pergantian LED

void setup() { // Inisiasi awal
  for (int i = 2; i <= 7; i++) { //Loop untuk semua pin LED
    pinMode(i, OUTPUT); // Seet semua pin sebagai output
  }
}

void loop() { // Program berjalan terus
  // 3 LED kiri (pin 2,3,4)
  for (int i = 2; i <= 4; i++) {
    digitalWrite(i, HIGH);
  } // Menyalakan LED kiri
  for (int i = 5; i <= 7; i++) {
    digitalWrite(i, LOW);
  } // Mematikan LED kanan
  delay(timer); // Jeda waktu

  // 3 LED kanan (pin 5,6,7)
  for (int i = 5; i <= 7; i++) {
    digitalWrite(i, HIGH);
  } // Menyalakan LED kanan
  for (int i = 2; i <= 4; i++) {
    digitalWrite(i, LOW);
  } // Mematikan LED kiri
  delay(timer); // Jeda waktu sebelum ulang
}
```
