# Sistem de Blocare Inteligent (Smart Lock) cu Arduino

Un proiect de sistem de securitate integrat care utilizează o placă Arduino pentru a controla un mecanism de blocare electronic bazat pe cod PIN.

## Caracteristici Tehnice
* **Arhitectură de Control:** Implementare bazată pe Mașină cu Stări Finite (FSM) cu 4 stări distincte: "LOCKED", "ENTERING", "UNLOCKED" și "ALARM".
* **Securitate:** Sistemul permite maximum 3 încercări greșite înainte de a declanșa o alarmă sonoră de 10 secunde.
* **Multitasking Non-blocking:** Utilizarea funcției "millis()" pentru gestionarea intervalelor de timp (durata de deblocare și ritmul alarmei), permițând procesorului să rămână receptiv fără a fi blocat de funcții "delay()".
  **Feedback Audio-Vizual:** Utilizarea unui buzzer pentru confirmarea tastării și a unui servomotor pentru acționarea fizică a încuietorii.

## Componente Utilizate
  **Microcontroler:** Placă compatibilă Arduino.
  **Actuatoare:** Servomotor (pentru controlul încuietorii) și Buzzer (pentru feedback sonor).
  **Input:** 5 butoane (4 pentru cifrele PIN-ului și 1 pentru activare/confirmare).

## Logica Sistemului (Stări)
1. **LOCKED (Blocat):** Servomotorul este la 0 grade. Sistemul așteaptă apăsarea oricărui buton pentru a începe introducerea codului.
2. **ENTERING (Introducere):** Colectează o secvență de 4 cifre. La final, compară codul introdus cu cel salvat în memorie.
3. **UNLOCKED (Deblocat):** Dacă codul este corect, servomotorul se rotește la 90 de grade timp de 5 secunde, apoi revine automat la starea de blocare.
4. **ALARM (Alarmă):** După 3 încercări eșuate, sistemul blochează accesul și emite un semnal sonor intermitent timp de 10 secunde.

## Configurare
1. Conectați butoanele la pinii digitali specificați în cod (2, 4, 8, 11, 13).
2. Conectați servomotorul la pinul 3 și buzzerul la pinul 12.
3. Încărcați codul folosind Arduino IDE.
4. Codul PIN implicit este setat în variabila "PINCorect".
