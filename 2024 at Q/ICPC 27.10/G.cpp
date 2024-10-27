#include <bits/stdc++.h>
using namespace std;

struct Span {
    int start;
    int end;
};

struct IOManager {
    int n;
    string s;

    void read_input(){
        ios::sync_with_stdio(false);
        cin.tie(0); cout.tie(0);
        cin >> n;
        cin >> s;
    }

    void write_output(int res){
        cout << res;
    }
};

struct Matrix {
    int n;
    string s;
    vector<int> suffix_zeros;

    Matrix(int size, const string& str) : n(size), s(str), suffix_zeros(size +1,0){
        for(int i=n-1; i>=0; i--){
            if(s[i] == '0'){
                suffix_zeros[i] = suffix_zeros[i+1] +1;
            }
            else{
                suffix_zeros[i] = suffix_zeros[i+1];
            }
        }
    }

    int get_max_length(){
        vector<int> ones_pos;
        for(int i=0; i<n; i++) {
            if(s[i] == '1'){
                ones_pos.push_back(i);
            }
        }

        int total_ones = ones_pos.size();

        int prev_one = -1;
        vector<Span> spans;
        for(auto &i : ones_pos){
            int left_zeros = i - prev_one -1;
            int right_zeros = suffix_zeros[i +1];
            int k_i = min(left_zeros, right_zeros);
            int start = max(0, i -k_i);
            int end = min(n-1, i +k_i);
            spans.push_back(Span{start, end});
            prev_one = i;
        }

        sort(spans.begin(), spans.end(), [&](const Span&a, const Span&b)->bool{
            if(a.start != b.start) return a.start < b.start;
            return a.end < b.end;
        });

        vector<Span> merged_spans;
        if(!spans.empty()){
            Span current = spans[0];
            for(int i=1; i<spans.size();i++){
                if(spans[i].start <= current.end +1){
                    current.end = max(current.end, spans[i].end);
                }
                else{
                    merged_spans.push_back(current);
                    current = spans[i];
                }
            }
            merged_spans.push_back(current);
        }

        int max_length =0;
        for(auto &span : merged_spans){
            int len = span.end - span.start +1;
            if(len > max_length){
                max_length = len;
            }
        }

        return max_length;
    }
};

int main(){
    IOManager io;
    io.read_input();
    Matrix matrix(io.n, io.s);
    int max_length = matrix.get_max_length();
    io.write_output(max_length);
}
