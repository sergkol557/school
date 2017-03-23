/**
 * Implements a spell-checker.
 */

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include "headers/arraylist.h"


#define MAX_WORD_LENGTH 45

const string DEFAULT_DICTIONARY="dictionaries/large";


class StopWatch
{
private:
    double start_time;
    double finish_time;
public:
//====================================================================================================================
    void start_clock()//starts stop watch
    {
      start_time=clock()/(double)CLOCKS_PER_SEC;
    }
//====================================================================================================================
    void finishClock()
    {
     finish_time=clock()/(double)CLOCKS_PER_SEC;
    }
//====================================================================================================================
   double getResult()
   {
       return finish_time-start_time;
   }
//====================================================================================================================
};

class CheckArgs
{
public:
//=====================================================================================================================
    string checkCommandLineArgs(int argc, char* argv[])// check for correct number of args and
    {
      if (argc != 2 && argc != 3)
      {
          throw invalid_argument("Usage: speller [dictionary] text\n");
      }
    return (argc == 3) ? argv[1] : DEFAULT_DICTIONARY;
    }
//=====================================================================================================================
};
class FileLoader
{
private:
  FILE *inptr;
public:
//=====================================================================================================================
FileLoader()//constructor
    {
    }
//=====================================================================================================================
bool openFile(string file_name)//open file for file name
{
    inptr = fopen(file_name.c_str(), "r");
    if (inptr == NULL)
    {
       return false;
    }
    return true;
}
//=====================================================================================================================
    ~FileLoader()//destructor
    {
    if (inptr!=NULL)
      {
        fclose(inptr);
      }
    }
//=====================================================================================================================
char getNextChar()//returns next char from file
 {
    if (ferror(inptr))
    {
        fclose(inptr);
        throw invalid_argument("Error reading text");
    }
    return fgetc(inptr);
 }
};
//=====================================================================================================================
class Speller
{
private:
 FileLoader *loader;
 int index, misspellings, words;
 char word[MAX_WORD_LENGTH+1];
 CheckArgs *check_class;
 ArrayList<string> *dict;
public:
//=====================================================================================================================
 Speller()//constructor with create file loader
 {
     loader=new FileLoader;
     dict=new ArrayList<string>;
 }
//=====================================================================================================================
 ~Speller()
 {
      delete loader;
      delete dict;
 }
//=====================================================================================================================
void spellWords(string file_name)
{
    index = 0, misspellings = 0, words = 0;
    cout<<"\nMISSPELLED WORDS\n";
    loader->openFile(file_name);
    for (int c = loader->getNextChar(); c != EOF; c = loader->getNextChar())
    {
       if (isalpha(c) || (c == '\'' && index > 0)) // allow only alphabetical characters and apostrophes
        {
            word[index] = c; // append character to word
            index++;
            if (index > MAX_WORD_LENGTH) // ignore alphabetical strings too long to be words
            {
                while ((c = loader->getNextChar()) != EOF && isalpha(c)); // consume remainder of alphabetical string
                index = 0;// prepare for new word
            }
        }
        else if (isdigit(c))// ignore words with numbers (like MS Word can)
        {
            while ((c = loader->getNextChar()) != EOF && isalnum(c));// consume remainder of alphanumeric string
            index = 0;// prepare for new word
        }
        else if (index > 0) // we must have found a whole word
        {
            word[index] = '\0'; // terminate current word
            words++; // update counter
            if (!(dict->containOf(word)))// print word if misspelled
            {
                cout<<word<<endl;
                misspellings++;
            }
            index = 0;// prepare for next word
        }
    }
}
//=====================================================================================================================
void loadDictionary(string dictionary_name)
{
    dict->loadStringFromFile(dictionary_name);
}
//=====================================================================================================================
void printResults()
{
    cout<<"WORDS MISSPELLED:"<< misspellings<<endl;
    cout<<"WORDS IN DICTIONARY:"<<dict->sizeOfArray()<<endl;
    cout<<"WORDS IN TEXT:"<<words<<endl;
}
//=====================================================================================================================
};
//=====================================================================================================================
void printWatchResults(double speed_dictionary, double speed_word_spell)//print time result
{
    cout<<"\nTIME OF DICTIONARY LOAD "<<speed_dictionary<<" sec"<<endl;
    cout<<"TIME OF SPELL WORD "<<speed_word_spell<<" sec"<<endl;
}
//=====================================================================================================================

int main(int argc, char *argv[])
{
    CheckArgs *check_class = new CheckArgs;
    Speller *spell_text=new Speller;
    StopWatch *watcher= new StopWatch;
    string dictionary = check_class->checkCommandLineArgs(argc,argv);
    string text_filename = (argc == 3) ? argv[2] : argv[1];
    double load_dict=0;
    double spell_word=0;

    watcher->start_clock();
        spell_text->loadDictionary(dictionary);
    watcher->finishClock();
    load_dict=watcher->getResult();
    watcher->start_clock();
        spell_text->spellWords(text_filename);
    watcher->finishClock();
    spell_word=watcher->getResult();

    printWatchResults(load_dict, spell_word);
    spell_text->printResults();

    delete spell_text;
    delete check_class;
    delete watcher;
    return 0;
}
//=====================================================================================================================

