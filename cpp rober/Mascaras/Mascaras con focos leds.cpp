/*Ejemplo32
Roberto Lopez Rodriguez 
Manejo de mascaras 
29/05/24"
*/
int leds[8] = {1, 2, 3, 4 ,5, 6, 7,8};
int val;  
class Mascaras
{
    //Atributos
    short int mask;
    public:
        Mascaras(short int mask = 0);
        void onMask(short int);
        void offMask(short int);
        short int getMask();

};

Mascaras::Mascaras(short int mask)
{
    this->mask = mask;
}
void Mascaras::onMask(short int aux)
{
    this->mask |= aux; //Encender
}
void Mascaras::offMask(short int aux)
{
    this->mask &= aux; //Apagar
}
short int Mascaras::getMask()
{
    return this-> mask;
}

Mascaras obj;

void setup() {
  Serial.begin(9600);
  for(int i = 0; i<8; i++)
  pinMode(leds[i], OUTPUT);
  
 
  
}

void loop() {
   if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int hexValue = strtol(input.c_str(), NULL, 16);
    
     Serial.print("Valor hexadecimal recibido: ");
    Serial.print(input);
     Serial.print('\n');
     Serial.print("Quieres Encender [1] o apagar [0] los leds: ");
  while (!Serial.available());
     short int val2 = Serial.parseInt();
  if(val2 == 1)
    obj.onMask(hexValue);
  else if(val2 == 0)
    obj.offMask(hexValue);
  for (int i = 0; i < 8; i++) {
      if (obj.getMask() & (1 << i)) {
        digitalWrite(leds[i], HIGH);
      } else {
        digitalWrite(leds[i], LOW);
      }
    }
  }
}