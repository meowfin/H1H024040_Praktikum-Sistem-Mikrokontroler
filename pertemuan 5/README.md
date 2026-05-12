# 5.5.4 Pertanyaan Praktikum
## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
> Secara fisik, ketiga task tidak benar-benar berjalan secara bersamaan karena Arduino Uno hanya memiliki satu inti prosesor. Prosesor hanya mampu mengeksekusi satu instruksi dalam satu waktu.
Namun, FreeRTOS menggunakan mekanisme task scheduling dan context switching yang memungkinkan CPU berpindah dari satu task ke task lainnya dengan sangat cepat sehingga terlihat seperti berjalan bersamaan.

> Ketika TaskBlink1 sedang memasuki kondisi ```vTaskDelay()```, scheduler akan memberikan kesempatan kepada TaskBlink2 untuk dijalankan. Ketika TaskBlink2 juga memasuki delay, scheduler dapat menjalankan TaskPrint. Proses ini berlangsung secara terus-menerus dengan sangat cepat.
Mekanisme tersebut disebut concurrent execution, bukan parallel execution, karena semua task tetap dijalankan secara bergantian dalam satu CPU [1].
## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya! 
> Untuk menambahkan task keempat, langkah pertama adalah membuat fungsi task baru. Sebagai contoh, task keempat digunakan untuk menyalakan buzzer atau LED tambahan.

> Contoh deklarasi fungsi:
```cpp
void TaskFour(void *pvParameters){
    while(1){
        Serial.println("Task 4 berjalan");
        vTaskDelay(400/portTICK_PERIOD_MS);
    }
}
```
> Setelah fungsi dibuat, task harus didaftarkan pada fungsi setup() menggunakan xTaskCreate():
```cpp
xTaskCreate(
TaskFour,
"task4",
128,
NULL,
1,
NULL
);
```
> Setelah itu program di-compile dan di-upload kembali ke Arduino. Jika berhasil, maka scheduler akan mengatur empat task secara bergantian.Hasilnya, sistem masih dapat berjalan normal selama penggunaan memori Arduino masih mencukupi.
## 3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskan program pada file README.md.
```cpp
#include <Arduino_FreeRTOS.h> // library FreeRTOS untuk multitasking

void TaskBlink1(void *pvParameters); // deklarasi task LED 1
void TaskBlink2(void *pvParameters); // deklarasi task LED 2
void Taskprint(void *pvParameters);  // deklarasi task print serial
void TaskPot(void *pvParameters);    // deklarasi task potensiometer

int potValue = 0;   // variabel untuk nilai analog potensiometer
int delayTime = 200; // delay default LED

void setup() {
  Serial.begin(9600); // inisialisasi komunikasi serial

  // membuat task LED 1
  xTaskCreate(TaskBlink1, "task1", 128, NULL, 1, NULL);

  // membuat task LED 2
  xTaskCreate(TaskBlink2, "task2", 128, NULL, 1, NULL);

  // membuat task print serial
  xTaskCreate(Taskprint, "task3", 128, NULL, 1, NULL);

  // membuat task pembaca potensiometer
  xTaskCreate(TaskPot, "task4", 128, NULL, 1, NULL);

  vTaskStartScheduler(); // menjalankan scheduler RTOS
}

void loop() {} // tidak digunakan karena RTOS berjalan di task

void TaskBlink1(void *pvParameters) {
  pinMode(8, OUTPUT); // set pin 8 sebagai output LED
  while(1) {
    Serial.println("Task1"); // debug task 1
    digitalWrite(8, HIGH); // LED ON
    vTaskDelay(delayTime / portTICK_PERIOD_MS); // delay sesuai potensiometer
    digitalWrite(8, LOW); // LED OFF
    vTaskDelay(delayTime / portTICK_PERIOD_MS); // delay sesuai potensiometer
  }
}

void TaskBlink2(void *pvParameters) {
  pinMode(7, OUTPUT); // set pin 7 sebagai output LED
  while(1) {
    Serial.println("Task2"); // debug task 2
    digitalWrite(7, HIGH); // LED ON
    vTaskDelay(2 * delayTime / portTICK_PERIOD_MS); // delay lebih lama
    digitalWrite(7, LOW); // LED OFF
    vTaskDelay(2 * delayTime / portTICK_PERIOD_MS); // delay lebih lama
  }
}

void Taskprint(void *pvParameters) {
  int counter = 0; // variabel penghitung

  while(1) {
    counter++; // increment counter
    Serial.println(counter);   // tampilkan counter
    Serial.println(delayTime); // tampilkan delay saat ini
    vTaskDelay(500 / portTICK_PERIOD_MS); // delay print 500ms
  }
}

void TaskPot(void *pvParameters) {
  while(1) {
    potValue = analogRead(A0); // baca nilai potensiometer
    delayTime = map(potValue, 0, 1023, 100, 1000); // ubah ke range delay LED
    vTaskDelay(100 / portTICK_PERIOD_MS); // update setiap 100ms
  }
}
```
# 5.6.4 Pertanyaan Praktikum
## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
> Kedua task berjalan secara bergantian, bukan secara paralel. FreeRTOS scheduler akan mengatur kapan task pembaca data berjalan dan kapan task display berjalan.

