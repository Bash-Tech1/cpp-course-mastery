#include <algorithm>
#include <format>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

// ---------- small UI helpers ----------
namespace ui {
    string border(initializer_list<int> widths) {
        string line = "+";
        for (int w : widths)
            line += string(w + 2, '-') + "+";
        return line;
    }
    void ok(const string& msg)    { cout << "[OK] " << msg << "\n"; }
    void info(const string& msg)  { cout << "[i]  " << msg << "\n"; }
    void error(const string& msg) { cout << "[!]  " << msg << "\n"; }

    // All input goes through getline, so there are no leftover-newline problems
    string read_line(const string& prompt) {
        cout << prompt;
        string s;
        if (!getline(cin, s))
            throw runtime_error("Input closed.");
        return s;
    }
    int read_int(const string& prompt) {
        while (true) {
            string s = read_line(prompt);
            try {
                size_t pos = 0;
                int v = stoi(s, &pos);
                if (pos == s.size())
                    return v;
            } catch (...) {}
            error("Please enter a valid number.");
        }
    }
}

struct Book {
    inline static int id_assigner = 0;
    int id = 0;
    string name = "";
    int total_quantity = 0;   // copies currently available
    int total_borrowed = 0;   // copies currently borrowed
    Book() {}
    Book(string name, int amount) : name(name), total_quantity(amount) {
        id = id_assigner++;
    }
    static void print_header() {
        cout << ui::border({4, 30, 9, 8}) << "\n";
        cout << format("| {:<4} | {:<30} | {:>9} | {:>8} |\n", "ID", "Name", "Available", "Borrowed");
        cout << ui::border({4, 30, 9, 8}) << "\n";
    }
    static void print_footer() {
        cout << ui::border({4, 30, 9, 8}) << "\n";
    }
    void print_book() const {
        cout << format("| {:<4} | {:<30.30} | {:>9} | {:>8} |\n", id, name, total_quantity, total_borrowed);
    }
};

struct User {
    inline static int id_assigner = 0;
    int id = 0;
    inline static constexpr int MAX_BORROWED = 10;   // fixes the linker error
    string name;
    int borrowed_count = 0;
    int borrowed_books_ids[MAX_BORROWED];
    User() {}
    User(string name) : name(name) {
        id = id_assigner++;
    }
    int book_index(int book_id) const {
        for (int i = 0; i < borrowed_count; i++)
            if (borrowed_books_ids[i] == book_id)
                return i;
        return -1;
    }
    void left_shift(const int index) {
        for (int i = index; i < borrowed_count - 1; i++)
            borrowed_books_ids[i] = borrowed_books_ids[i + 1];
    }
    static void print_header() {
        cout << ui::border({4, 25, 8}) << "\n";
        cout << format("| {:<4} | {:<25} | {:>8} |\n", "ID", "Name", "Borrowed");
        cout << ui::border({4, 25, 8}) << "\n";
    }
    static void print_footer() {
        cout << ui::border({4, 25, 8}) << "\n";
    }
    void print_user() const {
        cout << format("| {:<4} | {:<25.25} | {:>5}/{:<2} |\n", id, name, borrowed_count, MAX_BORROWED);
    }
};

class Library {
    inline static constexpr int MAX_BOOKS = 10000;
    inline static constexpr int MAX_USERS = 10000;
    Book books[MAX_BOOKS] = {};
    User users[MAX_USERS] = {};
    int total_books = 0;
    int total_users = 0;

public:
    Library() {}

    Book* get_books_copy() {
        Book* temp_books = new Book[total_books];
        for (int i = 0; i < total_books; i++)
            temp_books[i] = books[i];
        return temp_books;
    }
    User* get_users_copy() {
        User* temp_users = new User[total_users];
        for (int i = 0; i < total_users; i++)
            temp_users[i] = users[i];
        return temp_users;
    }

    void print_library_menu() {
        static const char* items[] = {
            "add_book",
            "add_user",
            "user_borrow_book",
            "user_return_book",
            "search_books_by_prefix",
            "print_who_borrowed_book_by_name",
            "print_all_books",
            "print_available_books",
            "print_library_by_id",
            "print_library_by_name",
            "print_users",
            "print_user_borrowed_books",
            "Exit"
        };
        cout << "\n" << ui::border({3, 43}) << "\n";
        cout << format("| {:^49} |\n", "Library Menu");
        cout << ui::border({3, 43}) << "\n";
        cout << format("| {:>3} | {:<43} |\n", "No.", "Action Description");
        cout << ui::border({3, 43}) << "\n";
        int n = 1;
        for (const char* item : items)
            cout << format("| {:>3} | {:<43} |\n", n++, item);
        cout << ui::border({3, 43}) << "\n";
    }

