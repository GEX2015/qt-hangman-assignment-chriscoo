#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

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
    Ui::view *ui;
};

#endif // VIEW_H
