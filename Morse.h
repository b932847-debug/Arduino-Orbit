#pragma once

const int LED_PIN = 2;

// Timing (milliseconds)
const int DOT_TIME = 25;
const int DASH_TIME = 60;

const int SYMBOL_SPACE = 25;
const int LETTER_SPACE = 75;
const int WORD_SPACE = 125;


void dot() {
    

  digitalWrite(LED_PIN, HIGH);
  delay(DOT_TIME);

  digitalWrite(LED_PIN, LOW);
  delay(SYMBOL_SPACE);
}

void dash() {

  digitalWrite(LED_PIN, HIGH);
  delay(DASH_TIME);

  digitalWrite(LED_PIN, LOW);
  delay(SYMBOL_SPACE);
}
void sendPattern(const char* pattern) {

  while (*pattern) {

    if (*pattern == '.') {
      dot();
    }

    else if (*pattern == '-') {
      dash();
    }

    pattern++;
  }

  delay(LETTER_SPACE);
}

void sendMorseChar(char c) {

  c = toupper(c);

  switch (c) {

    // Letters

    case 'A': sendPattern(".-"); break;
    case 'B': sendPattern("-..."); break;
    case 'C': sendPattern("-.-."); break;
    case 'D': sendPattern("-.."); break;
    case 'E': sendPattern("."); break;
    case 'F': sendPattern("..-."); break;
    case 'G': sendPattern("--."); break;
    case 'H': sendPattern("...."); break;
    case 'I': sendPattern(".."); break;
    case 'J': sendPattern(".---"); break;
    case 'K': sendPattern("-.-"); break;
    case 'L': sendPattern(".-.."); break;
    case 'M': sendPattern("--"); break;
    case 'N': sendPattern("-."); break;
    case 'O': sendPattern("---"); break;
    case 'P': sendPattern(".--."); break;
    case 'Q': sendPattern("--.-"); break;
    case 'R': sendPattern(".-."); break;
    case 'S': sendPattern("..."); break;
    case 'T': sendPattern("-"); break;
    case 'U': sendPattern("..-"); break;
    case 'V': sendPattern("...-"); break;
    case 'W': sendPattern(".--"); break;
    case 'X': sendPattern("-..-"); break;
    case 'Y': sendPattern("-.--"); break;
    case 'Z': sendPattern("--.."); break;

    // Numbers

    case '0': sendPattern("-----"); break;
    case '1': sendPattern(".----"); break;
    case '2': sendPattern("..---"); break;
    case '3': sendPattern("...--"); break;
    case '4': sendPattern("....-"); break;
    case '5': sendPattern("....."); break;
    case '6': sendPattern("-...."); break;
    case '7': sendPattern("--..."); break;
    case '8': sendPattern("---.."); break;
    case '9': sendPattern("----."); break;

    // Punctuation

    case '.': sendPattern(".-.-.-"); break;
    case ',': sendPattern("--..--"); break;
    case '?': sendPattern("..--.."); break;
    case '!': sendPattern("-.-.--"); break;
    case ':': sendPattern("---..."); break;
    case ';': sendPattern("-.-.-."); break;
    case '-': sendPattern("-....-"); break;
    case '/': sendPattern("-..-."); break;
    case '@': sendPattern(".--.-."); break;

    default:
      break;
  }
}

void flashMorse(String text) {

  for (int i = 0; i < text.length(); i++) {

    char c = text.charAt(i);

    if (c == ' ') {

      delay(WORD_SPACE);

    } else {

      sendMorseChar(c);
    }
  }
}

void flashSOS() {
  flashMorse("SOS");
}

void flashOrbit() {
  flashMorse("ORBIT");
}

void flashHello() {
  flashMorse("HELLO");
}