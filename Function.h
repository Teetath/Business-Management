#ifndef FUNCTION_H
#define FUNCTION_H

template<typename T>
bool tryParse(const std::string& input, T& result) {
    std::istringstream iss(input);
    iss >> std::noskipws >> result;
    return iss.eof() && !iss.fail();
}

string getCurrentTimestamp() {
    time_t now = time(0);
    char timestamp[100];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(timestamp);
}

char getch() {
    char buf = 0;
    termios old = {};
    if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr()");
    termios newt = old;
    newt.c_lflag &= ~ICANON; // ปิด canonical mode
    newt.c_lflag &= ~ECHO;   // ไม่ echo ตัวอักษรออกจอ
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0) perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0) perror("read()");
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
}

bool check() {
    if (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }else{
        return true;
    }
}

void Pause() {
    cout << "\033[1;32mPress any key to continue...\033[0m\n";
    getch();
}

bool isValidID(const string& id) {
    for (char ch : id) {
        if (!isalnum(ch)) return false;

        // ตรวจสอบ Unicode ของภาษาไทย (ประมาณช่วง U+0E00 ถึง U+0E7F)
        if ((unsigned char)ch >= 0xE0) return false;
    }
    return true;
}

bool isValidName(const string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') return false;

        if ((unsigned char)ch >= 0xE0) return false;
    }
    return true;
}

string getTargetYearInput() {
    string year;
    while (true) {
        cout << "\033[1;34m📅 Enter year (YYYY) (leave blank to cancel): \033[0m";
        getline(cin, year);
        if (year.empty() || all_of(year.begin(), year.end(), ::isspace)) {
            cout << "\033[1;33m⚠️  Input cancelled.\033[0m\n";
            return "";
        }
        if (year.size() == 4 && all_of(year.begin(), year.end(), ::isdigit)) {
            return year;
        }
        cout << "\033[1;31m❌ Invalid year. Please enter a 4-digit year.\033[0m\n";
    }
}

string getTargetMonthInput() {
    string year = getTargetYearInput();
    if (year.empty()) return "";

    string month;
    while (true) {
        cout << "\033[1;34m📅 Enter month (MM) (leave blank to cancel): \033[0m";
        getline(cin, month);
        if (month.empty() || all_of(month.begin(), month.end(), ::isspace)) {
            cout << "\033[1;33m⚠️  Input cancelled.\033[0m\n";
            return "";
        }
        if (all_of(month.begin(), month.end(), ::isdigit) && (month.size() == 1 || month.size() == 2)) {
            int m = stoi(month);
            if (m >= 1 && m <= 12) {
                if (m < 10) month = "0" + to_string(m);
                return year + "-" + month;
            }
        }
        cout << "\033[1;31m❌ Invalid month. Must be 01 - 12.\033[0m\n";
    }
}

#endif
