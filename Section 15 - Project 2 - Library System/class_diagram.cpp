classDiagram
    class Library {
        -Book books[MAX_BOOKS]
        -User users[MAX_USERS]
        -int total_books
        -int total_users
        +run()
        +add_book()
        +add_user()
        +user_borrow_book()
        +user_return_book()
        +search_books_by_prefix()
        +print_library_by_id()
        +print_library_by_name()
        +print_users()
    }

    class User {
        +int id
        +string name
        +int borrowed_books_ids[MAX_BORROWED]
        +int borrowed_count
    }

    class Book {
        +int id
        +string name
        +int total_quantity
        +int total_borrowed
    }

    Library "1" *-- "many" Book : Owns Master Array
    Library "1" *-- "many" User : Owns Master Array
    User "many" --> "1" Book : References via Foreign Key (ID)