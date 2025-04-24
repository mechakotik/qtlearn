#ifndef ADD_BOOK_DIALOG_HPP
#define ADD_BOOK_DIALOG_HPP

#include <QDialog>
#include <QLineEdit>

class AddBookDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget* parent = nullptr);
    QString getTitle() const;
    QString getAuthor() const;
    int getYear() const;

private:
    QLineEdit* titleEdit;
    QLineEdit* authorEdit;
    QLineEdit* yearEdit;
};

#endif // ADD_BOOK_DIALOG_HPP
