#ifndef FIND_BOOK_DIALOG_HPP
#define FIND_BOOK_DIALOG_HPP

#include <QDialog>
#include <QLineEdit>

class FindBookDialog : public QDialog {
    Q_OBJECT

public:
    FindBookDialog(QWidget *parent = nullptr);
    [[nodiscard]] QString getTitle() const { return title->text(); }
    [[nodiscard]] QString getAuthor() const { return author->text(); }

    void showEvent(QShowEvent* event) override {
        title->setText("");
        author->setText("");
        QDialog::showEvent(event);
    }

private:
    QLineEdit* title;
    QLineEdit* author;
};

#endif // FIND_BOOK_DIALOG_HPP
