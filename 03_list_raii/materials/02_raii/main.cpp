// vim: set undofile:
// Program: raii

// C-ovski nacin implementacije
int foo_c()
{
    // Inicijalizacija necega
    FILE * file = fopen("data", "w");

    // Radimo nesto ...

    // Zbog inicijalizacije i deinicijalizacije resursa je
    // prilikom pisanja C programa nastala praksa da
    // bi metod trebalo da ima samo jedan izlaz - jednu
    // return komandu
    //
    // Za C++ ovo ne moze biti praksa, jer i pored jednog
    // return-a, izlaz iz metoda moze da se pojavi bilo gde
    // - bacen izuzetak bilo gde u kodu.
    //
    // Tako da je ideja inicijalizacije na pocetku metoda
    // i deinicijalizacija na kraju nesto sto je
    // obeshrabreno

    // Deinicijalizacija
    fclose(file);

    return 1;
}

// Umesto toga, koristi se RAII (Resource Acquisition Is Initialization)
// Za inicijalizaciju i deinicijalizaciju treba koristiti
// iskljucivo konstruktore i destruktore

class my_file {
public:
    my_file(...)
    {
        m_file = fopen(...);
    }

    ~my_file()
    {
        fclose(m_file);
    }

private:
    FILE * m_file;

};

int foo_cpp()
{
    my_file f("data", "w");

    // Radimo nesto ...
    //
    // Kakav god da je izlaz iz metoda - return ili izuzetak,
    // bice pozvan destruktor promenljive f, samim tim i fclose
    //
    // Ovaj princip je potrebno koristiti za sve sto ima
    // metode inicijalizacije i deinicijalizacije
    // (otvaranje i zatvaranje fajlova, zakljucavanje i otkljucavanje
    // muteksa, alokacija i dealokacija memorije...)

    return 1;
}

// Tako funkcionise std::unique_ptr (slicno i std::shared_ptr)


