#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const double eps = 1e-5;

struct student{
    string sid;
    string cid;
    string name;
    int chinese;
    int math;
    int english;
    int program;
    student(string sid,string cid,string name,int chinese,int math,int english,int program)
    {
        this->sid = sid;
        this->cid = cid;
        this->name = name;
        this->chinese = chinese;
        this->math = math;
        this->english = english;
        this->program = program;
    }
};

bool cmp(student x,student y)
{
    return x.chinese + x.math + x.english + x.program > y.chinese + y.math + y.english + y.program;
}

vector<student> students;

void add()
{
    while(true)
    {
        cout << "Please enter the SID, CID, name and four scores. Enter 0 to finish." << endl;
        string sid;
        string cid;
        string name;
        int chinese;
        int math;
        int english;
        int program;
        cin >> sid;
        if(sid == "0")
            break;
        cin >> cid >> name >> chinese >> math >> english >> program;
        student x(sid,cid,name,chinese,math,english,program);
        bool tag = false;
        for(auto s : students)
        {
            if(s.sid == sid)
            {
                tag = true;
                break;
            }
        }
        if (tag)
            cout << "Duplicated SID." << endl;
        else
        {
            students.push_back(x);
        }
    }
}

void remove()
{
    while(true)
    {
        cout << "Please enter SID or name. Enter 0 to finish." << endl;
        string sidOrName;
        cin >> sidOrName;
        if(sidOrName == "0")
            break;
        vector<bool> toDo(students.size(),false);
        int count = 0;
        for (int i = 0; i < students.size();++i)
        {
            if(students[i].sid == sidOrName || students[i].name == sidOrName)
            {
                toDo[i] = true;
                ++count;
            }
        }
        printf("%d student(s) removed.\n", count);
        int now = 0;
        int next = 0;
        while(next < students.size())
        {
            if(!toDo[next])
            {
                students[now] = students[next];
                ++now;
            }
            ++next;
        }
        while(count--)
            students.pop_back();
    }
}

void query()
{
    while(true)
    {
        cout << "Please enter SID or name. Enter 0 to finish." << endl;
        string sidOrName;
        cin >> sidOrName;
        if(sidOrName == "0")
            break;
        vector<student> result,rank;
        for (int i = 0; i < students.size();++i)
        {
            if(students[i].sid == sidOrName || students[i].name == sidOrName)
            {
                result.push_back(students[i]);
            }
            rank.push_back(students[i]);
        }
        sort(rank.begin(),rank.end(),cmp);
        map<string, int> mp;
        int index = 1;
        for (int i = 0; i < rank.size();++i)
        {
            if(i == 0)
                mp.insert(make_pair(rank[i].sid,1));
            else
            {
                index = i + 1;
                if (rank[i].chinese + rank[i].math + rank[i].english + rank[i].program == rank[i - 1].chinese + rank[i - 1].math + rank[i - 1].english + rank[i - 1].program)
                {
                    map<string, int>::iterator it = mp.find(rank[i - 1].sid);
                    index = it->second;
                }
                mp.insert(make_pair(rank[i].sid,index));
            }
        }
            for (int i = 0; i < result.size(); ++i)
            {
                int totscore = 0;
                map<string, int>::iterator it = mp.find(result[i].sid);
                totscore += result[i].chinese;
                totscore += result[i].math;
                totscore += result[i].english;
                totscore += result[i].program;
                cout << it->second << " " << result[i].sid << " " << result[i].cid << " " << result[i].name << " " << result[i].chinese << " " << result[i].math << " " << result[i].english << " " << result[i].program << " ";
                printf("%d %.2lf\n", totscore, totscore / 4.0 + eps);
            }
    }
}

void show_ranking()
{
    cout << "Showing the ranklist hurts students' self-esteem. Don't do that." << endl;
}

void show_statistics()
{
    cout << "Please enter class ID, 0 for the whole statistics." << endl;
    string cid;
    cin >> cid;
    int tot = 0;
    int cscore = 0, cpass = 0;
    int mscore = 0, mpass = 0;
    int escore = 0, epass = 0;
    int pscore = 0, ppass = 0;
    int pall = 0, pthree = 0, ptwo = 0, pone = 0, pzero = 0;
    for(auto x : students)
    {
        if(cid == "0" || x.cid == cid)
        {
            ++tot;
            cscore += x.chinese;
            int count = 0;
            if(x.chinese >= 60)
            {
                ++count;
                ++cpass;
            }
            mscore += x.math;
            if(x.math >= 60)
            {
                ++count;
                ++mpass;
            }
            escore += x.english;
            if (x.english >= 60)
            {
                ++count;
                ++epass;
            }
            pscore += x.program;
            if(x.program >= 60)
            {
                ++count;
                ++ppass;
            }
            if(count >= 4)
                ++pall;
            if(count >= 3)
                ++pthree;
            if(count >= 2)
                ++ptwo;
            if(count >= 1)
                ++pone;
            if(count == 0)
                ++pzero;
        }
    }
    printf("Chinese\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", cscore * 1.0 / tot + eps, cpass, tot - cpass);
    printf("Mathematics\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", mscore * 1.0 / tot + eps, mpass, tot - mpass);
    printf("English\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", escore * 1.0 / tot + eps, epass, tot - epass);
    printf("Programming\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", pscore * 1.0 / tot + eps, ppass, tot - ppass);
    printf("Overall:\nNumber of students who passed all subjects: %d\nNumber of students who passed 3 or more subjects: %d\nNumber of students who passed 2 or more subjects: %d\nNumber of students who passed 1 or more subjects: %d\nNumber of students who failed all subjects: %d\n\n",pall,pthree,ptwo,pone,pzero);
}

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    while (true)
    {
        cout << "Welcome to Student Performance Management System (SPMS)." << endl
             << endl;
        cout << "1 - Add\n"
            "2 - Remove\n"
            "3 - Query\n"
            "4 - Show ranking\n"
            "5 - Show Statistics\n"
            "0 - Exit"<<endl<<endl;
        int status;
        cin >> status;
        if(status == 0)
            break;
        if(status == 1)
            add();
        else if(status == 2)
            remove();
        else if(status == 3)
            query();
        else if(status == 4)
            show_ranking();
        else if(status == 5)
            show_statistics();
    }
    return 0;
}