> Task pembaca data akan mengirim data ke queue menggunakan xQueueSend(). Setelah data berhasil dikirim, task display akan menerima data menggunakan xQueueReceive() lalu menampilkannya pada serial monitor.
Karena perpindahan task terjadi sangat cepat, pengguna melihat seolah kedua task berjalan secara bersamaan.
## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan! 
> Program ini memiliki potensi race condition apabila dua task mengakses variabel yang sama secara langsung tanpa mekanisme pengamanan.

> Namun pada praktikum ini risiko race condition berhasil diminimalkan karena komunikasi data dilakukan melalui queue. Queue bertindak sebagai media perantara yang mengatur proses pengiriman dan penerimaan data secara terstruktur.
Dengan adanya queue, task tidak langsung mengakses data milik task lain sehingga sistem menjadi lebih aman [2].
## 3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md. 
```cpp
#include <Arduino_FreeRTOS.h> // library RTOS
#include <queue.h>            // library queue untuk komunikasi antar task
#include <DHT.h>              // library sensor DHT

#define DHTPIN 2   // pin data sensor DHT
#define DHTTYPE DHT11 // tipe sensor DHT11

DHT dht(DHTPIN, DHTTYPE); // inisialisasi sensor DHT

struct readings { // struktur data untuk suhu & kelembaban
  float temp; // variabel suhu
  float hum;  // variabel kelembaban
};

QueueHandle_t my_queue; // deklarasi queue RTOS

void read_data(void *pvParameters);    // task baca sensor
void display_data(void *pvParameters); // task tampilkan data
void setup() {
  Serial.begin(9600); // serial monitor
  dht.begin(); // mulai sensor DHT
  my_queue = xQueueCreate(5, sizeof(struct readings)); // buat queue kapasitas 5
  xTaskCreate(read_data, "read", 128, NULL, 1, NULL);     // task baca sensor
  xTaskCreate(display_data, "display", 128, NULL, 1, NULL); // task tampil data
}

void loop() {} // tidak dipakai karena RTOS

void read_data(void *pvParameters) {
  struct readings data; // variabel penyimpan data sensor
  while(1) {
    data.temp = dht.readTemperature(); // baca suhu
    data.hum = dht.readHumidity();      // baca kelembaban
    xQueueSend(my_queue, &data, portMAX_DELAY); // kirim ke queue
    vTaskDelay(2000 / portTICK_PERIOD_MS); // delay 2 detik (sesuai DHT)
  }
}

void display_data(void *pvParameters) {
  struct readings data; // variabel penerima data
  while(1) {
    if(xQueueReceive(my_queue, &data, portMAX_DELAY) == pdPASS) { // ambil data dari queue
      Serial.print("Suhu : "); // tampilkan teks suhu
      Serial.print(data.temp);  // tampilkan nilai suhu
      Serial.println(" C");     // satuan

      Serial.print("Kelembaban : "); // tampilkan teks kelembaban
      Serial.print(data.hum);        // tampilkan nilai kelembaban
      Serial.println(" %");          // satuan
    }
  }
}
```
> Hasil pengujian menunjukkan bahwa nilai suhu dan kelembapan berubah secara dinamis sesuai kondisi lingkungan sekitar.
