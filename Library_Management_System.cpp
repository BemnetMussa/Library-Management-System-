
// ASTU Book Store Management System
#include <iostream>
#include <string>


using namespace std;

// using doubly linked list
struct Stud_node {
    int studId;
    string studName;
    string bookBorrowed;
    Stud_node* prev;
    Stud_node* next;
};

struct BookNode {
    int bookId;
    string bookName;
    string author;
    BookNode* prev;
    BookNode* next;
};

const int max_size = 3; // Maximum size of the stack

// for the Stack
struct Student {
    int id;
    string name;
    Student* next;
    string borrowedBooks[max_size]; // Array to hold borrowed books
    int top ; // Index of the top element
};




// Function to initialize a student
void initializeStudent(Student& student, int id, const string& name) {
    student.id = id;
    student.name = name;
    student.top = -1; // Initialize top index to -1 (empty stack)
}

// Function to check if the stack is empty
bool isEmpty(const Student& student) {
    return student.top == -1;
}

// Function to push a book onto the stack
void push(Student& student, string& book) {
    if (student.top == max_size - 1) {
    cout << "Stack Overflow! Cannot borrow more books." << endl;
        return;
    }
    student.borrowedBooks[++student.top] = book;
}

// Function to pop (remove) a book from the stack
void pop(Student& student) {
    if (isEmpty(student)) {
        cout << "Stack Underflow! No books to return." << endl;
        return;
    }
    cout << "Book '" << student.borrowedBooks[student.top--] << "' returned." << endl;
}




// Create student node
Stud_node* createStudentNode(int id, const string& name, const string& book) {
    Stud_node* newNode = new Stud_node;
    newNode->studId = id;
    newNode->studName = name;
    newNode->bookBorrowed = book;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

// Create book node
BookNode* createBookNode(int id, const string& name, const string& author) {
    BookNode* newNode = new BookNode;
    newNode->bookId = id;
    newNode->bookName = name;
    newNode->author = author;
    newNode->next = nullptr;
    return newNode;
}





// Student Menu
// Adding a student to the front of the list
void addStudentToFront(Stud_node*& head, Student& student, int id, const string& name, const string& book) {
  if (student.top != max_size - 1) {


    Stud_node* newNode = createStudentNode(id, name, book);
    if (head == nullptr) {
        head = newNode;

    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }


    cout << "Student added at the front of a list successfully." <<endl;}

}


// Adding a student at the end of a list
void addStudentEnd (Stud_node*& head, Student& student, int id, const string& name, const string& book) {
    if (student.top != max_size - 1) {
   Stud_node* newNode = createStudentNode(id, name, book);
    if (head == nullptr) {
        head = newNode;

    } else {
         Stud_node* current = head;
         // until it reaches null
        while (current->next)
        {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;

    }
     cout << "Student added at the end of a list successfully." << std::endl;}
}


// Adding a student at the middle of a list
void addStudentMiddle(Stud_node*& head, Student& student, int id, const string& name, const string& book) {
   if (student.top != max_size - 1) {
    Stud_node* newNode = createStudentNode(id, name, book);

    if (head == nullptr) {
        // List is empty, so the new node becomes the head and tail
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
    } else {
        int mid = 0;
        Stud_node* current = head;
        while (current != nullptr) {
            mid++;
            current = current->next;
        }

        mid = mid / 2;

        Stud_node* middle_position = head;
        for (int i = 0; i < mid-1; i++) {
            middle_position = middle_position->next;
        }

        newNode->prev = middle_position;
        newNode->next = middle_position->next;
        if (middle_position->next != nullptr) {
            middle_position->next->prev = newNode;
        }
        middle_position->next = newNode;

        cout << "Student added at the middle of the list!" << endl;
    }}
}


// deleting a student from the front of a list
void deleteStudentFront(Stud_node*& head) {
    if (head == nullptr) {
        cout << "No students in the list." << endl;
        return;
    }

    Stud_node* temp = head;
    head = head->next;


    if (head != nullptr) {
        head->prev = nullptr;
    }

    delete temp;
}

// deleting a student from the end of a list
void deleteStudentEnd(Stud_node*& head) {
    if (head == nullptr) {
        cout<< "No students in the list." <<endl;
        return;
    }

    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Stud_node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->prev->next = nullptr;
    delete current;
}

// deleting a student from the middle of a list
void deleteStudentMiddle(Stud_node*& head) {
    if (head == nullptr) {
        cout<< "No students in the list." << endl;
        return;
    }

    int count = 0;
    Stud_node* curr = head;
    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }

    int mid = count / 2;
    Stud_node* mid_node = head;

    for (int i = 0; i < mid; i++) {
        mid_node = mid_node->next;
    }

    if (mid_node == head) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete mid_node;
    } else {
        mid_node->prev->next = mid_node->next;
        if (mid_node->next != nullptr) {
            mid_node->next->prev = mid_node->prev;
        }
        delete mid_node;
    }

    cout << "Student record removed from the middle of the list." << endl;
}


