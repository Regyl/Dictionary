/*
1.Добавить возможность исправления слова
3.Удаление конкретных слов
4.Примеры использования слов в том или ином контексте
5.По приколу можно сделать экзамен. Набираешь N-е кол-во очков - получаешь ссылку на гифку с котиком

666.Вместо передачи слова в функции записи нового сделать ссылкой, дабы не копировать его лишний раз
*/
#include <fstream>//for possibility work with files
#include <iostream> //for input/output
#include <ctime> //for random numerics
#include <Windows.h>//for correct output in Russian
#include <string> //if u don't understand why this library is here, than close this and go away
void Information()
{
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "0 - End" << std::endl;
    std::cout << "1 - record new word" << std::endl;
    std::cout << "2 - get random word" << std::endl;
    std::cout << "3 - verificate Rus into Eng translation" << std::endl;
    std::cout << "4 - verificate Eng into Rus translation" << std::endl;
    std::cout << "5 - phrases in English" << std::endl;
    std::cout << "6 - remove particular word(don't work yet)" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
}
void RemoveWordInNative()
{   
    
}
void RemoveWordInForeign()
{
    
}
void InputTranslatedWords() //input new translated word
{
    std::cout << "Enter the translate of word:" << std::endl;
    std::ofstream TranslatedWords("translated.txt", std::ios_base::app);
    std::string TranslatedLine;
    std::getline(std::cin, TranslatedLine);
    TranslatedWords << "\n";
    TranslatedWords << TranslatedLine;
    TranslatedWords.close();
    Information();
}

void InputEnglishWords() //input new eng word
{
    std::string line;
    std::getline(std::cin, line);
    if (line == "") //crutch. Just because I break down something (idk what exactly) and input new english word don't work without that 2 lines
        std::getline(std::cin, line);
    std::ifstream VerifyLackWord("english.txt"); //to ensure in lack new word
    while (!VerifyLackWord.eof()) {
        std::string WordInFile;
        std::getline(VerifyLackWord, WordInFile);
        if (WordInFile == line) {
            std::cout << "This word already in dictionary.\nRecording wasn't complete." << std::endl;
            return; //end of input new word
        }
    }
    VerifyLackWord.close();
    std::ofstream EngWords("english.txt", std::ios_base::app); // ios_base - function of extra recording in the file
    EngWords << "\n";
    EngWords << line;//cannot bring with the lattest line. Just in cause.
    EngWords.close(); //Information() here is useless
    InputTranslatedWords();
}

void RandomOutput() //output random couple words
{
    unsigned int index = 0;
    std::ifstream EngWordsOutput("english.txt"); 
    while (!EngWordsOutput.eof()) { //to calculate quantity of lines in the file
        index += 1;
        std::string buffer;
        std::getline(EngWordsOutput, buffer);
    }
    unsigned int digit = time(NULL)*rand() % (index)+1; //the formula was stole from the internet
    EngWordsOutput.close();
    std::ifstream EngWordsOutputSecond("english.txt");//повторное включение файла т.к. иначе он(файл) уже прочтен до конца в предыдущем цикле
    for (int i = 0; i < digit; i++) {
        std::string buffer;
        std::getline(EngWordsOutputSecond, buffer);
        if (i == digit - 1) {
            std::cout << buffer << " - ";
        }
    }
    EngWordsOutputSecond.close();
    std::ifstream TranslatedWords("translated.txt");
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(TranslatedWords, buffer);
        if (i == digit - 1)
            std::cout << buffer << std::endl;
    }
    TranslatedWords.close();
    std::cout << std::endl;
    Information();
}

