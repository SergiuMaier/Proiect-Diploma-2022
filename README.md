## Sistem de evaluare a infectării cu virusul SARS-CoV-2 utilizând temperatura corporală

### 📑 Scurtă descriere:

Sistemul detectează temperatura corporală după poziționarea mâinii în intervalul de scanare predefinit. 
Valorile achiziționate de la senzori sunt transmise în timp real prin Bluetooth către telefonul mobil și afișate într-o [aplicație](http://ai2.appinventor.mit.edu/#4972066926624768) realizată în mediul online de dezvoltare MIT App Inventor. 
Pe lângă asta, din aplicație pot fi modificate setările implicite ale sistemului. 

La alegerea utilizatorului, valorile afișate în aplicație pot fi stocate într-o foaie de calcul Google pentru o analiză ulterioară.
Pentru această funcționalitate a fost realizat un [script](https://script.google.com/d/1ZvxSbKQELXQpO4ODZA-MBYUkUSaNE9s10FG8xVb0a-EfYcUUJ65DivRc/edit) pe platforma Google Apps Script.

### 📦 Componente:


Sistemul este bazat pe un modul Arduino Nano si următorele componente:

- senzor de temperatură cu IR fără contact MLX90614;
- senzor cu ultrasunete HC-SR04;
- modul Bluetooth HC-05;
- buzzer;
- buton fără reținere;
- 2 x PCB;
- 5 rezistori 1kΩ;
- 5 rezistori 220Ω;
- 4 LED-uri roșii;
- 3 LED-uri verzi;
