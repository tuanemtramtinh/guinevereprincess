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

bool PrimeCheck(int x){
    if (x == 1 || x == 0) return false;
    for (int i = 2; i <= sqrt(x); i++){
        if (x % i == 0) return false;
    }
    return true;
}

bool ArthurCheck(int maxHP){
    if (maxHP == 999) return true;
    return false;
}

bool LancelotCheck(int maxHP){
    if (PrimeCheck(maxHP)) return true;
    return false;
}

//CHECK EFFECT OF SHAMAN AND VASJH -------------------------------------------------------------------------

void StatusCheck(string x, int & BadEffect1, int & BadEffect2, int & StatusCheck1, int & StatusCheck2, int & ShamanMeet, int & VajshMeet){
    if (ShamanMeet == 1){
            if (BadEffect1 > 0 && BadEffect1 <= 4){
                BadEffect1--;
                if (BadEffect1 == 0){
                    StatusCheck1 = 1;
                    ShamanMeet = 0;
                }
                else StatusCheck1 = 0;
            }
    }
    if (VajshMeet == 1){
        if (BadEffect2 > 0 && BadEffect2 <= 4){
            BadEffect2--;
            if (BadEffect2 == 0){
                StatusCheck2 = 1;
                VajshMeet = 0;
            }
            else StatusCheck2 = 0;
        }
    }
}

void StatusDeadline(int & HP, int & level, int & StatusCheck1, int & StatusCheck2, int levelSave, int maxHP, int & ShamanMeet, int & VajshMeet){
    if (StatusCheck1 == 1){
        if (HP > 0)
        {
            HP *= 5;
            if (HP > maxHP) HP = maxHP;
            StatusCheck1 = 0;
        }
        else{
            HP = maxHP;
            StatusCheck1 = 0;
        }
    }
    if (StatusCheck2 == 1){
        level = levelSave;
        StatusCheck2 = 0;
        if (HP <= 0) HP = maxHP;
        VajshMeet = 0;
    }
}

//DAMAGE CALCULATOR ------------------------------------------------------------------------------------

void damageCalculator(string index, int & HP, int & level, int MonsterLevel, int maxHP)
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
    if (MonsterLevel < level || LancelotCheck(maxHP) == true || ArthurCheck(maxHP) == true){
        level++;
        if (level >= 10) level = 10;
    }
    else if (MonsterLevel > level){
        int damage = baseDamage[temp] * MonsterLevel * 10;
        HP -= damage;
    }
}

//MUSH MARIO ---------------------------------------------------------

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
    bool check = false;
    while (check == false){
        HP++;
        if (PrimeCheck(HP)) check = true;
    }
    if (maxHP < HP) HP = maxHP;
}

//MUSH FIBO ---------------------------------------------------------

void MushFibo(int & HP){
    int arr[18];
    arr[1] = 1; arr[2] = 1;
    for (int i = 3; i < 17; i++) arr[i] = arr[i - 1] + arr[i - 2];
    if (HP > 1){
        for (int i = 16; i >= 1; i--){
            if (HP > arr[i]){
                HP = arr[i];
                break;
            }
        }
    }
    else HP = 1;
}

//MUSH_GHOST PROCESS-------------------------------------------------------

//MUSH_GHOST CODE 1 PROCESS----------------------------------------

