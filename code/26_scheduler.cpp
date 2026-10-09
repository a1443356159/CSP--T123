#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int N = 200005;
struct Task { long long arrival, priority, duration; int id; };
Task tasks[N];
long long start_time[N], finish_time[N];
bool by_arrival(Task a, Task b) {
    if (a.arrival != b.arrival) return a.arrival < b.arrival;
    return a.id < b.id;
}
bool lower_priority(Task a, Task b) {
    if (a.priority != b.priority) return a.priority < b.priority;
    if (a.arrival != b.arrival) return a.arrival > b.arrival;
    return a.id > b.id;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld%lld%lld", &tasks[i].arrival,
              &tasks[i].priority, &tasks[i].duration);
        tasks[i].id = i;
    }
    sort(tasks, tasks + n, by_arrival);
    typedef bool (*Compare)(Task, Task);
    priority_queue<Task, vector<Task>, Compare> ready(lower_priority);
    long long now = 0, max_wait = 0;
    int i = 0;
    while (i < n || !ready.empty()) {
        if (ready.empty()) now = max(now, tasks[i].arrival);
        while (i < n && tasks[i].arrival <= now) ready.push(tasks[i++]);
        Task t = ready.top(); ready.pop();
        start_time[t.id] = now; finish_time[t.id] = now + t.duration;
        max_wait = max(max_wait, now - t.arrival);
        now += t.duration;
    }
    for (int j = 0; j < n; j++)
        printf("%lld %lld\n", start_time[j], finish_time[j]);
    printf("%lld\n", max_wait);
    return 0;
}
