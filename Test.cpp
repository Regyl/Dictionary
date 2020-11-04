/*
1.Добавить возможность исправления слова
2.Во время записи новых слов проверить, не записано ли уже это слово
3.Удаление конкретных слов
4.Примеры использования слов в том или ином контексте
5.По приколу можно сделать экзамен. Набираешь N-е кол-во очков - получаешь ссылку на гифку с котиком
6.Поиск перевода конретного слова

666.Возможно добавить отдельно фразы (но без проверки на правильность перевода - сразу с переводом выдавать)
*/
#include <fstream>//for possibility work with files
#include <iostream> //for input/output
#include <ctime> //for random numerics
#include <Windows.h>//for correct output in Russian
#include <string>
void Information()
{
    std::cout << "0 - Закончить" << std::endl;
    std::cout << "1 - записать новое слово " << std::endl;
    std::cout << "2 - получить случайное слово " << std::endl;
    std::cout << "3 - проверка перевода с русского на английский" << std::endl;
    std::cout << "4 - проверка перевода с английского на русский" << std::endl;
    std::cout << "5 - фразы на английском" << std::endl;
}
void InputEnglishWords(std::string line) //input new eng word
{
    std::ofstream EngWords("english.txt", std::ios_base::app); // ios_base - функция ДОзаписи в файл под названием cppstudio.txt
    EngWords << "\n";
    EngWords << line;//cannot bring with the lattest line. Just in cause.
    EngWords.close(); //здесь описание последующих действий НЕ нужно (т.е. Information here is useless)
}
void InputTranslatedWords () //input new translated word
{
    std::cout << "Введите перевод слова"<<std::endl;
    std::ofstream TranslatedWords("translated.txt", std::ios_base::app);
    std::string TranslatedLine;
    std::cin >> TranslatedLine;
    TranslatedWords << "\n";
    TranslatedWords << TranslatedLine;
    TranslatedWords.close();
    Information();
}

void RandomOutput() //output random couple words
{
    unsigned int index = 0;
    std::ifstream EngWordsOutput("english.txt"); 
    while (!EngWordsOutput.eof()) {
        index += 1;
        std::string buffer;
        std::getline(EngWordsOutput, buffer);
        //EngWordsOutput >> buffer;
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

void Zverify()//output translated, input eng
{
    std::ifstream Translated("translated.txt");
    int index = 0;
    std::string Translate;
    for (; !Translated.eof(); ) {
        std::string buffer;
        std::getline(Translated, buffer);
        //Translated >> buffer;
        index += 1;
    }
    Translated.close();
    std::ifstream TranslatedSecond("translated.txt");//повторное открытие
    unsigned int digit = time(NULL) * rand() % (index)+1;
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(TranslatedSecond, buffer);
        //TranslatedSecond >> buffer;
        if (i == digit - 1)
        {
            Translate = buffer;
        }
    }
    TranslatedSecond.close();//edge of output translated word
    std::cout << Translate << std::endl << "Введите перевод" << std::endl;
    std::ifstream EngWord("english.txt");
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(EngWord, buffer);
        //EngWord >> buffer;
        if (i == digit - 1)
        {
            bool temp = false;
            while (!temp)
            {
                std::string InputWord; //перевод слова, вводимый с клавиатуры
                std::cin >> InputWord;
                if (InputWord == buffer)
                    temp = true;
                else
                    std::cout << "Неверно. Попробуйте еще раз" << std::endl;
            }
            std::cout << "You're right" << std::endl;
            break;
        }
    }
    Information();
}

void ReverseVerify() //output eng, input translated
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
        {
            Translate = buffer;
        }
    }
    TranslatedSecond.close();//edge of output translated word
    std::cout << Translate << std::endl << "Введите перевод" << std::endl;
    std::ifstream EngWord("translated.txt");
    for (int i = 0; i < digit; i++)
    {
        std::string buffer;
        std::getline(EngWord, buffer);
        //EngWord >> buffer;
        if (i == digit - 1)
        {
            bool temp = false;
            while (!temp)
            {
                std::string InputWord; //перевод слова, вводимый с клавиатуры
                std::cin >> InputWord;
                if (InputWord == buffer)
                    temp = true;
                else {              //REVIEW
                    std::cout << "Неверно. Попробуйте еще раз" << std::endl;
                    std::cout << buffer << std::endl;
                }
            }
            std::cout << "You're right" << std::endl;
            break;
        }
    }
    Information();
}
void RandomPhrases()
{
    unsigned int index = 0;
    std::ifstream Phrase("phrases.txt");
    while (!Phrase.eof()) {
        index += 1;
        std::string buffer;
        std::getline(Phrase, buffer);
    }
    std::cout << index << " index" << std::endl;
    unsigned int digit = time(NULL) * rand() % (index)+1; //the formula was stole from the internet
    Phrase.close();
    std::ifstream PhraseSecond("phrases.txt");
    for (int i = 0; i < digit; i++) {
        std::string buffer;
        std::getline(PhraseSecond, buffer);
        if (i == digit - 1) {
            std::cout << buffer << std::endl;
        }
    }
    PhraseSecond.close();
    Information();
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);//correct input
    SetConsoleOutputCP(1251);//correct output
    setlocale(LC_ALL, "");
    int index;//magic number, yeah
    std::string line;
    Information();
    while (std::cin >> index && index != 0)
    {
        switch (index)
        {
        case 1:
            std::cout << "Just write this FWord" << std::endl;
            std::cin>>line;
            InputEnglishWords(line);
            InputTranslatedWords();
            break;
        case 2:
            RandomOutput();
            break;
        case 3:
            Zverify();
            break;
        case 4:
            ReverseVerify();
            break;
        case 5:
            RandomPhrases();
            break;
        default:
            Information();
        }
    }
    return 0;
}