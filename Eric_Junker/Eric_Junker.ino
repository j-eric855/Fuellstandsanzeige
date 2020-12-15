

/*
  Funktion:         Messwertanzeige; mit Hilfe eines Tasters wird eine Messwertanzeige aktiviert;
                    bei einem Messwert < 3 gehen nur grüne LEDs an
                    bei einem Messwert 3-5 gehen nur gelbe LEDs an
                    bei einem Messwert > 5 gehen nur rote LEDs an
  Programierer:     Eric Junker
  letzte Änderung:  15.12.2020
  Version:           V1.0
  Hardware:         Pin 2 Taster Pull-Down
                    Pin 5-7 grüne LEDs
                    Pin 9-11 gelbe LEDs
                    Pin 12-13 rote LEDs
*/

#include <OneButton.h>                          // Bibliothek wird eingebunden um das Tastenentprellen zu unterbinden

OneButton taster(2, false);                     //Taster wird auf Pin 2 - als Pull-Down taster - festgelegt
byte led[8] = {5, 6, 7, 9, 10, 11, 12, 13};     //Angabe der Pins für die LEDs - in einem Array
byte ledZustand[3][8] = {                       //Zustände der LEDs bei den drei verschiedenen Wertebereichen
  {1, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 1},
};
byte messwert = 7;                              //messwert Variable, zeigt den Füllstand an
bool merkerPower = false;                       //merker für die angabe ob der Taster gedrückt wurde


void setup()
{
  for (byte i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);                    //Pins in dem Array led werden als Ausgänge deklariert
  }

  taster.attachClick(Taster_Funktion);

}


void loop()
{
  taster.tick();

  if (merkerPower == true)                        //Bei betätigen des Tasters wird die Füllstandsanzeige aktiviert
  {

    if (messwert < 3)
    {
      for (byte i = 0; i < 8; i++)
      {
        digitalWrite(led[i], ledZustand[0][i]);   //Bei einem Füllstand bis zum Wert 2 wird die 1te Zeile des ledZustands Arrays ausgeführt
      }
    }
    if ((messwert > 2) && (messwert < 6))
    {
      for (byte i = 0; i < 8; i++)
      {
        digitalWrite(led[i], ledZustand[1][i]);   //Bei einem Füllstand vom Wert 3 bis 5 wird die 2te Zeile des ledZustands Arrays ausgeführt
      }
    }
    if (messwert > 5)
    {
      for (byte i = 0; i < 8; i++)
      {
        digitalWrite(led[i], ledZustand[2][i]);   //Bei einem Füllstand ab einem Wert 6 wird die 3te Zeile des ledZustands Arrays ausgeführt
      }
    }
  }

  else
  {
    for (byte i = 0; i < 8; i++)
    {
      digitalWrite(led[i], LOW);                   //Bei erneutem drücken des Tasters wird die Füllstandsanzeige deaktiviert
    }

  }

}


void Taster_Funktion()
{
  merkerPower = !merkerPower;                       //Taster wird als Schalter benutzt
}

