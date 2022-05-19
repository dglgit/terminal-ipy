#include<ncurses.h>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;

string vecline(WINDOW* w){
   string line="";
   char ch;
   while(true){
      ch=wgetch(w);
      if(ch==10){
         break;
      }
      if (ch==KEY_MOUSE){
         MEVENT event;
         if(getmouse(&event)==OK){
            if(event.bstate & BUTTON0_CLICKED){
               wmove(w,event.y,event.x);
               mvwprintw(w, 1,0,"(%i,%i)",event.y,event.x);
            }
         }
      }
      line+=ch;
      wrefresh(w);
   }
   return line;
}
class writable{
   public:
   vector<string> text;
   int currentLine;
   writable(){
      vector<string> text_;
      text=text;
      currentLine=0;
   }
   int length(){
      return text.size();
   }
   void changeLine(int lineNum){
      if (lineNum>length()){
         for(int i=0;i<lineNum-length();i++){
            text.push_back("");
         }
      }
      currentLine=lineNum;
   }
   void write(string s){
      text[currentLine].insert(text[currentLine].size(),s);
   }
   void write(string s, int pos){
      text[currentLine].insert(pos,s);
   }

};
int main(){
   initscr();
   raw();
   mousemask(BUTTON0_PRESSED | BUTTON2_PRESSED,NULL);
   printf("\033[?1003h\n");
   keypad(stdscr,TRUE); 
   move(1,0);
   vecline(stdscr);
   endwin();
   return 0;
}