void EngVerify()//output in your native language, input in Engish
{
    std::ifstream Translated("translated.txt");
    int index = 0;
    std::string Translate;
    for (; !Translated.eof(); ) { //to calculate quantity of lines in the file
        std::string buffer;
        std::getline(Translated, buffer);
        index += 1;
    }
    Translated.close();
    std::ifstream TranslatedSecond("translated.txt");//повторное открытие
    unsigned int digit = time(NULL) * rand() % (index)+1;
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(TranslatedSecond, buffer);
        if (i == digit - 1)
        {
            Translate = buffer;
        }
    }
    TranslatedSecond.close();//edge of output translated word
    std::cout << Translate << std::endl << "Enter the translation:" << std::endl;
    std::ifstream EngWord("english.txt");
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(EngWord, buffer);
        if (i == digit - 1)
        {
            bool temp = false;
            while (!temp)
            {
                std::string InputWord; //перевод слова, вводимый с клавиатуры
                std::getline(std::cin, InputWord);
                if (InputWord == buffer || InputWord == "help") {
                    if (InputWord == buffer)
                        temp = true;
                    else
                        std::cout << buffer << " is right answer." << std::endl;
                }
                else {
                    std::cout << "Неверно. Попробуйте еще раз" << std::endl;
                    std::cout << "If you need a clue write *help*" << std::endl;
                }
            }
            std::cout << "Definitely!" << std::endl;
            break;
        }
    }
    Information();
}

void NativeVerify() //output English word, input in your native language
{
    std::ifstream Translated("english.txt");
    int index = 0;
    std::string Translate;
    for (; !Translated.eof(); ) {
        std::string buffer;
        std::getline(Translated, buffer);
        index += 1;
    }
    Translated.close();
    std::ifstream TranslatedSecond("english.txt");//повторное открытие
    unsigned int digit = time(NULL) * rand() % (index)+1;
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(TranslatedSecond, buffer);
        if (i == digit - 1)
            Translate = buffer;
    }
    TranslatedSecond.close();//edge of output translated word
    std::cout << Translate << std::endl << "Enter the translation:" << std::endl;
    std::ifstream EngWord("translated.txt");
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(EngWord, buffer);
        if (i == digit - 1)
        {
            bool temp = false;
            while (!temp)
            {
                std::string InputWord; //перевод слова, вводимый с клавиатуры
                std::getline(std::cin, InputWord);
                if (InputWord == buffer || InputWord == "help") {
                    if (InputWord == buffer)
                        temp = true;
                    else
                        std::cout << buffer << " was the right answer." << std::endl;
                }
                else {                                                                                  //REVIEW
                    std::cout << "Неверно. Попробуйте еще раз" << std::endl;
                    std::cout << "If you need a clue write *help*" << std::endl;
                }
            }
            std::cout << "Excellent!" << std::endl;
            break;
        }
    }
    Information();
}
std::string RandomPhrases() //output random phrase in eng and translate
{
    unsigned int index = 0;
    std::ifstream Phrase("phrases.txt");
    while (!Phrase.eof()) { //to calculate quantity of lines in the file
        index += 1;
        std::string buffer;
        std::getline(Phrase, buffer);
    }   
    unsigned int digit = time(NULL) * rand() % (index)+1; //the formula was stolen from the internet
    Phrase.close();
    std::ifstream PhraseSecond("phrases.txt");
    for (int i = 0; i < digit; i++) {
        std::string buffer;
        std::getline(PhraseSecond, buffer);
        if (i == digit - 1) {
            return buffer;
        }
    }
    PhraseSecond.close();
    Information();
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);//correct input
    SetConsoleOutputCP(1251);//correct output
    int index;
    Information();
    std::cout << "Your decision:";
    while (std::cin >> index && index != 0)
    {
        std::cout << std::endl;
        switch (index)
        {
        case 1:
            std::cout << "Just write this FWord" << std::endl;
            InputEnglishWords();
            break;
        case 2:
            RandomOutput();
            break;
        case 3:
            EngVerify();
            break;
        case 4:
            NativeVerify();
            break;
        case 5:
            std::cout << RandomPhrases() << std::endl;
            Information();
            break;
        case 6:
            std::cout << "Wanna include search in your native language? (y/n)" << std::endl;
            char n; std::cin >> n;
            n=='y' ? RemoveWordInNative() : RemoveWordInForeign();
            break;
        default:
            Information();
        }
        std::cout << "Your decision:";
    }
    std::cout << "|----------------------------------------|" << std::endl;
    std::cout << "|----          See you soon!         ----|" << std::endl;
    std::cout << "|----------------------------------------|" << std::endl;
    return 0;
}