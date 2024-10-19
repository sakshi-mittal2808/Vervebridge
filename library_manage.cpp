#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

// class to store info about book
class book
{
    public:
        string title,author,isbn;
        bool isIssued;

        // constructor initization list
        book(string t, string a, string i, bool isIssued=false): title(t), author(a), isbn(i), isIssued(isIssued) {}
};

void showMenu( )
{
    cout<<"***** WELCOME TO LIBRARY MANAGEMENT SYSTEM *****\n\n";
    cout<<"1. Add a new Book\n";
    cout<<"2. Issue a Book\n";
    cout<<"3. Return a Book\n";
    cout<<"4. Search for a Book\n";
    cout<<"5. Display available books\n";
    cout<<"6. Exit\n";
}

// search book
void searchBook(vector<book>& Book)
{
    int ch;
    bool found=false;
    string a,t,isbn;
    cout<<"Seach by: \n";
    cout<<"1. ISBN\n";
    cout<<"2. Author\n";
    cout<<"3. Title\n";
    cout<<"Enter your choice: ";
    cin>>ch;
    cin.ignore( );

    switch (ch)
    {
        case 1: cout<<"Enter ISBN: ";
                getline(cin,isbn);
                
                for(const auto& b: Book)
                {
                    if(b.isbn==isbn)
                    {
                        found=true;
                        cout<<"Author: "<<b.author<<endl;
                        cout<<"Title: "<<b.title<<endl;
                        cout<<"ISBN: "<<b.isbn<<endl<<endl;
                    }
                }
                if(!found)
                cout<<"No book found with this ISBN number...!!!\n\n";
                break;
        case 2: cout<<"Enter Author: ";
                getline(cin,a);

                for(const auto &b: Book)
                {
                    if(b.author==a)
                    {
                        found=true;
                        cout<<"Author: "<<b.author<<endl;
                        cout<<"Title: "<<b.title<<endl;
                        cout<<"ISBN: "<<b.isbn<<endl<<endl;
                    }
                }
                if(!found)
                cout<<"No book found with this Author Name...!!!\n\n";
                break;
        case 3: cout<<"Enter Title: ";
                getline(cin,t);

                for(const auto &b: Book)
                {
                    if(b.title==t)
                    {
                        found=true;
                        cout<<"Author: "<<b.author<<endl;
                        cout<<"Title: "<<b.title<<endl;
                        cout<<"ISBN: "<<b.isbn<<endl<<endl;
                    }
                }
                if(!found)
                cout<<"No book found with this Title...!!!\n\n";
                break;
        default:cout<<"Invalid option...\n\n";
            return;
    }
}

// Adding books
void addBook(vector<book>& Book)
{
    string t, a, isbn;
    cout<<"Enter book title: ";
    cin.ignore(); // to ignore newline character from previous input--- only used 1 time
    getline(cin,t);

    cout<<"Enter book author name: ";
    getline(cin,a);

    cout<<"Enter ISBN: ";
    getline(cin,isbn);

    // check if book already exists or not
    for(const auto& book: Book)
    {
        if(book.isbn == isbn)
        {
            cout<<"Book already exists...!!!\n\n";
            return;  // Only return if the book is found
        }
    }

    // If no existing book is found, add the new book
    Book.push_back(book(t, a, isbn));
    cout<<"Book added successfully.\n\n";
}


// issuing books
void issueBook(vector<book>& Book)
{
    string isbn;
    cout<<"Enter ISBN: ";
    cin.ignore();
    getline(cin,isbn);

    // searching for a book with isbn num
    for(auto &book: Book)
    {
        if(book.isbn==isbn)
        {
            if(!book.isIssued)
            {
                book.isIssued=true;
                cout<<"Book Issued Successfully...!!!\n\n";
            }
            else
            cout<<"Book is already issued...!!!\n\n";
            return;
        }
    }
    cout<<"Book not found...!!!\n\n";
}

// return Book
void returnBook(vector<book>& Book)
{
    string isbn;
    cout<<"Enter ISBN of the book you want to return: ";
    cin.ignore();
    getline(cin,isbn);

    // search for a book by isbn and return it
    for(auto &book: Book)
    {
        if(book.isbn==isbn)
        {
            book.isIssued=false;
            cout<<"Book returned successfully...!!!\n\n";
        }
        else
        cout<<"Book not found...!!!\n\n";
        return;
    }
    cout<<"Book not found...!!!\n\n";
}

void display(vector<book>& Book)
{
    if(Book.size( )==0)
    {
        cout<<"No books available\n\n";
        return;
    }

    cout<<"List of books with their titles:\n\n";
    for(int i=0;i<Book.size( );i++)
    {
        cout<<"Author: "<<Book[i].author<<endl;
        cout<<"Title: "<<Book[i].title<<endl;
        cout<<"ISBN: "<<Book[i].isbn<<endl;
        cout<<"Issued: "<<(Book[i].isIssued?"Yes":"No")<<endl<<endl;
    }
    return;
}

void saveLibrary(vector<book>& lib)
{
    ofstream file("library_data.txt");
    for(const auto &book: lib)
    file<<book.title<<"|"<<book.author<<"|"<<book.isbn<<"|"<<book.isIssued<<endl;
    file.close( );
    cout<<endl<<"Library data saved successfully...!!!\n\n";
}

void loadLibrary(vector<book> &lib)
{
    ifstream file("library_data.txt");
    if(file.is_open( ))
    {
        string title,author,isbn;
        bool isIssued;
        while(file>>ws && getline(file,title,'|'))
        {
            getline(file,author,'|');
            getline(file,isbn,'|');
            file>>isIssued;
            lib.push_back(book(title,author,isbn,isIssued));
        }
        file.close( );
        cout<<endl<<"Library data loaded successfully...!!!\n\n";
    }
    else
    cout << "No existing library data found. Starting fresh.\n";
}

int main( )
{
    vector<book>lib; // vector to store books
    loadLibrary(lib); //load existing library data  from file

    int ch;
    while(true)
    {
        showMenu( );
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1: addBook(lib);
                    break;
            case 2: issueBook(lib);
                    break;
            case 3: returnBook(lib);
                    break;
            case 4: searchBook(lib);
                    break;
            case 5: display(lib);
                    break;
            case 6: saveLibrary(lib);
                    cout<<"Existing program.... All data saved successfully...!!!\n";
                    exit(0);
            default: cout<<"Enter valid number: ";
                exit(0);
        }
    }
}
