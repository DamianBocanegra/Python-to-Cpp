#include <iostream>
#include<fstream>
#include<string>

using namespace std;


void findToken(string);
string executePrintToken(int, string);
string findWord(string, int);
bool findFuncStart(string, int);
string getType(string);
void makeVarible(string, int);
string getValue(string, int);

bool error = false;
const int MAX_SIZE = 256;

struct var
{
    string type;
    string name;
    string value;
};

var newvars[MAX_SIZE];

int main()
{

  ifstream inFile("python.py");
  string oneline = "";

  newvars[0].type = "end";



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
    size_t found;

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
        else if(line.find("=") != string::npos)
        {
            found = line.find("=");
            cout << "Varible detected" << endl;
            return;
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

void makeVarible(string line, int equalSign)
{
    string searching = "";
    string name, value, type;
    for(int i = 0; i < line.length(); i++)
    {
        searching += line[i];
        if(line[i] == ' ')
        {
            if((i + 1) != equalSign)
            {
                error = true;
                cout << "ERROR INVALID NAME!" << endl;
                return;
            }
            else
            {
                name = searching;
                value = getValue(line, equalSign);
                type = getType(value);
                return;
            }
        }
    }
}

string getValue(string line, int position)
{
    string value = "";
    bool firstCharFound = false;

    for(int i = position + 1; i < line.length(); i++)
    {

          if(!firstCharFound && (line[i] != " "))
          {
              firstCharFound = true;
          }
          if(firstCharFound)
          {
              value += line[i];
          }

    }

    return value;
}

string getType(string value)
{
    if(value[0] == '"')
    {
        if(value[value.length() - 1] != '"')
        {
            error = true;
            return "error";

        }
        else
        {
            return "string";
        }
    }

    else if(value[0] == "'")
    {
        if(value[value.length() - 1] != "'")
        {
            error = true;
            return "error";

        }
        else
        {
            return "string";
        }
    }
    else if(int(value[0]) >= 48 && int(value[0]) < 58)
    {
        for(int i = 0; i < value.length(); i++)
        {
            if(int(value[i]) < 48 || int(value[i]) >= 58)
            {
                error = false;
                return "error";
            }
        }

        return "int";
    }
}
