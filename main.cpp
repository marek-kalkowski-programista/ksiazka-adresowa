#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

struct Person
{
    int idNumber = 0;
    string name = "", surname = "", phoneNumber = "", emailAdress = "", adress = "";
};

void loadPersonFromFileToVector(vector<Person> &persons);

void addPerson(vector<Person> &persons);

void displayAllPersons(vector<Person> &persons);

void searchPersonByName(vector<Person> &persons);

void searchPersonBySurname(vector<Person> &persons);

void editPerson (vector<Person> &persons);

void loadPersonsFromVectorToFile (vector<Person> &persons);

void deletePerson (vector<Person> &persons);

int main()
{
    vector<Person> persons;
    loadPersonFromFileToVector(persons);
    displayAllPersons(persons);

    char userChoice;

    while(true)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwiksu" << endl;
        cout << "4. Wypisz wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> userChoice;

        if (userChoice == '1')
        {
            addPerson(persons);
        }
        else if (userChoice == '2')
        {
            searchPersonByName(persons);
        }
        else if (userChoice == '3')
        {
            searchPersonBySurname(persons);
        }
        else if (userChoice == '4')
        {
            displayAllPersons(persons);
        }
        else if (userChoice == '5')
        {
            deletePerson(persons);
        }
        else if (userChoice == '6')
        {
            editPerson(persons);
        }
        else if (userChoice == '9')
        {
            cout << endl << "Do zobaczenia!" << endl;
            exit(0);
        }
    }
    return 0;
}

void deletePerson (vector<Person> &persons)
{
    Person newPerson;
    int idPersonToDelete;
    char confirmationToDelete;
    cout << endl << "Podaj ID adresata, ktorego chcesz usunac: ";
    cin >> idPersonToDelete;

    for (int i = 0; i <= persons.size(); i++)
    {
        if (persons[i].idNumber == idPersonToDelete)
        {
            system("cls");
            cout << "Osoba o podanym ID: " << endl << endl;
            cout << persons[i].idNumber << "|";
            cout << persons[i].name << "|";
            cout << persons[i].surname << "|";
            cout << persons[i].phoneNumber << "|";
            cout << persons[i].emailAdress << "|";
            cout << persons[i].adress << "|" << endl << endl;

            cout << "Jezeli jestes pewien, ze chcesz usunac ta osobe wcisnij t: ";
            cin >> confirmationToDelete;

            if (confirmationToDelete == 't')
            {
                persons.erase(persons.begin() + i);
                cout << endl << "Adresat usuniety prawidlowo." << endl << endl;
                Sleep(1000);
                break;
            }
        }
    }
    loadPersonsFromVectorToFile(persons);
}

void loadPersonsFromVectorToFile (vector<Person> &persons)
{
    fstream file;

    if(remove("KsiazkaAdresowa.txt") != 0)
    {
        cout << "Nie znaleziono pliku KsiazkaAdresowa.txt" << endl << endl;
        Sleep(1000);
    }
    else
    {
        file.open ("KsiazkaAdresowa.txt", ios::out);
        if (file.good() == false)
        {
            file.open( "KsiazkaAdresowa.txt", ios::out);
        }

        if (file.good())
        {
            for(int i = 0; i < persons.size(); i++)
            {
                file << persons[i].idNumber << "|";
                file << persons[i].name << "|";
                file << persons[i].surname << "|";
                file << persons[i].phoneNumber << "|";
                file << persons[i].emailAdress << "|";
                file << persons[i].adress << "|" << endl;
            }
        }
        file.close();
    }
}

