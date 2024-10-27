#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    struct Node {
        int children[2];
        int fail;
        bool output;
        Node() : fail(0), output(false) {
            children[0] = -1;
            children[1] = -1;
        }
    };

    vector<Node> trie;

    AhoCorasick() {
        trie.emplace_back();
    }

    void insert(const vector<int>& pattern) {
        int node = 0;
        for(auto bit : pattern){
            if(trie[node].children[bit] == -1){
                trie[node].children[bit] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].children[bit];
        }
        trie[node].output = true;
    }

    void build() {
        queue<int> q;
        for(int bit=0; bit<2; bit++){
            int child = trie[0].children[bit];
            if(child != -1){
                trie[child].fail = 0;
                q.push(child);
            }
            else{
                trie[0].children[bit] = 0;
            }
        }

        while(!q.empty()){
            int current = q.front(); q.pop();
            for(int bit=0; bit<2; bit++){
                int child = trie[current].children[bit];
                if(child != -1){
                    int fail = trie[current].fail;
                    while(trie[fail].children[bit] == -1 && fail != 0){
                        fail = trie[fail].fail;
                    }
                    if(trie[fail].children[bit] != -1){
                        fail = trie[fail].children[bit];
                    }
                    trie[child].fail = fail;
                    trie[child].output = trie[child].output || trie[fail].output;
                    q.push(child);
                }
                else{
                    trie[current].children[bit] = trie[trie[current].fail].children[bit];
                }
            }
        }
    }
};

struct ReplacementRules {
    unordered_map<int, vector<vector<int>>> rules;

    void add_rule(int x, const vector<int>& replacement){
        rules[x].emplace_back(replacement);
    }
};

struct BFSState {
    int automaton_state;
    vector<int> queue;
    long long length;

    BFSState(int state, const vector<int>& q, long long l) : automaton_state(state), queue(q), length(l) {}
};

struct IOManager {
    int Z, n, m;
    ReplacementRules replacement_rules;
    vector<vector<int>> forbidden_sequences;

    void read_input(){
        ios::sync_with_stdio(false);
        cin.tie(0); cout.tie(0);
        cin >> Z >> n >> m;
        for(int i=0; i<n; i++){
            int x, k;
            cin >> x >> k;
            vector<int> replacement(k);
            for(auto &num : replacement) cin >> num;
            replacement_rules.add_rule(x, replacement);
        }
        for(int i=0; i<m; i++){
            int k;
            cin >> k;
            vector<int> seq(k);
            for(auto &bit : seq) cin >> bit;
            forbidden_sequences.emplace_back(seq);
        }
    }

    void write_output(const vector<long long>& results){
        for(auto res : results){
            cout << res << "\n";
        }
    }
};

int main(){
    IOManager io;
    io.read_input();

    AhoCorasick automaton;
    for(auto &pattern : io.forbidden_sequences){
        automaton.insert(pattern);
    }
    automaton.build();

    ReplacementRules& rules = io.replacement_rules;

    int start_a_min = 2;
    int start_a_max = io.Z -1;
    int total_a = start_a_max - start_a_min +1;
    vector<long long> results;

    for(int a = start_a_min; a <= start_a_max; a++){
        queue<BFSState> q;
        q.emplace(0, vector<int>{a}, 0);

        unordered_map<int, unordered_set<string>> visited;
        auto serialize_queue = [&](const vector<int>& q_vec) -> string{
            string s = "";
            for(auto num : q_vec){
                s += to_string(num) + ",";
            }
            return s;
        };
        visited[0].insert(serialize_queue(vector<int>{a}));

        bool found = false;
        long long answer = 0;

        while(!q.empty()){
            BFSState current = q.front(); q.pop();

            if(current.queue.empty()){
                answer = current.length;
                found = true;
                break;
            }

            int symbol = current.queue[0];
            vector<int> remaining_queue(current.queue.begin()+1, current.queue.end());

            if(symbol ==0 || symbol ==1){
                int automaton_state = current.automaton_state;
                automaton_state = automaton.trie[automaton_state].children[symbol];
                if(automaton.trie[automaton_state].output){
                    continue;
                }
                long long new_length = current.length +1;
                if(remaining_queue.empty()){
                    answer = new_length;
                    found = true;
                    break;
                }
                string serialized = serialize_queue(remaining_queue);
                if(visited[automaton_state].find(serialized) == visited[automaton_state].end()){
                    visited[automaton_state].insert(serialized);
                    q.emplace(automaton_state, remaining_queue, new_length);
                }
            }
            else{
                if(rules.rules.find(symbol) == rules.rules.end()){
                    continue;
                }
                for(auto &replacement : rules.rules[symbol]){
                    vector<int> new_queue = replacement;
                    new_queue.insert(new_queue.end(), remaining_queue.begin(), remaining_queue.end());
                    string serialized = serialize_queue(new_queue);
                    if(visited[current.automaton_state].find(serialized) == visited[current.automaton_state].end()){
                        visited[current.automaton_state].insert(serialized);
                        q.emplace(current.automaton_state, new_queue, current.length);
                    }
                }
            }
        }

        if(found){
            results.emplace_back(answer);
        }
        else{
            results.emplace_back(0);
        }
    }

    io.write_output(results);
}
