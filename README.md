# Penjelasan Soal Shift Modul 4

## No 1
* Fungsi atbash cipher
``` 
    char msg[1024] ;
    strcpy(msg, message) ;
    int x=strlen(msg);
    int i ;
    for(i = 0 ; i < x ; i++) {
        if (msg[i] >= 'A' && msg[i] <= 'Z') 
            msg[i] = 'Z' - (msg[i] - 'A') ;
        else if (msg[i] >= 'a' && msg[i] <= 'z') 
            msg[i] = 'z' - (msg[i] - 'a') ;
 
    }
    char* cipher = msg ;
    return cipher ;
```
Cara kerja algoritma atbash cipher adalah mencerminkan/membalikkan huruf untuk melakukan decrypt dan encrypt, misalnya a menjadi z, b menjadi y, dan seterusnya. Sehingga pada fungsi ini hanya perlu membalik huruf tersebut untuk *uppercase* dan *lowercase*. String yang akan di decrypt atau encrypt disimpan pada sebuah *char msg* untuk mengantisipasi alamat yang menunjuk ke alamat lain karena merupakan sebuah pointer. 

* Fungsi untuk mendapatkan path asli
``` 
    char *atoz;
    if (strcmp(path, "/") != 0) {
        atoz= strstr(path, "/AtoZ_");
        if (atoz) {
            // Jika ada, set cekk = 1 
            cekk = 1 ;
            cekaz = 1 ;
            // Geser pointer kekanan agar / nya ga kena
            atoz++ ;
        }
    }
```
  Pertama perlu mengecek apakah folder pada `/home/usr/Downloads` terdapat directory dengan nama `AtoZ_folder`, kemudian menggeser pointer karena path string yang dicek dimulai dari *'/'*.
``` 
     x = 0 ;
        while ((encName = strtok_r(cut, "/", &cut))) {
            bzero(temp, 1024) ;
            if(x == 0) {
                strcpy(temp, encName) ;
                // Sambungkan realpath
                strcat(realPath, temp) ;
                x = 1 ;
                continue ;
            }
```
  Apabila benar terdapat directory `AtoZ_folder` maka menggunakan *strtok_r* untuk mengecek masing-masing folder atau filename yang dipisahkan oleh *'/'*. Ketika sudah selesai mengecek hingga ujung path, kita perlu mengecek apakah file tersebut sesuai dengan file path relatif.
``` 
    char *dot = strchr(encName, '.') ;
    char fileName[1024] ;
    bzero(fileName, 1024) ;
    // Kalau ada extension
    if (dot) {
    // Untuk dapetin nama file nya doang
        strncpy(fileName, encName, strlen(encName) - strlen(dot)) ;
        strcpy(fileName, atbash(fileName)) ;
        strcat(fileName, dot) ;
      }
   // Kalau ga ada extension
    else {
        strcpy(fileName, encName) ;
        strcpy(fileName, atbash(fileName)) ;
    }
```
  Untuk file, perlu mengecek apakah file tersebut memiliki extension atau tidak karena extension tidak perlu di-encode. Setelah itu, filename di encode dan di *strcat* dengan path sebelumnya.
``` 
    char folderName[1024] ;
    bzero(folderName, 1024) ;
    strcpy(folderName, encName) ;
    strcpy(folderName, atbash(folderName)) ;
    strcat(realPath, folderName) ;
            }
```
  Untuk folder, kita bisa langsung melakukan encode nama folder tersebut. Foldername juga perlu di *strcat* dengan path sebelumnya.
  
* Fungsi untuk membuat log ketika `rename` dan `mkdir`
``` 
    kodingan
```
Log dibuat untuk mencatat apabila user melakukan `rename` folder dan `mkdir`. Menggunakan mode 1 untuk `rename`, dan mode 2 untuk `mkdir`. Log akan mencatat nama sebelum dan sesudah rename foldername untuk `rename` dan nama folder baru untuk `mkdir`

* Penjelasan `fuse_operations` <br/>
    Menggunakan `readdir`, `read`, dan`readdir` untuk menjalankan fuse. Ketika operasi fuse ini digunakan agar bisa mendapatkan file dan folder dari */home/usr/Downloads* secara rekursif sehingga semua elemen terpindah ke dalam fuse. Sedangkan, `mkdir` untuk membuat directory baru pada folder fuse dan `rename` untuk mengganti nama pada folder fuse.

### Output
1. **1a** Jika sebuah direktori dibuat dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode. <br/>
2. **1b** Jika sebuah direktori di-rename dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode. <br/>
_isi folder test_  <br/>
![image](https://user-images.githubusercontent.com/75319371/121634674-33147b80-caaf-11eb-809d-e6706af6d286.png)<br/>
_isi folder test setelah direname menjadi AtoZ_test_ <br/>
![image](https://user-images.githubusercontent.com/75319371/121634726-4c1d2c80-caaf-11eb-9d84-044181141e26.png) <br/>
3. **1c** Apabila direktori yang terenkripsi di-rename menjadi tidak ter-encode, maka isi direktori tersebut akan terdecode
_folder yang terenkripsi_ <br/>
![image](https://user-images.githubusercontent.com/75319371/121634925-9e5e4d80-caaf-11eb-9636-caa59dbc83e9.png)  <br/>
_isi folder_<br/>
![image](https://user-images.githubusercontent.com/75319371/121634996-bc2bb280-caaf-11eb-9c88-b6284e4fa672.png)<br/>
_setelah direname menjadi tidak ter-encode_<br/>
![image](https://user-images.githubusercontent.com/75319371/121635270-28a6b180-cab0-11eb-8775-6f04dd8155b5.png) <br/>
_isi folder_<br/>
![image](https://user-images.githubusercontent.com/75319371/121635305-352b0a00-cab0-11eb-82b3-752b49e817a6.png) <br/>
4. **1d** Setiap pembuatan direktori ter-encode (mkdir atau rename) akan tercatat ke sebuah log.

### Kendala yang dialami
1. Kesulitan untuk mendapatkan path asli pada *getattr* dan *readdir* sehingga fuse tidak berhasil, seperti folder fuse yang kosong atau folder fuse tidak bisa dibuka. Solusinya kami memperbaiki fungsi *prosesPath* kami agar bisa mendapatkan path asli yang benar.
### Screenshot Eror
1. Eror ketika membuka folder fuse <br\>
![messageImage_1622425486034](https://user-images.githubusercontent.com/75319371/121636213-c2bb2980-cab1-11eb-90a3-250d224fb797.jpg)

## No 4
