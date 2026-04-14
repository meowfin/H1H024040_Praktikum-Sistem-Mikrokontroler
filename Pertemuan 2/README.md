# 2.5.4 Pertanyaan Praktikum
## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan! 
<img width="952" height="606" alt="skematik_percobaan2" src="https://github.com/user-attachments/assets/8094b616-b09b-427d-acde-f40f39fcafb8" />

## 2. Apa yang terjadi jika nilai num lebih dari 15?
Jika parameter num yang dilewatkan ke fungsi displayDigit(int num) bernilai lebih dari 15, program akan mengalami Array Out of Bounds. Matriks digitPattern hanya memiliki indeks 0 hingga 15. Mengakses indeks ke-16 atau lebih akan memaksa mikrokontroler membaca blok memori yang tidak didefinisikan (berisi garbage data). Akibatnya, nyala LED pada segmen akan menjadi acak (glitch), atau dalam kasus terburuk, mikrokontroler dapat mengalami crash dan perlu di-reset.
## 3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasannya!
Program ini menggunakan Common Cathode (Katoda Bersama).
Alasan: Pada tipe Common Cathode, pin Common dihubungkan ke Ground (0V). Agar LED menyala, pin Arduino harus menyuplai tegangan 5V (Logika HIGH atau 1). Hal ini selaras dengan deklarasi array biner pada program, misalnya pada pola angka '0' {1,1,1,1,1,1,0,0}, di mana angka 1 digunakan untuk menyalakan segmen. Jika ini adalah Common Anode, logika yang digunakan akan terbalik (0 untuk menyala, 1 untuk mati).
## 4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan di setiap baris kodenya dalam bentuk README.md!

``` c++
int segmentPins[] = {7,6,5,11,10,8,9}; //Menyimpan pin Arduino yang terhubung ke segmen

byte numbers[16][7] = { //Array berisi pola LED untuk angka 0–F
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}, //9
  {1,1,1,0,1,1,1}, //A
  {0,0,1,1,1,1,1}, //b
  {1,0,0,1,1,1,0}, //C
  {0,1,1,1,1,0,1}, //d
  {1,0,0,1,1,1,1}, //E
  {1,0,0,0,1,1,1}  //F
};

void setup() { //Mengatur semua pin sebagai OUTPUT
  for(int i=0;i<7;i++){
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() { //Program utama berjalan terus menerus
  for(int i=15; i>=0; i--){ //Loop dari F (15) ke 0
    for(int j=0;j<7;j++){
      digitalWrite(segmentPins[j], numbers[i][j]); //Mengirim sinyal HIGH/LOW ke setiap segmen
    }
    delay(1000); //Memberikan jeda 1 detik antar tampilan
  }
}
```
# 2.6.4 Pertanyaan Praktikum 
## 1. Gambarkan rangkaian schematic yang digunakan pada percobaan! 
<img width="817" height="532" alt="skematik_percobaan2b" src="https://github.com/user-attachments/assets/d9d3f3a5-5ef3-4e07-81b7-36cffb53d24b" />

## 2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa? 
Mode INPUT_PULLUP digunakan untuk mengaktifkan resistor internal (berkisar 20k-50k $\Omega$) yang terdapat di dalam mikrokontroler AVR. Resistor internal ini menghubungkan pin input ke VCC (5V).

Keuntungan dibandingkan rangkaian biasa:
- Menghindari Floating: Mencegah pin membaca tegangan liar dari induksi elektromagnetik sekitar yang dapat menyebabkan pembacaan acak. Pin dijamin bernilai HIGH saat tombol tidak ditekan.
- Efisiensi Hardware: Rangkaian menjadi jauh lebih sederhana karena kita tidak perlu lagi menambahkan komponen resistor pull-up atau pull-down eksternal di atas breadboard.
## 3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?
Sisi Hardware: Kabel jumper yang terhubung ke segmen tersebut putus di dalam.
- Resistor pembatas arus tidak tertancap dengan baik di breadboard (longgar).
- Dioda LED pada segmen spesifik tersebut telah rusak/terbakar.

Sisi Software: Kesalahan memetakan pin pada array segmentPins.
- Terdapat typo pengetikan logika biner pada array digitPattern, misalnya secara tidak sengaja mengetik '0' (mati) pada indeks yang seharusnya '1' (nyala) untuk pola angka tertentu.
## 4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
```c++
int buttonUp = 2; //Pin untuk tombol tambah
int buttonDown = 3; //Pin untuk tombol kurang

int counter = 0;

void setup() {
  pinMode(buttonUp, INPUT_PULLUP); //Menggunakan resistor internal Arduino
  pinMode(buttonDown, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(buttonUp) == LOW){ //Membaca kondisi tombol
    counter++; //Menambah nilai
    delay(200); // Debounce sederhana
  }

  if(digitalRead(buttonDown) == LOW){
    counter--; //Mengurangi nilai
    delay(200);
  }

  if(counter > 15) counter = 0; //Reset ke 0
  if(counter < 0) counter = 15; //embali ke 15

  displayNumber(counter); //Fungsi untuk menampilkan angka
}

void displayNumber(int num){
  // tampilkan ke seven segment (pakai array seperti sebelumnya)
}
```