    // ---------- adding ----------
    void add_book() {
        if (total_books == MAX_BOOKS)
            throw invalid_argument("Library is full, no room for more books!");
        string name = ui::read_line("Book name: ");
        if (name.empty())
            throw invalid_argument("Book name can't be empty.");
        if (search_on_book(name) != -1)
            throw invalid_argument(format("'{}' already exists in the library.", name));
        int amount = ui::read_int("Quantity: ");
        if (amount <= 0)
            throw invalid_argument("Quantity must be at least 1.");
        Book b(name, amount);
        books[b.id] = b;
        total_books++;
        ui::ok(format("Added '{}' (id {}, {} copies).", name, b.id, amount));
    }

    void add_user() {
        if (total_users == MAX_USERS)
            throw invalid_argument("Library is full, no room for more users!");
        string name = ui::read_line("User name: ");
        if (name.empty())
            throw invalid_argument("User name can't be empty.");
        if (search_on_user(name) != -1)
            throw invalid_argument(format("A user named '{}' already exists.", name));
        User user(name);
        users[user.id] = user;
        total_users++;
        ui::ok(format("Added user '{}' (id {}).", name, user.id));
    }

    // ---------- searching ----------
    int search_on_user(const string& name) {
        for (int i = 0; i < total_users; i++)
            if (name == users[i].name)
                return users[i].id;
        return -1;
    }
    int search_on_book(const string& name) {
        for (int i = 0; i < total_books; i++)
            if (name == books[i].name)
                return books[i].id;
        return -1;
    }

    // ---------- borrow / return ----------
    void user_borrow_book() {
        string user_name = ui::read_line("User name: ");
        string book_name = ui::read_line("Book name: ");

        int user_id = search_on_user(user_name);
        int book_id = search_on_book(book_name);
        if (user_id == -1)
            throw invalid_argument(format("There is no user named '{}'!", user_name));
        if (book_id == -1)
            throw invalid_argument(format("'{}' doesn't exist in the library!", book_name));

        if (!books[book_id].total_quantity) {
            ui::error(format("No copies of '{}' are available right now.", book_name));
            return;
        }
        if (users[user_id].book_index(book_id) != -1) {
            ui::error(format("{} already has '{}'.", user_name, book_name));
            return;
        }
        if (users[user_id].borrowed_count == User::MAX_BORROWED) {
            ui::error(format("{} has reached the maximum of {} borrowed books.", user_name, User::MAX_BORROWED));
            return;
        }
        users[user_id].borrowed_books_ids[users[user_id].borrowed_count++] = book_id;
        books[book_id].total_quantity--;
        books[book_id].total_borrowed++;
        ui::ok(format("{} borrowed '{}'.", user_name, book_name));
    }

    void user_return_book() {
        string user_name = ui::read_line("User name: ");
        string book_name = ui::read_line("Book name: ");

        int user_id = search_on_user(user_name);
        int book_id = search_on_book(book_name);
        if (user_id == -1)
            throw invalid_argument(format("There is no user named '{}'!", user_name));
        if (book_id == -1)
            throw invalid_argument(format("'{}' doesn't exist in the library!", book_name));

        int index = users[user_id].book_index(book_id);
        if (index == -1) {
            ui::error(format("{} didn't borrow '{}'.", user_name, book_name));
            return;
        }
        users[user_id].left_shift(index);
        users[user_id].borrowed_count--;
        books[book_id].total_quantity++;
        books[book_id].total_borrowed--;
        ui::ok(format("{} returned '{}'.", user_name, book_name));
    }

    // ---------- queries ----------
    void searching_for_a_book_by_prefix() {
        string prefix = ui::read_line("Prefix: ");
        int found = 0;
        for (int i = 0; i < total_books; i++) {
            if (books[i].name.rfind(prefix, 0) == 0) {
                if (!found)
                    cout << format("Books starting with '{}':\n", prefix);
                cout << format("  {}. {} (id {})\n", ++found, books[i].name, books[i].id);
            }
        }
        if (!found)
            ui::info(format("No books start with '{}'.", prefix));
    }

    void print_who_borrowed_book_by_name() {
        string book_name = ui::read_line("Book name: ");
        int book_id = search_on_book(book_name);
        if (book_id == -1)
            throw invalid_argument(format("'{}' doesn't exist in the library!", book_name));

        int found = 0;
        for (int i = 0; i < total_users; i++) {
            if (users[i].book_index(book_id) != -1) {
                if (!found)
                    cout << format("Users who borrowed '{}':\n", book_name);
                cout << format("  {}. {} (id {})\n", ++found, users[i].name, users[i].id);
            }
        }
        if (!found)
            ui::info(format("Nobody has borrowed '{}'.", book_name));
    }

