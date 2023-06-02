/* 22100396, Yeji Song
// Write a program that implements min-priority queue. 

References URL
1. My github code: https://github.com/YYYEJI/DS/blob/master/basic_heap.cpp
2. Namjun Kim's blog url: https://ict-nroo.tistory.com/56
3. 말랑 너구리's blog url: https://doorrock.tistory.com/13
4. leeeha's blog url: https://velog.io/@jxlhe46/C-getline-함수
5. 댄코's blog url: https://danco.tistory.com/69
6. 배산임수's blog url: https://qo-grizz.tistory.com/7
*/
#include <iostream>
#include <string.h>
using namespace std;
#define HSIZE 31

string menu();
class info_stu {
public:
    string name; 
    int id;
    string school;
    info_stu();
    void set_data(string n, int i, string s);
};
class mp_queue {
public:
    info_stu heap[HSIZE];
    int h_size;
    mp_queue();
    int size();
    bool empty();
};
mp_queue queue;
info_stu input();
info_stu insert(info_stu s[], info_stu x);
info_stu minimum(info_stu s[]);
void extract_min(info_stu s[]);
void decrease_key(info_stu s[], int x, int k);
void print_all(info_stu s[]);

int main() {
    mp_queue q;
    info_stu s, tmp;
    string answer;

    while(1) {
        answer = menu();

        if(answer == "I" || answer == "i") {
            s = input();
            tmp = insert(queue.heap, s);
            cout << "New element [" << tmp.name << ", " << tmp.id << ", " << tmp.school << "] is inserted."<< endl;
        }
        else if(answer == "D" || answer == "d") extract_min(queue.heap);
        else if(answer == "C" || answer == "c") {
            int index, id;
            cout << "index of element: ";
            cin >> index;

            do {
                cout << "Enter id value: ";
                cin >> id;
            } while(id<1000 || id>=10000);
            decrease_key(queue.heap, index, id);
        }
        else if(answer == "O" || answer == "o") {
            tmp = minimum(queue.heap);
            cout << "[" << tmp.name << ", " << tmp.id << ", " << tmp.school << "] " << endl;
        }
        else if(answer == "p" || answer == "p") print_all(queue.heap);
        else if(answer == "q" || answer == "Q") break;
    }

    cout << "Thank you. Bye!";
    return 0;
}

string menu() {
    string answer;
     
    cout << "\n*************** MENU ***************\n";
    cout << "I : Insert new element into queue.\n";
    cout << "D : Delete element with smallest key from queue.\n";
    cout << "C : Decrease key of element in queue.\n";
    cout << "O : Print out one element in queue.\n";
    cout << "P : Print out all elenments in queue.\n";
    cout << "Q : Quit";

    cout << "\n\nChoose menu: ";
    cin >> answer;

    return answer;
}

info_stu::info_stu() {
    name = "";
    id = 0;
    school = "";
}
void info_stu::set_data(string n, int i, string s) {
    name = n;
    id = i;
    school = s;
}

mp_queue::mp_queue() {
    h_size = 0;
}

int mp_queue::size() {
    return h_size;
}

info_stu input() {
    info_stu s;

    cout << "Enter name of element: ";
    cin.ignore();
    getline(cin,s.name);

    /* Case 1 - 4 digit number */
    // do {
    //     cout << "Enter id of element: ";
    //     cin >> s.id;
    // } while(s.id<1000 || s.id>=10000);
    

    /* Case 2 - 4 digit string */
    // int j = 0;
    // string id;
    // while(1) {
    //     int new_id = 0;
    //     cout << "Enter id of element: ";
    //     getline(cin, id);
        
   
    //     for(int i = 0; i<id.size(); i ++) {
    //         if(id[i]>47 && id[i]<58) new_id = new_id*10 + id[i] - 48; 
    //     }
    //     s.id = new_id;
    //     if(s.id>=1000 && s.id<10000) break;
    // }
    

    /* Another Case 2 - 4 digit string */
    
    while(1) {
        string id;
        
    }


    // 'school' key is either "Handong", "Doodong", or "Sedong" 
    while(1) {
        cout << "Enter school of element: ";
        cin >> s.school;
        
        string str = s.school;
        char ch[10];
        strcpy(ch, str.c_str());
        for(int i = 0; i<10; i++) {
            if(ch[i]>='A' && ch[i]<='Z') ch[i] += 32;
        }
    
        // if(s.school == "Handong" || s.school == "Doodong" || s.school == "Sedong") break;
        if(strcmp(ch, "handong") == 0 || strcmp(ch, "doodong") == 0 || strcmp(ch, "sedong") == 0) break;
    }

    return s;
}


info_stu insert(info_stu s[], info_stu x) {
    int k;
    queue.h_size++;
    k = queue.h_size;

    while((k!=1)&&(x.id < s[k/2].id)){    // child key < parent key
        s[k] = s[k/2];                     
        k/=2;                               
    }
    s[k] = x;  

    return x;
}


info_stu minimum(info_stu s[]) {
    return s[1];
}

void extract_min(info_stu s[]) {
    info_stu t;
    info_stu tmp;
    int parent, child;

    t = s[1];
    tmp = s[queue.h_size];
    queue.h_size--;
    parent = 1;
    child = 2;

    while(child<=queue.h_size) {
        if((child<queue.h_size) && s[child].id > s[child+1].id) child++;
        if(tmp.id <= s[child].id) break;
        s[parent] = s[child];
        parent = child;
        child *= 2;
    }
    s[parent] = tmp;

    cout << "[" << t.name << ", " << t.id << ", " << t.school << "] is deleted." << endl;
}


void print_all(info_stu s[]) {
    for(int i = 1; i<queue.size()+1; i++) 
        cout << "[" << s[i].name << ", " << s[i].id << ", " << s[i].school << "] ";

    cout << endl;
}


void decrease_key(info_stu s[], int x, int k) {
    s[x].id = k;

    int key = x;
    int key_value = s[x].id;
    info_stu value = s[x];

    while((key!=1) && (key_value<s[key/2].id)) {
        s[key] = s[key/2];
        key/=2;
    }
    s[key] = value;
}

bool mp_queue::empty() {
    if(size()==0) return true;
    else return false;
}