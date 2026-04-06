# 1. Pada kondisi apa program masuk ke blok if? 
Program masuk ke blok if ketika nilai timeDelay <= 100.
# 2. Pada kondisi apa program masuk ke blok else? 
Program masuk ke blok else ketika timeDelay > 100.
# 3. Apa fungsi dari perintah delay(timeDelay)? 
- Mengatur jeda waktu LED menyala atau mati
- Menentukan kecepatan kedipan LED
- Semakin besar nilai delay → LED semakin lambat
- Semakin kecil nilai delay → LED semakin cepat
# 4. Jika program yang dibuat memiliki alur mati → lambat → cepat → reset (mati), ubah menjadi LED tidak langsung reset → tetapi berubah dari cepat → sedang → mati dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md! 
# Program Percabangan LED

int ledPin = 6;
→ Menentukan pin LED pada Arduino

int timeDelay = 1000;
→ Nilai awal delay (kedip lambat)

void setup() {
  pinMode(ledPin, OUTPUT);
}
→ Mengatur pin LED sebagai output

void loop() {
→ Program berjalan terus menerus

digitalWrite(ledPin, HIGH);
→ LED menyala

delay(timeDelay);
→ Menunggu sesuai delay

digitalWrite(ledPin, LOW);
→ LED mati

delay(timeDelay);
→ Menunggu sesuai delay

if (timeDelay > 300) {
→ Kondisi saat LED masih lambat menuju cepat
timeDelay -= 100;
→ Mempercepat kedipan
}

else if (timeDelay > 100) {
→ Kondisi transisi ke kecepatan sedang
timeDelay -= 50;
→ Perubahan lebih halus
}

else {
→ Kondisi ketika sudah sangat cepat
digitalWrite(ledPin, LOW);
→ LED dimatikan
delay(2000);
→ Jeda sebelum reset
timeDelay = 1000;
→ Reset ke kondisi awal
}
}
