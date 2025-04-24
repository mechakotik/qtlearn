#ifndef USER_HPP
#define USER_HPP

#include <QString>
#include <vector>
#include "book.hpp"

class User {
public:
    User(const QString& name, int id) : name(name), id(id) {}

    [[nodiscard]] QString getName() const { return name; }
    [[nodiscard]] int getId() const { return id; }
    [[nodiscard]] std::vector<std::shared_ptr<Book>> getBooks() const { return books; }
    [[nodiscard]] std::shared_ptr<Book> getBookAt(int index) const { return books[index]; }

    void addBook(const std::shared_ptr<Book>& book) {
        if(!hasBook(book)) {
            books.push_back(book);
        }
    }

    bool hasBook(const std::shared_ptr<Book>& book) {
        return std::find(books.begin(), books.end(), book) != books.end();
    }

    void removeBook(const std::shared_ptr<Book>& book) {
        books.erase(std::remove(books.begin(), books.end(), book), books.end());
    }

private:
    QString name;
    int id;
    std::vector<std::shared_ptr<Book>> books;
};

inline std::shared_ptr<User> makeUser(const QString& name, int id) {
    return std::make_shared<User>(name, id);
}

inline void printUserInfo(const std::shared_ptr<User>& user) {
    qDebug() << "Name: " << user->getName();
    qDebug() << "ID: " << user->getId();
    qDebug() << "Books:";
    for(const std::shared_ptr<Book>& book : user->getBooks()) {
        printBookInfo(book);
    }
}

#endif // USER_HPP
