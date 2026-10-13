    #include<iostream>
    #include<string>
    #include<vector>
    #include<cstring>

    class Resource {
    public:
        Resource(std::string name) : name_(name), amount_(0){}
        void add(int value){
        amount_ += value;  }

        int getAmount() const{
            return amount_;
        }
        bool spend(int value) {
            if (amount_ >= value) {
                amount_ -= value;
                return true;
            }
            else {
                return false;
            }
        }

    private:
        std::string name_;
        int amount_;

    };
    class Upgrade {
    public:
        Upgrade (std::string name, int cost, int bonus)
            : name_(name), cost_(cost), powerBonus_(bonus){ }
        const std::string& getName() const{
            return name_;
        }
        int getCost() const {
            return cost_;
        }
        int getBonus() const {
            return powerBonus_;
        }

     private:
        std::string name_;
        int cost_;
        int powerBonus_;

    };
    class Game{
    public:
        Game() : resource_("Coin"), clickPower_(1) {
            upgrades_.push_back(Upgrade("Колебаться, значит проиграть ", 13, 3));
            upgrades_.push_back(Upgrade("По ком звонит колокол ", 50, 20));
        }
        void click(){
            resource_.add(clickPower_);
        }
        int getScore()const {
            return resource_.getAmount();
        }
        void tryBuyUpgrade(int index) {
            if (index < 0 || index >= upgrades_.size()) {
                std::cout << "Ну уж нет дружочек, хочешь мне магазин сломать? \n";
            }
            else{
            const Upgrade& up = upgrades_[index];
            if (resource_.spend(up.getCost())) {
                clickPower_ += up.getBonus();
                std::cout << "Было приобретено " << up.getName() << " \n";
            }
            else { std::cout << "Не хватает гроши \n"; }
            }
        }
        void showUpgrades() const {
            std::cout << "В магазине доступно \n";
            for (int i = 0; i < upgrades_.size(); i++) {
                std::cout << i+1 << " - " << upgrades_[i].getName() << " " << upgrades_[i].getCost() << " " << upgrades_[i].getBonus() << "\n";
            }
        }
    private:
        Resource resource_;
        int clickPower_;
        std::vector<Upgrade> upgrades_;
    };

    int main()
    {
        setlocale(LC_ALL, "ru");
        Game game;

        std::string input;
        while (true) {
            std::cin >> input;
            if (input[0] == '1') {
                game.click();  
                std::cout << "Click, ты накопил -> " << game.getScore() << "\n";
            }
            else if (input[0] == '0') {
                break;
            }
            else if (input[0] == '2') {
                int choose;
                game.showUpgrades();
                std::cout << "Выбери, что хочешь купить? \n";
                std::cin >> choose;
                game.tryBuyUpgrade(choose - 1);
            }
        }
    }
