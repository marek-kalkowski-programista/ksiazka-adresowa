#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

struct User
{
    int userId = 0;
    string userLogin = "", userPassword = "";
};

struct Person
{
    int idNumber = 0, userIdNumber = 0;
    string name = "", surname = "", phoneNumber = "", emailAdress = "", adress = "";
};

void loadPersonFromFileToVector(vector<Person> &persons);

void addPerson(vector<Person> &persons, int loggedUserId);

void displayAllPersons(vector<Person> &persons);

void searchPersonByName(vector<Person> &persons);

void searchPersonBySurname(vector<Person> &persons);

void editPerson (vector<Person> &persons);

void loadPersonsFromVectorToFile (vector<Person> &persons);

void deletePerson (vector<Person> &persons);

void userMenu (vector<User> &users, vector<Person> &persons, int loggedUserId);

int loginAndRegistrationMenu (vector<User> &users, int loggedUserId);

void userRegistration(vector<User> &users);

void userLogin(vector<User> &users);

void loadUsersFromFileToVector (vector<User> &users);

int userLogin(vector<User> &users, int currentUserId);

void changePassword(vector<User> &users, int loggedUserId);

void loadUsersFromVectorToFile (vector<User> &users);

int main()
{
    vector<Person> persons;
    vector<User> users;
    int loggedUserId = 0;

    loadUsersFromFileToVector (users);


    //displayAllPersons(persons);

    loggedUserId = loginAndRegistrationMenu (users, loggedUserId);

    loadPersonFromFileToVector(persons);


    userMenu (users, persons, loggedUserId);



    return 0;
}

int loginAndRegistrationMenu (vector<User> &users, int loggedUserId)
{
    char nonLoggedUserChoice;
    int currentUserId = 0;

    while(true)
    {
        if (currentUserId == 0)
        {
            system("cls");
            cout << "PROGRAM KSIAZKA ADRESOWA" << endl;
            cout << "Aby przejsc do panelu uzytkownika wystarczy sie zalogowac. Jezeli nie masz jeszcze konta - dokonaj rejestracji." << endl << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
            cin >> nonLoggedUserChoice;

            if (nonLoggedUserChoice == '1')
            {
                while(loggedUserId == 0)
                {
                    loggedUserId = userLogin(users, currentUserId);
                }
                return loggedUserId;
                break;
            }
            else if (nonLoggedUserChoice == '2')
            {
                userRegistration(users);
                while(loggedUserId == 0)
                {
                    loggedUserId = userLogin(users, currentUserId);
                }
                return loggedUserId;
                break;
            }
            else if (nonLoggedUserChoice == '9')
            {
                exit(0);
            }
        }
    }
}

void userMenu (vector<User> &users, vector<Person> &persons, int loggedUserId)
{
    char loggedUserChoice;

    cout << "Logged User ID: " << loggedUserId << endl;
    Sleep(3000);


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
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> loggedUserChoice;

        if (loggedUserChoice == '1')
        {
            addPerson(persons, loggedUserId);
        }
        else if (loggedUserChoice == '2')
        {
            searchPersonByName(persons);
        }
        else if (loggedUserChoice == '3')
        {
            searchPersonBySurname(persons);
        }
        else if (loggedUserChoice == '4')
        {
            displayAllPersons(persons);
        }
        else if (loggedUserChoice == '5')
        {
            deletePerson(persons);
        }
        else if (loggedUserChoice == '6')
        {
            editPerson(persons);
        }
        else if (loggedUserChoice == '7')
        {
            changePassword(users, loggedUserId);
        }
        else if (loggedUserChoice == '8')
        {
            system("cls");
            loggedUserId = 0;
            loggedUserId = loginAndRegistrationMenu (users, loggedUserId);
        }
        else if (loggedUserChoice == '9')
        {
            cout << endl << "Do zobaczenia!" << endl;
            exit(0);
        }
    }
}

