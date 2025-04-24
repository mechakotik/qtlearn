#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <vector>
#include "book.hpp"
#include "user.hpp"

class Library {
public:
    void addBook(const std::shared_ptr<Book>& book) { books.push_back(book); }
    void removeBook(const std::shared_ptr<Book>& book) {
        books.erase(std::remove(books.begin(), books.end(), book), books.end());
    }
    std::shared_ptr<Book> getBook(int index) { return books[index]; }
    std::vector<std::shared_ptr<Book>> getBooks() const { return books; }

    void addUser(const std::shared_ptr<User>& user) { users.push_back(user); }

    void removeUser(const std::shared_ptr<User>& user) {
        users.erase(std::remove(users.begin(), users.end(), user), users.end());
    }

    int findBook(const QString& title, const QString& author) {
        for(int i = 0; i < static_cast<int>(books.size()); i++) {
            if((title.isEmpty() || books[i]->getTitle() == title) && (author.isEmpty() || books[i]->getAuthor() == author)) {
                return i;
            }
        }
        return -1;
    }

    void printBooks() {
        for(const std::shared_ptr<Book>& book : books) {
            printBookInfo(book);
        }
    }

    void printUsers() {
        for(const std::shared_ptr<User>& i : users) {
            printUserInfo(i);
        }
    }
    std::shared_ptr<User> getUser(int index) { return users[index]; }
    std::vector<std::shared_ptr<User>> getUsers() const { return users; }

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
    user->addBook(lib.getBook(lib.findBook("title1", "")));
    user->addBook(lib.getBook(lib.findBook("", "author2")));
    lib.addUser(user);
    lib.printUsers();
}

inline void demoMakeShared() {
    Library lib;

    std::shared_ptr<User> user1 = std::make_shared<User>("user1", 0);
    std::shared_ptr<User> user2 = std::allocate_shared<User>(std::allocator<User>(), "user2", 0);

    lib.addUser(user1);
    lib.addUser(user2);
}

#endif // LIBRARY_HPP
