#include "view.h"
#include "ui_view.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <QDebug>


view::view(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::view)
{
    ui->setupUi(this);
    auto vlMain = new QHBoxLayout(ui->centralWidget);
    auto glMain = new QGridLayout();
    auto glLetters = new QGridLayout();

    //
    for (char c='a'; c<='z';++c)
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(20,20);
        btn->setMaximumSize(20,20);
        btn->setText(QString(c));

        int idx = c-'a';
        glLetters->addWidget(btn, idx / 6, idx%6);


        connect(btn, &QPushButton::clicked,this, &view::onLetterClicked);
    }
    ui->centralWidget->setMinimumSize(800,700);
    auto lblGallows = new QLabel();
    auto lblWord = new QLabel();
    lblGallows->setMinimumSize(300,500);
    lblGallows->setMaximumSize(300,500);
    lblGallows->setStyleSheet("background-color: rgb(170, 255, 0);");

    lblWord->setText("test String");
    auto btnPlay = new QPushButton();
    btnPlay->setMinimumSize(100,35);
    btnPlay->setText(" NEW WORD");

    glMain->addWidget(lblGallows, 0, 0);
    glMain->addLayout(glLetters, 0, 1);
    glMain->addWidget(lblWord, 1, 0);
    glMain->addWidget(btnPlay, 1, 1);



    vlMain->addLayout(glMain);
    vlMain->addLayout(glLetters);
}

view::~view()
{
    delete ui;
}

void view::onLetterClicked()
{
    //sender must be a QPushButon
    //downcasting is safe
    QPushButton* btn = dynamic_cast<QPushButton*>(sender()); //lets us use the btn that was pressed

    //updates the model
    //hangman.guess(btn->text()) <- QString



    //draw():
    btn->setEnabled(false);
    qWarning() << btn->text();
}
