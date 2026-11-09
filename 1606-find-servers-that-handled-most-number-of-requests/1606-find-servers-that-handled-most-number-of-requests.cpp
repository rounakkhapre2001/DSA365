class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> available;
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> busy;

        vector<int> count(k, 0);

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        for (int i = 0; i < arrival.size(); i++) {

            // Release servers whose requests are completed.
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) {
                continue;
            }

            // Find the next available server starting from i % k.
            int target = i % k;
            auto it = available.lower_bound(target);

            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;
            available.erase(it);

            count[server]++;

            // Mark server as busy.
            busy.push({arrival[i] + load[i], server});
        }

        // Find maximum handled requests.
        int mx = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == mx) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};