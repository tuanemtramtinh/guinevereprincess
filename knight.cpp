#include "knight.h"



void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

int levelO(int x){
    int b = x % 10;
    int result = x > 6 ? (b > 5 ? b : 5) : b;
    return x;
}

void Dungeon_Process(string index, int x, int & level, int & HP, int & remedy, int & BadEffect){
    int MonsterLevel;
    MonsterLevel = levelO(x);
    int damage;
    if (index == "1"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level++;
        }
        else if (MonsterLevel > level){
            damage = 1 * MonsterLevel * 10;
            HP -= damage;
            if (BadEffect > 0){
                BadEffect--;
                if (BadEffect == 0) HP *= 5;
            }
        }
    }
    if (index == "2"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level++;
        }
        else if (MonsterLevel > level){
            damage = 1.5 * MonsterLevel * 10;
            HP -= damage;
            if (BadEffect > 0){
                BadEffect--;
                if (BadEffect == 0) HP *= 5;
            }
        }
    }
    if (index == "3"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level++;
        }
        else if (MonsterLevel > level){
            damage = 4.5 * MonsterLevel * 10;
            HP -= damage;
            if (BadEffect > 0){
                BadEffect--;
                if (BadEffect == 0) HP *= 5;
            }
        }
    }
    if (index == "4"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level++;
        }
        else if (MonsterLevel > level){
            damage = 7.5 * MonsterLevel * 10;
            HP -= damage;
            if (BadEffect > 0){
                BadEffect--;
                if (BadEffect == 0) HP *= 5;
            }
        }
    }
    if (index == "5"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level++;
        }
        else if (MonsterLevel > level){
            damage = 9.5 * MonsterLevel * 10;
            HP -= damage;
            if (BadEffect > 0){
                BadEffect--;
                if (BadEffect == 0) HP *= 5;
            }
        }
    }
    if (index == "6"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level = level + 2;
        }
        else if (MonsterLevel > level){
            if (remedy >= 1){
                remedy--;
                HP = HP / 5;
                HP = HP * 5;
            }
            else{
                HP = HP / 5;
                BadEffect += 3;
            }
        }
    }

}

void EventProcess(string event[], int size, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    int levelCheck = 0;
    int maxHP = HP;
    int BadEffect = 0;
    for (int i = 0; i < size; i++){
        
        if (event[i] == "0"){ //Kiem tra dieu kien thang ngay lap tuc
            rescue = 1;
            break;
        }
        levelCheck = levelO(i + 1);
        if (level == levelCheck) continue; //Kiem tra dieu kien hoa
        else {//Xu li neu level khong bang nhau
            Dungeon_Process(event[i], i + 1, level, HP, remedy, BadEffect);
            if (HP < 0) {
                if (phoenixdown >= 1){
                    HP = maxHP;
                    phoenixdown--;
                }
                else rescue = 0;
            }
        }
    }
    if (HP > 0) rescue = 1;
}


void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    //Input Section ------------------------------------------------------------
    ifstream infile;
    infile.open(file_input);
    string str1, str2, str3;
    getline(infile, str1);
    istringstream s1(str1);
    while (s1){
        s1 >> HP >> level >> remedy >> maidenkiss >> phoenixdown >> rescue;
    }
    getline(infile, str2);
    istringstream s2(str2);
    string event[100];
    int i = 0;
    while (s2){
        if (s2){
            s2 >> event[i];
            i++;
        }
    }
    int EventElement = i - 1;
    getline(infile, str3);
    for (int i = 0; i < str3.size(); i++)
        if (str3[i] == ',') str3[i] = ' ';
    string mush_ghost, asclepius_pack, merlin_pack;
    istringstream s3(str3);
    s3 >> mush_ghost >> asclepius_pack >> merlin_pack;
    //Input Section ------------------------------------------------------------
    rescue = -1;
    EventProcess(event, EventElement, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);

}
