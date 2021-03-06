#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
#include <QKeyEvent>
#include <QVariantMap>

class Core;
class Game;

enum class InventoryType {
    POPUP, BUILTIN
};

enum class ColorTheme {
    LIGHT, DARK
};

enum class LoggerLevel {
    RELEASE,
    DEBUG
};

enum class Controls {
    HIDE_UI_ELEMENTS,
    TOGGLE_FULLSCREEN_MODE,
    GO_TO_PREVIOUS_MENU,
    EXIT_FROM_THE_GAME,
    CONTROLS_N
};

class Config {
public: /* Constants */
    static const QString imagesDirectory;
    static const QColor LIGHT_THEME_WINDOW_COLOR;
    static const QColor LIGHT_THEME_TEXT_COLOR;
    static const QColor DARK_THEME_WINDOW_COLOR;
    static const QColor DARK_THEME_TEXT_COLOR;
    static const int MIN_AUTO_SAVE_PERIOD = 1;
    static const int MAX_AUTO_SAVE_PERIOD = 120;
    static const int STATISTICS_UPDATE_PERIOD = 1000;
    static const int MARKET_UPDATE_PERIOD = 10000;
    static const int MAX_INPUT_HISTORY_SIZE = 128;
    static const int SELLERS_COUNT = 3;
    static const int SLOTS_COUNT = 9;
    static const int STORE_MAX_ITEMS_COUNT = 16;
    static const int LOTTERY_BUTTONS_COUNT = 50;
    static const int LOTTERY_NEED_BUTTONS_COUNT = 7;
    static const int LOTTERY_BASIC_TICKET_COEFFICIENT = 100;
    static const int LOTTERY_RARE_TICKET_COEFFICIENT = 1000;
    static const int NETS_TIMER_INTERVAL = 5 * 60 * 1000;
    static const int STACKTRACE_SIZE = 1024;
private:
    bool isReady = false;
    Core *core;
    QKeySequence defaultControls[(size_t)Controls::CONTROLS_N],
                 controls[(size_t)Controls::CONTROLS_N];
public:
    Config() = delete;
    Config(Core *core);
    ~Config() = default;
    void deserialize(const QVariantMap &map);
    QJsonObject serialize() const;
    void setKey(Controls control, int key);
    QKeySequence getKey(Controls control) const;
    void setDefaultKey(Controls control, int key);
    QKeySequence getDefaultKey(Controls control) const;
    friend class ControlsMenu;
};

#endif  // INCLUDE_CONFIG_H_