int userLogin(vector<User> &users, int currentUserId)
{
    string login, password;
    int i = 0;
    system ("cls");
    cout << ">>> LOGOWANIE <<<" << endl;
    cout << "Podaj LOGIN: ";
    cin >> login;

    while (i < users.size())
    {
        if (users[i].userLogin == login)
        {
            do
            {
                for (int loginAttempts = 0; loginAttempts < 3; loginAttempts++)
                {
                    cout << "Podaj haslo. Pozostalo prob" << 3 - loginAttempts << ": ";
                    cin >> password;
                    if (users[i].userPassword == password)
                    {
                        cout << "Zalogowales sie." << endl;
                        currentUserId = users[i].userId;
                        Sleep(1000);
                        return currentUserId;
                    }
                }
                cout << "Podales 3 razy bledne haslo. Sprobuj ponownie." << endl;
                Sleep(3000);
                system ("cls");

            }while(password != users[i].userPassword);
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem. Sprobuj ponownie." << endl;
    Sleep(2000);
    return 0;
}

void userRegistration(vector<User> &users)
{
    string userLogin, userPassword;

    User newUser;
    int sizeOfUserVector;
    fstream file;

    file.open ("Uzytkownicy.txt", ios::out | ios::app);
    if (file.good() == false)
    {
        file.open( "Uzytkownicy.txt", ios::out | ios::app);
    }

    system ("cls");
    cout << ">>> REJESTRACJA <<<" << endl;
    cout << "Podaj LOGIN: ";
    cin >> newUser.userLogin;
    cout << "Podaj HASLO: ";
    cin >> newUser.userPassword;

    sizeOfUserVector = users.size();
    if(sizeOfUserVector == 0)
    {
        newUser.userId = 1;
    }
    else
    {
        for (int i = sizeOfUserVector; i >= sizeOfUserVector - 1; i--)
        {
            newUser.userId = users[i].userId + 1;
        }
    }
    if (file.good())
    {
        file << newUser.userId << "|";
        file << newUser.userLogin << "|";
        file << newUser.userPassword << "|" << endl;

        cout << "Zarejestrowales sie pomyslnie. Aby przejsc do panelu uzytkownika - zaloguj sie." << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
    users.push_back(newUser);
    file.close();
}

void changePassword(vector<User> &users, int loggedUserId)
{
    string newPassword;

    system("cls");
    cout << "ZMIANA HASLA" << endl << endl;
    cout << "Podaj nowe haslo: ";
    cin >> newPassword;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].userId == loggedUserId)
        {
            users[i].userPassword = newPassword;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(2000);
        }
    }
    loadUsersFromVectorToFile (users);
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

void loadUsersFromVectorToFile (vector<User> &users)
{
    fstream file;

    if(remove("Uzytkownicy.txt") != 0)
    {
        cout << "Nie znaleziono pliku Uzytkownicy.txt" << endl << endl;
        Sleep(1000);
    }
    else
    {
        file.open ("Uzytkownicy.txt", ios::out);
        if (file.good() == false)
        {
            file.open( "Uzytkownicy.txt", ios::out);
        }

        if (file.good())
        {
            for(int i = 0; i < users.size(); i++)
            {
                file << users[i].userId << "|";
                file << users[i].userLogin << "|";
                file << users[i].userPassword << "|" << endl;
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

void addPerson(vector<Person> &persons, int loggedUserId)
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

    newPerson.userIdNumber = loggedUserId;

    sizeOfPersonVector = persons.size();

    cout << "wielkosc pliku: " << sizeOfPersonVector << endl;
    system ("pause");



    if(sizeOfPersonVector == 0)
    {
        newPerson.idNumber = 1;
    }
    else
    {
        for (int i = sizeOfPersonVector; i >= sizeOfPersonVector - 1; i--)
        {
            newPerson.idNumber = persons[i].idNumber + 1;
            cout << "wielkosc wektora: " << newPerson.idNumber << endl;
            system("pause");
        }
    }
    if (file.good())
    {
        file << newPerson.idNumber << "|";
        file << newPerson.userIdNumber << "|";
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
            cout << persons[j].userIdNumber << "|";
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
            cout << persons[j].userIdNumber << "|";
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
                    newPerson.userIdNumber = atoi(partOfLine.c_str());
                    numberOfSign++;
                    break;
                case 2:
                    newPerson.name = partOfLine;
                    numberOfSign++;
                    break;
                case 3:
                    newPerson.surname = partOfLine;
                    numberOfSign++;
                    break;
                case 4:
                    newPerson.phoneNumber = partOfLine;
                    numberOfSign++;
                    break;
                case 5:
                    newPerson.emailAdress = partOfLine;
                    numberOfSign++;
                    break;
                case 6:
                    newPerson.adress = partOfLine;
                    numberOfSign++;
                    break;
                }
                if (numberOfSign >= 7)
                {
                    numberOfSign = 0;
                    persons.push_back(newPerson);
                }
            }
        }
    }
    file.close();
}

void loadUsersFromFileToVector (vector<User> &users)
{
    User newUser;
    char sign = '|';
    int numberOfSign = 0;
    string partOfLine;
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
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
                    newUser.userId = atoi(partOfLine.c_str());
                    numberOfSign++;
                    break;
                case 1:
                    newUser.userLogin = partOfLine;
                    numberOfSign++;
                    break;
                case 2:
                    newUser.userPassword = partOfLine;
                    numberOfSign++;
                    break;
                }
                if (numberOfSign >= 3)
                {
                    numberOfSign = 0;
                    users.push_back(newUser);
                }
            }
        }
    }
    file.close();
}
