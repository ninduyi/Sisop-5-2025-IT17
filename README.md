# Sisop-5-2025-IT-Template

## Kelompok

Nama | NRP
--- | ---
Nabilah Anindya Paramesti | 5027241006
Balqis Sani Sabillah | 5027231002
Muhammad Khairul Yahya | 5027241092

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

[https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb](https://github.com/user-attachments/assets/fb26747c-689e-49a6-b418-8cd1c6a56ea5)


## Laporan

## Soal 1 ## 
---
## Soal 2 ## 
---
## Soal 3 ##

```c
} else if (strcmp(cmd, "user") == true) {
  if (arg[0][0] != '\0') {
    int k = 0;
    while (arg[0][k] != '\0' && k < 32) {
      current_username[k] = arg[0][k];
      k++;
    }
    current_username[k] = '\0';
    printString("Username changed to ");
    printString(current_username);
    printString("\n");
  } else {
    strcpy(current_username, "user");
    printString("Username changed to user\n");
  }
  is_known_command = true;
}

```
### Penjelasan ### 

```c
} else if (strcmp(cmd, "user") == true) {
```
Mengecek apakah perintah `(cmd)` yang diketik user adalah `"user"` 
— artinya ingin mengubah username. 

```c 
  if (arg[0][0] != '\0') {
```
Mengecek apakah ada argumen pertama `(arg[0])` yang diberikan — contohnya: user Tia.  
Jika ada, maka lanjut untuk mengganti `current_username` dengan `string` tersebut.

``` c
    int k = 0;
    while (arg[0][k] != '\0' && k < 32) {
      current_username[k] = arg[0][k];
      k++;
    }
    current_username[k] = '\0';
```
Menyalin karakter demi karakter dari `arg[0]` ke dalam variabel global `current_username`, dengan maksimal 32 karakter.
Ini semacam `strncpy`, tapi ditulis manual.
Diakhiri dengan `\0` untuk menandai akhir `string` (wajib dalam C).

```c 
    printString("Username changed to ");
    printString(current_username);
    printString("\n");
```
Menampilkan pesan bahwa username telah diganti, beserta nama barunya.

``` c
  } else {
    strcpy(current_username, "user");
    printString("Username changed to user\n");
  }
```
Jika tidak ada argumen, maka nama dikembalikan ke default "user".

``` c
  is_known_command = true;
}
```
Menandai bahwa perintah "user" telah dikenali dan diproses oleh shell. Jika tidak diberi ini, maka perintah akan dianggap tidak valid dan dicetak ulang.

## Soal 4 ## 

``` c
} else if (strcmp(cmd, "grandcompany") == true) {
  if (arg[0][0] != '\0') { // Pastikan ada argumen untuk nama GC
    if (strcmp(arg[0], "maelstrom") == true) {
      setTextColor(ATTRIBUTE_MAELSTROM);
      clearScreen(); // Clear dengan warna baru
      strcpy(current_gc_title, "@Storm");
    } else if (strcmp(arg[0], "twinadder") == true) {
      setTextColor(ATTRIBUTE_TWIN_ADDER);
      clearScreen();
      strcpy(current_gc_title, "@Serpent");
    } else if (strcmp(arg[0], "immortalflames") == true) {
      setTextColor(ATTRIBUTE_IMMORTAL_FLAMES);
      clearScreen();
      strcpy(current_gc_title, "@Flame");
    } else {
      printString("Error: Invalid Grand Company specified.\n");
      printString("Usage: grandcompany [maelstrom|twinadder|immortalflames]\n");
    }
  } else {
    printString("Error: Grand Company name required.\n");
    printString("Usage: grandcompany [maelstrom|twinadder|immortalflames]\n");
  }
  is_known_command = true;
}
```
### Penjelasan ###
```c
} else if (strcmp(cmd, "grandcompany") == true) {
```
Mengecek apakah perintah `(cmd)` yang diketik oleh user adalah `"grandcompany"` — artinya `user` ingin bergabung dengan salah satu dari tiga Grand Company.
```c
  if (arg[0][0] != '\0') { 
```
Mengecek apakah `user` memberikan nama Grand Company sebagai argumen pertama `(arg[0])`
```c
    if (strcmp(arg[0], "maelstrom") == true) {
```
Ubah warna teks terminal menjadi warna khas Maelstrom (merah).
```c
      strcpy(current_gc_title, "@Storm");
```
Tambahkan `@Storm` di belakang username pada prompt sebagai tanda bahwa user telah bergabung dengan Maelstrom.
```c
    } else if (strcmp(arg[0], "twinadder") == true) {
      setTextColor(ATTRIBUTE_TWIN_ADDER);
      clearScreen();
      strcpy(current_gc_title, "@Serpent");
```
 Jika user memilih Twin Adder:
- Warna terminal diubah ke kuning.  
- Prompt akan menjadi `user@Serpent`.
```c
    } else if (strcmp(arg[0], "immortalflames") == true) {
      setTextColor(ATTRIBUTE_IMMORTAL_FLAMES);
      clearScreen();
      strcpy(current_gc_title, "@Flame");
```
 Jika user memilih Immortal Flames:
- Warna terminal diubah ke biru.
- Prompt akan menjadi `user@Flame`.
```c
    } else {
      printString("Error: Invalid Grand Company specified.\n");
      printString("Usage: grandcompany [maelstrom|twinadder|immortalflames]\n");
```
Jika nama GC salah (misalnya grandcompany abc), maka tampilkan pesan error.
```c
  } else {
    printString("Error: Grand Company name required.\n");
    printString("Usage: grandcompany [maelstrom|twinadder|immortalflames]\n");
```
Jika tidak ada argumen sama sekali (hanya ketik grandcompany), tampilkan error dan cara pakainya.
```c
  is_known_command = true;
}
```
Menandai bahwa perintah "grandcompany" dikenali dan sudah ditangani.

---
## Soal 5 ## 
### Implementasi Kalkulator Sederhana

Fitur kalkulator memungkinkan pengguna untuk melakukan operasi aritmatika dasar (`add`, `sub`, `mul`, `div`) dari baris perintah.

#### Alur Kerja Perintah Kalkulator:

1.  **Input Pengguna:** Pengguna mengetikkan perintah, misalnya `mul 3 -2`, di dalam *loop* utama fungsi `shell()` di `shell.c`.
2.  **Parsing Perintah:** Fungsi `parseCommand(buf, cmd, arg)` dipanggil untuk memecah input pengguna menjadi tiga bagian:
    * Perintah utama (`cmd`): misal, `"mul"`.
    * Argumen pertama (`arg[0]`): misal, `"3"`.
    * Argumen kedua (`arg[1]`): misal, `"-2"`.
3.  **Identifikasi Perintah:** Di dalam `shell()`, serangkaian `if-else if` digunakan untuk mencocokkan `cmd` dengan perintah yang dikenali.
    ```c
    // shell.c
    if (strcmp(cmd, "add") == true || strcmp(cmd, "sub") == true || ... ) {
        // ... logika kalkulator
    }
    ```
4.  **Konversi Argumen:** Argumen yang masih berupa *string* (`"3"` dan `"-2"`) diubah menjadi tipe data *integer*. Ini dilakukan dengan memanggil fungsi `atoi` dari `std_lib.c`. Fungsi `atoi` ini sudah dirancang untuk dapat menangani angka negatif dengan memeriksa karakter `'-'` di awal *string*.
    ```c
    // shell.c
    atoi(arg[0], &a); // Mengubah argumen pertama menjadi integer a
    atoi(arg[1], &b); // Mengubah argumen kedua menjadi integer b
    ```
5.  **Operasi Aritmatika:**
    * **Penjumlahan (`add`) & Pengurangan (`sub`):** Dilakukan langsung menggunakan operator `+` dan `-` dari bahasa C.
    * **Perkalian (`mul`):** Diimplementasikan menggunakan logika penjumlahan berulang di dalam `shell.c`. Fungsi ini juga menangani tanda negatif dengan menentukan apakah hasil akhir harus negatif atau positif.
    * **Pembagian (`div`):** Memanggil fungsi `div(a, b)` dari `std_lib.c`. Fungsi ini diimplementasikan menggunakan pengurangan berulang dan telah dirancang untuk menangani angka negatif dengan benar serta mencegah pembagian dengan nol.
6.  **Konversi Hasil:** Hasil perhitungan yang berupa *integer* diubah kembali menjadi *string* agar dapat dicetak ke layar. Ini dilakukan menggunakan fungsi `itoa` dari `std_lib.c`, yang juga mampu menangani angka negatif.
    ```c
    // shell.c
    itoa(result, result_str); // Mengubah hasil integer menjadi string
    ```
7.  **Tampilkan Hasil:** *String* hasil akhir dicetak ke layar menggunakan `printString(result_str)`.

---

## Soal 6 ## 
### Implementasi Perintah `yogurt`

Fitur `yogurt` dirancang untuk memberikan salah satu dari tiga respons yang telah ditentukan secara acak setiap kali perintah dipanggil.

#### Alur Kerja Perintah `yogurt`:

1.  **Penyimpanan Respons:** Sebuah *array of strings* bernama `gurt_responses` didefinisikan secara global di `shell.c` untuk menyimpan semua kemungkinan respons.
    ```c
    // shell.c
    char* gurt_responses[] = {
        "yo\n",
        "ts unami gng </3\n",
        "sygau\n"
    };
    int num_gurt_responses = 3;
    ```
2.  **Identifikasi Perintah:** Sama seperti kalkulator, *loop* utama di `shell()` memeriksa apakah perintah yang dimasukkan adalah `"yogurt"`.
3.  **Mendapatkan Nilai "Acak":**
    * Untuk menghasilkan keacakan, sistem memanggil fungsi `getBiosTick()` yang dideklarasikan di `kernel.h` dan diimplementasikan dalam *assembly* di `kernel.asm`.
    * Fungsi ini menggunakan `int 0x1A` untuk membaca *BIOS tick counter*, yaitu sebuah penghitung internal yang terus bertambah sejak komputer dinyalakan. Nilai ini selalu berubah, sehingga dapat digunakan sebagai sumber nilai pseudo-acak yang sederhana.
    ```c
    // shell.c
    tick_value = getBiosTick();
    ```
4.  **Memilih Respons:**
    * Untuk memastikan indeks yang dihasilkan selalu berada dalam rentang yang valid untuk *array* `gurt_responses` (yaitu 0, 1, atau 2), digunakan operasi modulo.
    * Fungsi `custom_unsigned_modulo(tick_value, num_gurt_responses)` dipanggil. Fungsi ini mengambil nilai *tick* dan membaginya dengan jumlah total respons (3). Sisanya (`0`, `1`, atau `2`) digunakan sebagai indeks acak.
    ```c
    // shell.c
    random_index = custom_unsigned_modulo(tick_value, num_gurt_responses);
    ```
5.  **Menampilkan Respons:** Respons yang sesuai dengan indeks acak yang didapat dari *array* `gurt_responses` kemudian dicetak ke layar menggunakan `printString`.
    ```c
    // shell.c
    printString("gurt> ");
    printString(gurt_responses[random_index]);
    ```

---






