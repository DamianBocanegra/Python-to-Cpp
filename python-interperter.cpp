#include <iostream>
#include<fstream>

using namespace std;


void findToken(string);
string executePrintToken(int, string);

const int MAXLINE = 256;



int main()
{

  ifstream inFile("python.py");
  char oneline[MAXLINE];


  while(inFile)
  {
      inFile.getline(oneline, MAXLINE);
      findToken(oneline);
  }


  inFile.close();

  return 0;
}

void findToken(string line)
{
    string tokken = "";
    for(int i = 0; i < MAXLINE; i++)
    {
        tokken += line[i];

        if (tokken == "print")
        {
            tokken == "";
            cout << executePrintToken(i, line) << endl;
            return;
        }
    }
}

string executePrintToken(int position, string line)
{
    string printLine = "";
    for(int k = position; k < MAXLINE; k++)
    {
        if(line[k] == '"')
        {
            for(int j = k + 1; j < MAXLINE; j++)
            {
                if(line[j] == '"')
                {
                    return printLine;
                }

                printLine += line[j];
            }
        }
    }
}
