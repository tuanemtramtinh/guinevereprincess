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

bool PrimCheck(int x){
    if (x == 1 || x == 0) return false;
    for (int i = 2; i <= x; i++){
        if (x % i == 0) return false;
    }
    return true;
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
    int temp = x - '0';
    if (MonsterLevel < level){
        if (level == 10) level = level;
        else level++;
    }
    else if (MonsterLevel > level){
        int damage = baseDamage[temp] * MonsterLevel * 10;
        HP -= damage;
    }
}

void MushMario(int & HP, int level, int phoenixdown, int maxHP){
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
    HP = HP + (s % 100);
    while (PrimCheck(HP) != 1) HP++;
    if (maxHP < HP) HP = maxHP;
}

void MushFibo(int & HP){
    int arr[18];
    arr[1] =1; arr[2] = 1;
    for (int i = 3; i < 17; i++) arr[i] = arr[i - 1] + arr[i - 2];
    if (HP > 1){
        for (int i = 16; i >= 1; i--){
            if (HP >= arr[i]){
                HP = arr[i];
                break;
            }
        }
    }
    else HP = 1;
}

//MUSH_GHOST PROCESS-------------------------------------------------------

void Mush_Ghost_Code_1(int n, int arr[], int & HP, int maxHP){
    int maxIndex, minIndex, max = -INT_MAX, min = INT_MAX;
    for (int i = 0; i < n; i++){
        if (max <= arr[i]){
            max = arr[i];
            maxIndex = i;
        }
        if (min >= arr[i]){
            min = arr[i];
            minIndex = i;
        }
    }
    HP = HP - (maxIndex + minIndex);
    if (HP > maxHP) HP = maxHP;
}

void Mush_Ghost_Code_2(int n, int arr[], int & HP, int maxHP){
    int *max = max_element(arr, arr + n), maxIndex, count = 0, mtx = -2, mti = -3;
    bool check1 = false, check2 = false;
    for (int i = 0; i < n; i++) if (*max == arr[i]){
        maxIndex = i;
        count++;
    }
    if (count == 1){
        if (maxIndex == 0) check1 = 1;
        else{
            for (int i = 0 ; i < maxIndex; i++){
                if (arr[i] < arr[i + 1]) check1 = true;
                else check1 = false;
            }
        }
        if (maxIndex == n - 1) check2 = 1;
        else{
            for (int i = maxIndex; i < n - 1; i++){
                if (arr[i] > arr[i + 1]) check2 = true;
                else check2 = false;
            }
        }
        if (check1 == true && check2 == true){
            HP = HP - (*max + maxIndex);
        }
    }
    else {
        HP = HP - (mtx + mti);
    }
    if (HP > maxHP) HP = maxHP;
}

void Mush_Ghost_Code_3(int n, int arr[], int & HP, int maxHP){
    int temp[n];
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    for (int i = 0; i < n; i++){
        if (temp[i] < 0){
            temp[i] = -temp[i];
            temp[i] = (17 * arr[i] + 9) % 257;
        }
        else temp[i] = (17 * arr[i] + 9) % 257;
    }
    int max = -INT_MAX, min = INT_MAX, maxIndex, minIndex;
    for (int i = 0; i < n; i++){
        if (temp[i] > max){
            max = temp[i];
            maxIndex = i;
        }
        if (temp[i] < min){
            min = temp[i];
            minIndex = i;
        }
    }
    HP = HP - (maxIndex + minIndex);
    if (HP > maxHP) HP = maxHP;
}


void Mush_Ghost_Code_4(int n, int arr[], int & HP, int maxHP){
    int temp[n];
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    for (int i = 0; i < n; i++){
        if (temp[i] < 0){
            temp[i] = -temp[i];
            temp[i] = (17 * temp[i] + 9) % 257;
        }
        else temp[i] = (17 * temp[i] + 9) % 257;
    }
    
    int max2_3x, max2_3i; //max3x, max3i là số lớn nhất trong 3 số đầu tiên của dãy
    if (n >= 3){
        if (temp[0] == temp[1] && temp[1] == temp[2] && temp[0] == temp[2]) {
            max2_3x = -5; max2_3i = -7;
        }
        else{
            int b[3];
            for (int i = 0; i < 3; i++) {b[i] = temp[i];}
            sort(b, b + 3);
            max2_3x = b[1];
            for (int i = 0; i < 3; i++){
                if (max2_3x == temp[i]){
                    max2_3i = i;
                    break;
                }
            }
        }
    }
    else{
        max2_3x = -5; max2_3i = -7;
    }
    HP = HP - (max2_3x + max2_3i);
    if (HP > maxHP) HP = maxHP;
}

void Mush_Ghost_Process(string index, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, string mush_ghost, int maxHP){
    //INPUT SECTION --------------------------------------
    int n, arr[1000];
    int maxElement = -INT_MAX, minElement = INT_MAX;
    ifstream infilenew;
    infilenew.open(mush_ghost);
    infilenew >> n;
    for (int i = 0; i < n; i++){
        infilenew >> arr[i];        
    }
    
    //PROCESS
    for (int i = 2; i < index.size(); i++){
        if (index[i] == '1'){
            Mush_Ghost_Code_1(n, arr, HP, maxHP);
            /*if (i != index.size() - 1)
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);*/
        }
        if (index[i] == '2'){
            Mush_Ghost_Code_2(n, arr, HP, maxHP);
            /*if (i != index.size() - 1)
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);*/
        }
        if (index[i] == '3'){
            Mush_Ghost_Code_3(n, arr, HP, maxHP);
            /*if (i != index.size() - 1)
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);*/
        }
        if (index[i] == '4'){
            Mush_Ghost_Code_4(n, arr, HP, maxHP);
            /*if (i != index.size() - 1)
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);*/
        }
    }
}