void Mush_Ghost_Code_1(int n, int arr[], int & HP, int maxHP){
    int maxIndex; int minIndex; int max = -999999; int min = 999999;
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

//MUSH_GHOST CODE 2 PROCESS----------------------------------------

void Mush_Ghost_Code_2(int n, int arr[], int & HP, int maxHP){
    int max = -999999; int maxIndex; int count = 0; int mtx = -2; int mti = -3;
    bool check1 = false, check2 = false;
    for (int i = 0; i < n; i++) if (max < arr[i]) max = arr[i];
    for (int i = 0; i < n; i++) if (max == arr[i]){
        maxIndex = i;
        count++;
    }
    if (count == 1){
        if (maxIndex == 0){
            if (n == 1){
                check1 = true;
                check2 = true;
            }
            else{
                for (int i = 0; i < n - 1; i++){
                    if (arr[i] > arr[i + 1]){
                        check1 = true;
                        check2 = true;
                    }
                    else {
                        check1 = false;
                        check2 = false;
                        break;
                    }
                }
            }
        }
        else if (maxIndex == n - 1){
            for (int i = 0; i < n - 1; i++)
            {
                if (arr[i] < arr[i + 1]){
                    check1 = true;
                    check2 = true;
                }
                else{
                    check2 = false;
                    check1 = false;
                    break;
                }
            }
        }
        else{
            for (int i = 0 ; i < maxIndex; i++){
                if (arr[i] < arr[i + 1]) check1 = true;
                else{
                    check1 = false;
                    break;
                }
            }
            for (int i = maxIndex; i < n - 1; i++){
                if (arr[i] > arr[i + 1]) check2 = true;
                else{
                    check2 = false;
                    break;
                }
            }
        }
        if (check1 == true && check2 == true){
            HP = HP - (max + maxIndex);
        }
        else HP = HP - (mtx + mti);
    }
    else {
        HP = HP - (mtx + mti);
    }
    if (HP > maxHP) HP = maxHP;
}

//MUSH_GHOST CODE 3 PROCESS----------------------------------------

void Mush_Ghost_Code_3(int n, int arr[], int & HP, int maxHP){
    int temp[n];
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    for (int i = 0; i < n; i++){
        if (temp[i] < 0){
            temp[i] = -1 * temp[i];
            temp[i] = (17 * temp[i] + 9) % 257;
        }
        else temp[i] = (17 * temp[i] + 9) % 257;
    }
    int max = -999999; int min = 999999; int maxIndex; int minIndex;
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
    //cout << HP << endl;
}

//MUSH_GHOST CODE 4 PROCESS----------------------------------------

void Mush_Ghost_Code_4(int n, int arr[], int & HP, int maxHP){
    int temp[n];
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    for (int i = 0; i < n; i++){
        if (temp[i] < 0){
            temp[i] = -1 * temp[i];
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
            for (int i = 0; i < 3; i++){
                for (int j = i; j < 3; j++){
                    if (b[i] > b[j]) swap(b[i], b[j]);
               }
            }
            if (b[1] == b[2] ) max2_3x = b[0];
            else if (b[0] == b[1]) max2_3x = b[0];
            else max2_3x = b[1];
            for (int i = 0; i < 3; i++){
                if (max2_3x == temp[i]){
                    max2_3i = i;
                    break;
                }
            }
        }
        //cout << max2_3i << " " << max2_3x;
    }
    else if (n == 2){
        int a, b;
        a = temp[0];
        b = temp[1];
        if (a < b){
            max2_3i = 0;
            max2_3x = a;
        }
        else if (b < a){
            max2_3i = 1;
            max2_3x = b;
        }
        else if (a == b){
          max2_3x = -5; max2_3i = -7;  
        }
    }
    else{
        max2_3x = -5; max2_3i = -7;
    }
    HP = HP - (max2_3x + max2_3i);
    if (HP > maxHP) HP = maxHP;
}

//MUSH_GHOST MAIN PROCESS------------------------------------------------------------------------------------------

void Mush_Ghost_Process(string index, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, string mush_ghost, int maxHP){
    //INPUT SECTION --------------------------------------
    int n, arr[1000];
    int maxElement = -999999; int minElement = 999999;
    ifstream infilenew;
    infilenew.open(mush_ghost);
    string N;
    infilenew >> n;
    getline(infilenew, N);
    string NumberSequence;
    getline(infilenew, NumberSequence);
    for (int i = 0; i < NumberSequence.size(); i++) if (NumberSequence[i] == ',') NumberSequence[i] = ' ';
    istringstream str(NumberSequence);
    for (int i = 0; i < n; i++) str >> arr[i];
    infilenew.close();
    //PROCESS
    for (int i = 2; i < index.size(); i++){
        if (index[i] == '1')
        {
            Mush_Ghost_Code_1(n, arr, HP, maxHP);
        }
        if (index[i] == '2')
        {
            Mush_Ghost_Code_2(n, arr, HP, maxHP);
        }
        if (index[i] == '3')
        {
            Mush_Ghost_Code_3(n, arr, HP, maxHP);
        }
        if (index[i] == '4')
        {
            Mush_Ghost_Code_4(n, arr, HP, maxHP);
        }
        if (HP <= 0){
            if (phoenixdown >= 1){
                HP = maxHP;
                phoenixdown--;
            }
            else break;
        }
    }
}

//ASCLEPIUS PROCESS ---------------------------------------------------------------------------------

void Asclepius_Process(string asclepius_pack, int & remedy, int & phoenixdown, int & maidenkiss){
    static int Asclepius_Meet = 0;
    if (Asclepius_Meet == 0){
        int potionCount = 0;
        ifstream infile;
        infile.open(asclepius_pack);
        int n, t; string N,T;
        getline(infile, N);
        istringstream NN(N);
        NN >> n;
        getline(infile, T);
        istringstream TT(T);
        TT >> t;
        int arr[n][t];
        for (int i = 0; i < n; i++){
            string s;
            getline(infile, s);
            istringstream str(s);
            for (int j = 0; j < t; j++){
                str >> arr[i][j];
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < t; j++){
                if (potionCount == 3) continue;
                else if (arr[i][j] == 16){
                    remedy++;
                    potionCount++;
                }
                else if (arr[i][j] == 17){
                        maidenkiss++;
                        potionCount++;
                    }
                else if (arr[i][j] == 18){
                        phoenixdown++;
                        potionCount++;
                    }
            }
            potionCount = 0;
        }
        if (remedy > 99) remedy = 99;
        if (maidenkiss > 99) maidenkiss = 99;
        if (phoenixdown > 99) phoenixdown = 99;
        Asclepius_Meet++;
        infile.close();
    }
}

//MERLIN_PROCESS------------------------------------------

void Merlin_Process(string merlin_pack, int & HP){
    static int MerlinMeet = 0;
    if (MerlinMeet == 0){
        ifstream infile;
        infile.open(merlin_pack);
        int n;
        infile >> n;
        string N;
        getline(infile, N);
        string s;
        int countM = 0, countE = 0, countR = 0, countL = 0, countI = 0, countN = 0;
        for (int  i = 0; i < n; i++){
            getline(infile, s);
            if (s.find("merlin") != string::npos || s.find("Merlin") != string::npos) HP += 3;
            else {
                for (int j = 0; j < s.size(); j++){
                    if (s[j] == 'M' || s[j] == 'm') countM++;
                    if (s[j] == 'E' || s[j] == 'e') countE++;
                    if (s[j] == 'R' || s[j] == 'r') countR++;
                    if (s[j] == 'L' || s[j] == 'l') countL++;
                    if (s[j] == 'I' || s[j] == 'i') countI++;
                    if (s[j] == 'N' || s[j] == 'n') countN++;
                }
                if (countM > 0 && countE > 0 && countR > 0 && countL > 0 && countI > 0 && countN > 0) HP += 2;
                countM = 0; countE = 0; countR = 0; countL = 0; countI = 0; countN = 0;
            }
        }
        MerlinMeet++;
        infile.close();
    }
}

//SHAMAN & VAJSH PROCESS (APPLY FOR EVENT 6 AND EVENT 7) ----------------------------------------------------------------------

void Shaman_Event(int & HP, int & BadEffect1, int & remedy){
    if (remedy >= 1){
        remedy--;
    }
    else{
        if (HP < 5) HP = 1;
        else HP /= 5;
        BadEffect1 = 4;
    }
}

void Vajsh_Event(int & level, int levelSave, int & BadEffect2, int & maidenkiss){
    level = 1;
    if (maidenkiss >= 1){
        level = levelSave;
        maidenkiss--;
    }
    else BadEffect2 = 4;
}

//PROCESS SHAMAN AND VASJH EVENT----------------------------------------------------------------------

void Witch_Process(string index, int & HP, int & remedy, int & maidenkiss, int & level, int MonsterLevel, int & BadEffect1, int & BadEffect2, int levelSave, int maxHP, int & ShamanMeet, int & VajshMeet){
    if (MonsterLevel < level || LancelotCheck(maxHP) == true){
        level += 2;
        if (level >= 10) level = 10;
    }
    else if (MonsterLevel > level){
        if (BadEffect1 == 0 && BadEffect2 == 0){
            if (index == "6"){
                ShamanMeet = 1;
                Shaman_Event(HP, BadEffect1, remedy);
            }
            if (index == "7"){
                VajshMeet = 1;
                Vajsh_Event(level, levelSave, BadEffect2, maidenkiss);
            }
        }
    }
}

//DUNGEON_PROCESS(APPLY FOR EVENT 1 -> 7)-----------------------------------------------------------------------------

void Dungeon_Process(string index, int x, int & level, int & HP, int & remedy, int & maidenkiss, int & phoenixdown, int & BadEffect1, int & BadEffect2, int maxHP, int & levelSave, int & ShamanMeet, int & VajshMeet){
    levelSave = level;
    int MonsterLevel;
    MonsterLevel = levelO(x);
    if (index == "1" || index == "2" || index == "3" || index == "4" || index == "5") damageCalculator(index, HP, level, MonsterLevel, maxHP);
    else if (index == "6" || index == "7") Witch_Process(index, HP, remedy, maidenkiss, level, MonsterLevel, BadEffect1, BadEffect2, levelSave, maxHP, ShamanMeet, VajshMeet);
}

//BOWSER APPLY FOR EVENT 99 ---------------------------------------------------------------------------------------

bool Bowser_Process(int & level, int maxHP){
    if (ArthurCheck(maxHP)) return true;
    if (LancelotCheck(maxHP) && level >= 8){
        level = 10;
        return true;
    }
    if (level == 10) return true;
    return false;
}

//PICKING_UP_PROCESS APPLY FOR EVENT 11, 12, 13, 15, 16, 17---------------------------------------------------------------------

void PickingUpProcess(string index, string mush_ghost, string asclepius_pack, string merlin_pack, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, int maxHP, int & BadEffect1, int & BadEffect2, int levelSave, int & StatusCheck1, int & StatusCheck2, int & ShamanMeet, int & VajshMeet){
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
        if (BadEffect1 != 0){
            if (remedy >= 1){
                StatusCheck1 = 1;
                StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
                remedy--;
                BadEffect1 = 0;
            }
        }
    }
    else if (index == "16"){
        maidenkiss++;
        if (maidenkiss > 99) maidenkiss = 99;
        if (BadEffect2 != 0){
                if (maidenkiss >= 1){
                    StatusCheck2 = 1;
                    StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
                    maidenkiss--;
                    BadEffect2 = 0;
                }
        }
    }
    else if (index == "17"){
        phoenixdown++;
        if (phoenixdown > 99) phoenixdown = 99;
    }
}

