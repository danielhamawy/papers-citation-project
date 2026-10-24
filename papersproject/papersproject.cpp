#include <bits/stdc++.h>
using namespace std;

static void trim(string& s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) s.pop_back();
    size_t i = 0;
    while (i < s.size() && s[i] == ' ') i++;
    s.erase(0, i);
}

int main() {
    auto t0 = chrono::steady_clock::now();
    auto lap = [&](const string& label) {
        auto t1 = chrono::steady_clock::now();
        cout << label << ": " << chrono::duration<double, milli>(t1 - t0).count() << " ms\n";
        t0 = t1;
    };

    unordered_map<int, string> names;
    {
        ifstream in("nodes.csv");
        if (!in) { cerr << "Could not open nodes.csv\n"; return 1; }
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
    lap("Load titles");

    unordered_map<int, int> cites;
    unordered_map<int, vector<int>> out, citedBy;   // paper -> papers it cites; paper -> papers citing it
    {
        ifstream in("edges.csv");
        if (!in) { cerr << "Could not open edges.csv\n"; return 1; }
        string line;
        while (getline(in, line)) {
            size_t c = line.find(',');
            if (c == string::npos) continue;
            int a, b;
            try { a = stoi(line.substr(0, c)); b = stoi(line.substr(c + 1)); } catch (...) { continue; }
            cites[b]++;
            out[a].push_back(b);
            citedBy[b].push_back(a);
        }
    }
    lap("Count citations");

    vector<pair<int, int>> items;
    items.reserve(cites.size());
    for (auto& [id, cnt] : cites) items.push_back({cnt, id});
    priority_queue<pair<int, int>> pq(less<pair<int, int>>(), move(items));
    lap("Build heap");

    {
        auto pqCopy = pq;
        auto s = chrono::steady_clock::now();
        int pops = min<size_t>(1000, pqCopy.size());
        for (int i = 0; i < pops; i++) pqCopy.pop();
        double ms = chrono::duration<double, milli>(chrono::steady_clock::now() - s).count();
        cout << "Avg extract-max: " << ms / pops << " ms\n";
    }

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

    // Bonus: closest papers by shared citations
    unordered_map<string, int> byTitle;
    for (auto& [id, t] : names) byTitle[t] = id;

    const int THRESHOLD = 2;
    cout << "\nBonus: enter a paper id or exact title (q to quit): ";
    while (getline(cin, cmd) && cmd != "q") {
        trim(cmd);
        int p = -1;
        if (byTitle.count(cmd)) p = byTitle[cmd];
        else { try { p = stoi(cmd); } catch (...) {} }
        if (!names.count(p)) { cout << "Paper not found\n> "; continue; }

        unordered_map<int, int> shared;
        for (int c : out[p])
            for (int q : citedBy[c])
                if (q != p) shared[q]++;

        vector<pair<int, int>> res;
        for (auto& [q, n] : shared) if (n >= THRESHOLD) res.push_back({n, q});
        sort(res.rbegin(), res.rend());

        cout << res.size() << " closest papers (sharing at least " << THRESHOLD << " citations):\n";
        for (auto& [n, q] : res) cout << n << " shared | id " << q << " | " << names[q] << "\n";
        cout << "> ";
    }
}