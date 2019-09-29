#include <iostream>
#include<fstream>

using namespace std;


void findToken(string);
string executePrintToken(int, string);
string findWord(string, int);
bool findFuncStart(string, int);

bool error = false;

int main()
{

  ifstream inFile("python.py");
  string oneline = "";


  while(inFile)
  {
      getline(inFile, oneline);
      //cout << oneline << endl;
      findToken(oneline);

      if(error)
      {
          cout << "COMPILE ERROR! TERMINATED!" << endl;
          return 1;
      }
      cout << endl;
  }

  inFile.close();

  return 0;
}

void findToken(string line)
{
    //cout << "ENTER TOKKEN" << endl;
    string tokken = "";
    string printME = "test";
    bool start = false;
    for(int i = 0; i < line.length(); i++)
    {

        tokken += line[i];


        if (tokken == "print")
        {
            start = findFuncStart(line, i + 1);
            if(!start)
            {
                error = true;
                cout << "ERROR '(' MISSING!" << endl;

            }
            else
            {
                printME = executePrintToken(i + 1, line);
                //cout << "Execute comp" << endl;
                cout << printME << endl;
                //cout << "Tokken exit" << endl;
                return;
            }

        }
    }


}

string executePrintToken(int position, string line)
{
    if(line[line.length() - 1] != ')')
    {
        error = true;
        return "ERROR ')' MISSING!";
    }

    string printLine = "";
    string result;

    for(int k = position + 1; k < line.length(); k++)
    {
        //cout << line[k] << endl;
        if(line[k] == '"')
        {
            result = findWord(line, k + 1);
            if(result != "ERROR!")
            {
                k = k + result.length() + 1;
                printLine += result;
            }
            else
            {
                error = true;
                return "ERROR OQ";
            }
        }
        else if(line[k] == '+')
        {
           //cout << "Found +" << endl;
        }
        else if(line[k] == ' ')
        {
            //cout << "Found ' '" << endl;
        }
        else if(line[k] == '(')
        {
            //ignore
        }
        else if(line[k] == ')')
        {
            return printLine;
        }
        else
        {
            error = true;
            return "ERROR INVALID OP";
        }
    }
}

string findWord(string line, int position)
{
    string phrase = "";
    for(int a = position; a < line.length(); a++)
    {
        if(line[a] == '"')
        {
            return phrase;
        }
        phrase += line[a];
    }

    error = true;
    return "ERROR!";
}

bool findFuncStart(string line, int position)
{
    for(int b = position; b < line.length(); b++)
    {
        if(line[b] == '(')
        {
            return true;
        }
        else if (line[b] == ' ')
        {
            //Ignore
        }
        else
        {
            return false;
        }
    }
}
