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
    bool found=false;
    do
    {
        getline(save,tmp,'\n');
        cerr<<"TEST 1 = "<<tmp<<endl;
        cerr<<"TEST 2 = "<<number<<endl;
        if(tmp==number)
        {
            cerr<<"ROWNA SIE"<<endl;
            cerr<<"DUPA"<<endl;
            getline(save,tmp,'\n');
            cerr<<"DUPA2"<<endl;
            if(tmp==number2)
            {
                getline(save,tmp,'\n');
                if(tmp!=content)
                {
                    cerr<<"ZAMIENIAMY"<<endl;
                    replace(save,tmp,content);
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

void Saver::replace(fstream& save,string from,string to)
{
    fstream temp("temp.txt");
    save.clear();
    save.seekg(0, ios::beg);
    string line;
    while(getline(save,line))
    {
        if(line!=from)
        {
            temp<<line<<endl;
        }
        else
        {
            temp<<to<<endl;
        }
    }
    remove("save1.txt");
    rename("temp.txt","save1.txt");
}