// delete a student by an id
void deleteStudentbyId(Stud_node*& head, int id){
   if (head == nullptr) {
        cout << "No students in the list." << endl;
        return;
    }

    Stud_node* current = head;
    while (current != nullptr) {
        if (current->studId == id) {
            if (current == head) {
                deleteStudentFront(head);
            }
            else if (current->next == nullptr) {
                deleteStudentEnd(head);
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            return;
        }
        current = current->next;
    }

    cout << "Student with ID " << id << " not found." << endl;}


// Display a student by studID
void displayStudentsbyID(Stud_node* head, int id){

    Stud_node* current = head;
    while (current != nullptr) {
    if (current->studId == id) {
        std::cout << "Student ID: " << current->studId << std::endl;
        std::cout << "Student Name: " << current->studName << std::endl;
        std::cout << "Book Borrowed: " << current->bookBorrowed << std::endl;
        break;
    }
    current = current->next;
    }
    if (current == nullptr) {
    std::cout << "Student with ID " << id << " not found." << std::endl;
}

}


// Display all of student that are Recorded
void displayAllStudents(Stud_node* head) {
    if (head == nullptr) {
        cout << "No students in the list." << endl;
        return;
    }

    else {
    Stud_node* current = head;
    while (current != nullptr) {
        cout << "Student ID: " << current->studId << endl;
        cout << "Student Name: " << current->studName << endl;
        cout << "Book Borrowed: " << current->bookBorrowed << endl;
        cout << endl;
        current = current->next;
    }}
}






// Book List

// Adding new book to the store ~ at the front
void addBook(BookNode*& head, int id, const string& name, const string& author) {
    BookNode* newNode = createBookNode(id, name, author);


    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}


// Adding new book at the middle
void addBookToMiddle(BookNode*& head, int id, const string& name, const string& author) {
    BookNode* newNode = createBookNode(id, name, author);
      if (head == nullptr) {
        // List is empty, so the new node becomes the head
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = nullptr;
    } else {
        int mid = 0;
        BookNode* current = head;
        while (current != nullptr) {
            mid++;
            current = current->next;
        }

        mid = mid / 2;
        current = head;
        for (int i = 0; i < mid; i++) {
            current = current->next;
        }

        newNode->prev = current;
        newNode->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;

        std::cout << "new Book Added at the middle of the list! ";
}}


// Display all books
void displayAllBooks(BookNode* head) {
    if (head == nullptr) {
        std::cout << "No books in the store." << std::endl;
        return;
    }

    BookNode* current = head;
    while (current != nullptr) {
        std::cout << "Book ID: " << current->bookId << std::endl;
        std::cout << "Book Name: " << current->bookName << std::endl;
        std::cout << "Author: " << current->author << std::endl;
        std::cout << std::endl;
        current = current->next;
    }
}


// Delete a book by Book ID
void deleteBookById(BookNode*& head, int id) {
    // if there is no book
    if (head == nullptr) {
        std::cout << "No books in the store." << std::endl;
        return;
    }

    // if the book is at the front
    if (head->bookId == id) {
        BookNode* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        std::cout << "Book with ID " << id << " deleted." << std::endl;
        return;
    }

    // if the book is on the middle
    BookNode* current = head;
    while (current != nullptr) {
        if (current->bookId == id) {
            BookNode* prev = current->prev;
            BookNode* next = current->next;
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next != nullptr) {
                next->prev = prev;
            }
            delete current;
            std::cout << "Book with ID " << id << " deleted." << std::endl;
            return;
        }
        current = current->next;
    }

    std::cout << "Book with ID " << id << " not found." << std::endl;
}



// Book Borrowed display the top most of the stack

// Function to display all borrowed books
void displayBorrowedBooks(const Student& student) {
    cout << "Borrowed Books for Student ID: " << student.id << endl;
    if (isEmpty(student)) {
        cout << "No books borrowed." << endl;
        return;
    }
    cout << "Books:";
    for (int i = student.top; i >= 0; --i) {
        cout << student.borrowedBooks[i] <<", ";
    }
}