    void print_user_borrowed_books() {
        string user_name = ui::read_line("User name: ");
        int user_id = search_on_user(user_name);
        if (user_id == -1)
            throw invalid_argument(format("There is no user named '{}'!", user_name));

        const User& u = users[user_id];
        if (!u.borrowed_count) {
            ui::info(format("{} hasn't borrowed any books.", user_name));
            return;
        }
        cout << format("Books borrowed by {} ({}/{}):\n", u.name, u.borrowed_count, User::MAX_BORROWED);
        Book::print_header();
        for (int i = 0; i < u.borrowed_count; i++)
            books[u.borrowed_books_ids[i]].print_book();
        Book::print_footer();
    }

    // ---------- printing books ----------
    static bool sort_by_names(const Book& b1, const Book& b2) { return b1.name < b2.name; }
    static bool sort_by_id(const Book& b1, const Book& b2) { return b1.id < b2.id; }

    void print_books_sorted(bool (*cmp)(const Book&, const Book&)) {
        if (!total_books) {
            ui::info("The library has no books yet.");
            return;
        }
        Book* temp = get_books_copy();
        sort(temp, temp + total_books, cmp);
        Book::print_header();
        for (int i = 0; i < total_books; i++)
            temp[i].print_book();
        Book::print_footer();
        cout << total_books << " book(s)\n";
        delete[] temp;
    }
    void print_all_books_by_name() { print_books_sorted(sort_by_names); }
    void print_all_books_by_id()   { print_books_sorted(sort_by_id); }

    // every book in the library plus a summary of the totals
    void print_all_books() {
        if (!total_books) {
            ui::info("The library has no books yet.");
            return;
        }
        int available = 0, borrowed = 0;
        Book::print_header();
        for (int i = 0; i < total_books; i++) {
            books[i].print_book();
            available += books[i].total_quantity;
            borrowed += books[i].total_borrowed;
        }
        Book::print_footer();
        cout << format("{} title(s) | {} cop(ies) available | {} cop(ies) borrowed | {} total\n",
                       total_books, available, borrowed, available + borrowed);
    }

    // only books that still have at least one free copy
    void print_available_books() {
        int count = 0;
        for (int i = 0; i < total_books; i++) {
            if (books[i].total_quantity > 0) {
                if (!count)
                    Book::print_header();
                books[i].print_book();
                count++;
            }
        }
        if (!count) {
            ui::info("No books are available right now.");
            return;
        }
        Book::print_footer();
        cout << count << " book(s) available\n";
    }

    // ---------- printing users ----------
    static bool sort_users_by_names(const User& u1, const User& u2) { return u1.name < u2.name; }
    void print_all_users_by_name() {
        if (!total_users) {
            ui::info("There are no users yet.");
            return;
        }
        User* temp = get_users_copy();
        sort(temp, temp + total_users, sort_users_by_names);
        User::print_header();
        for (int i = 0; i < total_users; i++) {
            temp[i].print_user();
            for (int j = 0; j < temp[i].borrowed_count; j++) {
                const Book& b = books[temp[i].borrowed_books_ids[j]];
                cout << format("|      -> {} (id {})\n", b.name, b.id);
            }
        }
        User::print_footer();
        cout << total_users << " user(s)\n";
        delete[] temp;
    }
};

int main() {
    // Library is ~1.4 MB, so keep it on the heap instead of the stack
    auto lib = make_unique<Library>();
    int choice = 0;
    const int EXIT = 13;
    while (choice != EXIT) {
        lib->print_library_menu();
        try {
            choice = ui::read_int("Choose an option (1-13): ");
            switch (choice) {
                case 1:  lib->add_book(); break;
                case 2:  lib->add_user(); break;
                case 3:  lib->user_borrow_book(); break;
                case 4:  lib->user_return_book(); break;
                case 5:  lib->searching_for_a_book_by_prefix(); break;
                case 6:  lib->print_who_borrowed_book_by_name(); break;
                case 7:  lib->print_all_books(); break;
                case 8:  lib->print_available_books(); break;
                case 9:  lib->print_all_books_by_id(); break;
                case 10: lib->print_all_books_by_name(); break;
                case 11: lib->print_all_users_by_name(); break;
                case 12: lib->print_user_borrowed_books(); break;
                case 13: cout << "Goodbye!\n"; break;
                default: ui::error("Invalid option, choose 1-13.");
            }
        } catch (const exception& e) {
            ui::error(e.what());
            if (!cin) break;   // stdin closed, stop instead of looping forever
        }
    }
    return 0;
}