
/*
This code is for CS214 project .
This code is represent the *Read & Think* Book store.
 */
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<conio.h>
#include <string.h>
#include <ctime>
#include<windows.h>
using namespace std;
// **********  GLOBAL STRUCTURE for File handling  *****************/

struct Node_File {
    int ISBN;
    char Book_name[30];
    char author[20];
    char category[20];
    float price;
};
// *******  GLOBAL STRUCTURE for Linked List in computer's memory *********/

struct Node_Comp {
    int ISBN;
    char Book_name[30];
    char author[20];
    char category[20];
    float price;
    struct Node_Comp *next;
};
//***************  GLOBAL  VARIABLES  ***************/
struct Node_Comp *Head = NULL;
int page_no;

/*********************  FUNCTIONS PROTOTYPES  ********************/
void info();
void LoadList();
void AddBook(void);
void DeleteBook(void);
void Search_for_Book(void);
void SaveList(void);
void DisplayList_of_Books(void);
void Heading(void);
SYSTEMTIME Time_now;
void space(char s[]); //to display a space in the output
void info();

/*************************MAIN FUNCTION****************************/

int main() {
    short int Choice = 0;
    SYSTEMTIME Time_now;
    GetLocalTime(&Time_now);
    LoadList(); // This function will load all records from the file into Linked List

    while (true) {
        cout << "                \n\t\t**Read & Think**" << endl;
        cout << "               \t   Book store" << endl;
        cout << "                \n\t\t   Main Menu" << endl;
        cout << "                   ~~~~~~~~~" << endl;
        cout << "\n\n\t[1]  Add a New Book to the Store";
        cout << "\n\n\t[2] Delete a New Book from the Store ";
        cout << "\n\n\t[3]  Books List / Report ";
        cout << "\n\n\t[4]  Search for a Book ";
        cout << "\n\n\t[5]  Save Book  in the  File ";
        cout << "\n\n\t[6]  Info ";
        cout << "\n\n\t[7]  Exit Program";
        cout << "\n\n\n\t\tPlease,Enter your choice --> ";
        cin>>Choice;

        switch (Choice) {
            case 1:
                AddBook();
                break;
            case 2:

                DeleteBook();
                break;

            case 3: page_no = 0;
                DisplayList_of_Books();
                break;
            case 4:
                if (Head == NULL) {
                    cout << "Sorry,but we cannot search because the store is  empty! " << endl;
                    break;
                }
                Search_for_Book();
                break;

            case 5:
                SaveList();
                break;
            case 6:
                info(); //information function
                break;
            case 7:
                SaveList();
                cout << "\n\n\n GoodBye!!!\n";
                exit(0);
            default:
                cout << "\nInvalid Choice...";

        }

    }
    return 0;
} // end of main() function

void AddBook(void) {
    struct Node_Comp *Prev, *Curr;

    struct Node_Comp *NewNode = new Node_Comp;

    cout << "\n\n\n\n\n\t\t Data for the Book \n\n";
    cout << " Enter ISBN: " << flush;
    cin >> NewNode->ISBN;

    cout << " Put the Book name : ";
    cin.ignore();
    cin.getline(NewNode->Book_name, 50);
    cout << "Put the author name : ";
    cin >> NewNode->author;
    cout << "Put the category  : ";
    cin >> NewNode->category;
    cout << "Enter Book price  : ";
    cin >> NewNode->price;
    NewNode -> next = NULL;

    if (Head == NULL) {
        Head = NewNode;
        return;
    } // this is to add first node in the list

    if (NewNode->ISBN < Head->ISBN) //  insert on top of linked list
    {
        NewNode->next = Head;
        Head = NewNode;
        return;
    }

    Prev = Curr = NULL;
    for (Curr = Head; Curr != NULL; Curr = Curr->next) {
        if (NewNode->ISBN < Curr->ISBN)
            break;
        Prev = Curr;
    }

    NewNode->next = Prev->next;
    Prev->next = NewNode;
} // end of Add function

void space(char s[]) { //to display a space in the output
    int coun = 0, i = 0;
    while (s[i] != '\0') {
        coun++;
        ++i;
    }
    int sp;
    sp = 20 - coun;
    for (sp; sp > 0; sp--) {
        cout << " ";
    }
}

void DeleteBook() {
    struct Node_Comp *Prev, *Scan, *Curr;
    int data;

    if (Head == NULL) {
        cout << "Sorry,but your shop is empty " << endl;
        return;
    }

    /*for (Scan = Head; Scan != NULL; Scan = Scan->next) {
        cout<<"The Books in your store is "<<Head->ISBN<<endl ;}*/

    cout << " Enter ISBN of the Book to Delete : " << flush;
    cin>> data;
    if (data == Head->ISBN) {
        Head = Head->next;

        cout << "The Book *" << Head->Book_name << "* has been deleted !" << endl;
        return;
    }

    for (Scan = Head; Scan != NULL; Scan = Scan->next) {
        if (Scan->ISBN == data) {
            break;
            // cout << "The Book " << " " << Head->Book_name << " " << " has been deleted !" << endl;
            // return;
        }

        Prev = Scan;
    }
    if (Scan == NULL) {
        cout << "Sorry, but the ISBN not found  in the list !" << endl;
    } else {
        cout << "The Book *" << Head->Book_name << "* has been deleted !" << endl;
        Prev->next = Scan->next;
    }
}

