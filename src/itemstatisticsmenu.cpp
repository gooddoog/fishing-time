#include "game.h"
#include "itemstatisticsmenu.h"

ItemStatisticsMenu::ItemStatisticsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&statisticsLabel, 0, 1);
    statisticsLabel.setVisible(false);
    statisticsLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&statisticsText, 1, 0, 1, 3);
    statisticsText.setReadOnly(true);
    statisticsText.setVisible(false);
    statisticsText.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    statisticsText.setTextInteractionFlags(Qt::NoTextInteraction);
    statisticsText.setFrameStyle(QFrame::NoFrame);

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ItemStatisticsMenu::updateStatistics() {
    QString statText;
    statText += "<table border=\"1\" width=\"100%\" table-layout=\"fixed\">";
    statText += QString(
        "<tr>"
            "<td align=\"center\">%1</td>"
            "<td align=\"center\">%2</td>"
            "<td align=\"center\">%3</td>"
            "<td align=\"center\">%4</td>"
            "<td align=\"center\">%5</td>"
            "<td align=\"center\">%6</td>"
        "</tr>"
    ).arg(
        game->str.item,
        game->str.stats["stats.got"],
        game->str.stats["stats.used"],
        game->str.stats["stats.sold"],
        game->str.stats["stats.bought"],
        game->str.stats["stats.caught"]
    );
    auto it2 = game->str.itemNames.cbegin();
    Q_ASSERT(game->str.itemNames.size() > 1);
    const auto &itemStats = game->users[game->activeUser].inventory.getItemStats();
    while (it2 != game->str.itemNames.cend()) {
        if (it2.key() != "item.undefined") {
            auto item = itemStats.find(it2.key());
            if (item == itemStats.end()) {
                ++it2;
                continue;
            }
            int gotValue = 0;
            if (item.value().find("stats.got") != item.value().end()) {
                gotValue = item.value()["stats.got"];
            }
            int usedValue = 0;
            if (item.value().find("stats.used") != item.value().end()) {
                usedValue = item.value()["stats.used"];
            }
            int soldValue = 0;
            if (item.value().find("stats.sold") != item.value().end()) {
                soldValue = item.value()["stats.sold"];
            }
            int boughtValue = 0;
            if (item.value().find("stats.bought") != item.value().end()) {
                boughtValue = item.value()["stats.bought"];
            }
            int caughtValue = 0;
            if (item.value().find("stats.caught") != item.value().end()) {
                caughtValue = item.value()["stats.caught"];
            }
            statText += QString(
                "<tr>"
                    "<td align=\"center\">%1</td>"
                    "<td align=\"center\">%2</td>"
                    "<td align=\"center\">%3</td>"
                    "<td align=\"center\">%4</td>"
                    "<td align=\"center\">%5</td>"
                    "<td align=\"center\">%6</td>"
                "</tr>"
            ).arg(
                *it2.value(),
                QString::number(gotValue),
                QString::number(usedValue),
                QString::number(soldValue),
                QString::number(boughtValue),
                QString::number(caughtValue)
            );
        }
        ++it2;
    }
    statText += "</table>";
    statisticsText.setText(statText);
}

void ItemStatisticsMenu::display() {
    this->pre_display();

    updateStatistics();
    statisticsLabel.setVisible(true);
    statisticsLabel.setText(game->str.itemStatistics);

    statisticsText.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void ItemStatisticsMenu::backFunction() {
    this->hide();
    game->statisticsMenu.display();
}

void ItemStatisticsMenu::hide() {
    this->pre_hide();

    statisticsLabel.setVisible(false);

    statisticsText.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

ItemStatisticsMenu::~ItemStatisticsMenu() {

}
