#include <iostream>
#include<limits>
#include<conio.h>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;
const int MAX_STUDENTS = 100;

int book_id[MAX_BOOKS];
string book_title[MAX_BOOKS];
string book_author[MAX_BOOKS];
int book_copies[MAX_BOOKS];
int book_count = 0;

int student_id[MAX_STUDENTS];
string student_name[MAX_STUDENTS];
string student_password[MAX_STUDENTS];
int student_borrowed[MAX_STUDENTS];
int student_fine[MAX_STUDENTS];

// SINGLE 1D ARRAY for borrowed days
int borrowed_days[MAX_STUDENTS * 3]; // MAX_STUDENTS * 3 = 300 elements

int student_count = 0;

string admin_user = "admin";
string admin_pass = "admin123";

int current_student = -1;
int current_day = 1;

// Helper function to get index in 1D array
int getBorrowIndex(int student_idx, int slot) {
    return student_idx * 3 + slot; // (0,0)=0, (0,1)=1, (0,2)=2, (1,0)=3, etc.
}

void addBook()
{
    if (book_count >= MAX_BOOKS)
    {
        cout << "Library is full! Cannot add more books.\n";
        return;
    }

    cout << "\n--- Add New Book ---\n";

    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, book_title[book_count]);

    cout << "Enter Author Name: ";
    getline(cin, book_author[book_count]);

    cout << "Enter Number of Copies: ";
    cin >> book_copies[book_count];

    book_id[book_count] = 1000 + book_count;
    book_count++;
    cout << " Book ID: " << book_id[book_count - 1] << "\n";

    cout<<"Book added successfully!" <<endl;
}

void viewBooks()
{
    if (book_count == 0)
    {
        cout << "\nNo books in library!\n";
        return;
    }

    cout << "\n--- All Books in Library ---\n";
    cout << "ID  \t  Title \t Author  \t   Copies \n";
    cout << "------------------------------------------------\n";

    for (int i = 0; i < book_count; i++)
    {
        cout << book_id[i] << "\t";
        cout << book_title[i] << "\t";
        cout << book_author[i] << "\t";
        cout << book_copies[i] << "\n";
    }
}

