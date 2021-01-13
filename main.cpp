#include <iostream>
using namespace std;

class Fraction {
    // private jest domyslnie. Czyli jak nie wpiszemy tego słowa, to c++ potraktuje wszystko jako private.
    // private oznacza to, że pola oraz metody nie są dostępne (ani nawet widzialne) "z zewnątrz".
    private:
      int numerator{2};
      int denominator{3};

    public:
      string some_public_field{};

      int read_numerator() {
        return numerator;
      };

      int read_denominator() {
        return denominator;
      };

      void set_numerator(int value) {
        numerator = value;
      };

      void set_denominator(int value) {
        denominator = value;
      };
  };


// A co jeśli chcemy żeby nasza klasa, przyjmowała jakieś parametry?
// Z pomocą przychodzi konstruktor.
class Fraction_with_constructor {
  private:
    int numerator{};
    int denominator{};

  public:
  // Konstruktor ma taką samą nazwę jak nasza klasa
  // Konstruktor może, ale nie musi, mieć parametry.
    Fraction_with_constructor() {
      cout << "Jestem konstruktorem bez parametrów 😢" << endl;
    };

    Fraction_with_constructor(int a, int b) {
      cout << "Jestem konstruktorem i posiadam dwa parametry 😎" << endl;

      numerator = a;
      denominator = b;
    };

    int read_numerator() {
      return numerator;
    };

    int read_denominator() {
      return denominator;
    };

    void set_numerator(int value) {
      numerator = value;
    };

    void set_denominator(int value) {
      denominator = value;
    };

    // Jest też coś takiego jak destruktor.
    // Destruktor uruchamia się wraz z końcem zakresu, w którym żyje nasz obiekt/klasa.

    // "A destructor is a member function that is invoked automatically when the object goes out     of scope or is explicitly destroyed by a call to delete"
    ~Fraction_with_constructor() {
      cout << "Jestem destruktorem! Uruchamiam się na końcu zakresu" << endl;
    };


    // c++ nie rozumie "od tak" co mamy na myśli, mówiąc ułamek1 + ułamek2.
    // Musimy więc przeciążyć (stworzyć funkcję) operator dodawania.
    // addend = dodajnik, czyli liczbą którą dodajemy
    Fraction_with_constructor operator+ (Fraction_with_constructor &addend) {
      Fraction_with_constructor result;

      // Tutaj poprostu sprawdzamy czy jest wspólny mianownik.
      // Jak jest to dodajemy a jak nie ma, to sprowadzamy do wspólnego mianownika.
      if(denominator == addend.denominator) {
        result.denominator = denominator;
        result.numerator = numerator + addend.numerator;
      } else {
        result.denominator = denominator * addend.denominator;
        result.numerator =  (numerator * addend.denominator) + (addend.numerator * denominator);
      }

      cout << "wynik to: " << result.numerator << "/" << result.denominator << endl;

      return result;

    };
  };



int main() {
  cout << "Classes 👍" << endl << endl;

  Fraction example_fraction;
  // example_fraction.numerator = 1;  <-- niezadziała, ponieważ pole numerator jest prywatne :(
  example_fraction.some_public_field = "Jestem dostępny publicznie 😎";

  cout << "Public field: " << example_fraction.some_public_field << endl << endl;

  // Odczytujemy prywatne pola licznik i mianownik za pomocą publiczych metod read_x.
  int numerator_vaue = example_fraction.read_numerator();
  int denominator_vaue = example_fraction.read_denominator();

  cout << "Licznik: " << numerator_vaue << endl << "Mianownik: " << denominator_vaue << endl << endl;

  // Zmieniamy licznik i mianownik za pomocą publicznej metody set_x.
  example_fraction.set_numerator(1);
  example_fraction.set_denominator(2);

  cout << "Po zmianie: " << endl;
  cout << "Licznik: " << numerator_vaue << endl << "Mianownik: " << denominator_vaue << endl << endl;



  // Tworzymy instancję klasy, ale tym razem mamy do dyspozycji konstruktor 👌
  Fraction_with_constructor my_lame_fraction;
   cout << my_lame_fraction.read_numerator() << "/" << my_lame_fraction.read_denominator() << endl <<endl;


  {
    Fraction_with_constructor in_block_scope(9, 10);
    cout << in_block_scope.read_numerator() << "/" << in_block_scope.read_denominator() << endl <<endl;
  }

  Fraction_with_constructor my_cool_fraction(1, 100);
   cout << my_cool_fraction.read_numerator() << "/" << my_cool_fraction.read_denominator() << endl <<endl;

  /* Kolejność wypisywania konstruktorów i dekonstruktorów:
     1. Najpierw włączy się konstruktor wywołany przez my_lame_fraction (zakres "globalny/main").

     2. Potem włączy się konstruktor wywołany przez in_block_scope (zakres blokowy).

     3. Wychodzimy z bloku, zatem wywoła się destruktor z in_block_scope (koniec zakresu blokowego).

     4. Potem włączy się konstruktor wywołany przez my_cool_fraction (zakres "globalny/main").

     5. Kończymy działanie głównego programu, zatem wywołują się dwa destruktory my_cool_fraction oraz my_lame_fraction). Koniec zakresu globalnego/main.
  */


  // Wszystko fajnie, ale teraz dodajmy dwa ułamki 🤔

  Fraction_with_constructor fraction1(1, 3);
  Fraction_with_constructor fraction2(2, 3);
  Fraction_with_constructor fraction3 = fraction1 + fraction2;

  Fraction_with_constructor fraction4(1, 2);
  Fraction_with_constructor fraction5(1, 3);
  Fraction_with_constructor fraction6 = fraction4 + fraction5;
 
}