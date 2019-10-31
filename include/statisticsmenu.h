#ifndef INCLUDE_STATISTICSMENU_H_
#define INCLUDE_STATISTICSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QTimer>
#include "menu.h"

class StatisticsMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QTextEdit statisticsText;
    QPushButton itemsButton,
                backButton;
    QGridLayout *grid;
    QTimer timer;
    QMetaObject::Connection timerUpdater;
private slots:
    void updateStatistics();
    void itemsFunction();
    void backFunction();
public:
    StatisticsMenu(Game *game, QGridLayout *grid);
    ~StatisticsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_STATISTICSMENU_H_
