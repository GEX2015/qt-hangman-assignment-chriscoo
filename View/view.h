#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class view;
}

class view : public QMainWindow
{
    Q_OBJECT

public:
    explicit view(QWidget *parent = 0);
    ~view();
public slots:
    void onLetterClicked();
private:
    QLabel* lblWord;
    QPushButton* btnPlay;
    Ui::view *ui;
};

#endif // VIEW_H