void deleteBook()
{
    int id;
    int found = -1;

    cout<< "\n--- Delete Book ---\n";

    cout<< "Enter Book ID to delete: ";
    cin>> id;

    for (int i = 0; i < book_count; i++)
    {
        if (book_id[i] == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        cout<< "Book not found!\n";
        return;
    }

    cout<<"Book Found: " << book_title[found] << " by " << book_author[found] << "\n";

    cout<<"Are you sure? (1 for yes, 0 for no): ";
    int choice;
    cin>> choice;

    if (choice == 1)
    {
        for(int i = found; i < book_count-1; i++)
        {
            book_id[i] = book_id[i + 1];     // ismy jo bookid jo user ny enter ki hogi wo wla index pr jo data hoga osko replace krty jaye gy continously agly index ki value sy. 
            book_title[i] = book_title[i + 1];  // issy array ma extra space (khali cell) nhi bachi hogi, memory less consume hogi, mtlb array size chota ho jaye ga. 
            book_author[i] = book_author[i + 1]; // parallel arrays h yay sari so sab ma data replace krna hoga.
            book_copies[i] = book_copies[i + 1];
        }
      
        book_count--;     //then book count ko km kry gy as book delete hoi h.

        cout<< "Book deleted successfully!\n";
    }
    else
    {
        cout<< "Deletion cancelled.\n";
    }
}

void editBook()
{
    int id;
    int found = -1;

    cout << "\n--- Edit Book Details ---\n";

    cout << "Enter Book ID to edit: ";  // jis book ki details ko edit krna h, oski id user ko enter krni hogi.
    cin >> id;

    for (int i = 0; i < book_count; i++)
    {
        if (book_id[i] == id)  
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        cout<< "Book not found!\n";
        return;
    }

    cout <<"\n Current Book Details:\n";

    cout<<"Title: " << book_title[found] <<"\n";
    cout<<"Author: " << book_author[found] <<"\n";
    cout<<"Copies: " << book_copies[found] <<"\n";

    int choice;
    cout<< "\nWhat do you want to edit?\n";
    cout<< "1. Edit Title\n";
    cout<< "2. Edit Author\n";
    cout<< "3. Edit Number of Copies\n";
    cout<< "4. Edit All Details\n";
    cout<< "5. Cancel\n";

    cout<< "Enter choice: ";
    cin>> choice;

    cin.ignore();

    if(choice == 1)
    {
      cout<< "Enter new title: ";
      getline(cin, book_title[found]);
      cout<< "Title updated successfully!\n";
    } 
    else if(choice == 2)
    {
        cout<< "Enter new author: ";
        getline(cin, book_author[found]);
        cout<< "Author updated successfully!\n";
    }
    else if( choice == 3)
    {
        cout<< "Enter new number of copies: ";
        cin>> book_copies[found];

        if (book_copies[found] < 0)  // in case user no. of copies -ve ma enter krdy tu error show krdo. 
        {
          cout<<"Invalid number! Setting to 0.\n";
          book_copies[found] = 0;  // array ma iski value ko zero krdy gy.
        }
        cout << "Number of copies updated successfully!\n";
    }
    else if(choice == 4)
    {
        cout<< "Enter new title: ";
        getline(cin, book_title[found]);
        cout<< "Enter new author: ";
        getline(cin, book_author[found]);
        cout<< "Enter new number of copies: ";
        cin>> book_copies[found];

        if (book_copies[found] < 0)
        {
            cout << "Invalid number! Setting to 0.\n";
            book_copies[found] = 0;
        }
        cout<< "All details updated successfully!\n";
    }

    else if(choice == 5)
        cout<< "Edit cancelled.\n";
        
    else          // agr 5 k elawa koi or option enter krdi tu invalid choice show hoga.
        cout<< "Invalid choice!\n";
        
}


void studentSignup()
{
    if (student_count >= MAX_STUDENTS)
    {
        cout << "Cannot register more students!\n";
        return;
    }

    cout << "\n--- Student Sign Up ---\n";

    cout << "Enter Your Name: ";
    cin.ignore();
    getline(cin, student_name[student_count]);

    cout << "Create Password: ";
    getline(cin, student_password[student_count]);

    student_id[student_count] = 5000 + student_count;  // student id phele student ko 5000 mily gi then 5001 and so on..
    student_borrowed[student_count] = 0;
    student_fine[student_count] = 0;

    // Initialize borrowed days array for this student
    for (int i = 0; i < 3; i++)
    {
        borrowed_days[getBorrowIndex(student_count, i)] = 0;
    }

    cout << "Registration successful! Your Student ID: " << student_id[student_count] << "\n";
    cout << "Remember your ID and password for login.\n";

    student_count++;
}

int studentLogin()
{
    int id;
    string password;

    cout << "\n--- Student Login ---\n";

    cout << "Enter Student ID: ";
    cin >> id;

    cout << "Enter Password: ";
    cin.ignore();
    getline(cin, password);

    for (int i = 0; i < student_count; i++)
    {
        if (student_id[i] == id && student_password[i] == password)
        {
            return i;
        }
    }

    return -1;
}

void searchBook()
{
    if(book_count == 0)
    {
     cout<<"No books in library!\n";
     return;
    }

    cout<< "\n--- Search Book ---\n";

      int id;
      cout<<"Enter book ID to search: ";
      cin>>id;

      bool found = false;

   for(int i = 0; i < book_count; i++)
     {
      if(book_id[i] == id)
         {
           cout<<"\nBook Found:\n";

           cout<<"ID: " << book_id[i] << "\nTitle: " << book_title[i];
           cout<<"\nAuthor: " << book_author[i] << "\nCopies Available: " << book_copies[i] << "\n";
           found = true;
           break;
          }
      }
        if(!found)
            cout<<"Book not found!\n";
    }
    else
    {
     cout<<"Invalid choice!\n";
    }
}

void borrowBook(int student_index)
{
    if (book_count == 0)
    {
        cout<<"No books available!\n";
        return;
    }

    if (student_borrowed[student_index] >= 3)
    {
        cout << "You have already borrowed maximum books (3)!\n";
        return;
    }

    cout << "\n--- Borrow Book ---\n";
    cout << "Enter Book ID to borrow: ";
    int id;
    cin >> id;

    int book_index = -1;
    for (int i = 0; i < book_count; i++)
    {
        if (book_id[i] == id)
        {
            book_index = i;
            break;
        }
    }

    if (book_index == -1)
    {
        cout << "Book not found!\n";
        return;
    }

    if (book_copies[book_index] <= 0)
    {
        cout << "Sorry, no copies available!\n";
        return;
    }

    // Find empty slot for student
    int slot = -1;
    for (int i = 0; i < 3; i++)
    {
        if (borrowed_days[getBorrowIndex(student_index, i)] == 0)
        {
            slot = i;
            break;
        }
    }

    if (slot == -1)
    {
        cout << "Error: No slot available!\n";
        return;
    }

    // Borrow the book
    book_copies[book_index]--;
    student_borrowed[student_index]++;

    // Set borrowed days to 1
    borrowed_days[getBorrowIndex(student_index, slot)] = 1;

    cout << "Book borrowed successfully!\n";
    cout << "You have borrowed " << student_borrowed[student_index] << " books.\n";
    cout << "Return within 7 days to avoid fine!\n";
}