void editPerson (vector<Person> &persons)
{
    Person newPerson;
    char editUserChoice;
    int idPersonToEdit;
    cout << endl << "Podaj ID adresata, ktorego chcesz edytowac: ";
    cin >> idPersonToEdit;

    for (int i = 0; i <= persons.size(); i++)
    {
        if (persons[i].idNumber == idPersonToEdit)
        {
            system("cls");
            cout << "Osoba o podanym ID: " << endl << endl;
            cout << persons[i].idNumber << "|";
            cout << persons[i].name << "|";
            cout << persons[i].surname << "|";
            cout << persons[i].phoneNumber << "|";
            cout << persons[i].emailAdress << "|";
            cout << persons[i].adress << "|" << endl << endl;

            cout << "Ktora pozycje chcialbys edytowac?" << endl << endl;
            cout << "1. imie" << endl;
            cout << "2. nazwisko" << endl;
            cout << "3. numer telefonu" << endl;
            cout << "4. email" << endl;
            cout << "5. adres" << endl;
            cout << "6. powrot do menu" << endl;
            cin >> editUserChoice;

            if (editUserChoice == '1')
            {
                cout << "Podaj nowe imie: ";
                cin >> newPerson.name;
                persons[i].name = newPerson.name;
                break;
            }
            else if (editUserChoice == '2')
            {
                cout << "Podaj nowe nazwisko: ";
                cin >> newPerson.surname;
                persons[i].surname = newPerson.surname;
                break;
            }
            else if (editUserChoice == '3')
            {
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin, newPerson.phoneNumber);
                persons[i].phoneNumber = newPerson.phoneNumber;
                break;
            }
            else if (editUserChoice == '4')
            {
                cout << "Podaj nowy email: ";
                cin >> newPerson.emailAdress;
                persons[i].emailAdress = newPerson.emailAdress;
                break;
            }
            else if (editUserChoice == '5')
            {
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, newPerson.adress);
                persons[i].adress = newPerson.adress;
                break;
            }
            else if (editUserChoice == '6')
            {
                break;
            }
        }
    }
    loadPersonsFromVectorToFile (persons);
}

void displayAllPersons(vector<Person> &persons)
{
    cout << "Oto twoja lista adresatow: " << endl << endl;
    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);
    if (file.good() == false)
    {
        cout << "Plik KsiazkaAdresowa nie istnieje. Dodaj pierwsza osobe do listy, a plik stworzy sie automatycznie." << endl << endl;
        cout << "Aby przejsc do MENU nacisnij dowolny klawisz." << endl;
        cin.sync();
        getchar();
    }
    else
    {
        for (int i = 0; i < persons.size(); i++)
        {
            cout << persons[i].idNumber << "|";
            cout << persons[i].name << "|";
            cout << persons[i].surname << "|";
            cout << persons[i].phoneNumber << "|";
            cout << persons[i].emailAdress << "|";
            cout << persons[i].adress << "|" << endl;
        }
        cout << endl;
        cout << "Aby przejsc do MENU nacisnij dowolny klawisz." << endl;
        cin.sync();
        cin.get();
    }
    file.close();
}

