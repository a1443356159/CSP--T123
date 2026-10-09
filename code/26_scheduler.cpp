#include <bits/stdc++.h>
using namespace std;
struct Task { long long arrival, priority, duration; int id; };
struct Compare {
    bool operator()(const Task &a, const Task &b) const {
        if (a.priority != b.priority) return a.priority < b.priority;
        if (a.arrival != b.arrival) return a.arrival > b.arrival;
        return a.id > b.id;
    }
};
int main() {
    int n; cin >> n; vector<Task> tasks(n);
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].arrival >> tasks[i].priority >> tasks[i].duration;
        tasks[i].id = i;
    }
    sort(tasks.begin(), tasks.end(), [](auto a, auto b) {
        return tie(a.arrival,a.id) < tie(b.arrival,b.id);
    });
    priority_queue<Task,vector<Task>,Compare> ready;
    vector<pair<long long,long long>> answer(n);
    long long now = 0, maxWait = 0; int i = 0;
    while (i < n || !ready.empty()) {
        if (ready.empty()) now = max(now, tasks[i].arrival);
        while (i < n && tasks[i].arrival <= now) ready.push(tasks[i++]);
        Task t = ready.top(); ready.pop();
        answer[t.id] = {now, now+t.duration};
        maxWait = max(maxWait, now-t.arrival); now += t.duration;
    }
    for (auto [start,finish] : answer) cout << start << ' ' << finish << '\n';
    cout << maxWait << '\n';
}
