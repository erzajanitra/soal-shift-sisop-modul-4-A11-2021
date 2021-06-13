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
  
* Fungsi untuk membuat log ketika `rename` dan `mkdir`<br/>
Log dibuat untuk mencatat apabila user melakukan `rename` folder dan `mkdir`, dimana terdapat pada fungsi `makeLog` yang merupakan fungsi yang sama untuk membuat log pada nomor 4. Penjelasan akan diletakkan pada nomor 4.

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
```
 if(strcmp(sys_call,"RENAME")==0){
        fprintf(LOGFILE4, "INFO::%d%02d%02d-%02d:%02d:%02d:%s::/%s::/%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
        fprintf(LOGFILE1, "%s : %s -> %s\n", sys_call, data.path1, data.path2);	
    }else if(strcmp(sys_call,"MKDIR")==0 ){
    	fprintf(LOGFILE1, "%s : %s\n", sys_call, data.path1);
        fprintf(LOGFILE4, "INFO::%d%02d%02d-%02d:%02d:%02d:%s::/%s::/%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
    }
```
  penyimpanan informasi log ada pada LOGFILE1 dengan format jika RENAME maka `oldname -> newname` dan jika MKDIR maka format hanya `newname`
### Kendala yang dialami
1. Kesulitan untuk mendapatkan path asli pada *getattr* dan *readdir* sehingga fuse tidak berhasil, seperti folder fuse yang kosong atau folder fuse tidak bisa dibuka. Solusinya kami memperbaiki fungsi *prosesPath* kami agar bisa mendapatkan path asli yang benar.
### Screenshot Eror
1. Eror ketika membuka folder fuse <br/>
![messageImage_1622425486034](https://user-images.githubusercontent.com/75319371/121636213-c2bb2980-cab1-11eb-90a3-250d224fb797.jpg)

## No 2
### 2a
**Soal :** Jika sebuah direktori dibuat dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan
nama isi sesuai kasus nomor 1 dengan algoritma tambahan ROT13 (Atbash + ROT13).
```
    bool rx_contains(char *dir){
    for(int i=0; i<rx_last_idx; i++){
        if(!strcmp(rx_directory[i].DIR, dir)) return true;
    }
    return false;
}
```
   Fungsi tersebut digunakan untuk mengecek apakah nama folder terdapat string *RX_*. Apabila benar terdapat string tersebut maka akan melakukan *return* true sehingga bisa melakukan proses encode, seperti pada fungsi `rx_insert` dibawah ini.
 ```
   void rx_insert(char* dir, int chiper){
    sprintf(rx_directory[rx_last_idx].DIR, "%s", dir);
    rx_directory[rx_last_idx].CHIPER = chiper;
    rx_last_idx++;
}
```
  Fungsi tersebut digunakan untuk melakukan encode dengan algoritma tambahan ROT13. Setelah mengecek path, nama file atau folder dalam folder *RX_* akan terencode menggunakan algoritma baru. Fungsi ini menyambungkan path dari foldername/filename yang sudah terencode dengan path dari */home/usr/Downloads* dengan meletakkan pada index terakhir. Pertama akan meng-encode foldername, kemudian meng-encode filename.
  
### 2b
**Soal :** Jika sebuah direktori di-rename dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan
nama isi sesuai dengan kasus nomor 1 dengan algoritma tambahan Vigenere Cipher dengan key “SISOP” (Case-sensitive, Atbash + Vigenere). <br/>
* Karena merupakan case-sensitive maka butuh mengecek untuk dua case, yaitu *lowercase* dan *uppercase*. Sehingga string tetap menjadi *lowecase* atau *uppercase*, tidak berubah(terganti menjadi *lowercase* atau *uppercase*). Kemudian, mengenkripsi string tersebut dengan atbash + viginere cipher. Viginere cipher adalah metode enkripsi yang  menggunakan metode substitusi polialfabetik oleh deretan sandi dari caesar cipher. Oleh karena itu, pada *for loop* perlu melakukan atbash cipher seperti nomor 1, lalu mengimplementasikan enkripsi vigenere cipher dengan menggunakan mod 26 untuk. <br/>

### 2c
**Soal :** Apabila direktori yang terencode di-rename (Dihilangkan “RX_” nya), maka folder menjadi tidak terencode dan isi direktori tersebut akan terdecode berdasar nama
aslinya.<br/>
* Mengecek apakah nama direktori tersebut memiliki string *RX_*, jika tidak maka folder dan file didalam direktori tersebut akan terencode kembali secara rekursif. Sama seperti cara nomor 1, pada fungsi `rename` perlu mengecek path asli dengan fungsi *prosesPath* agar path yang diambil benar dan dapat terdecode kembali.
<br/>

### 2d
**Soal :** Setiap pembuatan direktori terencode (mkdir atau rename) akan tercatat ke sebuah log file beserta methodnya (apakah itu mkdir atau rename).
<br/>
* Fungsi log file kami gabungkan pada fungsi `makeLog` dimana akan dijelaskan pada nomor 4.
<br/>

### 2e
**Soal :** Pada metode enkripsi ini, file-file pada direktori asli akan menjadi terpecah menjadi file-file kecil sebesar 1024 bytes, sementara jika diakses melalui
filesystem rancangan Sin dan Sei akan menjadi normal. 
<br/>
* Metode memecah file-file kecil sebesar 1024 bytes ini terdapat pada fungsi encrypt dan decrypt, baik pada algoritma baru yang ditambah ROT13 dan algoritma baru yang menggunakan case sensitive dan vigenere cipher
<br/>

### Kendala yang dialami
1. Kami mengalami kesulitan untuk mengimplementasikan algoritma untuk no 2b karena perlu menggabungkan dua jenis cipher.

## No 3
* Mengecek apakah nama direktori memiliki awalan *A_is_a_*, jika benar maka direktori tersebut adalah direktori spesial. Untuk membuat direktori spesial yaitu menggunakan *mknod*. Hal ini juga berlaku untuk direktori yang direname menjadi *A_is_a_*, sedangkan apabila nama direktori dikembalikan menjadi tidak memiliki awalan tersebut maka menjadi direktori normal.
* Direktori spesial adalah semua nama file pada folder fuse akan berubah menjadi lowercase insensitive dan diberi ekstensi baru berupa nilai
desimal dari binner perbedaan namanya.

### Kendala yang dialami
1. Kesulitan dalam menjadikan lowercase insensitive dan mengubah ekstensi dari desimal binner perbedaan namanya.

## No 4
### 4a penyimpanan log terdapat pada `/home/tsania/SinSeiFS.log`
* Membuat file SinseiFS.log pada fungsi `makeLog`
```
    FILE * LOGFILE = fopen(logPath, "a");
```
   File SinSeiFS.log ini dibuat pada */home/tsania/SinseiFS.log* sesuai dengan permintaan soal. Menggunakan fopen dengan command *append* agar string yang dicetak pada file log tersebut terappend dengan string yang sudah tersimpan sebelumnya, sehingga tidak terjadi *overwrite* file. 
   
### 4b format INFO dan WARNING
* Membuat format info dan warning fungsi `makeLog`
```
}else if(strcmp(sys_call,"RMDIR")==0 || strcmp(sys_call,"UNLINK")==0){
        fprintf(LOGFILE4, "WARNING::%d%02d%02d-%02d:%02d:%02d:%s::/%s::/%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
    }else{
        fprintf(LOGFILE4, "INFO::%d%02d%02d-%02d:%02d:%02d:%s::/%s::%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
    }
```
   fungsi makeLog yang dibuat disengaja dibuat bersamaan dengan log nomor 1. sehingga percabangannya lebih banyak dan lebih spesifik. format sudah sesuai dengan permintaan soal dimana timestamp harus mengoutputkan 2 digit pada bagian tanggal dan waktunya. kemudian diikuti jenis sys_call dan detail perubahannya. 
    
### 4c WARNING dioutputkan saat system_call adalah RMDIR dan UNLINK
*  WARNING hanya dioutputkan ketika terjadi UNLINK atau RMDIR.
```
else if(strcmp(sys_call,"RMDIR")==0 || strcmp(sys_call,"UNLINK")==0){
        fprintf(LOGFILE4, "WARNING::%d%02d%02d-%02d:%02d:%02d:%s::/%s::/%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
    }
```
### 4d INFO dioutputkan saat system_call selain RMDIR dan UNLINK
*  WARNING hanya dioutputkan selain ketika UNLINK atau RMDIR pada source code dibawah diambil sebagai contoh MKDIR dan RENAME.
```
  if(strcmp(sys_call,"RENAME")==0){
        fprintf(LOGFILE4, "INFO::%d%02d%02d-%02d:%02d:%02d:%s::/%s::/%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
        fprintf(LOGFILE1, "%s : %s -> %s\n", sys_call, data.path1, data.path2);	
    }else if(strcmp(sys_call,"MKDIR")==0 ){
    	fprintf(LOGFILE1, "%s : %s\n", sys_call, data.path1);
        fprintf(LOGFILE4, "INFO::%d%02d%02d-%02d:%02d:%02d:%s::/%s::/%s\n",timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, sys_call, data.path1, data.path2);
    }
```
### 4e format baris pada log.

Level : Level logging, dd : 2 digit tanggal, mm : 2 digit bulan, yyyy : 4 digit tahun, HH : 2 digit jam (format 24 Jam),MM : 2 digit menit, SS : 2 digit detik, CMD : System Call yang terpanggil, DESC : informasi dan parameter tambahan. Seperti yang dapat dilihat pada gambar :
![image](https://user-images.githubusercontent.com/69724694/121797375-ffba2400-cc49-11eb-9260-93ed0e136bae.png)

### Kendala yang dialami
1. Jenis Sys_call yang sedang berjalan tidak bisa muncul pada string yang disimpan pada file log. yaitu WARNING. dikarenakan pengaturan path pada UNLINK dan RMDIR masih salah sehingga file atau folder tidak bisa dihapus dan masih belum menemukan solusinya. dengan demikian yang hanya dapat terekam dalam logfile adalah level INFO.

### Screenshot Eror
![image](https://user-images.githubusercontent.com/69724694/121797375-ffba2400-cc49-11eb-9260-93ed0e136bae.png)


