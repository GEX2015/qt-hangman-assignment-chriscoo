////////////////////////////////////////////////////////////
///     Chris Arsenault
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <memory>
#include <QString>
#include <map>

class hangmanClass;
enum class Picture;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onLetterClicked();
    void onNewGameClicked();

private:
    void draw(); //updates the ui
    void delay(); //delay to show the popup box for the win/loss message

private:
    Ui::MainWindow *ui;
    const std::map<Picture,QString> _imageFor;

    std::unique_ptr<hangmanClass> _game;

    std::vector<QPushButton*> letters;
    QLabel* lblGallows;
    QLabel* lblPicture;
    QLabel* lblWord;
};

#endif // MAINWINDOW_H
