/*
1.Добавить возможность исправления слова
2.Отдельную функцию для проверки правильности перевода с английского на русский и обратно
3.Из-за странной формулы в случайном выводе есть смысл огородить слова, поставив сверху и снизу пару строк в стиле *строка n*
4.Прикрутить вывод русского слова к случайному английскому
5.Примеры использования слов в том или ином контексте

N.Возможно добавить отдельно фразы (но без проверки на правильность перевода - сразу с переводом выдавать)
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

void RandomOutput() 
{
    unsigned int index = 0;
    std::ifstream EngWordsOutput("english.txt"); 
    while (!EngWordsOutput.eof()) {
        index += 1;
        std::string buffer;
        EngWordsOutput >> buffer;
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

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);//correct input
    SetConsoleOutputCP(1251);//correct output
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
        default:
            Information();
        }
    }
    return 0;
}