// Returning a book to the store
void return_book(Student& student , int id) {

                Student* current = &student;
                while (current != nullptr){
                    if(isEmpty(*current)){

                        cout<<"Stack Underflow Error! There is no books to return!"<<endl;
                        break;
                    }
                    if (current->id == id){
                        cout<<"Returned book is: " <<current->borrowedBooks[current->top--]<<endl;
                        break;

                    }
                    current = current->next;
                if(current == nullptr){
                    cout<<"There is no Student with this id "<<id<<endl;
                    return;
        }}

}




int main() {
    // initialize the head and tail and the top of the stack
    Stud_node* studentHead = nullptr;
    BookNode* bookHead = nullptr;
    Student* studentHead1 = new Student;
    studentHead1->next = nullptr;


    int choice;
    while (true) {

        cout<<endl;
        cout<<endl;
        cout<<endl;
        ab:
        cout << "           **************** ASTU Book Store Management System  ****************" << endl;
        cout<<endl;
        cout << "           1. Student Management" << endl;
        cout << "           2. Book Management" << endl;
        cout << "           3. Display Borrowed Book for a Student" << endl;
        cout<<  "           4. Return a book " <<endl;
        cout << "           5. Exit" << endl;
        cout<<endl;
        cout << "Enter your choice: ";
        ba:

        cin >> choice;

        switch (choice) {

            case 1: {
                system("cls");
                int studentChoice;
                cout<<endl;
                cout<<endl;
                cout<<endl;
                cout << "           **************** Student Management **************** " << endl;
                cout<<endl;
                cout << "           1. Add new student at the front of a list" << endl;
                cout << "           2. Add new student at the middle of a list" << endl;
                cout << "           3. Add new student at the end of a list" << endl;
                cout << "           4. Display all students" << endl;
                cout << "           5. Display student by ID" << endl;
                cout << "           6. Delete a student from the front" << endl;
                cout << "           7. Delete a student from the middle" << endl;
                cout << "           8. Delete a student from the end" << endl;
                cout << "           9. Delete a student by ID" <<endl;
                cout << "           10. go back" << endl;
                cout<<endl;

                cout << "Enter your choice: ";
                bar:
                cin >> studentChoice;

                int id;
                string name, book;

                switch (studentChoice) {
                    // adding student to the front of a list
                    case 1: {
                        bega:
                        cout << "Enter student ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega;
                        }
                        cout << "Enter student name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter book borrowed: ";
                        getline(cin, book);


                        // same student borrowing a book
                        Student* current = studentHead1;
                        while (current != nullptr) {

                            if (current->id == id) {
                                push(*current, book); // adding the book to stack of borrow to a student stack
                                break;
                            }
                            current = current->next;
                            }

                        // Create a new student
                        if (current == nullptr){


                            Student* newStudent = new Student;
                            initializeStudent(*newStudent, id, name);
                            push(*newStudent, book);

                            // Insert the new student at the front of the list
                            newStudent->next = studentHead1->next;
                            studentHead1->next = newStudent;

                            addStudentToFront(studentHead, *newStudent, id, name, book);
                            }

                        break;
                    }

                    // adding student to the middle of a list
                    case 2: {
                           bega2:
                        cout << "Enter student ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega2;
                        }

                        cout << "Enter student name: ";
                        cin.ignore();
                        getline(std::cin, name);
                        cout << "Enter book borrowed: ";
                        getline(std::cin, book);

                // same student borrowing a book
                        Student* current = studentHead1;
                        while (current != nullptr) {

                            if (current->id == id) {
                                push(*current, book); // adding the book to stack of borrow to a student stack
                                break;
                            }
                            current = current->next;
                            }

                        // Create a new student
                        if (current == nullptr){


                            Student* newStudent = new Student;
                            initializeStudent(*newStudent, id, name);
                            push(*newStudent, book);

                            // Insert the new student at the front of the list
                            newStudent->next = studentHead1->next;
                            studentHead1->next = newStudent;


                        addStudentMiddle(studentHead,*newStudent, id, name, book);
                            }




                        break;

                    }

                    // adding student to the end of a list
                    case 3: {
                        bega3:
                        cout << "Enter student ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega3;
                        }

                        cout << "Enter student name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter book borrowed: ";
                        getline(cin, book);

                        // same student borrowing a book
                        Student* current = studentHead1;
                        while (current != nullptr) {

                            if (current->id == id) {
                                push(*current, book); // adding the book to stack of borrow to a student stack
                                break;
                            }
                            current = current->next;
                            }

                        // Create a new student
                        if (current == nullptr){


                            Student* newStudent = new Student;
                            initializeStudent(*newStudent, id, name);
                            push(*newStudent, book);

                            // Insert the new student at the front of the list
                            newStudent->next = studentHead1->next;
                            studentHead1->next = newStudent;

                            addStudentEnd(studentHead, *newStudent, id, name, book);
                            }




                        break;
                        }

                    case 4: {

                        displayAllStudents(studentHead);
                        break;
                    }
                    case 5: {

                       cout << "Enter student ID (it must be in an Integer): ";
                        cin >> id;
                        displayStudentsbyID(studentHead, id);
                        break;
                    }
                    case 6: {

                        deleteStudentFront(studentHead);
                        cout << "Student record deleted from the front." << std::endl;
                        break;
                    }
                    case 7: {
                        deleteStudentMiddle(studentHead);
                        break;
                    }
                    case 8: {
                        deleteStudentEnd(studentHead);
                        cout << "Student record deleted from the end." << std::endl;
                        break;
                    }

                    case 9: {
                              a:
                        cout << "Enter student ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto a;
                        }
                        deleteStudentbyId(studentHead, id);
                        break;
                    }
                    case 10: {

                        system("cls");
                        goto ab;
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please try again." << std::endl;
                        cin.clear();
                        cin.ignore();
                        goto bar;
                        break;
                    }
                }

                break;

            }

            case 2: {
                system("cls");
                int bookChoice;

                cout<<endl;
                cout<<endl;
                cout<<endl;
                cout << "           **************** Book Management **************** " << endl;
                cout<<endl;
                cout << "           1. Add new book to the store" << endl;
                cout << "           2. Add new book at the middle" << endl;
                cout << "           3. Display all books list from the store" << endl;
                cout << "           4. Delete a book by BookID" << endl;
                cout << "           5. go back "<< endl;
                cout<<endl;
                cout << "Enter your choice: ";

                cd:
                cin >> bookChoice;
                string name, author;
                int id;

                switch (bookChoice) {
                    case 1: {
                            bega4:
                        cout << "Enter book ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega4;
                        }

                        cout << "Enter book name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter author: ";
                        getline(cin, author);
                        addBook(bookHead, id, name, author);
                        cout << "Book added successfully." << std::endl;
                        break;
                    }

                    case 2: {
                            bega5:
                        cout << "Enter Book ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega5;
                        }

                        cout << "Enter book name: ";
                        cin.ignore();
                        getline(cin, name);
                        cout << "Enter author: ";
                        getline(cin, author);
                        addBookToMiddle(bookHead, id, name, author);
                        cout << "Book added successfully." << std::endl;
                        break;

                    }
                    case 3: {
                        displayAllBooks(bookHead) ;
                                      break;
            }
                        case 4: {
                            bega6:
                        cout << "Enter Book ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega6;
                        }
                        deleteBookById(bookHead, id);
                        break;
                    }

                    case 5: {
                        goto ab;
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Please try again." << endl;
                        cin.clear();
                        cin.ignore();
                        goto cd;
                        break;
                    }
                }
            break;
            }


            case 3: {
                system("cls");
                 // Display borrowed books for a student
                int id;
                       bega7:
                        cout << "Enter student ID: ";
                        cin >> id;

                        if (!id) {
                            cout<<endl;
                            cout<<"Error! try again, must be an integer type"<<endl;
                            cin.clear();
                            cin.ignore();
                            goto bega7;
                        }

                Student* current = studentHead1;
                while (current != nullptr) {
                    if (current->id == id) {
                        displayBorrowedBooks(*current);
                        break;
                    }
                    current = current->next;
                }
                if (current == nullptr) {
                    cout << "Student with ID " << id << " not found." << endl;
                }

                break;
                    }


            case 4: {
                int id;
                be:
                cout << "Enter student ID: ";
                cin >> id;

                if (!id) {
                    cout<<endl;
                    cout<<"Error! try again, must be an integer type"<<endl;
                    cin.clear();
                    cin.ignore();
                    goto be;
                        }
                return_book(*studentHead1, id);
                break;

            }
    // Close or logout from the system
            case 5: {
                system("cls");
                cout << "Exiting the program...... existed Successfully" << endl;
                // Clean up the allocated memory.............
                while (studentHead != nullptr) {
                    deleteStudentFront(studentHead);
                }

                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                cin.clear();
                cin.ignore();
                goto ba;

                break;
            }
        }
    }

    return 0;
}