//ASCLEPIUS PROCESS ---------------------------------------------------------------------------------


void Asclepius_Process(string asclpius_pack, int & remedy, int & phoenixdown, int & maidenkiss){
    static int Asclepius_Meet = 0;
    if (Asclepius_Meet == 0){
        ifstream infile;
        infile.open(asclpius_pack);
        int n, t;
        infile >> n;
        infile >> t;
        int potionCount = 0, x;
        for (int i  = 0; i < n; i++){
            for (int j = 0; j < t; j++){
                infile >> x;
                if (potionCount == 3) continue;
                else{
                    if (x == 16){
                        remedy++;
                        potionCount++;
                    }
                    if (x == 17){
                        maidenkiss++;
                        potionCount++;
                    }
                    if (x == 18){
                        phoenixdown++;
                        potionCount++;
                    }
                }
            }
            potionCount = 0;
        }
        infile.close();
        Asclepius_Meet++;
    }
}

void Dungeon_Process(string index, int x, int & level, int & HP, int & remedy, int & maidenkiss, int & phoenixdown, int & BadEffect1, int & BadEffect2, int maxHP, int & levelSave){
    levelSave = level;
    int MonsterLevel;
    MonsterLevel = levelO(x);
    if (index == "1" || index == "2" || index == "3" || index == "4" || index == "5") damageCalculator(index, HP, level, MonsterLevel);
    else if (index == "6"){
        if (MonsterLevel < level){
            if (level == 10) level = level;
            else level = level + 2;
        }
        else if (MonsterLevel > level){
            if (BadEffect1 == 0 && BadEffect2 == 0){
                if (HP < 5) HP = 1;
                else HP = HP / 5;
                if (remedy >= 1){
                    HP = HP * 5;
                    remedy--;
                }
                else BadEffect1 = 3;
            }
        }
    }
    else if (index == "7"){
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

void PickingUpProcess(string index, string mush_ghost, string asclepius_pack, string merlin_pack, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int maxHP, int & BadEffect1, int & BadEffect2, int levelSave){
    string Mush_Ghost_Event_Check = index.substr(0, 2);
    if (index == "11"){
        MushMario(HP, level, phoenixdown, maxHP);
    }
    else if (index == "12"){
        MushFibo(HP);
    }
    else if (Mush_Ghost_Event_Check == "13"){
        Mush_Ghost_Process(index, HP, level, remedy, maidenkiss, phoenixdown, rescue, mush_ghost, maxHP);
    }
    else if (index == "15"){
        remedy++;
        if (remedy > 99) remedy = 99;
    }
    else if (index == "16"){
        maidenkiss++;
        if (maidenkiss > 99) maidenkiss = 99;
    }
    else if (index == "17"){
        phoenixdown++;
        if (phoenixdown > 99) phoenixdown = 99;
    }
    else if (index == "19"){
        Asclepius_Process(asclepius_pack, remedy, phoenixdown, maidenkiss);
        if (BadEffect1 != 0){
            if (remedy >= 1){
                HP *= 5;
                remedy--;
            }
        }
        if (BadEffect2 != 0){
            if (maidenkiss >= 1){
                level = levelSave;
                maidenkiss--;
            }
        }
    }
}

void EventProcess(string event[], int size, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, string mush_ghost, string asclepius_pack, string merlin_pack){
    int levelCheck = 0, maxHP = HP, BadEffect1 = 0, BadEffect2 = 0, StatusCheck1 = 0, StatusCheck2 = 0, levelSave = level;
    for (int i = 0; i < size; i++){
        if (event[i] == "0"){
            rescue = 1;
            break;
        }
        if (event[i] == "1" || event[i] == "2" || event[i] == "3" || event[i] == "4" || event[i] == "5" || event[i] == "6" || event[i] == "7"){
            levelCheck = levelO(i + 1);
            if (level == levelCheck){
                StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2);
                StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave);
                continue;
            }
            else {
                Dungeon_Process(event[i], i + 1, level, HP, remedy, maidenkiss, phoenixdown, BadEffect1, BadEffect2, maxHP, levelSave);
                if (HP < 0) {
                    if (phoenixdown >= 1){
                        HP = maxHP;
                        phoenixdown--;
                    }
                    else{
                        rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;
                    }
                }
                StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2);
                StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave);
            }
        }
        else{
            PickingUpProcess(event[i], mush_ghost, asclepius_pack, merlin_pack, HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, BadEffect1, BadEffect2, levelSave);
            if (HP < 0) {
                if (phoenixdown >= 1){
                    HP = maxHP;
                    phoenixdown--;
                }
                else{
                    rescue = 0;
                    display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                    break;
                }
            }
        }
        if (i == size - 1) {
            if (HP > 0) rescue = 1; 
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else{
            rescue = -1;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
    }
     
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
    EventProcess(event, EventElement, HP, level, remedy, maidenkiss, phoenixdown, rescue, mush_ghost, asclepius_pack, merlin_pack);
}