void returnBook(int student_index)
{
    if (student_borrowed[student_index] == 0)
    {
        cout << "You haven't borrowed any books!\n";
        return;
    }

    cout << "\n--- Return Book ---\n";
    cout << "Enter Book ID to return: ";
    int id;
    cin >> id;

    // Find which slot has this book
    int slot = -1;
    for (int i = 0; i < 3; i++)
    {
        if (borrowed_days[getBorrowIndex(student_index, i)] > 0)
        {
            slot = i;
            break;
        }
    }

    if (slot == -1)
    {
        cout << "You haven't borrowed this book!\n";
        return;
    }

    // Search for book to return
    int book_index = -1;
    for (int i = 0; i < book_count; i++)
    {
        if (book_id[i] == id)
        {
            book_index = i;
            break;
        }
    }

    if (book_index == -1)
    {
        cout << "Book not found in library records!\n";
        return;
    }

    // Calculate days borrowed
    int days_borrowed = borrowed_days[getBorrowIndex(student_index, slot)];

    // Calculate fine if overdue (more than 7 days)
    if (days_borrowed > 7)
    {
        int overdue_days = days_borrowed - 7;
        int fine = overdue_days * 10;
        student_fine[student_index] += fine;

        cout << "Book is overdue by " << overdue_days << " days!\n";
        cout << "Fine charged: Rs " << fine << "\n";
        cout << "Total fine due: Rs " << student_fine[student_index] << "\n";
    }

    // Return the book
    book_copies[book_index]++;
    student_borrowed[student_index]--;

    // Clear the slot
    borrowed_days[getBorrowIndex(student_index, slot)] = 0;

    cout << "Book returned successfully!\n";
    cout << "You have " << student_borrowed[student_index] << " books borrowed.\n";
}

void payFine(int student_index)
{
    cout << "\n--- Pay Fine ---\n";
    cout << "Your current fine: Rs " << student_fine[student_index] << "\n";

    if (student_fine[student_index] == 0)
    {
        cout << "No fine to pay!\n";
        return;
    }

    cout << "Enter amount to pay: Rs ";
    int amount;
    cin >> amount;

    if (amount <= 0)
    {
        cout << "Invalid amount!\n";
        return;
    }

    if (amount > student_fine[student_index])
    {
        cout << "Amount exceeds fine. Paying full fine of Rs " << student_fine[student_index] << "\n";
        student_fine[student_index] = 0;
    }
    else
    {
        student_fine[student_index] -= amount;
        cout << "Paid Rs " << amount << ". Remaining fine: Rs " << student_fine[student_index] << "\n";
    }

    cout << "Payment successful!\n";
}

void checkOverdueBooks()
{
    cout << "\n--- Check Overdue Books ---\n";

    for (int i = 0; i < student_count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int days = borrowed_days[getBorrowIndex(i, j)];
            if (days > 7)
            {
                int overdue_days = days - 7;
                cout << student_name[i] << " (ID: " << student_id[i] << ") has book overdue by "
                     << overdue_days << " days. Fine: Rs " << (overdue_days * 10) << "\n";
            }
        }
    }
}

void updateDays()
{
    // Increase days for all borrowed books
    for (int i = 0; i < student_count; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int idx = getBorrowIndex(i, j);
            if (borrowed_days[idx] > 0)
            {
                borrowed_days[idx]++;
            }
        }
    }
    current_day++;
    cout << "System day updated to: Day " << current_day << "\n";
}

void viewMyInfo(int student_index)
{
    cout << "\n--- My Information ---\n";
    cout << "Student ID: " << student_id[student_index] << "\n";
    cout << "Name: " << student_name[student_index] << "\n";
    cout << "Books Borrowed: " << student_borrowed[student_index] << "\n";
    cout << "Current Fine: Rs " << student_fine[student_index] << "\n";

    if (student_borrowed[student_index] > 0)
    {
        cout << "\nBooks currently borrowed:\n";
        for (int i = 0; i < 3; i++)
        {
            int days = borrowed_days[getBorrowIndex(student_index, i)];
            if (days > 0)
            {
                cout << "Book #" << (i + 1) << " - Borrowed for " << days
                     << " days (Due in " << max(0, 7 - days) << " days)\n";
            }
        }
    }
}