//THE MAIN PROCESS TO PROCEED ALL EVENT NUMBER ---------------------------------------------------------------------------------------------------------------------------------------------------------

void EventProcess(string event[], int size, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue, string mush_ghost, string asclepius_pack, string merlin_pack){
    int levelCheck = 0, maxHP = HP, BadEffect1 = 0, BadEffect2 = 0, StatusCheck1 = 0, StatusCheck2 = 0, levelSave = level, ShamanMeet = 0, VajshMeet = 0;
    for (int i = 0; i < size; i++){
        if (event[i] == "0"){
            rescue = 1;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            break;
        }
        if (event[i] == "1" || event[i] == "2" || event[i] == "3" || event[i] == "4" || event[i] == "5" || event[i] == "6" || event[i] == "7"){
            levelCheck = levelO(i + 1);
            if (level == levelCheck){
                if (event[i] == "1" || event[i] == "2" || event[i] == "3" || event[i] == "4" || event[i] == "5")
                {
                    if (LancelotCheck(maxHP)) level++;
                    else if (ArthurCheck(maxHP) == true) level++;
                }
                if (event[i] == "6" || event[i] == "7"){
                    if (ArthurCheck(maxHP) == true || LancelotCheck(maxHP) == true) level += 2;
                }
                StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2, ShamanMeet, VajshMeet);
                StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
            }
            else {
                Dungeon_Process(event[i], i + 1, level, HP, remedy, maidenkiss, phoenixdown, BadEffect1, BadEffect2, maxHP, levelSave, ShamanMeet, VajshMeet);
                if (HP <= 0) {
                    if (BadEffect1 != 0){
                        if (phoenixdown >= 1){
                            phoenixdown--;
                            BadEffect1 = 0;
                            StatusCheck1 = 1;
                            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
                        }
                        else {
                            rescue = 0;
                            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                            break;
                        }
                    }
                    else if (BadEffect2 != 0){
                        if (phoenixdown >= 1){
                            phoenixdown--;
                            BadEffect2 = 0;
                            StatusCheck2 = 1;
                            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
                        }
                        else {
                            rescue = 0;
                            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                            break;
                        }
                    }
                    else if (phoenixdown >= 1){
                        phoenixdown--;
                        HP = maxHP;
                    }
                    else{
                        rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;
                    }
                }

                StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2, ShamanMeet, VajshMeet);
                StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
            }
        }
        else if (event[i] == "99"){
            if (Bowser_Process(level, maxHP) == false){
                rescue = 0;
                break;
            }
            StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2, ShamanMeet, VajshMeet);
            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
        }
        else if (event[i] == "18"){
            Merlin_Process(merlin_pack, HP);
            if (HP > maxHP) HP = maxHP;
            StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2, ShamanMeet, VajshMeet);
            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
        }
        else if (event[i] == "19"){
            //cout << asclepius_pack << " ";
            Asclepius_Process(asclepius_pack, remedy, phoenixdown, maidenkiss);
            if (BadEffect1 != 0){
                if (remedy >= 1){
                    StatusCheck1 = 1;
                    StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
                    remedy--;
                    BadEffect1 = 0;
                }
            }
            if (BadEffect2 != 0){
                if (maidenkiss >= 1){
                    StatusCheck2 = 1;
                    StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
                    maidenkiss--;
                    BadEffect2 = 0;
                }
            }
        }
        else{
            PickingUpProcess(event[i], mush_ghost, asclepius_pack, merlin_pack, HP, level, remedy, maidenkiss, phoenixdown, rescue, maxHP, BadEffect1, BadEffect2, levelSave, StatusCheck1, StatusCheck2, ShamanMeet, VajshMeet);
            if (HP <= 0) {
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
            StatusCheck(event[i], BadEffect1, BadEffect2, StatusCheck1, StatusCheck2, ShamanMeet, VajshMeet);
            StatusDeadline(HP, level, StatusCheck1, StatusCheck2, levelSave, maxHP, ShamanMeet, VajshMeet);
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

//FINAL FUNCTION-----------------------------------------------------------------------------------------------------------------------

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
    string mush_ghost, asclepius_pack, merlin_pack;
    int CheckPositionComma1 = str3.find(',');
    int CheckPositionComma2 = str3.find(',', CheckPositionComma1 + 1);
    if (CheckPositionComma1 == 0) mush_ghost = "";
    else mush_ghost = str3.substr(0, CheckPositionComma1);
    if (CheckPositionComma2 == 0) merlin_pack = "";
    else merlin_pack = str3.substr(CheckPositionComma2 + 1, str3.size() -  CheckPositionComma2);
    if (CheckPositionComma2 - CheckPositionComma1 == 1) asclepius_pack = "";
    else asclepius_pack = str3.substr(CheckPositionComma1 + 1, CheckPositionComma2 - CheckPositionComma1 - 1);
    //Input Section ------------------------------------------------------------
    rescue = -1;
    EventProcess(event, EventElement, HP, level, remedy, maidenkiss, phoenixdown, rescue, mush_ghost, asclepius_pack, merlin_pack);
}