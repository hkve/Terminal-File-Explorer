#include <iostream>
#include <string>
#include <map>
using namespace std;

void color(int f,int fg,int bg,string text)// f is for format
{
  string fs = ""; //fs for format string
  string fgs = "";// fgs for foreground string
  string bgs = "";//bgs for background string

  switch(f)
  {
    case 0: fs = "0;";break;
    case 1: fs = "1;";break;
    case 2: fs = "2;";break;
    case 3: fs = "3;";break;
    case 4: fs = "4;";break;
    case 5: fs = "5;";break;
    case 6: fs = "6;";break;
    case 7: fs = "7;";break;
    case 8: fs = "8;";break;
    case 9: fs = "9;";break;
  }
  
  switch(fg)
  {
    case 0: fgs = "";break;
    case 30: fgs = "30";break;
    case 31: fgs = "31";break;
    case 32: fgs = "32";break;
    case 33: fgs = "33";break;
    case 34: fgs = "34";break;
    case 35: fgs = "35";break;
    case 36: fgs = "36";break;
    case 37: fgs = "37";break;
  }

  if(bg == 0)
  {
    cout << "\033[" << fs << fgs << "m" << text << "\033[m";
  }
  else
  {
    
    switch(bg)
    {
      case 40: bgs = "40";break;
      case 41: bgs = "41";break;
      case 42: bgs = "42";break;
      case 43: bgs = "43";break;
      case 44: bgs = "44";break;
      case 45: bgs = "45";break;
      case 46: bgs = "46";break;
      case 47: bgs = "47";break;
    }
      
    cout << "\033[" << fs << fgs << ";" << bgs << "m" << text << "\033[m";
  }
}

map<string, string> textColor = {
  {"gray", "30"},
  {"red", "31"},
  {"green", "32"},
  {"yellow", "33"},
  {"blue", "34"},
  {"purple", "35"},
  {"cyan", "36"},
  {"white", "37"}
};

map<string, string> textBackground = {
  {"gray", "40"},
  {"red", "41"},
  {"green", "42"},
  {"yellow", "43"},
  {"blue", "44"},
  {"purple", "45"},
  {"cyan", "46"},
  {"white", "47"}
};

map<string, string> textFormat = {
  {"bold", "1"},
  {"underline", "4"}
};

int main(int argc, char const *argv[])
{
  for(int i = 30; i <= 37; i++) {
    for(int j = 40; j <= 47; j++) {
      string t = to_string(i);
      color(0, i, j, t); 
    }
    cout <<endl;
  }
  return 0;
}