#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QStringList>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

void game_init(){
    QString guessedWord = string;
    guessedWord.fill('_', string.length());
    displayLabel->setText(guessedWord);

}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);
    QLabel *displayLabel = new QLabel;

    QString string = "programming";
    QString guessedWord = string;
    guessedWord.fill('_', string.length());
    displayLabel->setText(guessedWord);

    displayLabel->setText(string);
    layout->addWidget(displayLabel);

    window.setLayout(layout);
    window.show();

    MainWindow w;
    w.show();
    return a.exec();
}
