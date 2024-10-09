#include <iostream>
#include <cstdlib> 
#include <vector>
#include <algorithm>

class Solution{
private:
    int num_mistakes; 
    bool show_mistakes;
    // Member variable to store the number of mistakes, 
    // referred as this->num_mistakes in constructor
public:
    Solution(int num_mistakes = 1, bool show_mistakes = true){
        this->num_mistakes = num_mistakes;
        this->show_mistakes = show_mistakes;
        srand(time(0));
    }
    
    // or,
    // Solution(int num_mistakes = 1) : num_mistakes(num_mistakes), show_mistakes(show_mistakes){
    //     srand(time(0));
    // }
    
    
    void generateSentences(std::string sentence, int num_times){
        std::string original_sentence = sentence;
        
        // initialize sentence with ' ';
        std::vector<std::vector<char>> sentence_table(num_times, std::vector<char>(sentence.length()));
        for(int i = 0; i < num_times; i++){
            // copies each character from the sentence string (from sentence.begin() to sentence.end()) 
            // into the i-th row of sentence_table (starting at sentence_table[i].begin()).
            std::copy(sentence.begin(), sentence.end(), sentence_table[i].begin());
        }
    
        // Distribute mistakes randomly
        int mistakes_placed = 0;
        while (mistakes_placed < num_mistakes) {
            int random_sentence_index = rand() % num_times;
            int random_character_index = rand() % sentence.length();
            char random_charactor = 'A' + rand() % 26;
    
            if (sentence_table[random_sentence_index][random_character_index] != random_charactor) {
                sentence_table[random_sentence_index][random_character_index] = random_charactor;
                mistakes_placed++;
            }
        }
        
        for(int i = 0; i < num_times; i++){
            if(show_mistakes){
                bool has_mistake;
                int count_mistakes = 0;
                for(int j = 0; j < sentence.length(); j++) {
                    if (sentence_table[i][j] != original_sentence[j]) {
                        has_mistake = true;
                        count_mistakes++;
                        //break;
                    }
                }
                if (has_mistake) {
                    std::cout << "-> " <<count_mistakes << " mistakes: ";
                    has_mistake = false;
                }
            }
            
            for(int j = 0; j < sentence_table[i].size(); j++){
                std::cout << sentence_table[i][j];
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    // number of mistakes, show_mistakes?
    Solution punishment(8);
    std::string sentence = "I will always use object-oriented design.";
    int iterations = 50;
    punishment.generateSentences(sentence, iterations);

    return 0;
}