void addPerson(vector<Person> &persons)
{
    Person newPerson;
    int sizeOfPersonVector;
    fstream file;

    file.open ("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (file.good() == false)
    {
        file.open( "KsiazkaAdresowa.txt", ios::out | ios::app);
    }

    system ("cls");
    cout << ">>> Dodawanie nowej osoby <<<" << endl;
    cout << "Podaj imie nowej osoby: ";
    cin >> newPerson.name;
    cout << "Podaj nazwisko nowej osoby: ";
    cin >> newPerson.surname;
    cout << "Podaj numer telefonu nowej osoby: ";
    cin.sync();
    getline(cin, newPerson.phoneNumber);
    cout << "Podaj email nowej osoby: ";
    cin >> newPerson.emailAdress;
    cout << "Podaj adres nowej osoby: ";
    cin.sync();
    getline(cin, newPerson.adress);

    sizeOfPersonVector = persons.size();
    if(sizeOfPersonVector == 0)
    {
        newPerson.idNumber = 1;
    }
    else
    {
        for (int i = sizeOfPersonVector; i >= sizeOfPersonVector - 1; i--)
        {
            newPerson.idNumber = persons[i].idNumber + 1;
        }
    }
    if (file.good())
    {
        file << newPerson.idNumber << "|";
        file << newPerson.name << "|";
        file << newPerson.surname << "|";
        file << newPerson.phoneNumber << "|";
        file << newPerson.emailAdress << "|";
        file << newPerson.adress << "|" << endl;

        cout << "Osoba zostala dodana pomyslnie." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    persons.push_back(newPerson);
    file.close();
}

void searchPersonByName(vector<Person> &persons)
{
    string nameOfSearchingPerson;
    fstream file;

    cout << "Wpisz imie osoby, ktorej szukasz: ";
    cin.sync();
    getline(cin, nameOfSearchingPerson);

    for (int i = 0; i <= persons.size(); i++)
    {
        if (persons[i].name == nameOfSearchingPerson)
        {
            cout << endl << "Adresaci o imieniu " << persons[i].name << ": " << endl << endl;
            break;
        }

    }
    int j = 0;
    while (j <= persons.size())
    {
        if (persons[j].name == nameOfSearchingPerson)
        {
            cout << persons[j].idNumber << "|";
            cout << persons[j].name << "|";
            cout << persons[j].surname << "|";
            cout << persons[j].phoneNumber << "|";
            cout << persons[j].emailAdress << "|";
            cout << persons[j].adress << "|" << endl;
        }
        j++;
    }
    cout << endl << "Nacisnij ENTER, aby powrocic do MENU" << endl;
    getchar();
}

void searchPersonBySurname(vector<Person> &persons)
{
    string surnameOfSearchingPerson;

    cout << "Wpisz nazwisko osoby, ktorej szukasz: ";
    cin.sync();
    getline(cin, surnameOfSearchingPerson);

    for (int i = 0; i <= persons.size(); i++)
    {
        if (persons[i].surname == surnameOfSearchingPerson)
        {
            cout << endl << "Adresaci o nazwisku " << persons[i].surname << ": " << endl << endl;
            break;
        }
    }
    int j = 0;
    while (j <= persons.size())
    {
        if (persons[j].surname == surnameOfSearchingPerson)
        {
            cout << persons[j].idNumber << "|";
            cout << persons[j].name << "|";
            cout << persons[j].surname << "|";
            cout << persons[j].phoneNumber << "|";
            cout << persons[j].emailAdress << "|";
            cout << persons[j].adress << "|" << endl;
        }
        j++;
    }
    cout << endl << "Nacisnij ENTER, aby powrocic do MENU" << endl;
    getchar();
}

void loadPersonFromFileToVector (vector<Person> &persons)
{
    Person newPerson;
    char sign = '|';
    int numberOfSign = 0;
    string partOfLine;
    fstream file;
    file.open("KsiazkaAdresowa.txt", ios::in);
    if (file.good() == true)
    {
        if(file.eof() == false)
        {
            while(getline(file, partOfLine, sign))
            {
                switch(numberOfSign)
                {
                case 0:
                    if(partOfLine == "\n")
                    {
                        break;
                    }
                    newPerson.idNumber = atoi(partOfLine.c_str());
                    numberOfSign++;
                    break;
                case 1:
                    newPerson.name = partOfLine;
                    numberOfSign++;
                    break;
                case 2:
                    newPerson.surname = partOfLine;
                    numberOfSign++;
                    break;
                case 3:
                    newPerson.phoneNumber = partOfLine;
                    numberOfSign++;
                    break;
                case 4:
                    newPerson.emailAdress = partOfLine;
                    numberOfSign++;
                    break;
                case 5:
                    newPerson.adress = partOfLine;
                    numberOfSign++;
                    break;
                }
                if (numberOfSign >= 6)
                {
                    numberOfSign = 0;
                    persons.push_back(newPerson);
                }
            }
        }
    }
    file.close();
}
