#ifndef FUNCTION_H
#define FUNCTION_H

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

#endif
