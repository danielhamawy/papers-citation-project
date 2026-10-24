#include <bits/stdc++.h>
using namespace std;

static void trim(string& s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) s.pop_back();
    size_t i = 0;
    while (i < s.size() && s[i] == ' ') i++;
    s.erase(0, i);
}

int main() {
    unordered_map<int, string> names;
    {
        ifstream in("nodes.csv");
        if (!in) { cerr << "Could not open the file\n"; return 1; }
        string line;
        while (getline(in, line)) {
            size_t c = line.find(',');
            if (c == string::npos) continue;
            int id;
            try { id = stoi(line.substr(0, c)); } catch (...) { continue; } 
            string title = line.substr(c + 1);
            trim(title);
            if (title.size() >= 2 && title.front() == '"' && title.back() == '"')
                title = title.substr(1, title.size() - 2);
            names[id] = title;
        }
    }

    unordered_map<int, int> cites;
    {
        ifstream in("edges.csv");
        if (!in) { cerr << "Could not open the file\n"; return 1; }
        string line;
        while (getline(in, line)) {
            size_t c = line.find(',');
            if (c == string::npos) continue;
            int cited;
            try { cited = stoi(line.substr(c + 1)); } catch (...) { continue; } // skips header
            cites[cited]++;
        }
    }

    vector<pair<int, int>> items;
    items.reserve(cites.size());
    for (auto& [id, cnt] : cites) items.push_back({cnt, id});
    priority_queue<pair<int, int>> pq(less<pair<int, int>>(), move(items));

    cout << "Press Enter for the next most cited paper, or type q to quit.\n";
    string cmd;
    while (!pq.empty()) {
        getline(cin, cmd);
        if (cmd == "q") break;
        auto [cnt, id] = pq.top();
        pq.pop();
        cout << cnt << " citations | id " << id << " | "
             << (names.count(id) ? names[id] : "(title not found)") << "\n";
    }
}