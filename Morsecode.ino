int val = 0;
//the length of a small pulse (dit) is set and all other lengths are defined in terms of it (Standard Morse Practice)
int dit = 500;
//Defining a data structure that assigns a character to a string of *s and -s (dits and dats), an array of this structure holds the morse for each letter
typedef struct
  { 
    char character;
    String value;
  } 
  morseDictionary;
  const morseDictionary myDictionaryArr[] 
  {
    {'a', "*-"},
    {'b', "-***"},
    {'c', "-*-*"},
    {'d', "-**"},
    {'e', "*"},
    {'f', "**-*"},
    {'g', "--*"},
    {'h', "****"},
    {'i', "**"},
    {'j', "*---"},
    {'k', "-*-"},
    {'l', "*-**"},
    {'m', "--"},
    {'n', "-*"},
    {'o', "---"},
    {'p', "*--*"},
    {'q', "--*-"},
    {'r', "*-*"},
    {'s', "***"},
    {'t', "-"},
    {'u', "**-"},
    {'v', "***-"},
    {'w', "*--"},
    {'x', "-**-"},
    {'y', "-*--"},
    {'z', "--**"},
  };
void setup() {
  
  
  pinMode(A0, OUTPUT);
  pinMode(A2, INPUT);
  analogReadResolution(12);
  Serial.begin(9600);
  while (!Serial); // wait until Serial is ready

}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    Serial.println(input);
    //this loop goes character by character through the string and encodes it, the last character is not encoded hence the input.length() - 1 in the loop defintion
    //this is because from the serial monitor evey string appears to have a dud space character attached at the end
    for (int i = 0; i < (input.length() - 1); i++)
    {
      //This row of stars signifies a new character is being encoded
      Serial.println("********");
      char ch = tolower(input[i]);
      if (ch == ' ')
      {
        Serial.println("SPACE");
        delay(7*dit);
      }
      else
      {
        //this loop structure iterates through the array of character value pairs until it finds the appropriate character, the morse in the value is then executed
        for(int j = 0; j < 26; j++) 
        {
          if(myDictionaryArr[j].character == ch)
          {
            for (int k = 0; k < myDictionaryArr[j].value.length(); k++)
            {
              if(myDictionaryArr[j].value[k] == '*')  
              {
                Serial.println("SHORT");
                analogWrite(A0, 4095);
                delay(dit);
                analogWrite(A0, 0);
                //this 100ms delay is not in terms of dits as its not part of the morse rules, without it the next iteration of the loop would immediately switch the light
                //on and there would appear to be one continous pulse
                delay(100);
              }
              else if(myDictionaryArr[j].value[k] == '-')  
              {
                Serial.println("LONG");
                analogWrite(A0, 4095);
                delay(dit*2.5);
                analogWrite(A0, 0);
                delay(100);
              }
            }
            delay(3*dit);
          }
        } 
      }
      
    }
   
  }

}
