#include <bits/stdc++.h>
using namespace std;

struct Student {
    string id;
    string name;
    int score;
    int idx; // insertion order
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Student> students;
    unordered_map<string, int> id_index; // id -> index in students
    unordered_map<string, int> name_index; // name -> index in students (queries guaranteed to exist)
    id_index.reserve(16384);
    name_index.reserve(16384);

    string line;
    while (true) {
        if (!getline(cin, line)) break;
        if (line.empty()) continue; // skip empty lines if any
        istringstream iss(line);
        int cmd;
        if (!(iss >> cmd)) continue;
        if (cmd == 1) {
            string id, name; int score;
            if (!(iss >> id >> name >> score)) continue; // invalid line, ignore
            if (id_index.find(id) != id_index.end()) {
                cout << "FAILED\n";
                continue;
            }
            Student s{ id, name, score, (int)students.size() };
            id_index[id] = (int)students.size();
            name_index[name] = (int)students.size();
            students.push_back(std::move(s));
            cout << "SUCCESS\n";
        } else if (cmd == 2) {
            if (!students.empty()) {
                for (const auto &s : students) {
                    cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
                }
            }
        } else if (cmd == 3) {
            string id; iss >> id;
            const auto it = id_index.find(id);
            if (it != id_index.end()) {
                const Student &s = students[it->second];
                cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
            }
        } else if (cmd == 4) {
            string name; iss >> name;
            const auto it = name_index.find(name);
            if (it != name_index.end()) {
                const Student &s = students[it->second];
                cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
            }
        } else if (cmd == 5) {
            if (!students.empty()) {
                vector<int> idx(students.size());
                iota(idx.begin(), idx.end(), 0);
                stable_sort(idx.begin(), idx.end(), [&](int a, int b){
                    // ascending by id (as string numeric, but ids are fixed 9-digit, string compare equals numeric)
                    return students[a].id < students[b].id;
                });
                for (int i : idx) {
                    const auto &s = students[i];
                    cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
                }
            }
        } else if (cmd == 6) {
            if (!students.empty()) {
                vector<int> idx(students.size());
                iota(idx.begin(), idx.end(), 0);
                stable_sort(idx.begin(), idx.end(), [&](int a, int b){
                    // score descending; ties keep insertion order due to stable_sort with key (score desc)
                    if (students[a].score != students[b].score) return students[a].score > students[b].score;
                    return false; // keep original order
                });
                for (int i : idx) {
                    const auto &s = students[i];
                    cout << s.id << ' ' << s.name << ' ' << s.score << '\n';
                }
            }
        } else if (cmd == 7) {
            cout << "END\n";
            break;
        }
    }
    return 0;
}
