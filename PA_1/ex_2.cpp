#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

class Solution{
public:
    Solution(){
        srand(time(0));
    }
    
    int generateBirthday() {
        return rand() % 365;
    }
    
    bool hasDuplicateBirthday(const std::vector<int>& birthdays) {
        for (int i = 0; i < birthdays.size(); i++) {
            for (int j = i + 1; j < birthdays.size(); j++) {
                if (birthdays[i] == birthdays[j])
                    return true;
            }
        }
        return false;
    }
    
    void birthdayParadox(int max_people, int trials){
        // Number of trials to run for each N

        std::cout << std::left << std::setw(5) << "N" << std::setw(15) << "Count out of 100" << std::endl;
        for(int n = 5; n <= max_people; n += 5) {
            int matchCount = 0; 
            
            for(int t = 0; t < trials; t++) {
                std::vector<int> birthdays;
                for(int j = 0; j < n; j++) {
                    // generate n birthdays for n people
                    int birthday = generateBirthday();
                    birthdays.push_back(birthday);
                }
                if (hasDuplicateBirthday(birthdays))
                    matchCount++;
            }
            //double probability = (double)matchCount / trials * 100;
            std::cout << std::left << std::setw(10) << n << std::setw(10) << matchCount << std::endl;
        }
    }
};


int main() {
    Solution birthday;
    birthday.birthdayParadox(100, 100);

    return 0;
}
