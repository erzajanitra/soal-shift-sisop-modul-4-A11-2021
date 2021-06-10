# Penjelasan Soal Shift Modul 4

## No 1
* Fungsi atbash cipher
``` 
    kodingan
```
Cara kerja algoritma atbash cipher adalah mencerminkan/membalikkan huruf untuk melakukan decrypt dan encrypt, misalnya a menjadi z, b menjadi y, dan seterusnya. Sehingga pada fungsi ini hanya perlu membalik huruf tersebut untuk *uppercase* dan *lowercase*. String yang akan di decrypt atau encrypt disimpan pada sebuah *char msg* untuk mengantisipasi alamat yang menunjuk ke alamat lain karena merupakan sebuah pointer. 

* Fungsi untuk mendapatkan path asli
``` 
    kodingan
```
  Pertama perlu mengecek apakah folder pada `/home/usr/Downloads` terdapat directory dengan nama `AtoZ_folder`, kemudian menggeser pointer karena path string yang dicek dimulai dari *'/'*.
``` 
    kodingan
```
  Apabila benar terdapat directory `AtoZ_folder` maka menggunakan *strtok_r* untuk mengecek masing-masing folder atau filename yang dipisahkan oleh *'/'*. Ketika sudah selesai mengecek hingga ujung path, kita perlu mengecek apakah file tersebut sesuai dengan file path relatif.
``` 
    kodingan
```
  Untuk file, perlu mengecek apakah file tersebut memiliki extension atau tidak karena extension tidak perlu di-encode. Setelah itu, filename di encode dan di *strcat* dengan path sebelumnya.
``` 
    kodingan
```
  Untuk folder, kita bisa langsung melakukan encode nama folder tersebut. Foldername juga perlu di *strcat* dengan path sebelumnya.
  
* Fungsi untuk membuat log ketika `rename` dan `mkdir`
``` 
    kodingan
```
Log dibuat untuk mencatat apabila user melakukan `rename` folder dan `mkdir`. Menggunakan mode 1 untuk `rename`, dan mode 2 untuk `mkdir`. Log akan mencatat nama sebelum dan sesudah rename foldername untuk `rename` dan nama folder baru untuk `mkdir`

* Penjelasan `fuse_operations` 
    Menggunakan `readdir`, `read`, dan`readdir` untuk menjalankan fuse. Ketika operasi fuse ini digunakan agar bisa mendapatkan file dan folder dari */home/usr/Downloads* secara rekursif sehingga semua elemen terpindah ke dalam fuse. Sedangkan, `mkdir` untuk membuat directory baru pada folder fuse dan `rename` untuk mengganti nama pada folder fuse.

### Output

### Kendala yang dialami

### Screenshot Eror

## No 2

## No 4
