#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "book.hpp"
#include "user.hpp"

class Library {
public:
    void addBook(const std::shared_ptr<Book>& book) { books.push_back(book); }

    void removeBook(const std::shared_ptr<Book>& book) {
        std::vector<std::shared_ptr<Book>> newBooks;
        for(const std::shared_ptr<Book>& i : books) {
            if(i != book) {
                newBooks.push_back(i);
            }
        }
        books = newBooks;
    }

    std::shared_ptr<Book> bookAt(int index) {
        return books.at(index);
    }

    void printBooks() {
        for(const std::shared_ptr<Book>& book : books) {
            printBookInfo(book);
        }
    }

    std::shared_ptr<Book> findBook(const QString& title, const QString& author) {
        for(const std::shared_ptr<Book>& book : books) {
            if((title.isEmpty() || book->getTitle() == title) && (author.isEmpty() || book->getAuthor() == author)) {
                return book;
            }
        }
        return nullptr;
    }

    void findBookAndPrint(const QString& title, const QString& author) {
        std::shared_ptr<Book> book = findBook(title, author);
        if(book != nullptr) {
            printBookInfo(book);
        } else {
            qDebug() << "Book not found";
        }
    }

    void addUser(const std::shared_ptr<User>& user) { users.push_back(user); }

    void removeUser(const std::shared_ptr<User>& user) {
        std::vector<std::shared_ptr<User>> newUsers;
        for(const std::shared_ptr<User>& i : users) {
            if(i != user) {
                newUsers.push_back(i);
            }
        }
        users = newUsers;
    }

    void printUsers() {
        for(const std::shared_ptr<User>& i : users) {
            printUserInfo(i);
        }
    }

private:
    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<User>> users;
};

inline void demoLibraryBooks() {
    Library lib;
    lib.addBook(makeBook("title1", "author1", 2010));
    lib.addBook(makeBook("title2", "author2", 2020));
    lib.printBooks();
}

inline void demoLibraryUsers() {
    Library lib;
    lib.addBook(makeBook("title1", "author1", 2010));
    lib.addBook(makeBook("title2", "author2", 2020));

    std::shared_ptr<User> user = makeUser("user1", 0);
    user->addBook(lib.findBook("title1", ""));
    user->addBook(lib.findBook("", "author2"));
    lib.addUser(user);
    lib.printUsers();
}

#endif // LIBRARY_HPP
