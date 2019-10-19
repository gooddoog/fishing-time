#include "statisticsmenu.h"
#include "game.h"

StatisticsMenu::StatisticsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&statisticsText, 0, 0, 1, 3);
    statisticsText.setTextFormat(Qt::RichText);
    statisticsText.setVisible(false);
    statisticsText.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

bool StatisticsMenu::isDisplayed() const {
    return displayed;
}

void StatisticsMenu::updateStatistics() {
    qDebug() << "Statistics have been updated";
    QString statText;
    auto stats = game->users[game->activeUser].getStatistsics(game);
    auto it = stats.cbegin();
    while (it != stats.cend()) {
        statText += QString("<table border=\"1\" width=\"100%\">"
                        "<tr>"
                            "<td width=\"50%\">%1</td>"
                            "<td width=\"50%\">%2</td>"
                        "</tr>"
                    "</table>")
            .arg(
                it->first,
                it->second
            );
            ++it;
    }
    statisticsText.setText(statText);
}

void StatisticsMenu::display() {
    timerUpdater = connect(&timer, SIGNAL(timeout()), this, SLOT(updateStatistics()));
    timer.start(1000);
    updateStatistics();
    statisticsText.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void StatisticsMenu::backFunction() {
    timer.stop();
    disconnect(timerUpdater);

    this->hide();
    game->gameMenu.display();
}

void StatisticsMenu::hide() {
    statisticsText.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

StatisticsMenu::~StatisticsMenu() {

}
