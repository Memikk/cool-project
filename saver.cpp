#include "saver.h"

Saver::Saver()
{
//    do
//    {
//        tmp.close();
//        tmp.open(name+to_string(++counter));
//    }
//    while(tmp.good());
}

void Saver::add(string number,string number2,string content)
{
    fstream save("save1.txt");
    string tmp;
    int c=0;
    bool found=false;
    do
    {
        getline(save,tmp,'\n');
        c++;
        if(tmp==number)
        {
            getline(save,tmp,'\n');
            c++;
            if(tmp==number2)
            {
                getline(save,tmp,'\n');
                c++;
                if(tmp!=content)
                {
                    cerr<<"ZAMIENIAMY"<<endl;
                    replace(save,c,content);
                }
                found=true;
                break;
            }
        }
    }
    while(tmp!="");

    save.close();
    fstream save2("save1.txt",ios::app);

    if(!found)
    {
        save2<<number<<endl<<number2<<endl<<content<<endl;
    }
    save2.close();
}

void Saver::replace(fstream& save,int counter,string to)
{
    ofstream temp("temp.txt");
    save.clear();
    save.seekg(0, ios::beg);
    string line;
    int c=0;
    while(getline(save,line))
    {
        c++;
        if(c!=counter)
        {
            temp<<line<<endl;
        }
        else
        {
            temp<<to<<endl;
        }
    }
    save.close();
    temp.close();
    if(remove("save1.txt")!=0)cerr<<"NIE MOZNA USUNAC PLIKU"<<endl;
    rename("temp.txt","save1.txt");
}