void adminMenu()
{
    while (true)
    {
        cout<< "\n========================================\n";
        cout<< "           ADMIN MENU";
        cout<< "\n========================================\n";
        cout<< "1. Add Book"   <<endl;
        cout<< "2. View All Books"    <<endl;
        cout<< "3. Edit Book Details" <<endl;
        cout<< "4. Delete Book"   <<endl;
        cout<< "5. View Students" <<endl;
        cout<< "6. Check Overdue Books" <<endl;
        cout<< "7. Update System Day"   <<endl;
        cout<< "8. Logout";
        cout<< "\n========================================\n";
          
        int choice;
        cout<< "Enter choice: ";
        cin>> choice;

        switch (choice)
        {
        if(choice == 1) 
           {
            system("cls");

            addBook();              // func. call

            cout<< "Press Enter to continue...";
            getch(); 

            system("cls");
          }

        else if(choice == 2)
          {        
            system("cls");

            viewBooks();       //func. call..

            cout<< "Press Enter to continue...";
            getch();

            system("cls");
          }
       
        else if(choice == 3)
         {
            system("cls");

            editBook();     //func. call..

            cout<< "Press Enter to continue...";
            getch();

            system("cls");
        }

      else if(choice == 4)
         {
            system("cls");

            deleteBook();  //func. call..

            cout<<"Press Enter to continue...";
            getch();

            system("cls");
         }
    
     else if(choice == 5)
       {
            system("cls");

            cout<< "\n--- Registered Students ---\n";

            if (student_count == 0)
            {
              cout<< "No students registered!\n";
            }
            else
            {
                for(int i = 0; i < student_count; i++)
                {
                    cout << "ID: " << student_id[i] << " | Name: " << student_name[i];
                    cout << " | Books Borrowed: " << student_borrowed[i];
                    cout << " | Fine Due: Rs " << student_fine[i] << "\n";
                }
            }
            cout<< "\nPress Enter to continue...";
            getch();
            system("cls");
         }
      else if(choice == 6)
         {
            system("cls");

            checkOverdueBooks();

            cout<< "Press Enter to continue...";
            getch();

            system("cls");
         }

       else if(choice == 7)
          {
            system("cls");

            updateDays();

            cout<<"Press Enter to continue...";
            getch();

            system("cls");
           }
        else if(choice == 8)
           {
            cout<< "Logging out...\n";
            return;
           }
       else
         {
            cout<< "Invalid choice! Try again." <<endl;
            cout<< "Press Enter to continue...";
            getch();
            system("cls");
           
        }
    }
}

void studentMenu(int student_index)
{
    int choice;

    while (true)
    {
        cout << "\n========================================\n";
        cout << "        STUDENT MENU\n";
        cout << "Welcome, " << student_name[student_index] << "!\n";
        cout << "========================================\n";
        cout << "1. Search Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "4. View My Info\n";
        cout << "5. Pay Fine\n";
        cout << "6. Logout\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            searchBook();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        case 2:
            system("cls");
            borrowBook(student_index);
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        case 3:
            system("cls");
            returnBook(student_index);
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        case 4:
            system("cls");
            viewMyInfo(student_index);
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        case 5:
            system("cls");
            payFine(student_index);
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        case 6:
            cout << "Logging out...\n";
            current_student = -1;
            return;
        default:
            cout << "Invalid choice! Try again.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
    }
}

int main()
{
    int choice;

    // Add some sample books
    book_id[0] = 1001;
    book_title[0] = "C++ Programming";
    book_author[0] = "Bjarne Stroustrup";
    book_copies[0] = 5;
    book_count++;

    book_id[1] = 1002;
    book_title[1] = "Data Structures";
    book_author[1] = "Adam Drozdek";
    book_copies[1] = 3;
    book_count++;

    book_id[2] = 1003;
    book_title[2] = "Algorithms";
    book_author[2] = "Thomas Cormen";
    book_copies[2] = 4;
    book_count++;

    system("cls");

    while (true)
    {
        cout << "========================================\n";
        cout << "    LIBRARY MANAGEMENT SYSTEM\n";
        cout << "       with Edit Book Feature\n";
        cout << "========================================\n";
        cout << "Current System Day: " << current_day << "\n";
        cout << "----------------------------------------\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Sign Up\n";
        cout << "3. Student Login\n";
        cout << "4. Exit\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string user, pass;
            system("cls");
            cout << "\n--- Admin Login ---\n";
            cout << "Enter Admin Username: ";
            cin.ignore();
            getline(cin, user);
            cout << "Enter Admin Password: ";
            getline(cin, pass);

            if (user == admin_user && pass == admin_pass)
            {
                cout << "Login successful!\n";
                cout << "\nPress Enter to continue...";
                cin.get();
                system("cls");
                adminMenu();
            }
            else
            {
                cout << "Invalid credentials!\n";
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                system("cls");
            }
            break;
        }
        case 2:
            system("cls");
            studentSignup();
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        case 3:
            system("cls");
            current_student = studentLogin();
            if (current_student != -1)
            {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                system("cls");
                studentMenu(current_student);
            }
            else
            {
                cout << "Login failed! Wrong ID or password.\n";
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                system("cls");
            }
            break;
        case 4:
            cout << "Thank you for using Library System!\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
            break;
        }
    }

    return 0;
}