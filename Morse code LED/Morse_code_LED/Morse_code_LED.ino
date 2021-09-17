#define TIME_UNIT 300

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  blinkSentence("hello sudo sensei");
  delay(TIME_UNIT * 10);
}

void blinkSentence(String s)
{
  for(int i = 0; i < s.length(); i++)
  {
    switch(s.charAt(i))
    {
      case 'a': blinkPattern(".-");
        break;
      case 'b': blinkPattern("-...");
        break;
      case 'c': blinkPattern("-.-.");
        break;
      case 'd': blinkPattern("-..");
        break;
      case 'e': blinkPattern(".");
        break;
      case 'f': blinkPattern("..-.");
        break;
      case 'g': blinkPattern("--.");
        break;
      case 'h': blinkPattern("....");
        break;
      case 'i': blinkPattern("..");
        break;
      case 'j': blinkPattern(".---");
        break;
      case 'k': blinkPattern("-.-");
        break;
      case 'l': blinkPattern(".-..");
        break;
      case 'm': blinkPattern("--");
        break;
      case 'n': blinkPattern("-.");
        break;
      case 'o': blinkPattern("---");
        break;
      case 'p': blinkPattern(".--.");
        break;
      case 'q': blinkPattern("--.-");
        break;
      case 'r': blinkPattern(".-.");
        break;
      case 's': blinkPattern("...");
        break;
      case 't': blinkPattern("-");
        break;
      case 'u': blinkPattern("..-");
        break;
      case 'v': blinkPattern("...-");
        break;
      case 'w': blinkPattern(".--");
        break;
      case 'x': blinkPattern("-..-");
        break;
      case 'y': blinkPattern("-.--");
        break;
      case 'z': blinkPattern("--..");
        break;
      case ' ': wordDone();
        break;
    }
    letterDone();
  }
}

void blinkPattern(String s)
{
  for(int i = 0; i < s.length(); i++)
  {
    if(s.charAt(i) == '.')
    {
      dit();
    }
    else if (s.charAt(i) == '-')
    {
      dah();
    }
    delay(TIME_UNIT); //gap within a character
  }
}

void dit()
{
  digitalWrite(13, HIGH);
  delay(TIME_UNIT);
  digitalWrite(13, LOW);
}
void dah()
{
  digitalWrite(13, HIGH);
  delay(TIME_UNIT * 3);
  digitalWrite(13, LOW);
}
void letterDone()
{
  delay(TIME_UNIT * 2); //gap after a character is supposed to be 3x,
                        //but the previous character already waits for 1
}
void wordDone()
{
  delay(TIME_UNIT * 4); //gap after a word is supposed to be 7x, but
                        //the letter finishing provides 3
}
