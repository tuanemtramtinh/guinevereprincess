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
    return result;
}

void StatusCheck(string x, int & BadEffect1, int & BadEffect2, int & StatusCheck1, int & StatusCheck2){
    if (x != "6"){
            if (BadEffect1 > 0 && BadEffect1 <= 3){
                BadEffect1--;
                if (BadEffect1 == 0) StatusCheck1 = 1;
                else StatusCheck1 = 0;
            }
    }
    if (x != "7"){
        if (BadEffect2 > 0 && BadEffect2 <= 3){
            BadEffect2--;
            if (BadEffect2 == 0) StatusCheck2 = 1;
            else StatusCheck2 = 0;
        }
    }
}

void StatusDeadline(int & HP, int & level, int & StatusCheck1, int & StatusCheck2, int levelSave){
    if (StatusCheck1 == 1){
        HP *= 5;
        StatusCheck1 = 0;
    }
    if (StatusCheck2 == 1){
        level = levelSave;
        StatusCheck2 = 0;
    }
}

void damageCalculator(string index, int & HP, int & level, int MonsterLevel)
{
    float baseDamage[6];
    baseDamage[1] = 1;
    baseDamage[2] = 1.5;
    baseDamage[3] = 4.5;
    baseDamage[4] = 7.5;
    baseDamage[5] = 9.5;
    char x;
    if (index.size() == 1) x = index[0];
    if (MonsterLevel < level){
        if (level == 10) level = level;
        else level++;
    }
    else if (MonsterLevel > level){
        int damage = baseDamage[x - '0'] * MonsterLevel * 10;
        HP -= damage;
    }
}

void MushMario(int & HP, int & level, int & phoenixdown){
    int x = ((level + phoenixdown) % 5 + 1) * 3;
    int count = 0;
    int s = 0;
    for (int i = 99; i >= 10; i--){
        if (i % 2 == 1){
            s += i;
            count++;
        } 
        if (count == x) break;
    }
}

void Dungeon_Process(string index, int x, int & level, int & HP, int & remedy, int & maidenkiss, int & BadEffect1, int & BadEffect2){
    int levelSave = level, MonsterLevel;
    MonsterLevel = levelO(x);
    damageCalculator(index, HP, level, MonsterLevel);
    if (index == "6"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level = level + 2;
        }
        else if (MonsterLevel > level){
            if (BadEffect1 == 0 && BadEffect2 == 0){
                HP = HP / 5;
                if (remedy >= 1){
                    HP = HP * 5;
                    remedy--;
                }
                else BadEffect1 = 3;
            }
        }
    }
    if (index == "7"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level = level + 2;
        }
        else if (MonsterLevel > level){
            if (BadEffect1 == 0 && BadEffect2 == 0){
                level = 1;
                if (maidenkiss >= 1){
                    level = levelSave;
                    maidenkiss--;
                }
                else BadEffect2 = 3;
            }
        }
    }
    
}

void EventProcess(string event[], int size, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    int levelCheck = 0, maxHP = HP, BadEffect1 = 0, BadEffect2 = 0, StatusCheck1 = 0, StatusCheck2 = 0, levelSave = level;
    for (int i = 0; i < size; i++){
        if (event[i] == "0"){
            rescue = 1;
            break;
        }
        levelCheck = levelO(i + 1);
        if (level == levelCheck){
            StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2);
            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave);
            continue;
        }
        else {
            Dungeon_Process(event[i], i + 1, level, HP, remedy, maidenkiss, BadEffect1, BadEffect2);
            if (HP < 0) {
                if (phoenixdown >= 1){
                    HP = maxHP;
                    phoenixdown--;
                }
                else rescue = 0;
            }
            StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2);
            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave);
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