void Search_for_Book(void) { //to search
    struct Node_Comp *Curr;
    int Look, I = 0, choice;
    char Fname;
    char Look_category[20];

    while (true) {
        cout << "\tSearch for Book by : " << endl;
        cout << "\n\t[1]-ISBN " << endl;
        cout << "\n\t[2]-First Letter in the author name " << endl;
        cout << "\n\t[3]-Category " << endl;
        cout << "\n\tPlease,Enter your choice --> " << flush;
        cin>>choice;
        switch (choice) {
            case 1:

                cout << "\tEnter the ISBN to Search :";
                cin >>Look;
                SaveList();
                for (Curr = Head; Curr != NULL; Curr = Curr->next) {
                    if (Curr->ISBN == Look) {

                        cout << Curr->ISBN << " " << Curr->Book_name << "\t" << "has been found " << endl;
                        cout << "\nThe Price is  " << Curr->price << " " << "Includes VAT !" << endl;

                    }
                    I++;
                }
                if (Look < 1) {



                    cout << "Book with ISBN " << Look << " " << "not in your store !" << endl;
                }

                break;
            case 2:

                cout << "\tEnter the First letter in the author name ";
                cin>>Fname;
                SaveList();
                for (Curr = Head; Curr != NULL; Curr = Curr->next) {

                    if (Curr->author[0] == Fname) {
                        cout << Curr->author << " " << "has been found " << endl;
                        cout << Curr->author << " " << "have the following Books";
                        cout << "\n" << Curr->Book_name << endl;
                        Fname++;
                    }

                }
                if (Fname < 1) {
                    cout << "not" << endl;
                    system("pause");
                }
                system("pause");
                break;



            case 3:
                cout << "\tEnter the category to Search :";
                cin >>Look_category;
                SaveList();
                for (Curr = Head; Curr != NULL; Curr = Curr->next) {
                    if (strcmp(Look_category, Curr->category) == 0) {

                        cout << "\n\tForm The *" << Curr->category << "*category" << endl;

                        cout << "\tThis Book has been found *" << Curr->Book_name << "* " << "has been found " << endl;
                        I++;

                    }
                }

            default:
                cout << "\nInvalid Choice...";
        }
        system("pause");
        return;

    }
}

void info() {
    cout << "\n\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "\n\n\t#To add a new Book to the store: ";
    cout << "\n\n\t #The ISBN  at least more than  4 digit.";
    cout << "\n\n\t #For the author name should contain first letter of first name and all the last name.";
    cout << "\n\n\t#For the Category of Books most be one of the following :";
    cout << "\n\n\t[1]-Drama\t[2]-Math\t[3]-Art\t\t[4]-Science\t[5]-Comics ";
    cout << "\n\n\t#The price should be floating point ,Note that the price is (Includes VAT) !. ";
    cout << "\n\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";


}

void SaveList(void) {
    ofstream pFile;
    pFile.open("Boo.dat", ios::binary);
    if (pFile == NULL) {
        cout << "Cannot Open File \n updated Data not saved into file\n\n";
        return;
    }

    struct Node_File NF; // structure variable to hold data for file
    struct Node_Comp *Curr;
    for (Curr = Head; Curr != NULL; Curr = Curr -> next) { // copy record from linked list into file record structure
        NF.ISBN = Curr->ISBN;
        strcpy(NF.Book_name, Curr -> Book_name);
        strcpy(NF.author, Curr->author);
        strcpy(NF.category, Curr->category);
        NF.price = Curr->price;

        pFile.write((char*) &NF, sizeof (NF)); // write record into file
    }
    pFile.close();

}

void LoadList() {
    ifstream piFile;
    piFile.open("Boo.dat", ios::binary);
    if (piFile == NULL) {
        cout << "File not Exist \n";
        return;
    }

    Node_File NF; // structure variable to hold data from file
    Node_Comp *NewNode; //  structure pointer to add data into linked list
    Node_Comp *Tail = NULL;

    // Read First Record from file
    piFile.read((char*) &NF, sizeof (NF));

    while (piFile) // if(pFile.eof( ))break;
    {
        NewNode = new Node_Comp; // create new node
        NewNode->ISBN = NF.ISBN;
        strcpy(NewNode -> Book_name, NF.Book_name);
        strcpy(NewNode->author, NF.author);
        strcpy(NewNode->category, NF.category);
        NewNode->price = NF.price;
        NewNode -> next = NULL;
        if (Head == NULL) {
            Head = NewNode;
            Tail = Head;
        } else {
            Tail-> next = NewNode;
            Tail = NewNode;
        }
        piFile.read((char*) &NF, sizeof (NF)); // read next record from file

    }
    piFile.close();
}

void DisplayList_of_Books(void) {
    if (Head == NULL) {
        cout << "\n\nSorry,but your store is empty ! ";
        cout << "\n Nothing to Display \n\n";
        return;
    }
    struct Node_Comp *Curr;
    int i = 0;

    Heading();

    for (Curr = Head; Curr != NULL; Curr = Curr -> next) {
        if (i % 20 == 0 && i != 0) {
            cout << "\n\n Press a key for next Page: .... ";
            Heading();
        }

        // print record
        cout << "  " << Curr->ISBN << "\t\t" <<
                Curr->Book_name;
        space(Curr->Book_name);
        cout << Curr->author;
        space(Curr->author);
        cout << Curr->category;
        space(Curr->category);
        cout << Curr->price;

        cout << endl;
        i++; // counter to control the page size
    } // end of while loop


    system("pause"); //  it use a  halt and need to press any key

}

void Heading() {
    system("cls"); // this statement clears the screen
    page_no++;
    // Print heading
    cout << "\t\t\t\tBook store  List \t\t  Page-No: " << page_no << "\t\t" << Time_now.wHour << endl;
    cout << "\t\t\t\t~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << setw(10) << "   ID.  " << setw(20) << "     Book_Name       ";
    cout << setw(9) << " The Author " << setw(9) << " \t The category " << setw(9) << "  \tThe price ";

    cout << endl << endl;

}


