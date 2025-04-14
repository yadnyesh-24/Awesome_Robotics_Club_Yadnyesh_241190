#include <bits/stdc++.h>
using namespace std;

struct position {
    int x, y;
    position(int x, int y) : x(x), y(y) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> matrix;
    vector<vector<bool>> visited;
    string line;
    position start(0, 0); // Initialize start position
    position end(0, 0); // Initialize end position
    while (getline(cin, line)) {
        if (line.empty()) break; // Stop input on an empty line
        vector<int> row;
        vector<bool> visitedRow; // Initialize visited row
        for (char ch : line) {
            if (ch == ' ') continue; // Skip spaces
            // row.push_back(ch); // Store each character in the row
            if(ch=='S'||ch=='G'){
                row.push_back(0); // Convert 'S' to '0'}
            }
            else if(ch=='.'){
                row.push_back(1); 
            }
            else if(ch=='#'){
                row.push_back(9); 
            }
            else if(ch=='~'){
                row.push_back(3);
            }
            else if(ch=='^'){
                row.push_back(5);
            };
            if(ch=='#'){
                visitedRow.push_back(true);
            }
            else{
                visitedRow.push_back(false);
            };

            if(ch=='S'){
                start.x=matrix.size(); // Store the starting position
                start.y=row.size()-1;
            }
            if(ch=='G'){
                end.x=matrix.size(); // Store the ending position
                end.y=row.size()-1;
            }
        }
        matrix.push_back(row);
        visited.push_back(visitedRow); // Store the visited row

    }

    // Output the matrix to verify input
    for (const auto& row : matrix) {
        for (int ch : row) {
            cout << ch<<' ';
        }
        cout << '\n';
    }

    cout<<"The matrix element [0][0] is : "<<matrix[0][0]<<endl;
    cout<<"The matrix element [0][1] is : "<<matrix[0][1]<<endl;

    // for (const auto& row : visited) {
    //     for (char ch : row) {
    //         cout << ch<<' ';
    //     }
    //     cout << '\n';
    // }

    cout<<"start position: "<<start.x<<' '<<start.y<<endl;
    cout<<"end position: "<<end.x<<' '<<end.y<<endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Direction vectors (up, down, left, right)
vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int rows = matrix.size();
int cols = matrix[0].size();

// Distance grid
vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));
distance[start.x][start.y] = 0;

// Min-heap: (cost, position)
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
pq.push({0, start.x, start.y});

while (!pq.empty()) {
    auto [cost, x, y] = pq.top();
    pq.pop();

    if (visited[x][y]) continue;
    visited[x][y] = true;

    if (x == end.x && y == end.y) {
        cout << "Reached the goal! Minimum cost: " << cost << '\n';
        break;
    }

    for (auto [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
            int newCost = cost + matrix[nx][ny];
            if (newCost < distance[nx][ny]) {
                distance[nx][ny] = newCost;
                pq.push({newCost, nx, ny});
            }
        }
    }
}

if (distance[end.x][end.y] == INT_MAX) {
    cout << "Goal not reachable.\n";
}

    return 0;
}