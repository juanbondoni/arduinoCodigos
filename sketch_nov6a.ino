const int PIN_LED = LED_BUILTIN;
const int TIEMPO = 120; //tiempo de 120 ms

typedef struct morse{
    char letra;
    const char* codigo;
};

const morse tabla[]={
  {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},
  {'E', "."},     {'F', "..-."},  {'G', "--."},   {'H', "...."},
  {'I', ".."},    {'J', ".---"},  {'K', "-.-"},   {'L', ".-.."},
  {'M', "--"},    {'N', "-."},    {'O', "---"},   {'P', ".--."},
  {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
  {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},
  {'Y', "-.--"},  {'Z', "--.."},
  {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
  {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
  {'8', "---.."}, {'9', "----."},
  {' ', " "}   // espacio entre palabras
};
const int CantidadDeLetras=37; //cantidad de letras de la tabla de arriba

void Punto()
{
  digitalWrite(PIN_LED,HIGH);
  delay(TIEMPO);
  digitalWrite(PIN_LED,LOW);
}

void Raya()
{
  digitalWrite(PIN_LED,HIGH);
  delay(TIEMPO*3); //la raya equivale a 3 unidades de tiempo
  digitalWrite(PIN_LED,LOW);
}

void PausaLetra(){ delay(TIEMPO*2);} //Pausa entre letras
void PausaPalabra(){ delay(TIEMPO*4);} //Pausa entre palabras

//ante un letra, te devuelve el codigo morse de dicha letra
const char* CodigoMorse(char c)
{
  for(int i=0;i<CantidadDeLetras;i++)
    if(tabla[i].letra == c)
      return tabla[i].codigo;
  
  return ""; //vacio si no es ninguna letra 
}

void ejecucionDefrase(char* frase)
{
  int cantLetras=strlen(frase);
  for(int i=0;i<cantLetras;i++)
  {
    if(frase[i]!= ' ')
    {
      const char* codigo=CodigoMorse(frase[i]); //le paso la letra y recibo su codigo morse

      for(int j=0;j<strlen(codigo);j++)
      {
        if(codigo[j]=='.')
          Punto();
        else
          Raya();
        delay(TIEMPO);//tiempo entre simbolo morse  
      }
      PausaLetra();
    }
    else
    PausaPalabra();//termino la palabra
  }
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);
}
const char* palabra="JUAN BONDONI";
void loop() {
  if(Serial.available()>0)
  {
    Serial.println(F("Listo. Escribi cualquier tecla + Enter para transmitir."));
    char c=Serial.read();

    Serial.print(F("Recibido '"));
    Serial.print(c);
    Serial.println(F("' -> Transmitiendo en Morse..."));

    delay(2000); //un delay de 2 segundos antes de mostrar la palabra
    ejecucionDefrase(palabra);
  }
}
