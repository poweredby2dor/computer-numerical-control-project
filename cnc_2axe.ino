#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int analogPin0 = 0; // Buton START
int analogPin1 = 1; // Buton Y
int analogPin2 = 2; // Buton X
int analogPin5 = 5; // Senzori limitrare
int start, butonx, butony, limit, x = 0, y = 0, a = 0, b = 0;
int spd = 1; // delay pas motor - viteza
float n, j, k; // numaratoare

int dir2 = 8; // Pini pentru drivere
int dir1 = 12;
int step2 = 10;
int step1 = 11;



void setup() //                        --- VOID SETUP ---
{
  pinMode(step1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(step2, OUTPUT);
  pinMode(dir2, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT); // Initializare LED onboard
  digitalWrite(LED_BUILTIN, HIGH); // Pornire LED Galben
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(" Studenti: ");
  lcd.setCursor(0, 1);
  lcd.print("  Andrei Chivu ");

  delay(2000); // 2 secunde

  lcd.setCursor(0, 1);
  lcd.print("  Tudor Cernat ");
  delay(2000); // 2 secunde
  lcd.setCursor(0, 1);
  lcd.print("  Adrian Ferent ");

  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sisteme de  ");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("conducere  ");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("a robotilor  ");
  lcd.setCursor(0, 1);
  delay(1000);
  lcd.print(" P R O I E C T  ");
  delay(1000);

  //                  CALIBRARE

  lcd.clear();
  limit = analogRead(analogPin5);
  lcd.print("Calibrare...");
  digitalWrite(dir1, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Axa X     ");

  while (limit > 500) // Axa X
  {
    digitalWrite(step1, HIGH);
    delay(spd);
    digitalWrite(step1, LOW);
    delay(spd);

    limit = analogRead(analogPin5);
  }

  n = 0;
  digitalWrite(dir1, HIGH);

  while (n < 1001)
  {
    digitalWrite(step1, HIGH);
    delay(spd);
    digitalWrite(step1, LOW);
    delay(spd);
    n=n+1;
  }

  delay(1000); // schimbare axe
  lcd.setCursor(0, 1);
  lcd.print("Axa Y     ");
  limit = analogRead(analogPin5);
  digitalWrite(dir2, LOW);

  while (limit > 500) // Axa Y
  {
    digitalWrite(step2, HIGH);
    delay(spd);
    digitalWrite(step2, LOW);
    delay(spd);

    limit = analogRead(analogPin5);
  }

  n = 0;
  digitalWrite(dir2, HIGH);

  while (n < 1001)
  {
    digitalWrite(step2, HIGH);
    delay(spd);
    digitalWrite(step2, LOW);
    delay(spd);
    n=n+1;
  }

  lcd.clear();
  lcd.print("Calibrare");
  lcd.setCursor(0, 1);
  lcd.print(" terminata");
  delay(2500);

  lcd.clear();
  digitalWrite(LED_BUILTIN, LOW); // Oprire LED Galben
}

void loop() //                        --- VOID LOOP ---
{
  start = analogRead(analogPin0);
  butonx = analogRead(analogPin2);
  butony = analogRead(analogPin1);

  if (butonx > 950) // Buton X
  {
    x = x + 1;
    if (x > 25) // limita axa X
      x = 0;
    //lcd.print(butonx);
    delay(500);
  }

  if (butony > 950) // Buton Y
  {
    y = y + 1;
    if (y > 40)
      y = 0;
    //lcd.print(butony);
    delay(500);
  }

  lcd.clear();
  lcd.print("X: ");
  lcd.print(x);
  lcd.setCursor(8, 0);
  lcd.print("Y: ");
  lcd.print(y);

  if (start > 950 && (x != a || y != b )) //          Buton START
  {
    lcd.setCursor(0, 1);
    lcd.print("Pozitionez axele");

// SETAREA DIRECTIILOR

  if ((x - a) > 0)
    {
      digitalWrite(dir1, HIGH); // X+
      j = x - a; 
    }
    
  else
    {
      digitalWrite(dir1, LOW); // X-
      j = a - x;
    }

    j = j * 2000;
    
   if ((y - b) > 0)
    {
      digitalWrite(dir2, HIGH); // Y+
      k = y - b; 
    }
    
  else
    {
      digitalWrite(dir2, LOW); // Y-
      k = b - y;
    }

    k = k * 2000;
    n = 0;

// INCEPEREA POZITIONARII

  limit = analogRead(analogPin5);  
  while ((n < j || n < k) && n != 999999)
    {
      if ( n < j )
        {
          digitalWrite(step1, HIGH);
        }
      if ( n < k )
        {
          digitalWrite(step2, HIGH);
        }

    delay(spd);
    digitalWrite(step1, LOW);
    digitalWrite(step2, LOW);
    delay(spd);
    n = n + 1;
    
    limit = analogRead(analogPin5);

    if (limit < 500)
      {
          n = 999999;
      }
    
    } // Final WHILE

    if (n != 999999)
      {
        a = x; // extraterestrii
        b = y;
        lcd.setCursor(0, 1);
        lcd.print("Executie term.  ");
        delay(3000);
      }
  } // final START
    
    if (n != 999999)
      {
        lcd.setCursor(0, 1);
        lcd.print("A: ");
        lcd.print(a);
        lcd.setCursor(8, 1);
        lcd.print("B: ");
        lcd.print(b);
        delay(100);
      }
      else
      {
        lcd.clear();
        lcd.print("Limita atinsa!");
        lcd.setCursor(0, 1);
        lcd.print("Verificati prog.");
        delay(2500);
        lcd.clear();
        lcd.print("Apasati butonul");
        lcd.setCursor(0, 1);
        lcd.print(" RESET.");
        delay(2500);
      } // final afisaj

} // final void loop
