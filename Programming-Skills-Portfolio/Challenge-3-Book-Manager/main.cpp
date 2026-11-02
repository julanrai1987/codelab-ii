#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class Book {
public:
    string title, author;
    int pages;
    string id;
    bool borrowed;

    Book(string t, string a, int p, string i, bool b)
        : title(t), author(a), pages(p), id(i), borrowed(b) {}

    void display() const {
        cout << "ID: " << id << " | Title: " << title
             << " | Author: " << author << " | Pages: " << pages
             << " | " << (borrowed ? "Borrowed" : "Available") << '\n';
    }
};

vector<Book> loadBooks(const string& filename) {
    ifstream file(filename);
    vector<Book> books;
    if (!file) {
        cerr << "Could not open " << filename << '\n';
        return books;
    }
    string line;
    while (getline(file, line)) {
        string title, author, pagesText, id, status;
        stringstream row(line);
        if (getline(row, title, ',') && getline(row, author, ',') &&
            getline(row, pagesText, ',') && getline(row, id, ',') &&
            getline(row, status)) {
            try {
                books.emplace_back(title, author, stoi(pagesText), id,
                                   status == "true");
            } catch (const exception&) {
                cerr << "Skipping invalid book record.\n";
            }
        }
    }
    return books;
}

bool saveBooks(const string& filename, const vector<Book>& books) {
    ofstream file(filename);
    if (!file) return false;
    for (const Book& book : books) {
        file << book.title << ',' << book.author << ',' << book.pages << ','
             << book.id << ',' << (book.borrowed ? "true" : "false") << '\n';
    }
    return static_cast<bool>(file);
}

Book* findBook(vector<Book>& books, const string& id) {
    for (Book& book : books) {
        if (book.id == id) return &book;
    }
    return nullptr;
}

int main() {
    const string filename = "bookData.txt";
    vector<Book> books = loadBooks(filename);
    if (books.empty()) {
        cerr << "No books available to manage.\n";
        return 1;
    }

    while (true) {
        cout << "\n=== Book Manager ===\n"
             << "1. View all books\n2. View book by ID\n"
             << "3. Borrow book\n4. Return book\n5. Exit\nChoice: ";
        int choice;
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid menu choice.\n";
            continue;
        }
        if (choice == 5) break;
        if (choice == 1) {
            for (const Book& book : books) book.display();
            continue;
        }
        if (choice < 2 || choice > 4) {
            cout << "Choose an option from 1 to 5.\n";
            continue;
        }
        string id;
        cout << "Enter book ID (e.g. 001): ";
        cin >> id;
        Book* book = findBook(books, id);
        if (!book) {
            cout << "Book not found.\n";
            continue;
        }
        if (choice == 2) {
            book->display();
        } else if (choice == 3) {
            if (book->borrowed) cout << "This book is already borrowed.\n";
            else {
                book->borrowed = true;
                cout << "Book borrowed successfully.\n";
                if (!saveBooks(filename, books)) cerr << "Could not save changes.\n";
            }
        } else {
            if (!book->borrowed) cout << "This book is already available.\n";
            else {
                book->borrowed = false;
                cout << "Book returned successfully.\n";
                if (!saveBooks(filename, books)) cerr << "Could not save changes.\n";
            }
        }
    }
    cout << "Goodbye!\n";
    return 0;
}
