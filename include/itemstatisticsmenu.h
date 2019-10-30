#ifndef INCLUDE_ITEMSTATISTICSMENU_H_
#define INCLUDE_ITEMSTATISTICSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QTextEdit>
#include <QTimer>
#include "menu.h"

class ItemStatisticsMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QTextEdit statisticsText;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void updateStatistics();
    void backFunction();
public:
    ItemStatisticsMenu(Game *game, QGridLayout *grid);
    ~ItemStatisticsMenu();
    void display() override;
    void hide() override;
    bool isDisplayed() const;
};

#endif  // INCLUDE_ITEMSTATISTICSMENU_H_
